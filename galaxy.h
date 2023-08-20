#include <iostream>
#include <vector>
#include <limits.h>
#include "node.h"

using namespace std;

#ifndef GALAXY_H
#define GALAXY_H

class galaxy : public node
{
public:
    bool set_new_node(string, string, string, string); // set name & id & type
    string get_galaxy_name();                          // return galaxy name
    bool set_adjacecy_costs(int, int, int);            // set way cost
    bool set_galaxy_name(string);
    int find_node_andis(string); // find node andis with node name
    void show_adjacency();       // show adjacency matrix
    void show_nodes();
    void dijkstra(int, int);          // find shortest way between two nodes with disktra algorithm
    void printParentPath(int *, int); // show the path between two nodes
    void check_isolted_node();        // check to recognize isolted node with dijkstra algorithm

private:
    vector<node> points;                // save  galaxies nodes info
    vector<vector<int>> adjacency{{0}}; // save adjacency matrix
    string galaxy_name;
};
#endif

void galaxy ::check_isolted_node()
{
    int source = 1; // defualt origin to start
    int distance[points.size()];
    bool visited[points.size()];
    int parent[points.size()];
    for (int i = 0; i < points.size(); i++)
    {
        parent[i] = -1;
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    distance[source] = 0;
    for (int i = 0; i < points.size() - 1; i++)
    {
        int min = INT_MAX;
        int min_index = INT_MAX;
        for (int i = 0; i < points.size(); i++)
        {
            if (!visited[i] && distance[i] <= min)
            {
                min = distance[i];
                min_index = i;
            }
        }

        visited[min_index] = true;
        for (int j = 0; j < points.size(); j++)
        {
            int curr_distance = distance[min_index] + adjacency[min_index][j];
            if (!visited[j] && adjacency[min_index][j] && curr_distance < distance[j])
            {
                parent[j] = min_index;
                distance[j] = curr_distance;
            }
        }
    }
    for (size_t i = 1; i < points.size(); i++)
    {
        if (distance[i] == INT_MAX) // when the node is isolted, way cost is INT_MAX
        {
            cout << "there is no way  from (" << points[0].get_node_name() << ") to (" << points[i - 1].get_node_name() << ") please enter way cost !!" << endl;
        }
    }
}

void galaxy ::printParentPath(int parent[], int i) // recursive function to show path
{
    if (parent[i] == -1)
    {
        cout << points[(i)].get_node_name();
        return;
    }
    printParentPath(parent, parent[i]);
    cout << "->" << points[(i)].get_node_name();
}

void galaxy ::dijkstra(int source, int destination)
{
    int distance[points.size()]; // save shortest way cost
    bool visited[points.size()]; // avoid repetition visit one node
    int parent[points.size()];   // save pre node index in way
    for (int i = 0; i < points.size(); i++)
    {
        parent[i] = -1;
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    distance[source] = 0; // to find the source node
    for (int i = 0; i < points.size() - 1; i++)
    {
        int min = INT_MAX;
        int min_index = INT_MAX;
        for (int j = 0; j < points.size(); j++) // find min way cost
        {
            if (!visited[j] && distance[j] <= min)
            {
                min = distance[j];
                min_index = j;
            }
        }
        visited[min_index] = true;
        for (int j = 0; j < points.size(); j++) // to find the way with less cost
        {
            int curr_distance = distance[min_index] + adjacency[min_index][j];

            if (!visited[j] && adjacency[min_index][j] && curr_distance < distance[j])
            {
                parent[j] = min_index;
                distance[j] = curr_distance;
            }
        }
        if (visited[destination])
        {
            break;
        }
    }
    if (distance[destination] != INT_MAX) // checking to be a way
    {

        cout << "Vertex\t\tDistance\tPath" << endl;
        cout << points[source].get_node_name() << "->" << points[destination].get_node_name() << "\t\t" << distance[destination] << "\t\t";
        printParentPath(parent, destination);
        cout << endl;
    }
    else
    {
        cout << "there is no way from (" << points[source].get_node_name() << ") to (" << points[destination].get_node_name() << ") !! \nplease set cost!" << endl;
    }
}

void galaxy ::show_nodes()
{
    cout << endl;
    cout << "number of nodes = " << points.size() << endl;
    for (size_t i = 0; i < points.size(); i++)
    {
        cout << points[i].get_node_name() << "  ";
    }
    cout << endl;
}

void galaxy ::show_adjacency()
{
    for (size_t i = 0; i < adjacency.size() - 1; i++)
    {
        for (size_t j = 0; j < adjacency[i].size() - 1; j++)
        {
            cout << adjacency[i][j] << " ";
        }
        cout << endl;
    }
}

string galaxy::get_galaxy_name()
{
    return galaxy_name;
}

bool galaxy ::set_new_node(string as, string node_name, string id, string type)
{
    for (size_t i = 0; i < points.size(); i++) // check  for avoiding  create node by same name
    {
        if (node_name == (points[i].get_node_name()))
        {
            cout << "there is one node with same name !!!" << endl;
            return false;
        }
    }
    if (type != "BG" && type != "NON-BG")
    {
        cout << "wrong type !!" << endl;
        return false;
    }

    points.push_back(node()); // add a new node
    points[points.size() - 1].set_node_name(node_name);
    points[points.size() - 1].set_id(id);
    points[points.size() - 1].set_type(type);
    points[points.size() - 1].set_galaxy_name(as);

    adjacency.push_back(adjacency[0]); // add row to adjacency matrix
    for (size_t j = 0; j < adjacency[adjacency.size() - 1].size(); j++)
    {
        adjacency[adjacency.size() - 1][j] = 0;
    }
    for (size_t i = 0; i < adjacency.size(); i++) // add col to adjacency matrix
    {
        adjacency[i].push_back(0);
    }
    return true;
}
bool galaxy ::set_adjacecy_costs(int row, int col, int cost1)
{
    if (cost1 < 0)
    {
        cout << "cost have to be postive !!" << endl;
        return false;
    }
    adjacency[row][col] = cost1;
    adjacency[col][row] = cost1;
    return true;
}
bool galaxy ::set_galaxy_name(string g2)
{
    galaxy_name = g2;
    return true;
}

int galaxy ::find_node_andis(string node_name)
{
    for (size_t i = 0; i < points.size(); i++)
    {
        if (node_name == points[i].get_node_name())
        {
            return i;
        }
    }
    return (-1);
}

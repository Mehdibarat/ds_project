#include <iostream>
#include "galaxy.h"
#include <vector>

using namespace std;

#ifndef UNIVERSE_H
#define UNIVERSE_H

class universe
{
public:
    vector<galaxy> AS;                                       // save galaxies of universe
    bool set_galaxy_or_node(string, string, string, string); // add galaxy or new node to galaxy
    int find_galaxy_andis(string);
    bool set_BG_point(string, string, string, string); // node_name  galaxy node_id node_type
    void show_BG_nodes();
    void show_intergalactic_adjacency();                                        // show adjacency matrix for intergalactic nodes
    bool set_intergalactic_adjacency_cost(string, string, string, string, int); // set cost

private:
    vector<node> BG_points;                           // save  intergalactic nodes info
    vector<vector<int>> intergalactic_adjacency{{0}}; // save adjacency matrix
};

#endif

bool universe ::set_intergalactic_adjacency_cost(string node_name1, string as1, string node_name2, string as2, int cost)
{
    int node_andis1 = -1;
    int node_andis2 = -1;

    for (size_t i = 0; i < BG_points.size(); i++) // to find nodes
    {
        if (node_name1 == BG_points[i].get_node_name() && as1 == BG_points[i].get_galaxy_name())
        {
            node_andis1 = i;
            break;
        }
    }
    for (size_t i = 0; i < BG_points.size(); i++)
    {
        if (node_name2 == BG_points[i].get_node_name() && as2 == BG_points[i].get_galaxy_name())
        {
            node_andis2 = i;
            break;
        }
    }
    if (node_andis1 == (-1)) // check for vaild index
    {
        cout << "node (" << node_name1 << ") not founded as BG node !!!" << endl;
        return false;
    }
    if (node_andis2 == (-1)) // check for valid index
    {
        cout << "node (" << node_name2 << ") not founded as BG node !!!" << endl;
        return false;
    }

    if (cost < 0) // check for valid cose
    {
        cout << "cost have to be postive" << endl;
    }

    intergalactic_adjacency[node_andis1][node_andis2] = cost;
    intergalactic_adjacency[node_andis2][node_andis1] = cost;
    return true;
}

void universe ::show_intergalactic_adjacency()
{
    cout << "intergalactic_adjacency " << endl;
    for (size_t i = 0; i < intergalactic_adjacency.size() - 1; i++)
    {
        for (size_t j = 0; j < intergalactic_adjacency[i].size() - 1; j++)
        {
            cout << intergalactic_adjacency[i][j] << " ";
        }
        cout << endl;
    }
}
void universe ::show_BG_nodes()
{
    cout << "BG_point size = " << BG_points.size() << endl;
    for (size_t i = 0; i < BG_points.size(); i++)
    {
        cout << BG_points[i].get_node_name() << "  ";
    }
    cout << endl;
}
bool universe ::set_BG_point(string node_name, string as, string id, string type) // node_name galaxy  node_id node_type
{
    BG_points.push_back(node()); // add a new node
    BG_points[BG_points.size() - 1].set_node_name(node_name);

    BG_points[BG_points.size() - 1].set_id(id);

    BG_points[BG_points.size() - 1].set_type(type);

    BG_points[BG_points.size() - 1].set_galaxy_name(as);

    intergalactic_adjacency.push_back(intergalactic_adjacency[0]); // add row to matrix
    for (size_t j = 0; j < intergalactic_adjacency[intergalactic_adjacency.size() - 1].size(); j++)
    {
        intergalactic_adjacency[intergalactic_adjacency.size() - 1][j] = 0;
    }
    for (size_t i = 0; i < intergalactic_adjacency.size(); i++) // add col to matrix
    {
        intergalactic_adjacency[i].push_back(0);
    }
    return true;
}
bool universe ::set_galaxy_or_node(string node_name, string as, string id, string type) // node_name galaxy_name node_id node_type
{
    for (size_t i = 0; i < AS.size(); i++) // to find existed galaxy
    {
        if (as == (AS[i].get_galaxy_name()))
        {
            if (!(AS[i].set_new_node(as, node_name, id, type)))
            {
                return false;
            }
            if (type == "BG")
            {
                set_BG_point(node_name, as, id, type);
            }
            return true;
        }
    }

    AS.push_back(galaxy()); // add a new galaxy
    AS[AS.size() - 1].set_galaxy_name(as);

    if (!(AS[AS.size() - 1].set_new_node(as, node_name, id, type)))
    {
        return false;
    }

    if (type == "BG")
    {
        set_BG_point(node_name, as, id, type);
    }
    return true;
}

int universe ::find_galaxy_andis(string as) // get galaxy name then return its andis
{
    for (size_t i = 0; i < AS.size(); i++)
    {
        if (as == AS[i].get_galaxy_name())
        {
            return i;
        }
    }
    return (-1);
}
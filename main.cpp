#include <iterator>
#include <string>
#include <vector>
#include <string>
#include <iostream>
#include "universe.h"

using namespace std;

bool set_cost(universe &, string, string, string, string, int); // for set way cost
bool input_processing(universe &, string);                      // define and handle the inputs
bool find_way(universe &, string, string, string, string);      // for find shortest way

int main()
{
    universe world; // anobject for universe
    string inp;     // input

    system("cls");
    cout << "guide:" << endl; // guidline
    cout << "CREATE (node_name: Node, {id: 'node_id', Type: 'node_type', galaxy: 'node_galaxy'})" << endl;
    cout << "CREATE (node_name) - [:ROAD {cost:way_cost}] -> (destination_node_name)            " << endl;
    cout << "FIND galaxy_name.node_name->galaxy_name.node_name                                  " << endl;
    cout << "type (exit) for close " << endl;
    cout << "enter the command : " << endl;

    getline(cin, inp);
    system("cls");

    while (inp != "exit") // for saty or leave app
    {
        input_processing(world, inp);
        cout << "press enter ";
        getchar();
        system("cls");

        cout << "guide:" << endl;
        cout << "CREATE (node_name: Node, {id: 'node_id', Type: 'node_type', galaxy: 'node_galaxy'})" << endl;
        cout << "CREATE (node_name.galaxy_name) - [:ROAD {cost:way_cost}] -> (node_name.galaxy_name)            " << endl;
        cout << "FIND galaxy_name.node_name->galaxy_name.node_name                                  " << endl;
        cout << "type (exit) for close " << endl;
        cout << "enter the command : " << endl;

        getline(cin, inp);
        system("cls");
    }

    for (size_t i = 0; i < world.AS.size(); i++) // show all of galaxies with thire nodes and way cost
    {
        cout << "    " << world.AS[i].get_galaxy_name() << endl;
        cout << " adjacency : " << endl;
        world.AS[i].show_adjacency();
        cout << "galaxy nodes : ";
        world.AS[i].show_nodes();
        world.AS[i].check_isolted_node();
    }

    world.show_intergalactic_adjacency(); // show intergalactic way cost
    world.show_BG_nodes();                // show BG points

    return 0;
}

bool input_processing(universe &world, string input)
{
    string node_name1;   // node name1
    string node_name2;   // node name2
    string node_galaxy1; // galaxy of node1
    string node_galaxy2; // galaxy of node2
    string node_id1;     // id of node1
    string node_type1;   // type of node1
    string cost_temp;    // for separate cost from input then change to integer
    string command_type; // for separating FIND commands from CREATE commands

    int hyphen_counter = 0;           // for counting "-"
    int space_counter = 0;            // for counting " "
    int point_counter = 0;            // for counting "."
    int cost = 0;                     // for save cost as integer
    int braces_counter = 0;           // for counting "{}"
    int node_counter = 0;             // in FIND used for separating node1 from node2
    int greater_than_counter = 0;     // for counting">"
    int parentheses_counter = 0;      // for counting "("
    int colon_counter = 0;            // for counting ":"
    int single_quotation_counter = 0; // for counting " ' "

    for (size_t i = 0; i < input.size(); i++)
    {
        if (input[i] == ' ')
        {
            break;
        }
        command_type += input[i];
    }
    if (command_type == "CREATE")
    {
        for (size_t j = 0; j < input.size(); j++)
        {
            if (input[j] == '>')
            {
                greater_than_counter++;
            }
        }
        if (greater_than_counter == 0)
        {
            for (size_t i = 0; i < input.size(); i++)
            {
                if (input[i] == '(')
                {
                    parentheses_counter++;
                    continue;
                }
                if (input[i] == ':')
                {
                    colon_counter++;
                    continue;
                }
                if (input[i] == '\'')
                {
                    single_quotation_counter++;
                    continue;
                }

                if (colon_counter == 0 && parentheses_counter == 1)
                {
                    node_name1 += input[i];
                }
                if (single_quotation_counter == 1 && parentheses_counter == 1)
                {
                    node_id1 += input[i];
                }
                if (single_quotation_counter == 3 && parentheses_counter == 1)
                {
                    node_type1 += input[i];
                }
                if (single_quotation_counter == 5 && parentheses_counter == 1)
                {
                    node_galaxy1 += input[i];
                }
            }
            // checking the correctness of the input form
            if (parentheses_counter = 1 && colon_counter == 4 && single_quotation_counter == 6)
            {
                if (node_name1.size() > 0 && node_id1.size() > 0 && node_type1.size() > 0 && node_galaxy1.size() > 0)
                {
                    world.set_galaxy_or_node(node_name1, node_galaxy1, node_id1, node_type1);
                }

                cout << "name :" << node_name1 << " id :" << node_id1 << " type :" << node_type1 << " galaxy :" << node_galaxy1 << endl;
            }
            else
            {
                cout << "wrong command \ntry again " << endl;
            }
        }
        else if (greater_than_counter == 1)
        {
            for (size_t i = 0; i < input.size(); i++)
            {
                if (input[i] == '(')
                {
                    parentheses_counter++;
                    node_counter++;
                    continue;
                }
                if (input[i] == ')')
                {
                    parentheses_counter--;
                    continue;
                }
                if (input[i] == '{')
                {
                    braces_counter++;
                    continue;
                }
                if (input[i] == '}')
                {
                    braces_counter--;
                }
                if (input[i] == ':')
                {
                    colon_counter++;
                    continue;
                }
                if (input[i] == '.')
                {
                    point_counter++;
                    continue;
                }
                if (parentheses_counter == 1 && node_counter == 1 && point_counter == 0)
                {
                    node_name1 += input[i];
                }
                if (parentheses_counter == 1 && node_counter == 1 && point_counter == 1)
                {
                    node_galaxy1 += input[i];
                }
                if (parentheses_counter == 1 && node_counter == 2 && point_counter == 1)
                {
                    node_name2 += input[i];
                }
                if (parentheses_counter == 1 && node_counter == 2 && point_counter == 2)
                {
                    node_galaxy2 += input[i];
                }

                if (colon_counter == 2 && braces_counter == 1)
                {
                    cost_temp += input[i];
                }
            }
            cost = stoi(cost_temp); // changse cost type " string to integer"
            // checking the correctness of the input form
            if (parentheses_counter == 0 && colon_counter == 2 && braces_counter == 0 && point_counter == 2)
            {

                if (node_name1.size() > 0 && node_name2.size() > 0 && node_galaxy1.size() > 0 && node_galaxy2.size() > 0 && cost_temp.size() > 0)
                {
                    set_cost(world, node_name1, node_galaxy1, node_name2, node_galaxy2, cost);
                }

                cout << "name1 :" << node_name1 << " galaxy1 :" << node_galaxy1 << " name2 :" << node_name2 << " galaxy2 :" << node_galaxy2 << " cost :" << cost << endl;
            }
            else
            {
                cout << "wrong command \ntry again " << endl;
            }
        }
        else
        {
            cout << "wrong command \ntry again " << endl;
        }
    }
    else if (command_type == "FIND")
    {
        for (size_t i = 0; i < input.size(); i++)
        {
            if (input[i] == '.')
            {
                point_counter++;
                continue;
            }
            if (input[i] == ' ')
            {
                space_counter++;
                continue;
            }
            if (input[i] == '-')
            {
                hyphen_counter++;
                continue;
            }
            if (input[i] == '>')
            {
                greater_than_counter++;
                continue;
            }
            if (space_counter == 1 && point_counter == 0)
            {
                node_galaxy1 += input[i];
            }
            if (space_counter == 1 && point_counter == 1 && hyphen_counter == 0)
            {
                node_name1 += input[i];
            }
            if (greater_than_counter == 1 && point_counter == 1)
            {

                node_galaxy2 += input[i];
            }
            if (point_counter == 2)
            {
                node_name2 += input[i];
            }
        }
        // checking the correctness of the input form
        if (point_counter == 2 && hyphen_counter == 1 && greater_than_counter == 1)
        {

            if (node_name1.size() > 0 && node_name2.size() > 0 && node_galaxy1.size() > 0 && node_galaxy2.size() > 0)
            {
                cout << "name1 :" << node_name1 << " galaxy1 :" << node_galaxy1 << " name2 : " << node_name2 << " galaxy2 :" << node_galaxy2 << endl;
                find_way(world, node_name1, node_galaxy1, node_name2, node_galaxy2);
            }
        }
    }
    else
    {
        cout << "wrong command \ntry again " << endl;
    }
    return true;
}

bool find_way(universe &world, string node_name1, string as1, string node_name2, string as2)
{
    int galaxy_andis;
    int source_andis;//origin of path
    int destination_andis;//destination of path

    if (as1 == as2)
    {
        galaxy_andis = world.find_galaxy_andis(as1);
        if (galaxy_andis == (-1))//check valid galaxy index
        {
            cout << "galaxy (" << as1 << ") not founded for finding way!!" << endl;
            return false;
        }
        source_andis = world.AS[galaxy_andis].find_node_andis(node_name1);
        if (source_andis == (-1))//check valid node1 index
        {
            cout << "node (" << node_name1 << ") not founded for finding way!!" << endl;
            return false;
        }
        destination_andis = world.AS[galaxy_andis].find_node_andis(node_name2);
        if (destination_andis == (-1))//check valid node2 index
        {
            cout << "node (" << node_name2 << ") not founded for finding way!!" << endl;
            return false;
        }

        world.AS[galaxy_andis].dijkstra(source_andis, destination_andis);//find shortest way and print
        return true;
    }
    else
    {
        cout << "this node are not in same galaxy !!" << endl;
        return false;
    }
}

bool set_cost(universe &world, string node_name1, string as1, string node_name2, string as2, int cost)
{
    int galaxy_andis1;
    int node_andis1;//node1 index
    int node_andis2;//node2 index

    if (as1 == as2)//for set cost inner of one galaxy
    {
        galaxy_andis1 = world.find_galaxy_andis(as1);// get galaxy name then  return index of galaxy
        if (galaxy_andis1 == (-1))//check valid  index
        {
            cout << "galaxy (" << as1 << ") not founded for for set cost!!" << endl;
            return false;
        }
        node_andis1 = world.AS[galaxy_andis1].find_node_andis(node_name1);// get node name then  return index of node
        if (node_andis1 == (-1))//check valid index
        {
            cout << "node (" << node_name1 << ") not founded for set cost!!" << endl;
            return false;
        }
        node_andis2 = world.AS[galaxy_andis1].find_node_andis(node_name2);// get node name then  return index of node

        if (node_andis2 == (-1))//check valid index
        {
            cout << "node (" << node_name2 << ") not founded for set cost!!" << endl;
            return false;
        }
        world.AS[galaxy_andis1].set_adjacecy_costs(node_andis1, node_andis2, cost);//set way cost in adjacency matrix
    }
    else
    {
        if (!world.set_intergalactic_adjacency_cost(node_name1, as1, node_name2, as2, cost))//set intergalactic way cost
        {
            return false;
        }
    }
    return true;
}
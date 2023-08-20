#include <iostream>

using namespace std;

#ifndef NODE_H
#define NODE_H

class node
{
public:
   bool set_node_name(string);//set node name
   bool set_id(string);//set node id
   bool set_type(string);//set node type
   bool set_galaxy_name(string);//set node's galaxy name
   string get_galaxy_name();//return node's galaxy name
   string get_node_name();//return node name
   string get_id();//return node id
   string get_type();//return node type
private:
   string node_name;
   string id;//node id
   string type;//node type
   string galaxy_name;//node's galaxy name
};

#endif

bool node::set_node_name(string node_name1)
{
   node_name = node_name1;
   return true;
}
string node::get_node_name()
{
   return node_name;
}
bool node::set_id(string id1)
{
   id = id1;
   return true;
}
bool node::set_type(string type1)
{
   type = type1;
   return true;
}
string node::get_id()
{
   return id;
}
string node::get_type()
{
   return type;
}
bool node ::set_galaxy_name(string galaxy_name1)
{
   galaxy_name = galaxy_name1;
   return true;
}
string node ::get_galaxy_name()
{
   return galaxy_name;
}
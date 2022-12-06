#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

class Node{
public:
    vector<vector<char>> state;
    vector<int> coordinate;
    Node *parent;
    vector<Node> children;
    vector<int> R;
    int pcost; int hcost; int gcost;

public: 

    Node();
    Node(int u_gcost);
    Node(vector<vector<char>>u_state, vector<int> u_coordinate, Node *u_parent, vector<int> u_R);
    void move(vector<int>shift);
    void print();
    bool equals(vector<vector<char>> u_state);

};

void expand(Node *initial); 

#endif
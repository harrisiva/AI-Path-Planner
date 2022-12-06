#ifndef PQ_H
#define PQ_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
#include "../Util/util.hpp"
#include "../Node/node.hpp"
using namespace std;


void inSort(vector<Node*>*a);

class PriorityQueue{
public: 
    vector<Node*> nodes;
public:
    PriorityQueue();
    bool is_empty();
    bool contains(Node node);
    void insert(Node *node);
    Node* pop();
    void print();
};


#endif
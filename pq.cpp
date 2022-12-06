#include "pq.hpp"

void inSort(vector<Node*>*a) 
{
    int n = (*a).size();
    int i,j;
    int kcost;  
    Node *temp;

    for (int i=1;i<n;i++){
        temp = ((*a)[i]);
        kcost = (*((*a)[i])).gcost;
        j = i-1;
        while (j>=0 && (*((*a)[j])).gcost>kcost){ // gcost of node at j is greater than kcost
            // set the current index in nodes node pointer to point to the address of the node in the prev index
            (*a)[j+1] =  (*a)[j];
            j = j - 1;
        } 
        // set the current element to be the temp
        (*a)[j+1]=temp;
    }
    return;
}

PriorityQueue:: PriorityQueue(){
    return;
}

bool PriorityQueue::is_empty(){
    return (nodes.size()==0);
}

bool PriorityQueue::contains(Node node){
    bool contains_node = false;
    for (int i=0; i<nodes.size(); i++){
        if ((*nodes[i]).equals(node.state)){contains_node=true;}
    }
    return contains_node;
}

void PriorityQueue::insert(Node *node){ // Inserts the node in sorted order using insertation sort
    // If empty, just push back
    nodes.push_back(node);
    if (nodes.size()>1){inSort(&nodes);} // else, call insort on the nodes after pushing back
    return;
}

Node* PriorityQueue::pop(){
    Node *first = nodes[0];
    nodes.erase(nodes.begin());
    return first;
}

void PriorityQueue::print(){ // TODO: Print the cost of each node in the nodes list
    for (int i=0; i<nodes.size();i++){
        cout << "(" << i << "): " << (*nodes[i]).gcost << ", ";
    } cout << endl;
    return;
}
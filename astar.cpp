#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

class Node{
public: // Public variables
    vector<vector<char>> state;
    vector<int> coordinate;
    // Node parent;
    // vector<Node> children;

public: // Public methods

    // Default constructor (Initialize the node with the given state, robot location/coordinate given)
    Node(vector<vector<char>>u_state, vector<int> u_coordinate){ 
        coordinate = u_coordinate;
        state = u_state;
        return;
    }
    
    void move(vector<int>shift){ // just adjust the coordinate and state of this node's public variable
        int val_at_shift_position = state[((coordinate[0])+shift[0])][((coordinate[1])+shift[1])];
        state[((coordinate[0])+shift[0])][((coordinate[1])+shift[1])]='B';
        state[((coordinate[0])+shift[0])][((coordinate[1])+shift[1])] = val_at_shift_position;
        return;
    }

    void print(){
        // print the current nodes details
        return;
    }

};

int main(){
    int x; x=-1;
    int y;y=1;
    cout << y+x << endl;
// required:
    // frontier: priority queue structure (or vector with insort)
    // explored set: vector
    // node: contains current state, can call expand on it
    // isgoal(): checks if the given state matches with the global constant goal state

// Optional:
    // A game state (that tracks moves, has initial state, prints solution)?

// frontier PQ
// explored (simple hash table or a vector - to avoid resizing)
// loop do
// if the frontier is empty return failure
// pop a node from the frontier
// if the node is the goal state, return solution
// add the node to the explored list
// expand and add the children to the frontier (only if not in the explored list or frontier pq)
    
    return 0;
}
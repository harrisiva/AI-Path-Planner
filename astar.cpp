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

    // Default constructor
    Node(vector<vector<char>>state, vector<int> coordinate){ 
        // Keep track of the coordinate for this bot
        return;
    }
    
    // Function to return the children of the current bot based on the valid moves
    void expand(){
        // Call a function for deriving children
        // Pass the current state and coordinate
        // Return the children (type node with parent set)
        return;
    } 

    void compare(){
        // compares if this nodes state is the same as the given state
        return;
    }

    void print(){
        // print the current nodes details
        return;
    }

};

int main(){
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
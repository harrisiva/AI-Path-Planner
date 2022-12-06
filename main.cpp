#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
#include "Util/util.hpp"
#include "Node/node.hpp"
#include "PriorityQueue/pq.hpp"
using namespace std;

int main(){

    // Load input into appropriate variables
    string filename="Data/input.txt";
    vector<string> lines = getlines(filename);
    vector<int> dimensions = getdimensions(lines);  
    int N; N=stoi(lines[1]); // get the number of robots
    map<int,vector<int>> coordinates = getcoordinates(lines,N,dimensions); 
    vector<int> R = getrendezvous(lines,N,dimensions);
    vector<vector<char>> board = getboard(lines,dimensions,N); // board without the R and B set up in the right locations

    // Setup the initial generic board
    board[R[0]][R[1]] = 'R'; // set R at its location
    for (int i=0;i<coordinates.size();i++){
        board[coordinates[i][0]][coordinates[i][1]] = 'B'; // set B at its location for both the robots
    }

    // FOR EACH BOT

    // Setup the goal state (derived from board and make changes based on the current robot that you are moving)
    vector<vector<char>> goal = board;
    goal[R[0]][R[1]] = 'B'; // Set the rendevous point with B (since that is the goal state for all bots)
    goal[coordinates[1][0]][coordinates[1][1]] = '0';  // Set the second bot as 0 since that is how it will look in the goal state (this should be the ith bot)

    // Setup the initial node 
    cout << "simulating A* on the first robot of the test:" << endl;
    Node null_node = Node(); // Null node will act as the parent node for the initial node and it is identified with -1
    Node initial = Node(board,coordinates[1],&null_node,R); // For the first initial node
    cout << "Initial state of the first robot:" << endl;
    initial.print(); 

    // initialize the frontier as a PQ instance
    PriorityQueue frontier = PriorityQueue();
    frontier.insert(&initial); // add the intitial node to it
    vector<Node> explored; // will contain the node, use .equals to check on each node    

    bool found_goal = false;
    Node *goal_node = &null_node; // initialized as null, returned at the end

    while (frontier.nodes.size()>0 && found_goal==false){ // done untill frontier is empty or goal state is found
        Node *node = frontier.pop(); // pop the front node and store it as a pointer variable

        // check if the current node==the goal state
        if ((*node).equals(goal)){
            goal_node = node; // if true, set current node as the goal_node
            found_goal = true;
        } 
        
        else {
            expand(node); // expand the current node
            explored.push_back((*node)); // add the expanded node to the explored list

            // check if children are in respective vectors, if not, push_back/insert

            for (int i=0;i<(*node).children.size();i++){

                // testing if explored set contains this node

                bool explored_contains=false;
                for (int j=0;j<explored.size();j++){ // iterate through the explored sets indexes
                    if (explored[j].equals((*node).children[i].state)){ // check if the current node's child's state equals a node in the explored state
                        explored_contains=true; // if true, set this as true
                    }
                }

                if (explored_contains==false && frontier.contains((*node).children[i])==false){ // if the explored does not contain the current node's child, and the frontier does not contain the current node
                    frontier.insert(&((*node).children[i])); // insert the current node's child by reference
                } 

            }

        }
    }

    // this chunk need not be fixed, it is not even executed when the buggy coordinates are given to the while loop
    if (found_goal){
        // print the explored set and see the order
        cout << "Found solution. Printing solution backwards" << endl;
        int count = 0;
        // go backward from the node
        while ((*(*goal_node).parent).pcost!=-1){
            (*goal_node).print();
            goal_node = (*goal_node).parent;
            count ++;
        }
        cout << "Moves: " << count;

    } else {
        cout << "Goal not found" << endl;
    }


    return 0;
}
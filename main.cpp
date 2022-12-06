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
#include "AI/astar.hpp"
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
    for (int i=0;i<coordinates.size();i++){
        // Setup the goal state (derived from board and make changes based on the current robot that you are moving)
        vector<vector<char>> goal = board;
        goal[R[0]][R[1]] = 'B'; // Set the rendevous point with B (since that is the goal state for all bots)
        goal[coordinates[i][0]][coordinates[i][1]] = '0';  // Set the second bot as 0 since that is how it will look in the goal state (this should be the ith bot)

        // Setup the initial 
        cout << "simulating A*:" << endl;
        Node null_node = Node(); // Null node will act as the parent node for the initial node and it is identified with -1
        Node initial = Node(board,coordinates[i],&null_node,R); // For the first initial node
        cout << "Initial state of the robot:" << endl;
        initial.print(); 
        cout << endl;

        // initialize the frontier as a PQ instance
        PriorityQueue frontier = PriorityQueue(); 
        frontier.insert(&initial); // add the intitial node to it

        Node *goal_node = astar(frontier,goal);

        // this chunk need not be fixed, it is not even executed when the buggy coordinates are given to the while loop
        if ((*goal_node).pcost!=-1){
            // print the explored set and see the order
            cout << "Found solution. Printing solution backwards" << endl;
            int count = 0;
            // go backward from the node
            while ((*((*goal_node).parent)).pcost!=-1){
                (*goal_node).print();
                (*goal_node) = *((*goal_node)).parent;
                count ++;
            }
            cout << "Moves: " << count << endl << endl;

        } else {
            cout << "Goal not found" << endl;
        }
    }

    // TODO: Store the solution and write it a text file

    return 0;
}
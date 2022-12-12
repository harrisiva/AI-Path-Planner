#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
#include <iomanip> // for file writing

#include "Util/util.hpp"
#include "Node/node.hpp"
#include "PriorityQueue/pq.hpp"
#include "AI/astar.hpp"
using namespace std;

// Order the bots depending on their location (sometimes they can be in row, need to let the one blocking the exit first followed by the next and so on)

int main(){

    // General program variables
    string solution_filename = "Data/solution.txt";
    // Clear the solution file if one exists, else create a emtpy one
    ifstream w_file;
    w_file.open(solution_filename, std::ifstream::trunc | std::ifstream::out);
    w_file.close();

    // Create writing stream file
    ofstream file;
    
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

    // clean solution text file
    cout << "simulating A*:" << endl;
    for (int i=0;i<coordinates.size();i++){
        // Setup the goal state (derived from board and make changes based on the current robot that you are moving)
        vector<vector<char>> goal = board;
        goal[R[0]][R[1]] = 'B'; // Set the rendevous point with B (since that is the goal state for all bots)
        goal[coordinates[i][0]][coordinates[i][1]] = '0';  // Set the second bot as 0 since that is how it will look in the goal state (this should be the ith bot)

        // Setup the initial 
        string initial_move = "Null";
        Node null_node = Node(); // Null node will act as the parent node for the initial node and it is identified with -1
        Node initial = Node(board,coordinates[i],&null_node,R, initial_move); // For the first initial node

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
                (*goal_node).write(solution_filename);
                (*goal_node) = *((*goal_node)).parent;
                count ++;
            }
            initial.print();
            cout << "Moves: " << count-1 << " for bot #" << i << " located at " << coordinates[i][0] << "," << coordinates[i][1] << endl << endl;
            // Write the moves to the file and go up one
            file.open(solution_filename,ios_base::app);
            // write the initial node
            initial.write(solution_filename);
            file<< "Moves: " << count-1 << " for bot #" << i << " located at " << coordinates[i][0] << "," << coordinates[i][1] << endl << endl;
            file.close(); // close the solution file
            
        } else {
            cout << "Goal not found" << endl;
        }
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

vector<vector<int>> shifts{
    {-1,0}, // up
    {+1,0}, // down
    {0,-1}, // left
    {0,+1}, // right
};

void viewboard(vector<vector<char>> board){
    for (int i=0;i<board.size();i++){
        for (int j=0;j<board[i].size();j++){
            cout<<board[i][j];
        }
        cout<<endl;
    } return;
}

int manhatanDistance(vector<int> R, vector<int> coordinate) {
    // given the board/state (maybe you need the dimensions), the R coordinate, and the robots coordinate
    // calcualte the manhatan distance from the robots coordinate to the R coordinate
    int dist;
    int xDis = coordinate[0] - R[0];
    int yDis = coordinate[1] - R[1];
    dist = abs(xDis + yDis);
    return dist;
}

class Node{
public: // Public variables
    vector<vector<char>> state;
    vector<int> coordinate;
    Node *parent;
    vector<Node> children;
    vector<int> R;
    // need to keep track of the costs as integers
    // pcost (cost evaluted from the parent)
    int pcost; int hcost; int gcost;
    // hcost (cost evaluted from the heuristic)

public: // Public methods

    // Default null constructor
    Node(){pcost=-1;return;}

    // Default Place Holder Constructor (Used for testing insort)
    Node(int u_gcost){
        gcost = u_gcost;
        return;
    }

    // Default working constructor (Initialize the node with the given state, robot location/coordinate given)
    Node(vector<vector<char>>u_state, vector<int> u_coordinate, Node *u_parent, vector<int> u_R){ 
        coordinate = u_coordinate;
        state = u_state;
        parent = u_parent;
        // calcualte and set the hcost
        // set the pcost as parent.p_cost + 1
        pcost = ((*parent).pcost)+1;
        R = u_R;
        hcost = manhatanDistance(R,coordinate); // SET BY CALLING THE HEURISTIC FUNCTION (requires R location as well)
        gcost = pcost + hcost;
        return;
    }
    
    void move(vector<int>shift){ // just adjust the coordinate and state of this node's public variable
        char val_at_shift_position = state[((coordinate[0])+shift[0])][((coordinate[1])+shift[1])];
        int i = coordinate[0]+shift[0];
        int j = coordinate[1]+shift[1];
        state[i][j] = 'B';
        if (val_at_shift_position=='R'){
            val_at_shift_position='0';
        }
        state[coordinate[0]][coordinate[1]]=val_at_shift_position;
        coordinate[0] = i;
        coordinate[1] = j;
        return;
    }

    void print(){
        viewboard(state);
        cout << "p_cost: " << pcost << " h_cost: " << hcost << " g_cost: " <<gcost << endl;
        return;
    }

    bool equals(vector<vector<char>> u_state){
        if (state.size()==u_state.size()){ // If the size of the state is the same
            for (int i=0;i<state.size();i++){
                // if the size of the cols (inner vector) is the same
                if (state[i].size()==u_state[i].size()){
                    for (int j=0;j<state[i].size();j++){ // if the elements are the same
                        if (state[i][j]!=u_state[i][j]){
                            return false;
                        }
                    }
                } else {return false;}       
            } 
            return true;
        } return false; // if conditions are note met, return false
    }

};

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

class PriorityQueue{
public: // Public Variables
    vector<Node*> nodes;
public: // Public Methods

    // default constructor (overrided, no changes)
    PriorityQueue(){
        return;
    }

    bool is_empty(){
        return (nodes.size()==0);
    }

    bool contains(Node node){
        bool contains_node = false;
        for (int i=0; i<nodes.size(); i++){
            if ((*nodes[i]).equals(node.state)){contains_node=true;}
        }
        return contains_node;
    }

    void insert(Node *node){ // Inserts the node in sorted order using insertation sort
        // If empty, just push back
        nodes.push_back(node);
        if (nodes.size()>1){inSort(&nodes);} // else, call insort on the nodes after pushing back
        return;
    }

    Node* pop(){
        Node *first = nodes[0];
        nodes.erase(nodes.begin());
        return first;
    }

    void print(){ // TODO: Print the cost of each node in the nodes list
        for (int i=0; i<nodes.size();i++){
            cout << "(" << i << "): " << (*nodes[i]).gcost << ", ";
        } cout << endl;
        return;
    }
};


vector<string> getlines(string filename){
    // read the file lines by opening the file object
    vector<string> lines;
    fstream file;
    file.open(filename,ios::in);
    if (file.is_open()){
        string line;
        while (getline(file,line)){
            lines.push_back(line);}
    }
    return lines;
}

vector<int> getdimensions(vector<string>lines){
    // get the dimensions from the first line and add it to the vector dimensions
    vector<int> dimensions;
    stringstream StrIn(lines[0]);
    while(!StrIn.fail()){
        string c; 
        StrIn>>c;
        if (c.size()!=0){
            dimensions.push_back(stoi(c));
        }
    }
    return dimensions;
}

vector<int> cordconvert(vector<int> coordinate, vector<int> dimensions){ // TODO: Pass by reference
    int max_y; vector<int> convertedCord;
    max_y = dimensions[0]-1;

    convertedCord.push_back(max_y-coordinate[1]); // row 
    convertedCord.push_back(coordinate[0]); // keep x (col) the same as it is parallel
    return convertedCord;
}

map<int,vector<int>> getcoordinates(vector<string>lines,int N,vector<int> dimensions){
    // get the coordinates for the robots as a dictionary (indexed by the robot number)
    map<int,vector<int>> coordinates; // to return

    vector<vector<int>> coordinatesVector; // create a temp coordinatesVector for initial access (is this faster?)
    for(int r=N;r<N+N;r++){
        stringstream strIn(lines[r]); vector<int> coordinate;
        // load the current lines coordinate into the internal coordinate vector
        while (!strIn.fail()){
            string line;
            strIn >> line;
            if (line.size()!=0){coordinate.push_back(stoi(line));}
        } 
        coordinate = cordconvert(coordinate,dimensions);
        coordinatesVector.push_back(coordinate);// push the coordinate vector retrived from the current line to the coordinatesVector 
    }

    // move coordinates to the map for faster access
    for (int i=0;i<coordinatesVector.size();i++){
        for (int j=0;j<coordinatesVector[i].size();j++){
            coordinates[i].push_back(coordinatesVector[i][j]);
        }
    }
    return coordinates;
}

vector<int> getrendezvous(vector<string>lines,int N, vector<int> dimensions){
    // Get the rendezvous location
    vector<int> R;
    stringstream strIn(lines[2+N]);
    while (!strIn.fail()){
        string line; strIn>>line;
        if (line.size()!=0){R.push_back(stoi(line));}
    }
    R = cordconvert(R, dimensions);
    return R;
}

vector<vector<char>> getboard(vector<string> lines, vector<int> dimensions, int N){
    vector<vector<char>> board; // Initialize a vector for the board
    for (int i=3+N;i<lines.size();i++){
        if (lines[i].size()!=0){
            vector<char> line(lines[i].begin(),lines[i].end());
            board.push_back(line);
        }
    } return board;
}

void expand(Node *initial){
    cout << "In expand" << endl;

    // to check if valid (and create a list of valif shifts), check if the val at shift is 0 or R, all other values are rejected
    for (int i=0;i<shifts.size();i++){ // for different shift options
        vector<int> shift = shifts[i]; // Grab the index shift

        Node initial_clone = *initial; // get the pointer to the initial


        // set the new indexes for the Bot (B)
        int new_i; int new_j;
        new_i = ((*initial).coordinate[0])+(shift[0]); 
        new_j= ((*initial).coordinate[1])+(shift[1]);

        // get the variable at the new coordinate
        char var_at_new_coordinate = (*initial).state[new_i][new_j];
        // check if the veriable is 0 or R, in all other cases, move not possible
        if (var_at_new_coordinate =='0' || var_at_new_coordinate=='R'){
            cout << "Passed new coordinate check for " << new_i << " " << new_j << endl;
            // create the new node and set the parent and children relation
            initial_clone.move(shift); // creat a move 
            Node child = Node(initial_clone.state,initial_clone.coordinate,initial,initial_clone.R);
            (*initial).children.push_back(child);
        } 
    }
    cout << "returning" << endl;
    return; // THIS POINT IS NOT ENTERED FOR THE STATE THAT BREAKS IT (FIXING THIS MIGHT FIX THE PROBLEM)
}

int main(){
    // read lines from the input file
    string filename; filename="input.txt";
    vector<string> lines = getlines(filename);
    vector<int> dimensions = getdimensions(lines);   
    int N; N=stoi(lines[1]); // get the number of robots
    map<int,vector<int>> coordinates = getcoordinates(lines,N,dimensions);
    vector<int> R = getrendezvous(lines,N,dimensions);
    vector<vector<char>> board = getboard(lines,dimensions,N); // NOTE: Strings, need to convert for easy evaluation

    // print the input here (conversion from py to cpp for setting up)
    cout<<"Dimensions: "<<dimensions[0]<<" "<<dimensions[1]<<endl; // use printf
    cout<<"Number of Robots: "<<N<<endl;
    cout<<"Robots initial location: "<<endl;
    for (int i=0;i<coordinates.size();i++){
        for (int j=0;j<coordinates[i].size();j+=2){
            cout << "\tRobot "<< i << "'s coordinate: " << coordinates[i][j] <<","<<coordinates[i][j+1] << endl;
        }
    }
    cout<<"Rendezvous location: "<<R[0]<<" "<<R[1]<<endl; 
    // set the robot locations as B (bot) and the rendezvous as R
    board[R[0]][R[1]] = 'R';
    for (int i=0;i<coordinates.size();i++){
        board[coordinates[i][0]][coordinates[i][1]] = 'B';
    }


    // NOTE: GOAL STATE CURRENTLY SET FOR ROBOT AT INDEX 1 NOT 0 OR MUTUAL
    vector<vector<char>> goal = board;
    cout << "Initial board:" << endl;
    // set the given robots (TESTING WITH ONE) location as 0 (bot) and the rendezvous as B for the goal state
    goal[R[0]][R[1]] = 'B';
    goal[coordinates[1][0]][coordinates[1][1]] = '0';  // testing with the second robot

    // Setup the initial node 
    cout << "simulating A* on the first robot of the test:" << endl;
    Node null_node = Node(); // Null node will act as the parent node for the initial node and it is identified with -1
    Node initial = Node(board,coordinates[1],&null_node,R); // For the first initial node
    cout << "Initial state of the first robot:" << endl;
    initial.print(); 
    // no bugs with this part


    vector<vector<char>> breakerState = {
        {'1','0','0','0','R','0','0','0','0','1'},
        {'1','1','0','0','0','0','0','0','1','1'},
        {'0','0','0','0','0','0','0','0','0','0'},
        {'1','0','0','0','1','1','0','0','0','1'},
        {'1','0','0','1','1','1','1','0','0','1'},
        {'0','0','B','1','1','1','1','0','0','0'},
        {'0','0','0','0','1','1','0','0','0','0'},
        {'1','1','B','0','0','0','0','0','1','1'}
    };
    viewboard(breakerState);


    // // initialize the frontier as a PQ instance
    // PriorityQueue frontier = PriorityQueue();
    // frontier.insert(&initial); // add the intitial node to it
    // // intialize the explored set as an empty vector of node's (by value)
    // vector<Node> explored; // will contain the node, use .equals to check on each node    
    // // no bugs up untill this part

    // bool found_goal = false;
    // Node *goal_node = &null_node; // initialized as null, returned at the end

    // while (frontier.nodes.size()>0 && found_goal==false){ // done untill frontier is empty or goal state is found
    //     cout << "-----------------" << endl;
    //     frontier.print();
    //     Node *node = frontier.pop(); // pop the front node and store it as a pointer variable

    //     // check if the current node==the goal state
    //     if ((*node).equals(goal)){
    //         goal_node = node; // if true, set current node as the goal_node
    //         found_goal = true;
    //     } 
        
    //     else {
    //         cout << "calling expand" << endl;
    //         (*node).print();
    //         expand(node); // expand the current node
    //         cout << "Expanded" << endl;
    //         explored.push_back((*node)); // add the expanded node to the explored list

    //         // check if children are in respective vectors, if not, push_back/insert

    //         for (int i=0;i<(*node).children.size();i++){

    //             // testing if explored set contains this node

    //             bool explored_contains=false;
    //             for (int j=0;j<explored.size();j++){ // iterate through the explored sets indexes
    //                 if (explored[j].equals((*node).children[i].state)){ // check if the current node's child's state equals a node in the explored state
    //                     explored_contains=true; // if true, set this as true
    //                 }
    //             }

    //             if (explored_contains==false && frontier.contains((*node).children[i])==false){ // if the explored does not contain the current node's child, and the frontier does not contain the current node
    //                 frontier.insert(&((*node).children[i])); // insert the current node's child by reference
    //             } 

    //         }

    //     }
    // }



    // // this chunk need not be fixed, it is not even executed when the buggy coordinates are given to the while loop
    // if (found_goal){
    //     // print the explored set and see the order
    //     cout << "Found solution. Printing solution backwards" << endl;
    //     int count = 0;
    //     // go backward from the node
    //     while ((*(*goal_node).parent).pcost!=-1){
    //         (*goal_node).print();
    //         goal_node = (*goal_node).parent;
    //         count ++;
    //     }
    //     cout << "Moves: " << count;

    // } else {
    //     cout << "Goal not found" << endl;
    // }

    return 0;
}
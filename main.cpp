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


class Node{
public: // Public variables
    vector<vector<char>> state;
    vector<int> coordinate;
    Node *parent;
    vector<Node> children;
    // need to keep track of the costs as integers
    // pcost (cost evaluted from the parent)
    int pcost; int hcost;
    // hcost (cost evaluted from the heuristic)

public: // Public methods

    // Default null constructor
    Node(){pcost=-1;return;}

    // Default working constructor (Initialize the node with the given state, robot location/coordinate given)
    Node(vector<vector<char>>u_state, vector<int> u_coordinate, Node *u_parent){ 
        coordinate = u_coordinate;
        state = u_state;
        parent = u_parent;
        // calcualte and set the hcost
        // set the pcost as parent.p_cost + 1
        pcost = ((*parent).pcost)+1;
        return;
    }
    
    void move(vector<int>shift){ // just adjust the coordinate and state of this node's public variable
        char val_at_shift_position = state[((coordinate[0])+shift[0])][((coordinate[1])+shift[1])];
        int i = coordinate[0]+shift[0];
        int j = coordinate[1]+shift[1];
        state[i][j] = 'B';
        state[coordinate[0]][coordinate[1]]=val_at_shift_position;
        coordinate[0] = i;
        coordinate[1] = j;
        return;
    }

    void print(){
        viewboard(state);
        cout << "p_cost:" << pcost << endl;
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
        for (int i=0; i<nodes.size(); i++){
            if (!(*nodes[i]).equals(node.state)){return false;}
        }
        return true;
    }

    void insert(Node *node){ // TODO: Needs to insert and sort based on the g_cost
        nodes.push_back(node);
        return;
    }

    Node pop(){
        cout << nodes.size() << endl;
        Node first = *nodes[0];
        nodes.erase(nodes.begin());
        cout << nodes.size() << endl;
        return first;
    }

    void print(){ // TODO: Print the details and the nodes
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
    vector<vector<int>> valid_shifts;
    // to check if valid (and create a list of valif shifts), check if the val at shift is 0 or R, all other values are rejected
    for (int i=0;i<shifts.size();i++){
        vector<int> shift = shifts[i];
        Node initial_clone = *initial;
        int new_i; int new_j; 
        new_i = ((*initial).coordinate[0])+(shift[0]); 
        new_j= ((*initial).coordinate[1])+(shift[1]);
        char var_at_new_coordinate = (*initial).state[new_i][new_j];
        if (var_at_new_coordinate =='0' || var_at_new_coordinate=='R'){
            // create the new node and set the parent and children relation
            initial_clone.move(shift);
            Node child = Node(initial_clone.state,initial_clone.coordinate,initial);
            (*initial).children.push_back(child);
        }
    } return;
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

    // print the data here (conversion from py to cpp for setting up)
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

    cout << "simulating A* on the first robot of the test:" << endl;
    Node null_node = Node();
    Node initial = Node(board,coordinates[1],&null_node); // For the first initial node
    Node test_node = Node(board,coordinates[1],&null_node);
    initial.print();
    test_node.print();
    cout << "Testing equals and contains" << endl;
    cout << initial.equals(test_node.state) << endl;
    cout << "Testing priority queue contains" << endl;
    PriorityQueue pq = PriorityQueue();
    cout << "Insert PQ" << endl;
    pq.insert(&initial);
    cout << "Contains PQ" << endl;
    cout<< pq.contains(initial) << endl;

    cout << "Expand" << endl;
    expand(&initial);
    cout << "Children" << endl;
    for (int i=0;i<initial.children.size();i++){
        initial.children[i].print();
    }
    
    // A* logic for this board
    // Solve one robot at a time
    // Add the robot to the board and keep track of its location (use a unique character to represent its location)
    // define a goal state:
        // the unique character representing the robot in the R location

    return 0;
}
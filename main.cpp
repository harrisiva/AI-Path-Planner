#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

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

void viewboard(vector<vector<char>> board){
    for (int i=0;i<board.size();i++){
        for (int j=0;j<board[i].size();j++){
            cout<<board[i][j];
        }
        cout<<endl;
    } return;
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


int main(){
    // read lines from the input file
    string filename; filename="input.txt";
    vector<string> lines = getlines(filename);
    vector<int> dimensions = getdimensions(lines);   
    int N; N=stoi(lines[1]); // get the number of robots
    map<int,vector<int>> coordinates = getcoordinates(lines,N, dimensions);
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
    // view the board
    cout << "Board: " << endl;
    viewboard(board);

    // A* logic for this board
    // Solve one robot at a time
    // Add the robot to the board and keep track of its location (use a unique character to represent its location)
    // define a goal state:
        // the unique character representing the robot in the R location

    return 0;
}
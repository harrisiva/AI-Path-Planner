#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

int main(){
    // read lines from the input file
    string filename; filename="input.txt";
    
    // read the file lines by opening the file object
    vector<string> lines;
    fstream file;
    file.open(filename,ios::in);
    if (file.is_open()){
        string line;
        while (getline(file,line)){
            lines.push_back(line);}
    }

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
    
    int N; N=stoi(lines[1]); // get the number of robots

    // get the coordinates for the robots as dictionaries
    map<int,vector<int>> coordinates;
    
    vector<int> coordinate; // should be inside the loop
    coordinate.push_back(1);
    coordinate.push_back(2);
    coordinates[0] = coordinate;


    // print the data here (conversion from py to cpp for setting up)
    for (int i=0;i<dimensions.size();i++){
        cout<<dimensions[i]<<endl;
    }
    cout<<N<<endl;
    return 0;
}
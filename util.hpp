#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;


vector<string> getlines(string filename);
vector<int> getdimensions(vector<string>lines);
vector<int> cordconvert(vector<int> coordinate, vector<int> dimensions);
map<int,vector<int>> getcoordinates(vector<string>lines,int N,vector<int> dimensions);
vector<int>getrendezvous(vector<string>lines,int N, vector<int> dimensions);
vector<vector<char>> getboard(vector<string> lines, vector<int> dimensions, int N);
void viewboard(vector<vector<char>> board);
int manhatanDistance(vector<int> R, vector<int> coordinate);

#endif
#include "node.hpp"

vector<vector<int>> shifts = {
    {-1,0}, // up
    {+1,0}, // down
    {0,-1}, // left
    {0,+1}, // right
};

Node::Node(){pcost=-1;return;}

Node::Node(int u_gcost){
    gcost = u_gcost;
    return;
}

Node::Node(vector<vector<char>>u_state, vector<int> u_coordinate, Node *u_parent, vector<int> u_R){ 
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

void Node::move(vector<int>shift){ // just adjust the coordinate and state of this node's public variable
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

void Node::print(){
    viewboard(state);
    cout << "p_cost: " << pcost << " h_cost: " << hcost << " g_cost: " <<gcost << endl;
    return;
}

void Node::write(string filename){
    ofstream file;
    file.open(filename,ios_base::app);

    // viewboard logic but with writing instead of cout
    for (int i=0;i<state.size();i++){
        for (int j=0;j<state[i].size();j++){
            file << state[i][j];
        }
        file << endl;
    }

    // print line here but with write
    file << "p_cost: " << pcost << " h_cost: " << hcost << " g_cost: " <<gcost << endl;
    
    file.close(); 
    return;
}

bool Node::equals(vector<vector<char>> u_state){
    if (state.size()==u_state.size()){ // If the size of the state is the same
        for (int i=0;i<state.size();i++){
            if (state[i].size()==u_state[i].size()){
                for (int j=0;j<state[i].size();j++){ // if the elements are the same
                    if (state[i][j]!=u_state[i][j]){
                        return false;
                    }
                }
            } else {return false;}       
        } return true;
    } return false; // if conditions are note met, return false
}

void expand(Node *initial){

    // to check if valid (and create a list of valif shifts), check if the val at shift is 0 or R, all other values are rejected
    for (int i=0;i<shifts.size();i++){ // for different shift options
        vector<int> shift = shifts[i]; // Grab the index shift
        Node initial_clone = *initial; // get the pointer to the initial

        // set the new indexes for the Bot (B)
        int new_i; int new_j;
        new_i = ((*initial).coordinate[0])+(shift[0]); 
        new_j= ((*initial).coordinate[1])+(shift[1]);

        // perform range check, value check, and then perform move with shift
        if ( (new_i>=0) && (new_j>=0) && (new_i<=(initial_clone.state.size()-1)) && (new_j<=(initial_clone.state[0].size()-1))){ // check if new_i is within the number of rows and if the new_j is within the number of cols
            char var_at_new_coordinate = (*initial).state[new_i][new_j];
            // check if the veriable is 0 or R, in all other cases, move not possible
            if (var_at_new_coordinate =='0' || var_at_new_coordinate=='R'){
                // create the new node and set the parent and children relation
                initial_clone.move(shift); // creat a move 
                Node child = Node(initial_clone.state,initial_clone.coordinate,initial,initial_clone.R);
                (*initial).children.push_back(child);
            } 
        }
    }
    return; // THIS POINT IS NOT ENTERED FOR THE STATE THAT BREAKS IT (FIXING THIS MIGHT FIX THE PROBLEM)
}
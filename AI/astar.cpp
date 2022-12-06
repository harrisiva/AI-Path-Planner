#include "astar.hpp"


// given the frontier and the goal state, run the astar algorithm for the node

Node* astar(PriorityQueue frontier, vector<vector<char>> goal){ // changes the goal_node with the last child set or returns null node as is
    bool found_goal = false; 
    vector<Node> explored;

    // create a goal node and set it as a null node
    Node null_node = Node();
    Node *goal_node = &null_node;

    // A* algorithm required the node, frontier, and explored set (initialized within the code chunk)
    while (frontier.nodes.size()>0 && found_goal==false){ // done untill frontier is empty or goal state is found
        Node *node = frontier.pop(); // pop the front node and store it as a pointer variable

        // check if the current node==the goal state
        if ((*node).equals(goal)){

            goal_node = node; // if true, set current node as the goal_node // Currently not returning the node
            found_goal = true;
            cout << "Found goal" << endl;
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
    return goal_node;
}
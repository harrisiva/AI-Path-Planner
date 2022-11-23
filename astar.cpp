
// required:
    // frontier: priority queue structure (with insort)
    // explored set: vector
    // node: contains current state, can call expand on it
    // isgoal(): checks if the given state matches with the global constant goal state

// Optional:
    // A game state (that tracks moves, has initial state, prints solution)?

// frontier PQ
// explored (simple hash table or a vector - to avoid resizing)
// loop do
// if the frontier is empty return failure
// pop a node from the frontier
// if the node is the goal state, return solution
// add the node to the explored list
// expand and add the children to the frontier (only if not in the explored list or frontier pq)
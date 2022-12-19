# AI Path Planner

## Overview
The purpose of this CP468 - Artificial Intelligence term project is to design and implement an A* based algorithm to solve a path planning problem. A-star (A*) is a greedy best-first search algorithm, this category of algorithm expands nodes that appear to be the closest to a goal state using an evaluative function. Due to the iterative nature of the A* search algorithm, reducing runtime was a priority. Therefore, this project was built using C++ because of its speed relative to other languages such as Python (Tamimi, 2020).

## Problem Statement
The path planning problem tackled by this project can be described as follows: Consider a Museum room that is patrolled by N robots at night. At a predetermined time, the robots are supposed to rendezvous at a given point R in the room. The robots move inside the room, and the room contains obstacles, such as chairs and benches for the visitors, paintings, sculptures etc. The robots are supposed to know the locations of the obstacles in the room (Kotsireas, n.d.). 


The program is given data in the form of a text file that contains the room's dimensions, number of robots, initial positions of robots, rendezvous point, and the layout of the room. An example of the input is shown in image below. 

<a href="https://imgbb.com/"><img src="https://i.ibb.co/xScB9Hz/CP468-TP-Group6.jpg" alt="CP468-TP-Group6" border="0"></a>

## Solution Overview
This project uses a class-based component architecture to solve
the path planning problem presented in the problem overview.
There are four main components: Util, Node, Priority Queue,
and A-star. Each of these components follows the single
responsibility principle. To derive the solution, these
components interact with each other as well as the main
module.

## References
Tamimi, N. (2021, January 13). How fast is C++ compared to python? Medium. https://towardsdatascience.com/how-fast-is-c-compared-to-python-978f18f474c7 

Kotsireas, I. S. (n.d.). Path Planning. Laurier MyLearning Space.

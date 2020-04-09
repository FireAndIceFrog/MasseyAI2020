#ifndef aStar_ExpandedList
#define aStar_ExpandedList
#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <thread>
#include <functional>
#include <thread>
#include "puzzle.h"
#include <fstream>
#include <queue>
#include <unordered_set>

using namespace std;

class AStar {

private:

    class node : public Puzzle {

    public:
        //Constructor: Takes a constant referance to a node and copies
        node(const node &p):Puzzle(p){}; 
        //Constructor: Constructs from Initial given state
        node(string const elements, string const goal):Puzzle(elements,goal){};

        //Overriding the updateCost func
        void updateCost(int hFunction){
            //For A* Strict expanded List, Total cost is Path Length + Heuristic
            //For our example, Each path moves the Blank tile by One Space
            //Therefore, PathLength is equal to the Number of moves which is equal to depth
            //Cost = depth + heuristic value
            cost = h(hFunction) + depth;
        }

        //Greater than Operator Overload for the Priority Queue
        bool operator> ( const node& rhs) const{
	        return this->getCost() > rhs.getCost();
        }
    };

    //Queue
    priority_queue<node, std::vector<node>, std::greater<node> > stateQueue;
    unordered_set<string> expanded;
    
    //Details for Output
    size_t maxQLen;
    string path;
    string init;
    string goal;
    int stateExpansions;
    int heuristic;

public:

    //Constructor for AStar Class
    AStar(string start, string goal):maxQLen{0}, path{""},goal{goal}, init{start}, stateExpansions{0}{}
    //Get AStar Path
    string getPath(){
        return path;
    }
    //Get Number of State expansions
    int getStateExpansions(){
        return stateExpansions;
    }
    //Get Maximum Queue Length
    size_t getMaxQLen() {
        return maxQLen;
    }

    void search(){
        // (1) Initialise Q with search node (S) as only entry; set Expanded = ()

        node curr = node(init, goal);
        stateQueue.push(curr);
        expanded.insert(init);

        while(!stateQueue.empty()){

        // (2) If Q is empty, fail.  Else, pick some search node N from Q.
            curr = stateQueue.top();
            
        // (3) Check if N is goal State. 
        //     If it is, return N
            if (curr.toString() == goal) { path = curr.getPath(); return; }
            ++stateExpansions;
        //     If not, Take N from Q and Expand
            stateQueue.pop();

        // (4) If State N is already in Expanded List, Discard and move to step 2
            //If Current State exists in Expanded, will return greater than 0
            if(expanded.count(curr.getPath()) != 0){
                //State already exists, Skip back to Step 2
                continue;
            }
        // (5) Find all children of N (Not in expanded) and create them
            if(curr.canMoveDown()) {
                node* child = (node*)curr.moveDown();
                pushChild(child);
            } 
            if(curr.canMoveRight()) {
                node* child = (node*)curr.moveRight();
                pushChild(child);
            } 
            if(curr.canMoveUp()) {
                node* child = (node*)curr.moveUp();
                pushChild(child);

            }
            if(curr.canMoveLeft()) {
                node* child = (node*)curr.moveLeft();
                pushChild(child);
            }
        // (6) Add all the extended paths, if Child already in Q, keep Smaller F Cost

        // (7) Go to 2

        }

    }

    void pushChild(node* child){
        child->updateCost(heuristic);
        
        //Check if the Child Node's State already exists in the Queue
        
        if(expanded.count(child->toString()) == 0) { 
            stateQueue.push(node(*child));
            expanded.insert(child->toString());
        }
        delete child;
    }



};
#endif
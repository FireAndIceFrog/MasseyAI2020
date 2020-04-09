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

        // (2) If Q is empty, fail.  Else, pick some search node N from Q.

        // (3) Check if N is goal State. 
        //              If it is, return N
        //              If not, Take N from Q and Expand

        // (4) If State N is already in Expanded List, Discard and move to step 2

        // (5) Find all children of N (Not in expanded) and create them

        // (6) Add all the extended paths, if Child already in Q, keep Smaller F Cost

        // (7) Go to 2



    }



};
#endif
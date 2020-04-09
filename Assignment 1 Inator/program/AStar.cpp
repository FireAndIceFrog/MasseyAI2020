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
        //Greater than Operator Overload for the Priority Queue
        bool operator> ( const node& rhs) const{
	        return this->getHCost() > rhs.getHCost();
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

    

};
#endif
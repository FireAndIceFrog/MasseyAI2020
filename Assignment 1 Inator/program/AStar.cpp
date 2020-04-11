#ifndef aStar_expandL
#define aStar_expandL
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
#include <set>

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

        //Less than Operator Overload for the Priority Queue
        bool operator> ( const node& rhs) const{
	        return this->getCost() > rhs.getCost();
        }
    };

    //Queue
    //priority_queue<node, std::vector<node>, std::greater<node> > stateQueue;
    set<node> stateQueue;
    set<node>::iterator qIt;
    //vector<node> &iterableQueue = Container(stateQueue);
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
    AStar(string start, string goal, int heuristic):maxQLen{0}, path{""},goal{goal}, init{start}, stateExpansions{0}, heuristic{heuristic}{}
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
        stateQueue.insert(curr);
        int sQSize = 0;

        while(!stateQueue.empty()){

            curr.printBoard();
            
            if(sQSize > 50 ){
                return;
            } else {
                sQSize++;
            }


        // (2) If Q is empty, fail.  Else, pick some search node N from Q.
            qIt = stateQueue.begin();
            curr = node((*qIt));
            

            
        // (3) Check if N is goal State. 
        //     If it is, return N
            if (curr.strBoard == goal) { 
                path = curr.getPath(); 
                cout << "\n\nFound Path!!\n\n";
                return; 
            }
            ++stateExpansions;
        //     If not, Take N from Q and Expand
            stateQueue.erase(qIt);

        // (4) If State N is already in Expanded List, Discard and move to step 2
            //If Current State exists in Expanded, will return greater than 0
            if(expanded.count(curr.getPath()) != 0){
                //State already exists, Skip back to Step 2
                cout<<"\nAlready exists, discard node\n";
                continue;
            }
            //Now add to expanded list
            expanded.insert(curr.strBoard);

        // (5) Find all children of N (Not in expanded) and create them
        // (6) Add all the extended paths, if Child already in Q, keep Smaller F Cost
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
        

        // (7) Go to 2

        }

    }
    //Insert a Child into the queue correctly and update the expanded list
    void pushChild(node* child){

        bool exists = false;
        child->updateCost(heuristic);
        
        //Check if the Child Node's State already exists in the Queue
        for(qIt = stateQueue.begin(); qIt != stateQueue.end(); ){
            // If the states are the same and If the child being examined is cheaper than the node in the queue
            if( (*qIt).strBoard == child->strBoard && (*qIt).getCost() > child->getCost()){
                //State already exists, so theoretically this should be the only insertion (1 for 1 swap, only one state can exist at one time)
                exists = true;
                //erase returns an iterator to the next position in the set
                qIt = stateQueue.erase(qIt);
                //COME BACK HERE TO TEST FOR EFFICIENCY
                //Might be a problem if next in the queue has same fCost
                cout<<"\nSwapped from Queue, foudn the same";
                stateQueue.insert(node(*child));
                   
            } else {
                qIt++;
            }
        }
        //State is a new state
        if(!exists){
            //Add to queue
            stateQueue.insert(node(*child));
        }

        
        delete child;
    }



};
#endif
#ifndef pds_vis_strtict_H
#define pds_vis_strtict_H
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
#include <stack>
#include <unordered_set>

using namespace std;

class PDSSL {
    private:
    class node : public Puzzle{
        public:
        node(const node &p):Puzzle(p){}; //Constructor
        node(string const elements, string const goal):Puzzle(elements,goal){};
        bool operator> ( const node& rhs) const{
	        return this->getHCost() > rhs.getHCost();
        }

    };



    stack<node> stateQueue;
    unordered_set<std::string> visited;
    size_t maxQLen;
    string path;
    string init;
    string goal;
    int stateExpansions;
    int maxDepth;


    //Hasnt been implemented, just a suggestion for reduction of code repetition
    void pushChild(node* child, node* curr){
        child->setDepth(curr->getDepth()+1);
        //moving to stack This is mostly constant time.
        if(visited.count(child->toString()) == 0 && child->getDepth() < maxDepth) { 
            stateQueue.push(node(*child));
            visited.insert(child->toString());
        }
        delete child;
    }

    

    public:
    //set up the base variables.
    PDSSL(string start, string goal):maxQLen{0}, path{""},goal{goal}, init{start}, stateExpansions{0}, maxDepth{1}{
        
    }

    string getPath(){
        return path;
    }
    int getStateExpansions(){
        return stateExpansions;
    }
    size_t getMaxQLen() {
        return maxQLen;
    }
    void search(){
        node curr = node(init, goal);
        int heuristic = manhattanDistance;
        string nl = "\n";
        //1.Initialize Q with search node (s) as only entry
        stateQueue.push(curr);
        visited.insert(init);
        int step = 1;
        
        for(;; maxDepth += step){
            while(!stateQueue.empty()){
            
                //2.If Q is empty, fail. Otherwise pick a node from Q
                curr = stateQueue.top();
                stateQueue.pop();
                //3. IF state is goal, return it otherwise remove item from queue
                if (curr.toString() == goal) { path = curr.getPath(); return; }
                if (curr.getDepth()+1 == maxDepth) continue;
                ++stateExpansions;
                //4.Find all the decendants of the state N (not visited) + create all one step extensions of N
                if(curr.canMoveLeft()) {
                    node* child = (node*)curr.moveLeft();
                    child->setDepth(curr.getDepth()+1);
                    //moving to stack This is mostly constant time.
                    if(visited.count(child->toString()) == 0 && child->getDepth() < maxDepth) { 
                        stateQueue.push(node(*child));
                        visited.insert(child->toString());
                    }
                    delete child;
                }
                if(curr.canMoveUp()) {
                    node* child = (node*)curr.moveUp();
                    child->setDepth(curr.getDepth()+1);
                    //moving to stack This is mostly constant time.
                    if(visited.count(child->toString()) == 0 && child->getDepth() < maxDepth) { 
                        stateQueue.push(node(*child));
                        visited.insert(child->toString());
                    }
                    delete child;

                }
                if(curr.canMoveRight()) {
                    node* child = (node*)curr.moveRight();
                    child->setDepth(curr.getDepth()+1);
                    //moving to stack This is mostly constant time.
                    if(visited.count(child->toString()) == 0 && child->getDepth() < maxDepth) { 
                        stateQueue.push(node(*child));
                        visited.insert(child->toString());
                    }
                    delete child;

                } 
                if(curr.canMoveDown()) {
                    node* child = (node*)curr.moveDown();
                    child->setDepth(curr.getDepth()+1);
                    //moving to stack This is mostly constant time.
                    if(visited.count(child->toString()) == 0 && child->getDepth() < maxDepth) { 
                        stateQueue.push(node(*child));
                        visited.insert(child->toString());
                    }
                    delete child;

                } 
                
                
                
                // cout<<"Q Len: "<<stateQueue.size()<<"\n";
                //5. Add extended paths to the Q; Add all children to visited
                maxQLen = std::max(maxQLen, stateQueue.size());
                //6.Go to step 2
            
            }
            //reset visited
            visited = unordered_set<std::string>();
            //reset states
            stateQueue = stack<node>();
            //set curr
            node curr = node(init, goal);
            stateQueue.push(curr);
            visited.insert(init);
            
        }

    }



   
   
};
#endif
// int main() {
    
//     string const initialState = "123456780";
//     string const goalState = "087654321"; 
//     int numOfStateExpansions = 0;
//     int maxQLength = 0;
//     string moves = "";

//     BFV item = BFV(initialState, goalState);
//     item.search();
//     moves = item.getPath();
//     cout<<"------------------------\n";
//     cout<<"Init: "<<initialState<<"\n";
//     cout<<"Goal: "<<goalState<<"\n";
//     cout<<"State expansions: "<<item.getStateExpansions()<<"\n";
//     cout<<"Q Length: "<<item.getMaxQLen()<<"\n";
//     cout<<"Moves: "<<moves<<"\n";
//     cout<<"------------------------\n";




// }

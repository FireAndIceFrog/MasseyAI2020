#ifndef pds_vis_NOstrtict_H
#define pds_vis_NOstrtict_H
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

class PDSNSL {
    private:
    class node : public Puzzle{
        public:
        node(const node &p):Puzzle(p){}; //Constructor
        node(string const elements, string const goal):Puzzle(elements,goal){};
        bool operator> ( const node& rhs) const{
	        return this->getHCost() > rhs.getHCost();
        }

    };
    struct visitedNode { 
    string state;
    int depth; 
  
        visitedNode(string f, int l) { 
            state = f; 
            depth = l; 
        } 
    
        bool operator==(const visitedNode& p) const   { 
            return state == p.state; 
        } 
    }; 
    
    class HashFunction { 
    public: 
    
        // We use predfined hash functions of strings 
        // and define our hash function as XOR of the 
        // hash values. 
        size_t operator()(const visitedNode& p) const
        { 
            return (hash<string>()(p.state)); 
        } 
    }; 







    stack<node> stateQueue;
    unordered_set<visitedNode, HashFunction> visited;
    size_t maxQLen;
    string path;
    string init;
    string goal;
    int stateExpansions;
    int maxDepth;
    public:
    //set up the base variables.
    PDSNSL(string start, string goal):maxQLen{0}, path{""},goal{goal}, init{start}, stateExpansions{0}, maxDepth{1}{
        
        
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
        visitedNode vis = visitedNode(init, 0);
        int heuristic = manhattanDistance;
        string nl = "\n";
        //1.Initialize Q with search node (s) as only entry
        stateQueue.push(curr);
        visited.insert(vis);
        int step = 1;
        
        for(;; maxDepth += step){
            while(!stateQueue.empty()){
            
                //2.If Q is empty, fail. Otherwise pick a node from Q
                curr = stateQueue.top();
                stateQueue.pop();
                //3. IF state is goal, return it otherwise remove item from queue
                if (curr.toString() == goal) { path = curr.getPath(); return; }
                if (curr.getDepth()+1 >= maxDepth) continue;
                ++stateExpansions;
                //4.Find all the decendants of the state N (not visited) + create all one step extensions of N
                if(curr.canMoveLeft()) {
                    node* child = (node*)curr.moveLeft();
                    child->setDepth(curr.getDepth()+1);
                    //moving to stack This is mostly constant time.
                    vis = visitedNode(child->toString(), child->getDepth());
                    if(visited.count(vis) == 0 && child->getDepth() < maxDepth ) { 
                        stateQueue.push(node(*child));
                        visited.insert(vis);
                    } else if ((*(visited.find(vis))).depth > vis.depth  && child->getDepth() < maxDepth){
                        visited.erase(visited.find(vis));
                        visited.insert(vis);
                        stateQueue.push(node(*child));
                    } 
                    delete child;
                }
                if(curr.canMoveUp()) {
                    node* child = (node*)curr.moveUp();
                    child->setDepth(curr.getDepth()+1);
                    //moving to stack This is mostly constant time.
                    vis = visitedNode(child->toString(), child->getDepth());
                    if(visited.count(vis) == 0 && child->getDepth() < maxDepth) { 
                        stateQueue.push(node(*child));
                        visited.insert(vis);
                    }else if ((visited.find(vis))->depth > vis.depth  && child->getDepth() < maxDepth){
                        visited.erase(visited.find(vis));
                        visited.insert(vis);
                        stateQueue.push(node(*child));
                    }
                    delete child;

                }
                if(curr.canMoveRight()) {
                    node* child = (node*)curr.moveRight();
                    child->setDepth(curr.getDepth()+1);
                    //moving to stack This is mostly constant time.
                    vis = visitedNode(child->toString(), child->getDepth());
                    if(visited.count(vis) == 0 && child->getDepth() < maxDepth) { 
                        stateQueue.push(node(*child));
                        visited.insert(vis);
                    }else if ((*(visited.find(vis))).depth > vis.depth  && child->getDepth() < maxDepth){
                        visited.erase(visited.find(vis));
                        visited.insert(vis);
                        stateQueue.push(node(*child));
                    }
                    delete child;

                } 
                if(curr.canMoveDown()) {
                    node* child = (node*)curr.moveDown();
                    child->setDepth(curr.getDepth()+1);
                    //moving to stack This is mostly constant time.
                    vis = visitedNode(child->toString(), child->getDepth());
                    if(child->getDepth() < maxDepth){
                        if(visited.count(vis) == 0 ) { 
                            stateQueue.push(node(*child));
                            visited.insert(vis);
                        }else if ((*(visited.find(vis))).depth > vis.depth ){
                            visited.erase(visited.find(vis));
                            visited.insert(vis);
                            stateQueue.push(node(*child));
                        }
                    }
                    delete child;

                } 
                
                
                
                // cout<<"Q Len: "<<stateQueue.size()<<"\n";
                //5. Add extended paths to the Q; Add all children to visited
                maxQLen = std::max(maxQLen, stateQueue.size());
                //6.Go to step 2
            
            }
            //reset visited
            visited.clear();
            //reset states
            stateQueue = stack<node>();
            //set curr
            curr = node(init, goal);
            vis = visitedNode(init, 0);
            stateQueue.push(curr);
            visited.insert(vis);
            
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

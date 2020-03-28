
#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>

#include "PDS.cpp"
#include <thread>

#include <fstream>

using namespace std;

class PDFS: public PDS {
    protected:
    int maxDepth;

    
    
    public:
    PDFS():PDS(){  };
    //set the init state, return this
    //1.Initialize Q with search node (s) as only entry (already implemented)
    //2.If Q is empty, fail. Otherwise pick a node from Q
    //this is to be overridden by a child class - return the index to be removed, the step function will handle the removal of the item
    //3. IF state is goal, return it otherwise remove item from queue
    //4.Find all the decendants of the state N (not visited) + create all one step extensions of N
    void getChild(int ZeroIndex, int direction, stateNode* curr, stateNode &state){
        //if the states are done, skip them.
                if(statePointers[ZeroIndex][direction] == -1) return;
                //if it is in the visited list, skip it!
                string newPath = genString(ZeroIndex, statePointers[ZeroIndex][direction], curr->path);
                //if the node is visited already, dont expand.
                if((*visitedStates)[newPath].visited){  return;}
                state = createState(newPath);
                //set the state to +1 depth
                state.depth = curr->depth+1;
                //directions in the pointer nods is calculated as (positions are  DOWN RIGHT UP LEFT)
                switch (direction)
                {
                case (3):
                    //LEFT. Set direction to 'l' + parent's direction
                    state.direction = curr->direction + "L"  ;
                    break;
                case (2):
                    //UP. Set direction to 'u' + parent's direction
                    state.direction = curr->direction + "U";
                    break;
                case (1):
                    //Right. Set direction to 'r' + parent's direction
                    state.direction = curr->direction + "R";
                    break;
                case (0):
                    //DOWN. Set direction to 'd' + parent's direction
                    state.direction = curr->direction + "D" ;
                    break;
                
                default:
                    break;
                }
                
                
                //else put it in the tree
                // cout<<"Adding the state: "<<state.path<<"\n";
                
                (*visitedStates)[state.path] = createVisited();
                //add the children states to the list.
    }

    




};
// int main() {
    
//     string const initialState = "123456780";
//     string const goalState = "087654321"; 
//     int numOfStateExpansions = 0;
//     int maxQLength = 0;
//     int ultimateMaxDepth = 0;
//     string moves = "";

//     PDFS item = PDFS();
//     moves = item.start(initialState, goalState, &numOfStateExpansions,&maxQLength,  &ultimateMaxDepth );
//     cout<<"------------------------\n";
//     cout<<"Init: "<<initialState<<"\n";
//     cout<<"Goal: "<<goalState<<"\n";
//     cout<<"State expansions: "<<numOfStateExpansions<<"\n";
//     cout<<"Q Length: "<<maxQLength<<"\n";
//     cout<<"Ultimate Depth: "<<ultimateMaxDepth<<"\n";
//     cout<<"Moves: "<<moves<<"\n";
//     cout<<"------------------------\n";




// }

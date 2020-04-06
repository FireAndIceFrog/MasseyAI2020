#ifndef best_first_NoVis_H
#define best_first_NoVis_H
#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <thread>

#include "bestFirst.cpp"
#include <thread>

#include <fstream>

using namespace std;

class BFV: public BF {
    protected:
    int maxDepth;
    thread stateRemoverThreads[4];
    
    
    public:
    BFV():BF(){  };
    //THis is a best-first with a closed list.
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
                int cost = manhattanH(this->initState, this->goalState);
                //get a list of the returnables.

                if ((*visitedStates)[newPath].visited ) return;
                else  (*visitedStates)[newPath] = createVisited(0,cost);
                
                
                state = createState(newPath,0,cost);
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
                
                
                // cout<<"Adding the state: "<<state.path<<"\n";
    }

    




};
#endif
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

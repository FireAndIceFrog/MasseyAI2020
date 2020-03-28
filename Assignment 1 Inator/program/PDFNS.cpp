
#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <thread>
#include <ctime>
#include <fstream>
#include "PDS.cpp"



using namespace std;

class PDFNS: public PDS {
    protected:
    int maxDepth;

    
    
    public:
    PDFNS():PDS(){

    };
    //set the init state, return this
    //1.Initialize Q with search node (s) as only entry (already implemented)

    //2.If Q is empty, fail. Otherwise pick a node from Q
    //this is to be overridden by a child class - return the index to be removed, the step function will handle the removal of the item
    //3. IF state is goal, return it otherwise remove item from queue
    //4.Find all the decendants of the state N (not visited) + create all one step extensions of N
    void getChild(int ZeroIndex, int direction, stateNode* curr, stateNode& state){
        //if the states are done, skip them.
                if(statePointers[ZeroIndex][direction] == -1) return;
                string pathText = genString(ZeroIndex, statePointers[ZeroIndex][direction], curr->path);
                //if it is in the visited list, skip it!
                if((*visitedStates)[pathText].visited && (*visitedStates)[pathText].depth<=curr->depth+1) return;
                state = createState(pathText);
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
                
                
                
                if((*visitedStates)[state.path].depth>state.depth ){
                    //if the current state is shallower than the current visited, set visited to current depth & add to list
                    (*visitedStates)[state.path].depth=state.depth; 
                    
                }  else {
                    //create a new visited node of current depth.
                    (*visitedStates)[state.path] = createVisited(state.depth);
                }
    }
    

            
    
    //5. Add extended paths to the Q; Add all children to visited
    
    //6.Go to step 2
    

};
// int main() {
    
//     string const initialState = "041532786";
//     string const goalState = "123456780"; 
//     int numOfStateExpansions = 0;
//     int maxQLength = 0;
//     int ultimateMaxDepth = 0;
//     string moves = "";

//     PDFNS item = PDFNS();
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

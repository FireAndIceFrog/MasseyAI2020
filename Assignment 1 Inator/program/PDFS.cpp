
#include "hashTable.h"
#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>

#include "state.cpp"
#include <thread>

#include <fstream>



class PDFS: public state {
    protected:
    int maxDepth;

    
    
    public:
    PDFS& setMaxDepth(int maxDepth){this->maxDepth = maxDepth; return *this; }
    int getMaxDepth() {return maxDepth; }
    PDFS():state(){ maxDepth = 0;  };
    //set the init state, return this
    //1.Initialize Q with search node (s) as only entry (already implemented)

    //2.If Q is empty, fail. Otherwise pick a node from Q
    //this is to be overridden by a child class - return the index to be removed, the step function will handle the removal of the item
    int selectItem(int depth, int cost){
        int size = states->size();
        if(size <= 0) {
            return -1;
        } else {
            //because we are working with a vector -> return the max value (for optimization!) 
            //size of vector with 1 element = 1. index of that element is 0.
            return size-1;
        }
    }
    //3. IF state is goal, return it otherwise remove item from queue
    //4.Find all the decendants of the state N (not visited) + create all one step extensions of N
    void getNode(int ZeroIndex, int direction, stateNode* curr, stateNode &state){
        //if the states are done, skip them.
                if(statePointers[ZeroIndex][direction] == -1) return;
                //if it is in the visited list, skip it!
                string newPath = genString(ZeroIndex, statePointers[ZeroIndex][direction], curr->path);
                //if the node is visited already, dont expand.
                if((*visitedStates)[newPath].visited){  return;}
                state = createState(newPath);
                //set the state to +1 depth
                state.depth = curr->depth+1;
                //directions in the pointer nods is calculated as (positions are  LEFT UP RIGHT DOWN)
                switch (direction)
                {
                case (0):
                    //LEFT. Set direction to 'l' + parent's direction
                    state.direction = curr->direction + "L"  ;
                    break;
                case (1):
                    //UP. Set direction to 'u' + parent's direction
                    state.direction = curr->direction + "U";
                    break;
                case (2):
                    //Right. Set direction to 'r' + parent's direction
                    state.direction = curr->direction + "R";
                    break;
                case (3):
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
    vector<stateNode>* getChildNodes(stateNode curr, bool* passed){
        int pos = curr.path.find("0");
        thread threadPool[4];
        stateNode stateManager[4];
        vector<stateNode>* childStates = new vector<stateNode>();
        //only expand if the maxDepth > current depth, else ignore this node.
        if(curr.depth+1 < maxDepth){
            *passed = true;
            stateNode defaultState = stateNode();
            defaultState.path = "";
            for (int i = 0; i < 4; ++i){
                stateManager[i] = defaultState;
                threadPool[i] = thread(&PDFS::getNode,this,pos, i, &curr, ref(stateManager[i]));
                threadPool[i].join();
            }
            for (int i = 0; i < 4; ++i){
                
                // stateManager[i] = nullptr;
                // getNode(pos, i, curr, stateManager[i]);
                if(stateManager[i].path == defaultState.path) continue;
                childStates->push_back(stateManager[i]); 
                
            }
        } else *passed = false;
        return childStates;

            
    }
    //5. Add extended paths to the Q; Add all children to visited
    // The step function will handle selecting, removal and deletion from the list. 
    
    stateNode* step(bool* passed){
        stateNode curr;
        int index = selectItem(0,0);
        //if states is empty -> return null
        if(index < 0) throw "Ran out of expandable nodes";
        
        this->enqueue++;
        //check for goal
         if((*states)[index].path == goalState)  return &(*states)[index]; 
        //otherwise remove from the list
        curr = (*states)[index];
        states->pop_back();
        //get all the children nodes, return false if outside depth range
        vector<stateNode>* children = getChildNodes(curr, passed);
        
    
        while (!children->empty()){
            states->push_back((*children)[children->size()-1]);
            children->pop_back();
        }
        delete children;


        *passed = (states->size()!=0);
        this->maxQueueSize = this->max(this->maxQueueSize, states->size());

        return nullptr;
    }


    //6.Go to step 2
    //this will handle any extre features that the list will control.
    string start(string const initialState, string const goalState, 
        int *numOfStateExpansions, int*maxQLength,  int *ultimateMaxDepth){
        string moves;
        maxDepth = 2;
        int step = 5;
        int currentDepth = 0;
        bool passed = true;
        this->setInitState(initialState).setGoalState(goalState);
        stateNode* finalState = nullptr;

        while (finalState == nullptr){
            if(!passed){
                maxDepth += step;
                this->setInitState(initialState);
                this->setGoalState(goalState);
                passed = true;
                
            }
            string str;
            try {
                finalState = this->step(&passed) ;
            }
            catch(const char* e)
            {
                std::cerr << e << '\n';
                break;
            }
            
        }
        //set the returnables.
        *numOfStateExpansions = this->enqueue;
        *maxQLength = this->maxQueueSize;
        *ultimateMaxDepth = finalState->depth;
        moves = finalState->direction;
        return moves;
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

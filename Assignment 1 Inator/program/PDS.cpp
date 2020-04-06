#ifndef PDS_H
#define PDS_H

#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>

#include "state.cpp"
#include <thread>

#include <fstream>

using namespace std;

class PDS: public state {
    protected:
    int maxDepth;

    
    
    public:
    PDS& setMaxDepth(int maxDepth){this->maxDepth = maxDepth; return *this; }
    int getMaxDepth() {return maxDepth; }
    PDS():state(){ maxDepth = 0;  };
    //set the init state, return this
    //1.Initialize Q with search node (s) as only entry (already implemented)

    //2.If Q is empty, fail. Otherwise pick a node from Q
    //this is to be overridden by a child class - return the index to be removed, the step function will handle the removal of the item
    int selectItem(int depth, int cost){
        int size = states->size();
        //because we are working with a vector -> return the max value (for optimization!) 
        //size of vector with 1 element = 1. index of that element is 0.
        return size-1;
        
    }
    //3. IF state is goal, return it otherwise remove item from queue
    //4.Find all the decendants of the state N (not visited) + create all one step extensions of N
    virtual void getChild(int ZeroIndex, int direction, stateNode* curr, stateNode &state){
        return;
    }
    vector<stateNode> getChildNodes(stateNode curr){
        int pos = curr.path.find("0");
        thread threadPool[4];
        stateNode stateManager[4];
        vector<stateNode> childStates =  vector<stateNode>();
        //only expand if the maxDepth > current depth, else ignore this node.
        
        stateNode defaultState = stateNode();
        defaultState.path = "";
        for (int i = 0; i < 4; ++i){
            //create a vector (used as a stack) -> DOWN->LEFT->UP->RIGHT 
            stateManager[i] = defaultState;
            threadPool[i] = thread(getChild,this,pos, i, &curr, ref(stateManager[i]));
            threadPool[i].join();
        }
        for (int i = 0; i < 4; ++i){
            //push into vector (as though it were a stack) DOWN(0)->RIGHT(1)->UP(2)->LEFT(3)
            if(stateManager[i].path == defaultState.path) continue;
            childStates.push_back(stateManager[i]); 
            
        }
        
        return childStates;

            
    }
    //5. Add extended paths to the Q; Add all children to visited
    // The step function will handle selecting, removal and deletion from the list. 
    
    stateNode* step(bool* passed){
        stateNode curr;
        int index = selectItem(0,0);
        //if states is empty -> return null
        if(index < 0) throw "Ran out of expandable nodes";
        
        
        //check for goal
         if((*states)[index].path == goalState)  return &(*states)[index]; 
        //otherwise remove from the list
        curr = (*states)[index];
        states->pop_back();
        if(curr.depth < maxDepth){
            ++enqueue;
            //get all the children nodes, return false if outside depth range
            vector<stateNode> children = getChildNodes(curr);
            
            int childrenSize = children.size()-1;
            while (!children.empty()){
                //push the children into the list; Convert the order from DOWN->RIGHT->UP->LEFT->(HEAD) to LEFT->UP->RIGHT->DOWN->(HEAD)
                states->push_back((children)[childrenSize--]);
                children.pop_back();
            }

        }
        *passed = (states->size()!=0);
        this->maxQueueSize = this->max(this->maxQueueSize, states->size());

        return nullptr;
    }


    //6.Go to step 2
    //this will handle any extre features that the list will control.
    string start(string const initialState, string const goalState, 
        int *numOfStateExpansions, int*maxQLength,  int *ultimateMaxDepth){
        string moves;
        maxDepth = 1;
        int step = 1;
        int currentDepth = 0;
        bool passed = true;
        this->setInitState(initialState).setGoalState(goalState);
        stateNode* finalState = nullptr;

        while (finalState == nullptr){
            if(!passed){
                maxDepth += step;
                this->setInitState(initialState);
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

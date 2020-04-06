#ifndef _best_first_H
#define _best_first_H

#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include "state.cpp"
#include "heuristic.cpp"
#include <thread>
#include <fstream>
using namespace std;
class BF: public state {
    protected:

    int compare(stateNode first, stateNode second){
        return first.cost == second.cost ? 0 : (first.cost<second.cost ? 1 : -1);
    }

    //-------------------------------------------------------------------Algorithm mergesort copied from Geeks for Geeks.org -------------------------------
    // Merges two subarrays of arr[]. 
    // First subarray is arr[l..m] 
    // Second subarray is arr[m+1..r] 
    //vector<stateNode>* states
    void merge(vector<stateNode>& arr, int l, int m, int r) 
    { 
        int i, j, k; 
        int n1 = m - l + 1; 
        int n2 =  r - m; 
    
        /* create temp arrays */
        vector<stateNode> L, R; 
        L = vector<stateNode>(n1);
        R = vector<stateNode>(n2);
    
        /* Copy data to temp arrays L[] and R[] */
        for (i = 0; i < n1; i++) 
            L[i] = arr[l + i]; 
        for (j = 0; j < n2; j++) 
            R[j] = arr[m + 1+ j]; 
    
        /* Merge the temp arrays back into arr[l..r]*/
        i = 0; // Initial index of first subarray 
        j = 0; // Initial index of second subarray 
        k = l; // Initial index of merged subarray 
        while (i < n1 && j < n2) 
        { 
            if (compare(L[i] , R[j]) )
            { 
                arr[k] = L[i]; 
                i++; 
            } 
            else
            { 
                arr[k] = R[j]; 
                j++; 
            } 
            k++; 
        } 
    
        /* Copy the remaining elements of L[], if there 
        are any */
        while (i < n1) 
        { 
            arr[k] = L[i]; 
            i++; 
            k++; 
        } 
    
        /* Copy the remaining elements of R[], if there 
        are any */
        while (j < n2) 
        { 
            arr[k] = R[j]; 
            j++; 
            k++; 
        } 
    } 
    
    /* l is for left index and r is right index of the 
    sub-array of arr to be sorted */
    void mergeSort(vector<stateNode>& arr, int l, int r) 
    { 
        if (l < r) 
        { 
            // Same as (l+r)/2, but avoids overflow for 
            // large l and h 
            int m = l+(r-l)/2; 
    
            // Sort first and second halves 
            mergeSort(arr, l, m); 
            mergeSort(arr, m+1, r); 
    
            merge(arr, l, m, r); 
        } 
    }
    //------------------------------------------------------------------------------end of algorithm copied-----------------------------------------------------------
    

    
    
    public:
    BF():state(){ };
    //set the init state, return this
    //1.Initialize Q with search node (s) as only entry (already implemented)

    //2.If Q is empty, fail. Otherwise pick a node from Q
    //this is to be overridden by a child class - return the index to be removed, the step function will handle the removal of the item
    int selectItem(int depth, int cost){
        int size = states->size()-1;
        //because we are working with a vector -> return the max value (for optimization!) 
        //The vector should be a prioritized list; pick the first index of the list.
        //size of vector with 1 element = 1. index of that element is 0.
        return size;
        
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
        ++enqueue;
        //get all the children nodes, return false if outside depth range
        vector<stateNode> children = getChildNodes(curr);
        
        int childrenSize = children.size()-1;
        //ofstream output;
        //output.open("output.txt", std::ios_base::app);
        //output<<"Reading node with state: "<<curr.path<<"\n";
        while (!children.empty()){
            //push the children into the list; Convert the order from DOWN->RIGHT->UP->LEFT->(HEAD) to LEFT->UP->RIGHT->DOWN->(HEAD)
            //insert according to heuristic value; if children is bigger or equal, insert to the left (meaning that the left side of tree is read first)
            vector<stateNode>::iterator it = states->end();
            //parse the array and find the position to insert at.
            
            //insert at position IT, decrement the size
            while ((*it).cost < children.back().cost && it != states->end()) --it;
            states->insert(it,children.back());
            children.pop_back();
        }

        
        *passed = (states->size()!=0);
        this->maxQueueSize = this->max(this->maxQueueSize, states->size());

        return nullptr;
    }


    //6.Go to step 2
    //this will handle any extra features that the list will control.
    string start(string const initialState, string const goalState, 
        int *numOfStateExpansions, int*maxQLength){
        string moves;
        bool passed = true;
        this->setInitState(initialState).setGoalState(goalState);
        stateNode* finalState = nullptr;

        while (finalState == nullptr){
            if(!passed){
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
        moves = finalState->direction;
        return moves;
    }
    

    

    




};
#endif
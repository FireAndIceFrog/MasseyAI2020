#ifndef _state_H
#define _state_H
#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;
class state {
        
        
        
    protected:
        int enqueue;
        int dequeue;
        int maxQueueSize;
        string genString(int origin, int end, string str){
            //function to swap two characters in a string and return the string.
            swap(str[origin], str[end]);
            return str;
        }
        int *statePointers[8];
        void setUpStatePointers(){
            //to work out direction, put (-1) as a place holder (positions are DOWN RIGHT UP LEFT)
            // 0 1 2
            // 3 4 5
            // 6 7 8
            statePointers[0] = new int[4] {3,1,-1,-1};
            statePointers[1] = new int[4] {4,2,-1,0};
            statePointers[2] = new int[4] {5,-1,-1,1};
            statePointers[3] = new int[4] {6,4,0,-1};
            statePointers[4] = new int[4] {7,5,1,3};
            statePointers[5] = new int[4] {8,-1,2,4};
            statePointers[6] = new int[4] {-1,7,3,-1};
            statePointers[7] = new int[4] {-1,8,4,6};
            statePointers[8] = new int[4] {-1,-1,5,7};
        }
        void deleteStatePointers(){
            for (int i = 0; i < 8; ++i){
                delete statePointers[i];
            }
        }
        int max(int r, int l){
            return (r<l?l:r);
        }
        struct stateNode{
            string path;
            string direction;
            int cost;
            int depth;
        } goalNode;
        struct visitedNode{
            bool visited;
            int depth;
            int cost;
        }defaultNode;
        string initState;
        string goalState;

        vector<stateNode>* states;
        map<string, visitedNode>* visitedStates;
    //function to create a simple node
    stateNode createState(string path = "", string direction = "", int depth = 0, int cost = 0 ){
        stateNode returnable = stateNode();
        returnable.path = path;
        returnable.direction = direction;
        returnable.depth = depth;
        returnable.cost = cost;
        return returnable;
    }
    visitedNode createVisited(int depth = 0, int cost = 0 ){
        visitedNode returnable = visitedNode();
        returnable.visited = true;
        returnable.depth = depth;
        returnable.cost = cost;
        return returnable;
    }
        
        
        



    public:
    state(){
            //function to remove the state. 
            //set up state pointers
            setUpStatePointers();
            //set up the returnables
            enqueue = 0;
            dequeue = 0;
            maxQueueSize = 0;
            goalState = "";
            initState = "";
            //state for the visited node
            visitedStates = new map<string, visitedNode>();
            //state for the queue.
            states = new vector<stateNode>();

        };
    ~state(){
        deleteStatePointers();
        
        delete visitedStates;
        deleteStates();
    }
    void deleteStates(){
        int i = 0;
        delete states;
        
    }
    //set the goal state, return this
    state& setGoalState(string goal){ goalState = goal; return *this;}
    //set the init state, return this
    //1.Initialize Q with search node (s) as only entry
    state& setInitState(string init){ 
        delete visitedStates;
        deleteStates();
        //state for the visited node
        visitedStates = new map<string, visitedNode>();
        //state for the queue.
        states = new vector<stateNode>();
        //once we have the visited states
        (*visitedStates)[init] = createVisited();
        initState = init; 
        states->push_back(createState(init));
        return *this;
    }
    //2.If Q is empty, fail. Otherwise pick a node from Q
    //this is to be overridden by a child class - return the index to be removed, the step function will handle the removal of the item
    int selectItem(int depth, int cost);
    //3. IF state is goal, return it otherwise remove item from queue
    //4.Find all the decendants of the state N (not visited) + create all one step extensions of N
    vector<stateNode*> getChildNodes(stateNode* curr);
    //5. Add extended paths to the Q; Add all children to visited
    // The step function will handle selecting, removal and deletion from the list. 
    stateNode* step();

    //6.Go to step 2
    //this will handle any extre features that the list will control.
    stateNode* start();
    

    

    




};
#endif
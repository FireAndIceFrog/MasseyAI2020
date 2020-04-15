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

    protected:

    unordered_set<string> local_list;

    public:
        //Constructor: Takes a constant referance to a node and copies
        node(const node &p):Puzzle(p){
            this->local_list = p.local_list;
        }; 

        node(const Puzzle *p):Puzzle(*p){
            this->local_list = unordered_set<string>();
            delete p;
        }
        //Constructor: Constructs from Initial given state
        node(string const& elements, string const& goal):Puzzle(elements,goal){
            local_list.insert(strBoard);
        };

        unordered_set<string> getLocal(){
            return local_list;
        }

        void setLocal(unordered_set<string> list){
            local_list = list;
        }
        
        bool existsInLocal(const string& state){
            //cout << "Checking in local\n";
            return local_list.count(state) > 0;
        }

        //Overriding the updateCost func
        void updateCost(int hFunction) override{
            //For A* Strict expanded List, Total cost is Path Length + Heuristic
            //For our example, Each path moves the Blank tile by One Space
            //Therefore, PathLength is equal to the Number of moves which is equal to depth
            //Cost = depth + heuristic value
            cost = h(hFunction) + depth;
        }

//        bool cmp(const node &a, const node &b){
//            return a.cost > b.cost;
//        }

        //Less than Operator Overload for the Priority Queue
        bool operator< ( const node& rhs) const{
	        return this->getCost() < rhs.getCost();
        }
    };

    //Queue
    vector<node> stateQueue;

    //Expanded list
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
        //cout<<"Node is made"<< endl;
        curr.getLocal().insert(init);
        curr.updateCost(heuristic);
        stateQueue.push_back(curr);

        make_heap(stateQueue.begin(), stateQueue.end());

        int sQSize = 0;


        while(!stateQueue.empty()){
        //while(!sQSize == 3){
            
            //sQSize++;


        // (2) If Q is empty, fail.  Else, pick some search node N from Q.

            //cout<<"Looking at curr node,  ";
            curr = node((stateQueue.front()));
            //cout <<"Cost of curr = " << curr.getCost() << endl;
            //curr.printBoard();
            

            
        // (3) Check if N is goal State. 
        //     If it is, return N
        maxQLen = std::max(maxQLen, stateQueue.size());
            if (curr.strBoard == goal) { 
                path = curr.getPath(); 
                //cout << "\n\nFound Path!!\n\n";
                return; 
            }

            stateExpansions++;
        //     If not, Take N from Q and Expand
            pop_heap(stateQueue.begin(),stateQueue.end());
            stateQueue.pop_back();
            //cout <<"Pop Queue" << endl;
        // (4) If State N is already in Expanded List, Discard and move to step 2
            //If Current State exists in Expanded, will return greater than 0
            if(expanded.count(curr.strBoard) != 0){
                //State already exists, Skip back to Step 2
                //cout<<"\nAlready exists, discard node\n";
                continue;
            }
            //Now add to expanded list
            expanded.insert(curr.strBoard);

        // (5) Find all children of N (Not in expanded) and create them
        // (6) Add all the extended paths, if Child already in Q, keep Smaller F Cost
            if(curr.canMoveLeft()) {
                //cout <<"Successfull left child:" << endl;
                node child = node(curr.moveLeft());
                //Checks if the state of the Child exists in the local list of the current
                if(!curr.existsInLocal(child.strBoard)){
                    child.setLocal(curr.getLocal());
                    child.getLocal().insert(child.strBoard);
                    pushChild(child);
                }
            }
            if(curr.canMoveUp()) {
                //cout <<"Successfull up child:" << endl;
                node child = node(curr.moveUp());
                //Checks if the state of the Child exists in the local list of the current
                if(!curr.existsInLocal(child.strBoard)){
                    child.setLocal(curr.getLocal());
                    child.getLocal().insert(child.strBoard);
                    pushChild(child);
                }

            }
            if(curr.canMoveRight()) {
                //cout <<"Successfull right child:" << endl;
                node child = node(curr.moveRight());
                //Checks if the state of the Child exists in the local list of the current
                if(!curr.existsInLocal(child.strBoard)){
                    child.setLocal(curr.getLocal());
                    child.getLocal().insert(child.strBoard);
                    pushChild(child);
                }
            } 
            if(curr.canMoveDown()) {
                //cout <<"Successfull down child:" << endl;
                node child = node(curr.moveDown());
                //Checks if the state of the Child exists in the local list of the current
                if(!curr.existsInLocal(child.strBoard)){
                    child.setLocal(curr.getLocal());
                    child.getLocal().insert(child.strBoard);
                    pushChild(child);
                }
            } 
            
            
            
        
            push_heap(stateQueue.begin(),stateQueue.end());
            sort_heap(stateQueue.begin(),stateQueue.end());
            // (7) Go to 2
            

        }

    }
    //Insert a Child into the queue correctly and update the expanded list
    void pushChild(node child){

        
        child.updateCost(heuristic);
        //cout <<"-------- In Child ----------\nChild Cost: " << child.getCost()<< endl;
        //child.printBoard();
        vector<node>::iterator qIt;
        qIt = stateQueue.begin();
        //Check if the Child Node's State already exists in the Queue
        while(qIt != stateQueue.end()){
            //cout <<"Checking queue for doubles..";
            // If the states are the same and If the child being examined is cheaper than the node in the queue
            if( (*qIt).strBoard == child.strBoard){
                //cout << "\nFound Duplicate State!";
                if((*qIt).getCost() > child.getCost()){
                    //cout <<"  And it has lower cost" << endl;
                    //State already exists, so theoretically this should be the only insertion (1 for 1 swap, only one state can exist at one time)
                    //erase returns an iterator to the next position in the set
                    qIt = stateQueue.erase(qIt);
                    //COME BACK HERE TO TEST FOR EFFICIENCY
                    //Might be a problem if next in the queue has same fCost
                    //cout<<"\nSwapped from Queue, found the same";
                    stateQueue.push_back(child);
                    //cout << "Added\n-----------------------\n";
                    //delete child;
                    return;
                } else {
                    //cout << "  Does not have lower Cost!\n----------------------\n" << endl;
                    //delete child;
                    return;
                }
                   
            } else {

                qIt++;
            }
        }
        
        //State is a new state
        //Add to queue
        //cout <<" No duplicates found..." << endl;
        stateQueue.push_back(child);
        //cout <<"Successfull add to queun------------------------\n" << endl;    
        //delete child;
        return;
    }



};


#endif
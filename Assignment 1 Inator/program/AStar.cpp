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
            local_list = p.local_list;
        }; 
        //Constructor: Constructs from Initial given state
        node(string const& elements, string const& goal):Puzzle(elements,goal){

            local_list.insert(strBoard);
        };

        void addToLocal(const string& state){
            local_list.insert(state);
        }
        
        bool existsInLocal(const string& state){
            cout << "Checking in local\n";
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

    //vector<node> &iterableQueue = Container(stateQueue);
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
        cout<<"Node is made"<< endl;
        stateQueue.push_back(curr);
        make_heap(stateQueue.begin(), stateQueue.end());

        int sQSize = 0;


        while(!stateQueue.empty()){




        // (2) If Q is empty, fail.  Else, pick some search node N from Q.

            cout<<"Looking at front node" << endl;
            curr = node((stateQueue.front()));
            cout <<"Successful, Cost of curr = " << curr.getCost() << endl;
            

            
        // (3) Check if N is goal State. 
        //     If it is, return N
            if (curr.strBoard == goal) { 
                path = curr.getPath(); 
                cout << "\n\nFound Path!!\n\n";
                return; 
            }

            ++stateExpansions;
        //     If not, Take N from Q and Expand
            pop_heap(stateQueue.begin(),stateQueue.end());
            cout <<"Successfull 2" << endl;
        // (4) If State N is already in Expanded List, Discard and move to step 2
            //If Current State exists in Expanded, will return greater than 0
            if(expanded.count(curr.getPath()) != 0){
                //State already exists, Skip back to Step 2
                cout<<"\nAlready exists, discard node\n";
                continue;
            }
            //Now add to expanded list
            expanded.insert(curr.strBoard);

        // (5) Find all children of N (Not in expanded) and create them
        // (6) Add all the extended paths, if Child already in Q, keep Smaller F Cost
            if(curr.canMoveDown()) {
                cout <<"Successfull down" << endl;
                node* child = (node*)curr.moveDown();
                if(!curr.existsInLocal(child->strBoard)){
                    pushChild(child);
                    
                }
            } 
            if(curr.canMoveRight()) {
                cout <<"Successfull right" << endl;
                node* child = (node*)curr.moveRight();
                if(!curr.existsInLocal(child->strBoard)){
                    pushChild(child);
                    cout <<"Successfull push" << endl;
                }
            } 
            if(curr.canMoveUp()) {
                cout <<"Successfull up" << endl;
                node* child = (node*)curr.moveUp();
                if(!curr.existsInLocal(child->strBoard)){
                    pushChild(child);
                }

            }
            if(curr.canMoveLeft()) {
                cout <<"Successfull left" << endl;
                node* child = (node*)curr.moveLeft();
                if(!curr.existsInLocal(child->strBoard)){
                    pushChild(child);
                }
            }
        
            push_heap(stateQueue.begin(),stateQueue.end());
            sort_heap(stateQueue.begin(),stateQueue.end());
        // (7) Go to 2

        }

    }
    //Insert a Child into the queue correctly and update the expanded list
    void pushChild(node* child){

        
        child->updateCost(heuristic);
        cout <<"Successfull 5" << endl;
        vector<node>::iterator qIt;
        qIt = stateQueue.begin();
        cout <<"Successfull 6" << endl;
        //Check if the Child Node's State already exists in the Queue
        while(qIt != stateQueue.end()){
            cout <<"Checking queue for doubles..";
            // If the states are the same and If the child being examined is cheaper than the node in the queue
            if( (*qIt).strBoard == child->strBoard){
                cout << "\nFound Duplicate State!";
                if((*qIt).getCost() > child->getCost()){
                    cout <<"  And it has lower cost" << endl;
                    //State already exists, so theoretically this should be the only insertion (1 for 1 swap, only one state can exist at one time)
                    //erase returns an iterator to the next position in the set
                    qIt = stateQueue.erase(qIt);
                    //COME BACK HERE TO TEST FOR EFFICIENCY
                    //Might be a problem if next in the queue has same fCost
                    cout<<"\nSwapped from Queue, found the same";
                    node temp = node(*child);
                    temp.addToLocal(temp.strBoard);
                    stateQueue.push_back(temp);
                    cout << "Added\n";
                    //delete child;
                    return;
                } else {
                    cout << "  Does not have lower Cost!" << endl;
                    //delete child;
                    return;
                }
                   
            } else {

                qIt++;
            }
        }
        
        //State is a new state
        //Add to queue
        node temp = node(*child);
        cout <<" No duplicates found... \nSuccessfull 7" << endl;
        temp.addToLocal(temp.strBoard);
        cout <<"Successfull 8" << endl;
        stateQueue.push_back(temp);
        cout <<"Successfull 9" << endl;    
        //delete child;
        return;
    }



};


#endif
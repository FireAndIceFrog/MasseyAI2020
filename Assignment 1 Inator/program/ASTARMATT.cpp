#ifndef ASTAR_H
#define ASTAR_H
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

using namespace std;

class AStar {
    private:
    class node : public Puzzle{
        public:
        node(const node &p):Puzzle(p){
            this->visited = p.visited;
        }; 
        //Constructor
        node(const Puzzle *p):Puzzle(*p){
            this->visited = unordered_set<std::string>();
            this->depth++;
            delete p;
        };
        node(const Puzzle *p, unordered_set<std::string> newVis):node(p){
            this->visited = newVis;
        }

        node& setVisited(unordered_set<std::string> vis){ this->visited = vis; return *this;}

        node(string const elements, string const goal):Puzzle(elements,goal){ };

        unordered_set<std::string> visited;

        bool operator> ( const node& rhs) const{
            
	        return this->getCost() > rhs.getCost();
        }
        bool operator>= ( const node& rhs) const{
            
	        return this->getCost() >= rhs.getCost();
        }
        bool operator==(const node& rhs) const {
            return this->strBoard == rhs.strBoard;
        }

        void updateCost(int hFunction){
            cost = h(hFunction) + depth;
        }

    };


    vector<node> stateQueue;
    unordered_set<std::string> expanded;
    size_t maxQLen;
    string path;
    string init;
    string goal;
    int stateExpansions;
    int heuristic;
    public:
    //set up the base variables.
    AStar(string start, string goal):maxQLen{0}, path{""},goal{goal}, init{start}, stateExpansions{0}{
        
    }
    void setHeuristic(int Heuristic){ this->heuristic = Heuristic; }

    string getPath(){
        return path;
    }
    int getStateExpansions(){
        return stateExpansions;
    }
    size_t getMaxQLen() {
        return maxQLen;
    }
    void insert( node value ) {
        //function to insert to vector backwards
        if(!remove_elms(value)) return;
        //handle the local lists
        if(value.visited.count(value.strBoard) != 0 ) return;
        //if it has already been expanded, dont add it!
        if(expanded.count(value.strBoard) != 0) return;
        
        value.visited.insert( value.strBoard);
        // find proper position in descending order
        stateQueue.push_back( value ); // insert backwards
        cout<<"<------"<<value.strBoard<<endl;
    }
    bool remove_elms( node value ){
        //function to remove elements with greater path costs than value
        bool insertable = true;
        for ( vector<node>::iterator begin = stateQueue.begin(); begin != stateQueue.end(); ) {
            if (*begin == value && ((*begin) >= value)) { 
                //if the States are the same and the cost is greate for the iterator, remove the iterator
                begin = stateQueue.erase(begin);
            }else if(*begin == value && !((*begin) >= value) ){
                //if the states are there but its SMALLER than the current one; do not insert.
                insertable = false;
                ++begin;
            } else {
                ++begin;
            } 
        }
        return insertable;
    }
    

    void printQueue(){
        cout<<"Printing State Queue: \n";
        for( node item : stateQueue){
            cout<<"( "<< item.strBoard<<","<<item.getCost()<<" )";
        }
        cout<<"\n";


    }

    void search(){
        //create the initial state and current items
        // 1. Initialise Q with search node (S) as only entry; set Expanded = egg
        auto comparator = std::greater_equal<node>();
        node curr = node (init, goal);
        
        curr.setDepth(0);
        curr.updateCost(heuristic);
        make_heap( stateQueue.begin(), stateQueue.end(),  comparator );
        for(insert(curr); !stateQueue.empty();  maxQLen = std::max(maxQLen, stateQueue.size())){
            printQueue();
            // 2. If Q is empty, fail.  Else, pick some search node N from Q.
            pop_heap(stateQueue.begin(), stateQueue.end(),  comparator);
            curr = stateQueue.back();
            cout<<"Node: "<<curr.strBoard<<endl;
            stateQueue.pop_back();
            stateExpansions++;
            // 3. If state (N) is a goal, return N (we’ve reached the goal).
            // 4. (Otherwise) Remove N from Q.
            if (curr.strBoard == goal) { path = curr.getPath(); return; }
            // 5. If state (N) in Expanded, go to Step 2; otherwise, add state (N) to Expanded List.
            if (expanded.count(curr.strBoard) != 0 ) continue;
            expanded.insert(curr.strBoard);
            // 6. Find all the children of state(N) (Not in Expanded) and create all the one-step extensions of N to each descendant.
            // 7. Add all the extended paths to Q. If descendant state already in Q, keep only shorter path to state in Q.
            if(curr.canMoveLeft()) {
                node child =  node(curr.moveLeft()).setVisited(curr.visited);
                child.updateCost(heuristic);
                insert(child);
                
            }
            if(curr.canMoveUp()) {

                node child =  node(curr.moveUp()).setVisited(curr.visited);
                child.updateCost(heuristic);
                insert(child);

            }
             if(curr.canMoveRight()) {
                node child =  node(curr.moveRight()).setVisited(curr.visited);
                child.updateCost(heuristic);
                insert(child);

            }
            if(curr.canMoveDown()) {
                node child =  node(curr.moveDown()).setVisited(curr.visited);
                child.updateCost(heuristic);
                insert(child);

            } 
            
            
            
            push_heap(stateQueue.begin(), stateQueue.end(),  comparator);
             
            
            
            // 8. Go to Step 2.
        }
    }



   
   
};



int main() {
    AStar algorithm = AStar("041532786", "123456780");
    algorithm.setHeuristic(manhattanDistance);
    cout<<"Start\n";
    algorithm.search();
    cout<<"Path: "<<algorithm.getPath()<<endl;
    cout<<"Max Q Length: "<<algorithm.getMaxQLen()<<endl;
    cout<<"State Expansions: "<<algorithm.getStateExpansions()<<endl;
}
#endif
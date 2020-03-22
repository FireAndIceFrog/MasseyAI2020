#include "state.h"
#include "hashTable.h"
class PDState : public stateFactory{
    
    public:
    dict<bool>  visitedStates = dict<bool>(false);
    int currentDepth;
    int maxDepth;
    string goalState;
    PDState(string initState, int maxDepth):stateFactory(initState){
        currentDepth = 0;
        this->maxDepth = maxDepth;
    }
    void setGoal(string str){
        goalState = str;
    }
    
    
    bool convertToData(stack<stateData*>* newStates){
        int i = 0; 
        stack<stateData*>* tempStates = new stack<stateData*>();
        currentDepth = states.top()->depth+1;
        for (int i = 0; i <= newStates->size(); ++i){
            string index = newStates->top()->state;
            if(index == goalState){
                cout<<"FOUND GOAL!\n\n--------------\n\n"<<goalState<<"\n\n";
                return true;
            }
            if(visitedStates[index]){
                delete (newStates->top());
            } else {
               //visitedStates[index] = true;

                newStates->top()->depth = currentDepth;
                tempStates->push(newStates->top());
            }
            newStates->pop();
            
        }
        delete newStates;
        replace(0, tempStates);
        return false;
        
    }
    string top(){
        return states.top()->state;
    }
    bool step(){
        int i = 0;
        if (states.empty()) return false;
        while(states.top()->depth > maxDepth){
            cout<<"Current step is out of bounds! Deleting!\n------------------------\n";
            delete states.top(); 
            states.pop();
            cout<<"<---- is states empty? "<<(states.empty() == true)<<"\n";
            if(states.empty()){
                
                cout<<"States is empty!\n";
                return false;
            }
        }
        if(states.empty()) return false;
        if(states.top()->depth <= maxDepth){
            
            stack<stateData*>* newStateData = getNextStates(top());
            if (convertToData(newStateData)){ return true;};
            cout<<"Visited dictionary size: "<<visitedStates.size()<<"\n";
        } else {
            cout<<"No items in stack?\n";
            return false;
            
        }
        cout<<"Current States: \n";
        stack<stateData * > currStates = states;
        i = currStates.size();
        while ( i > 0){
            cout<<"<-- Current State: "<<currStates.top()->state<<"\n";
            currStates.pop();
            --i;
        }
        return false;
        

    }
    bool isEmpty(){
        return states.empty();
    }



};

int main(){
    //string progressiveDeepeningSearch_VisitedList
    //(string const initialState, string const goalState, int &numOfStateExpansions, 
    //int& maxQLength, float &actualRunningTime, int ultimateMaxDepth){
    string goalState;
    cout<<"Enter the goal state\n";
    
    while (true){
        if(getline(cin, goalState)){
            PDState* stateManager = new PDState("012345678", 12);
            stateManager->setGoal(goalState);
            for(int i = 0; i <= 1000; ++i){
                cout<<"\n\nLoop: "<<i<<"\n-----------------\n";
                if(stateManager->step()){
                    break;
                };
                cout<<"Finished Loop level "<<i<<"\n";
            }
            delete stateManager;
            cout<<"Enter the goal state\n";
        }
    }
}
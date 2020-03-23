#include "state.h"
#include "hashTable.h"
#include <iostream>
class PDState : public stateFactory{
    
    public:
    dict<bool>  visitedStates = dict<bool>(false);
    dict<string> visitedPath = dict<string>("");
    int currentDepth;
    int maxDepth;
    string goalState;
    PDState(string initState, int maxDepth):stateFactory(initState){
        visitedStates[initState] = true;
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
        for (int i = 0; i <= newStates->size()+1; ++i){
            string index = newStates->top()->state;
            if(index == goalState){
                cout<<"Found the state!\n";
                return true;
            }
            if(visitedStates[index].data){
                // cout<<"This state is in the visited list already!\n";
                if(newStates->empty())break;
                index = newStates->top()->state;
                cout<<"Delete: "<<index<<" "<<newStates->top()->depth<<"\n";
                delete (newStates->top());
            } else {
                index = newStates->top()->state;
                // cout<<"Checking index!"<<index<<" == "<<goalState<< "\n";
               visitedStates[index] = true;
                newStates->top()->depth = currentDepth;
                
                cout<<"State: "<<index<<" "<<newStates->top()->direction<<"\n";
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

    void getVisitedPath(stack<stateData*>* newStateData){
        string top = this->states.top()->direction;
        reverse(newStateData);
        stateData* curr = newStateData->top();
        stack<stateData*>* reversedData = new stack<stateData*>();
        while(!newStateData->empty()){
            visitedPath[newStateData->top()->state] = newStateData->top()->direction+top;
            reversedData->push(newStateData->top());
            newStateData->pop();
        }
        reverse(reversedData);
        newStateData->swap(*reversedData);
        delete reversedData;


    }


    bool step(){
        int i = 0;
        
        if(states.empty()) return false;
        if(states.top()->depth <= maxDepth){
            
            stack<stateData*>* newStateData = getNextStates(top());
            cout<<"-----------------Total generated moves: "<<newStateData->size()<<"\n";
            // cout<<"Getting the new states\n";
            getVisitedPath(newStateData);
            if (convertToData(newStateData)){ return true;};
        } else {
            if (states.empty()) return false;
            while(states.top()->depth > maxDepth){
                delete states.top(); 
                states.pop();
                if(states.empty()){
                    // cout<<"Found the end of the list with no correct depth value!\n";
                    return false;
                }
            }
        }
        return false;
        

    }
    bool isEmpty(){
        return states.empty();
    }
    string getPath(string goal){
        return visitedPath[goal].data;
    }

    

};
    void progressiveDeepeningSearch_VisitedListAlgorithm(string origin, string goal){
        int level = 2;
            PDState* stateManager = new PDState(origin, level);
            stateManager->setGoal(goal);
            while(!stateManager->step()){
                if(stateManager->isEmpty()){
                    delete stateManager;
                    level+=5;
                    stateManager = new PDState(origin, level);
                    stateManager->setGoal(goal);
                    //cout<<"Resetting the states!\n";
                    
                }
            }
            cout<<"Getting state manager enqueue & dequeue states:\n";
            cout<<"Enqueue: "<<stateManager->getEnqueue()<<"\n";
            cout<<"Dequeue: "<<stateManager->getDequeue()<<"\n";
            cout<<"Path to item: "<<stateManager->getPath(goal)<<"\n";
            
            
            delete stateManager;
            

    }

int main(){
    //string progressiveDeepeningSearch_VisitedList
    //(string const initialState, string const goalState, int &numOfStateExpansions, 
    //int& maxQLength, float &actualRunningTime, int ultimateMaxDepth){
    string goalState;
    int i = -1;
   
    progressiveDeepeningSearch_VisitedListAlgorithm("185024367", "185204367");
    
    
}
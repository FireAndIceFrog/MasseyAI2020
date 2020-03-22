#include "state.h"
#include "hashTable.h"
class PDState : public stateFactory{
    
    public:

    dict<bool>  visitedStates = dict<bool>(false);
    int currentDepth;
    int maxDepth;
    PDState(string initState, int maxDepth):stateFactory(initState){
        currentDepth = 0;
        this->maxDepth = maxDepth;
    }
    
    
    void convertToData(stack<stateData*>* newStates){
        int i = 0; 
        stack<stateData*>* tempStates = new stack<stateData*>();
        currentDepth = states.top()->depth+1;
        for (int i = 0; i <= newStates->size(); ++i){
            string index = newStates->top()->state;
            if(visitedStates[index]){
                delete (newStates->top());
            } else {
                newStates->top()->depth = currentDepth;
                tempStates->push(newStates->top());
            }
            newStates->pop();
            
        }
        delete newStates;
        replace(0, tempStates);
        
    }
    string top(){
        return states.top()->state;
    }
    void step(){
        int i = 0;
        if(states.top()->depth < maxDepth){

            stack<stateData*>* newStateData = getNextStates(top());
            convertToData(newStateData);
        } else {
            delete states.top(); states.pop();
        }
        cout<<"Current States: \n";
        stack<stateData * > currStates = states;
        while (currStates.size() > 0){
            cout<<"<-- Current State: "<<currStates.top()->state<<"\n";
            currStates.pop();
        }

        

    }



};

int main(){
    //string progressiveDeepeningSearch_VisitedList
    //(string const initialState, string const goalState, int &numOfStateExpansions, 
    //int& maxQLength, float &actualRunningTime, int ultimateMaxDepth){
    PDState stateManager = PDState("012345678", 5);
    for(int i = 0; i < 4; ++i){
        cout<<"Depth: "<<i<<"\n-----------------\n";
        stateManager.step();
        cout<<"Finished depth level "<<i<<"\n";
    }

}
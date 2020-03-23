#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include <sstream>
#include <random>
#include <ctime>
#include <stack>

using namespace std;


            


class stateFactory{
    private : 
    string genString(int origin, int end, string str){
            //function to swap two characters in a string and return the string.
            swap(str[origin], str[end]);
            return str;
        }
    protected: 
        class stateData{
            public:
            stateData(string str):state{str}, direction{""},depth{0}, cost{0}{}
            string state;
            string direction;
            int depth;
            int cost;
        };
        stack<stateData*> states;
        int EnqueueStates;
        int DeQueueStates;
        


    public:
        stateFactory(string origin){
            EnqueueStates = 0;
            DeQueueStates = 0;
            states = stack<stateData*>();
            states.push(new stateData(origin));
        }
        ~stateFactory(){
            int i = states.size();
            while(i > 0){
                delete states.top();
                states.pop();
                --i;
            }
        }
        int getEnqueue(){
            return EnqueueStates;
        }
        int getDequeue(){
            return DeQueueStates;
        }

        void replace(int index, stack<stateData*>* newStates){
            //function to insert a stack of states into the current stack at given index. if the index is out of bounds, the stack does nothing.
            
            stack<stateData*> finalStack = stack<stateData*>();
            reverse(&states);
            if(index > states.size()) return;
            //the stack is reversed, so work the index from the end of the stack.
            index = states.size()-index-1;
            for (int i = 0; i < index; ++i){
                finalStack.push(states.top());
                states.pop();
            }
            
            if(!newStates->empty()) {
                for (int i = 0; i <= newStates->size(); ++i){
                    //add the enqueue on.
                    ++EnqueueStates;
                    finalStack.push(newStates->top());
                    newStates->pop();
                }
            }
            ++DeQueueStates;
            delete newStates;
            if(!states.empty()) delete states.top();
            
            for (int i = 0; i < states.size(); ++i){
                if (i != 0 ) finalStack.push(states.top());
                states.pop();
            }
            
            //swap stacks, the main stack now has the inserted element.
            states.swap(finalStack);
        }
        void reverse(stack<stateData*>* origin){
            stack<stateData*> reversed = stack<stateData*>();
            while (origin->size()>0){
                reversed.push(origin->top());
                origin->pop();
            }
            origin->swap(reversed);
        }

        
        stack<stateData*>* getNextStates(string state){
            stack<stateData*>*items = new stack<stateData*>();
            int pos = state.find("0");
            stateData* curr;
            //push to the stack in the order left up right down
            switch (pos){
            case 0:
                //if in the top right, add left->down
                //right
                curr = new stateData(genString(pos, 1, state));
                curr->direction = "r";
                items->push(curr);
                //down
                curr = new stateData(genString(pos, 3, state));
                curr->direction = "d";
                items->push(curr);
               
                break;
            case 1:
                //left
                curr = new stateData(genString(pos,  0, state));
                curr->direction = "l";
                items->push(curr);
                //right
                curr = new stateData(genString(pos, 2, state));
                curr->direction = "r";
                items->push(curr);
                //down
                curr = new stateData(genString(pos, 4, state));
                curr->direction = "d";
                items->push(curr);

                break;
            case 2:
                //left
                curr = new stateData(genString(pos,  1, state));
                curr->direction = "l";
                items->push(curr);
                //down
                curr = new stateData(genString(pos, 5, state));
                curr->direction = "d";
                items->push(curr);

                break;
            case 3:
                //up
                curr = new stateData(genString(pos,  0, state));
                curr->direction = "u";
                items->push(curr);
                //right
                curr = new stateData(genString(pos, 4, state));
                curr->direction = "r";
                items->push(curr);
                //down
                curr = new stateData(genString(pos, 6, state));
                curr->direction = "d";
                items->push(curr);
                break;
            case 4:
                //left
                curr = new stateData(genString(pos, 3, state));
                curr->direction = "l";
                items->push(curr);
                //up
                curr = new stateData(genString(pos,  1, state));
                curr->direction = "u";
                items->push(curr);
                //right
                curr = new stateData(genString(pos, 5, state));
                curr->direction = "r";
                items->push(curr);
                //down
                curr = new stateData(genString(pos, 7, state));
                curr->direction = "d";
                items->push(curr);
                break;
            case 5:
                //left
                curr = new stateData(genString(pos,  4, state));
                curr->direction = "l";
                items->push(curr);
                //up
                curr = new stateData(genString(pos, 2, state));
                curr->direction = "u";
                items->push(curr);
                //down
                curr = new stateData(genString(pos, 8, state));
                curr->direction = "d";
                items->push(curr);

                break;
            case 6:
                //up
                curr = new stateData(genString(pos,  3, state));
                curr->direction = "u";
                items->push(curr);
                //right
                curr = new stateData(genString(pos, 7, state));
                curr->direction = "r";
                items->push(curr);
                break;
            case 7:
                //left
                curr = new stateData(genString(pos,  6, state));
                curr->direction = "l";
                items->push(curr);
                //up
                curr = new stateData(genString(pos, 4, state));
                curr->direction = "u";
                items->push(curr);
                //down
                curr = new stateData(genString(pos, 8, state));
                curr->direction = "d";
                items->push(curr);

                break;
            case 8:
                //left
                curr = new stateData(genString(pos,  5, state));
                curr->direction = "l";
                items->push(curr);
                //up
                curr = new stateData(genString(pos, 7, state));
                curr->direction = "u";
                items->push(curr);

                break;
            default:

                break;
            }
            return items;

        }
        

        void convertToData(stack<string>* newStates);
};





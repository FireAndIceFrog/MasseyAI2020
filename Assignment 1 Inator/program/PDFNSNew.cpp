
#include <ctime>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <map>
#include <thread>
#include<stack>

#include <fstream>
using namespace std;
struct node {
    bool visited = false;
    int depth = 0;
} defaultNode;
int main() {
    int averageMap = 0;
    int averageVec = 0;
    int averageStack = 0;
    for (int j = 0; j < 20; j++){
        clock_t timer = clock();
        map<string, bool> dataset;
        for (int i = 0; i < 0xfffff; ++i){
            dataset[to_string(i)] = true;
        }
        for (int i = 0; i < 0xfffff; ++i){
            if(!(dataset.find(to_string(i))->fist)) cout<<"Not found!\n";
        
        }
        averageMap+=clock()-timer;
        cout<<"Operations took: "<<(clock()-timer)<<"ticks\n";
        
        timer = clock();
        vector<bool> datavec;
        for (int i = 0; i < 0xfffff; ++i){
            datavec.push_back(true);
        }
        cout<<"Size of vec: "<<datavec.size()<<"\n";
        for (int i = 0; i < 0xfffff; ++i){
            if(!datavec[datavec.back()]) cout<<"Not found!\n";
            datavec.pop_back();
        }
        averageVec += clock()-timer;
        cout<<"Operations took: "<<(clock()-timer)<<"ticks\n";
        stack<bool> dataStack;

        timer = clock();
        for (int i = 0; i < 0xfffff; ++i){
            dataStack.push(true);
        }
        cout<<"Size of stack: "<<dataStack.size()<<"\n";
        for (int i = 0; i < 0xfffff; ++i){
            if(!dataStack.top()) cout<<"Not found!\n";
            dataStack.pop();
        }
        averageStack += clock()-timer;
        cout<<"Operations took: "<<(clock()-timer)<<"ticks\n";
    }
    averageMap /= 20;
    averageStack /= 20;
    averageVec /= 20;
    string nl = "\n";
    cout<<"Map ticks: "<<averageMap<<nl;
    cout<<"Vec ticks: "<<averageVec<<nl;
    cout<<"Stack ticks: "<<averageStack<<nl;








}
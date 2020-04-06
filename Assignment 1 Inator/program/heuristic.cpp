#ifndef heuristic_h
#define heuristic_h

#include<tuple>
#include <string>
using namespace std;
//This page is to handle the two heuristic functions required for A* and Best First.
//For the best first application we will use the misplaced tiles as a heuristic function.

tuple<int,int> calcLoc(string str, char c){
    //function to calculate the location of a char
    int index = 1;
    int inputNum = c - '0';
    int res[3];
    while (inputNum > 0 && index>=0) 
    { 
        res[index--] = (inputNum % 3); 
        inputNum /= 3; 
    } 
    
    return make_tuple(res[0],res[1]);

}



//misplaced tiles heuristic function
// Get an input string "021346587" and a goal string eg "123456780"
// if index of goal does not match index of initial, add one to counter (do not count 0)
int misplacedH(string init, string goal){
    int heuristic = 0;
    for (int i = 0; i < goal.size(); ++i){
        if(goal[i] == '0') continue;
        else if (goal[i] != init [i]){
            ++heuristic;
        }
    }
    return heuristic;
}

int manhattanH(string init, string goal){
    //find the absolute distance from the target location.
    //H = | x1-x2 | + | y1 - y2 |
    int H = 0;
    string basic = "12345678";
    for (char c : basic){
        //find the location of C in goal
        auto [y1,x1] = calcLoc(goal,c);
        //find the location of C in current
        auto [y2,x2] = calcLoc(init,c);
        //calculate for the distance and add them.
        H += abs(x1-x2) + abs(y1-y2);

    }
    return H;
}




#endif
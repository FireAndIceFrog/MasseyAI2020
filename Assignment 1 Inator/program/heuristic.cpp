#ifndef heuristic_h
#define heuristic_h

#include<tuple>
#include <string>
#include <iostream>
using namespace std;
//This page is to handle the two heuristic functions required for A* and Best First.
//For the best first application we will use the misplaced tiles as a heuristic function.




//misplaced tiles heuristic function
// Get an input string "021346587" and a goal string eg "123456780"
// if index of goal does not match index of initial, add one to counter (do not count 0)
int misplacedH(string init, string goal){
    int heuristic = 0;
    for (int i = 0; i < goal.size(); ++i){
        if (goal[i] != init [i]){
            ++heuristic;
        }
    }
    return heuristic;
}

int manhattanH(string init, string goal){
    //find the absolute distance from the target location.
    //H = | x1-x2 | + | y1 - y2 |
    int H = 0;
    for (int i = 0; i != goal.size(); ++i){
        if ('0' == init[i]) continue;
        int digit = init[i] - '0';
        //Column  + Row using base 3 as a heuristic (putting the string into a matrix)
        H += abs(i/3-digit/3) + abs(i%3-digit%3);
    }
    return H;
}




#endif
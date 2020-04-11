#include "puzzle.h"
#include  <cmath>
#include  <assert.h>

using namespace std;



//////////////////////////////////////////////////////////////
//constructor
//////////////////////////////////////////////////////////////
Puzzle::Puzzle(const Puzzle &p) : path(p.path){
	
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		    board[i][j] = p.board[i][j];
		    goalBoard[i][j] = p.goalBoard[i][j];
		}
	}	
	
	x0 = p.x0;
	y0 = p.y0;
	//path = p.path;
	pathLength = p.pathLength;
	cost = p.cost;
	strBoard = toString(); //uses the board contents to generate the string equivalent
	depth = p.depth;
	
}

//////////////////////////////////////////////////////////////
//constructor
//inputs:  initial state, goal state
//////////////////////////////////////////////////////////////
Puzzle::Puzzle(string const elements, string const goal){
	
	int n;
	
	n = 0;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		    board[i][j] = elements[n] - '0';
		    if(board[i][j] == 0){
			    x0 = j;
			    y0 = i;
			 }
		    n++;
		} 
	}
		
	///////////////////////
	n = 0;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		    goalBoard[i][j] = goal[n] - '0';
		    n++;
		} 
	}		
	///////////////////////	
	path = "";
	pathLength=0;
	cost = 0;
	depth = 0;
	strBoard = toString();	
}


void Puzzle::setDepth(int d){
	depth = d;
}

int Puzzle::getDepth(){
	return depth;
}

void Puzzle::updateCost(int hFunction){
	
	cost = h(hFunction);
}


int Puzzle::getCost() const{
	return cost;
}



//Heuristic function implementation
int Puzzle::h(int hFunction){
	
	int sum=0;
	int h=0;
	int numOfMisplacedTiles=0;
	
	switch(hFunction){
		case 0:			      //Heuristic Value, by Misplaced Tiles
				//place your implementation here	
                h = numOfMisplacedTiles;
				for(int i=0; i < 3; i++){
					for(int j=0; j < 3; j++){	
						if(board[i][j] != 0 && board[i][j] != goalBoard[i][j]){
							++numOfMisplacedTiles;
						}
					} 
				}
				h = numOfMisplacedTiles;

		        break;
		         
		case 1:					//Heuristic Value, by Manhattan Distance
		        //place your implementation here
		        for(int i=0; i < 3; i++){
					for(int j=0; j < 3; j++){	
						if(board[i][j] == 0) continue;
						for(int n=0; n < 3; n++){
							for(int m=0; m < 3; m++){	
								if( board[i][j] == goalBoard[n][m]){
									//this should be |x1 - x2| + |y1 - y2|
									sum += abs(i-n) + abs(j-m);
								}
							}
						}

					} 
				}
		        h = sum; 					
		        break;         
		           
	};
	
	return h;
	
}


//converts board state into its string representation
string Puzzle::toString(){
  int n;
  string stringPath;
  
  n=0;
  for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){			    
		    stringPath.insert(stringPath.end(), board[i][j] + '0');
		    n++;
		} 
  }
  
//  cout << "toString = " << stringPath << endl;
  
  return stringPath;
}



bool Puzzle::goalMatch(){
	bool result=false;
    
    //this is incomplete...
	return result;
}

bool Puzzle::canMoveLeft(){
   return (x0 > 0);
	
}

const string Puzzle::getPath(){
	return path;
}

bool Puzzle::canMoveRight(){

   return (x0 < 2);
	
}


bool Puzzle::canMoveUp(){

   return (y0 > 0);
	
}

bool Puzzle::canMoveDown(){

   return (y0 < 2);
	
}

///////////////////////////////////////////////
//these functions will be useful for Progressive Deepening Search 
// 
// bool Puzzle::canMoveLeft(int maxDepth){
//  
// 	 bool m=false;
//   	//put your implementations here
//   	return m; 
// }
// bool Puzzle::canMoveRight(int maxDepth){
   
//   	bool m=false;
//   	//put your implementations here
//   	return m; 
// }
// 
// 
// bool Puzzle::canMoveUp(int maxDepth){
//    
//   	bool m=false;
//   	//put your implementations here
//   	return m; 
// }
// 
// bool Puzzle::canMoveDown(int maxDepth){
//    
//   	bool m=false;
//   	//put your implementations here
//   	return m; 
// }
// 
///////////////////////////////////////////////

Puzzle *Puzzle::moveLeft(){
	
	Puzzle* p = new Puzzle(*this);
	
	
   	if(x0 > 0){
		
		p->board[y0][x0] = p->board[y0][x0-1];
		p->board[y0][x0-1] = 0;
		
		p->x0--;
		
		p->path = path + "L";
		p->pathLength = pathLength + 1;  
		p->depth = depth + 1; 
		
		
	}
	p->strBoard = p->toString();

	return p;
	
}


Puzzle *Puzzle::moveRight(){
	
   Puzzle *p = new Puzzle(*this);
	
	
   if(x0 < 2){
		
		p->board[y0][x0] = p->board[y0][x0+1];
		p->board[y0][x0+1] = 0;
		
		p->x0++;
		
		p->path = path + "R";
		p->pathLength = pathLength + 1; 
     	
		p->depth = depth + 1;
		
	}
	
	p->strBoard = p->toString();
	
	return p;
	
}


Puzzle *Puzzle::moveUp(){
	
   Puzzle *p = new Puzzle(*this);
	
	
   if(y0 > 0){
		
		p->board[y0][x0] = p->board[y0-1][x0];
		p->board[y0-1][x0] = 0;
		
		p->y0--;
		
		p->path = path + "U";
		p->pathLength = pathLength + 1;  
	
		p->depth = depth + 1;
		
	}
	p->strBoard = p->toString();
	
	return p;
	
}

Puzzle *Puzzle::moveDown(){
	
   Puzzle *p = new Puzzle(*this);
	
	
   if(y0 < 2){
		
		p->board[y0][x0] = p->board[y0+1][x0];
		p->board[y0+1][x0] = 0;
		
		p->y0++;
		
		p->path = path + "D";
		p->pathLength = pathLength + 1;  
		
		p->depth = depth + 1;
		
	}
	p->strBoard = p->toString();	
	
	return p;
	
}

/////////////////////////////////////////////////////


void Puzzle::printBoard(){
	cout << "board: "<< endl;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		  //cout << endl << "board[" << i << "][" << j << "] = " << board[i][j];
		  cout << board[i][j]<< " ";
		}
		cout << endl;
	}
	cout << endl;
	
}

int Puzzle::getPathLength(){
	return pathLength;
}

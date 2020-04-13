

#include "algorithm.h"
#include "bestFirstVis.cpp"
#include "PDSSL.cpp"
#include "PDSNSL.cpp"
#include "AStar.cpp"






using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Best-First Search without the VisitedList
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string bestFirstSearch_No_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime){
    string path;
	clock_t startTime;
    //add necessary variables here


    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<bestFirstSearch_No_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;

	startTime = clock();
	BFNV* item = new BFNV(initialState, goalState);
	startTime = clock();
	item->search();
    path = item->getPath();
	numOfStateExpansions = item->getStateExpansions();
	maxQLength = item->getMaxQLen();



	// srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	// maxQLength= rand() % 800; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	// numOfStateExpansions = rand() % 600; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY

    // cout << "I'm running inside Best First Search without the Visited list" << endl;
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	// path = "DDRRLLLUUURDLUDURDLUU";  //this is just a dummy path for testing the function           
	return path;		
		
}


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  Best-First Search with VisitedList
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string bestFirstSearch_with_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime){
    string path;
	clock_t startTime;
    //add necessary variables here


    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<bestFirstSearch_No_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;

	startTime = clock();
	BFV* item = new BFV(initialState, goalState);
	startTime = clock();
	item->search();
    path = item->getPath();
	numOfStateExpansions = item->getStateExpansions();
	maxQLength = item->getMaxQLen();



	// srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	// maxQLength= rand() % 800; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	// numOfStateExpansions = rand() % 600; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY

    // cout << "I'm running inside Best First Search without the Visited list" << endl;
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	// path = "DDRRLLLUUURDLUDURDLUU";  //this is just a dummy path for testing the function           
	return path;		
		
}




///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  PDS using the Visited List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string progressiveDeepeningSearch_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth){
    string path;
	clock_t startTime;
    //add necessary variables here

    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<progressiveDeepeningSearch_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;
	startTime = clock();
	PDSSL* item = new PDSSL(initialState, goalState);
	startTime = clock();
	item->search();
    path = item->getPath();
	numOfStateExpansions = item->getStateExpansions();
	maxQLength = item->getMaxQLen();
	
	// srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	// maxQLength= rand() % 500; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	// numOfStateExpansions = rand() % 600; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY

	// progressiveDeepeningSearch_VisitedListAlgorithm(initialState, goalState, &numOfStateExpansions , 
    // &maxQLength, &ultimateMaxDepth, &path);
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	// path = "DDRRLLLUUURDLUDURDLUU";  //this is just a dummy path for testing the function           
	return path;		
		
}
	

///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  PDS using the Non-Strict Visited List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string progressiveDeepeningSearch_NonStrict_VisitedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime, int ultimateMaxDepth){
    string path;
	clock_t startTime;
    //add necessary variables here


    //algorithm implementation
	// cout << "------------------------------" << endl;
 //    cout << "<<progressiveDeepeningSearch_NonStrict_VisitedList>>" << endl;
 //    cout << "------------------------------" << endl;

	startTime = clock();
	PDSNSL* item = new PDSNSL(initialState, goalState);
	startTime = clock();
	item->search();
    path = item->getPath();
	numOfStateExpansions = item->getStateExpansions();
	maxQLength = item->getMaxQLen();
	// srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	// maxQLength= rand() % 500; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	// numOfStateExpansions = rand() % 600; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY

	
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	// path = "LR";  //this is just a dummy path for testing the function           
	return path;		
		
}
	


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  A* with the Strict Expanded List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string aStar_ExpandedList(string const initialState, string const goalState, int &numOfStateExpansions, int& maxQLength, 
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){
											 
   string path;
   clock_t startTime;

   AStar* item = new AStar(initialState, goalState, heuristic);

   
    // cout << "------------------------------" << endl;
    // cout << "<<aStar_ExpandedList>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;	
	startTime = clock();
	item->search();
	path = item->getPath();
	numOfStateExpansions = item->getStateExpansions();
	maxQLength = item->getMaxQLen();
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	
	             
	return path;		
		
}





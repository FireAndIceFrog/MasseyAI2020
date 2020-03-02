//////////////////////////////////////////////////////////////////////////////////
//
//    Project Name: Test code with simple graphics engine
//
//    Author: 
//    Date: 
//
//    History: 
//              March 2, 2019
//
//    Test code by:  Dr. Napoleon Reyes, n.h.reyes@massey.ac.nz
//    				 Computer Science, SNCS
//					 Massey University-Albany
//
//////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <windows.h>
#include "graphics2.h"

using namespace std;

int main() 
{
	int GraphDriver=0,GraphMode=0;
	initgraph( &GraphDriver, &GraphMode, "", 640, 480 ); // Start Window
	char msg[80];
	int page=0;

    try{

	    for(int n=10; n >= 0; n--){
	       page++;
		   page = page % 2;
	       setactivepage(page);
	       cleardevice();
	       settextstyle(TRIPLEX_FONT, HORIZ_DIR, 25);
	       sprintf(msg,"%d", n);
	       setcolor(YELLOW);
	       settextjustify(CENTER_TEXT, CENTER_TEXT);
		   outtextxy(getmaxx()/2, getmaxy()/2,msg);	
		   cout << n << endl;
		   setvisualpage(page);
		   Sleep(300);
		   
	    }
	    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
	    outtextxy(getmaxx()/2, getmaxy()-textheight("H"),"done.");	
    } catch(...){
    	cout << "Exception caught!\n";
   }

	
	
	
	
	
	getch(); //Wait for a key. (When main function ends, the window will close)

	return 0;
} //end of main()

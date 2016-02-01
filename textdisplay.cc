#include "textdisplay.h"
using namespace std;

//see textdisplay.h
TextDisplay::TextDisplay(int n):View(n){
	//TODO
	theDisplay=new char *[gridSize];                   //dynamically create an array of gridSize char *
	for(int i=0;i<gridSize;i++){                       //for each row
		theDisplay[i]=new char [gridSize];             //allocate gridSize cols
		for(int j=0;j<gridSize;j++) {                  //for each column in theDisplay[i]
			theDisplay[i][j]='0';
		}
	}
}

//see textdisplay.h
TextDisplay::~TextDisplay(){
	//TODO
	for(int i=0;i<gridSize;i++){                       //use a loop to delete theDisplay[i]
		delete [] theDisplay[i];
	}
	delete [] theDisplay;                              //delete the array of theDisplay
}

//see textdisplay.h
void TextDisplay::notify(int r, int c, char ch){
	//TODO
    if((r>=gridSize)||(c>=gridSize)){
        return;
    }
	theDisplay[r][c]=ch+'0';
}

//see textdisplay.h
void TextDisplay::print(std::ostream &out){
	//TODO
	for(int i=0;i<gridSize;i++){
		for(int j=0;j<gridSize;j++){
			out<<theDisplay[i][j];
		}
        out<<endl;
	}
}


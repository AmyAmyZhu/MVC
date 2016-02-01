#include "game.h"
using namespace std;
//see game.h
void Game::clearGame(){
	for(int i=0;i<gridSize;i++){                              //use a loop to delete theGrid[i]
		delete [] theGrid[i];
	}
	delete [] theGrid;                                        //delete the array of theGrid
}

//see game.h
Game::Game():theGrid(),gridSize(),notification(){
    for(int i=0;i<=maxNeighbours;i++){
        colours[i]=0;
    }
}

//see game.h
Game::~Game(){
	clearGame();
}


//see game.h
void Game::notify(int r,int c,unsigned int oldState,unsigned int newState){
    colours[newState]++;
    colours[oldState]--;
    notification->notify(r,c,newState);
}


//see game.h
//this is the ineffient way
bool Game::isWon(){
	char theFirst=theGrid[0][0].getState();                  //get the (0,0) colour
	int count=0;                                             //count how many cells have the same colour as the (0,0) cell
	for(int i=0;i<gridSize;i++){                             //use a loop to recursively found the cells that has the same colour as the (0,0) cell
		for(int j=0;j<gridSize;j++){
			if(theGrid[i][j].getState()==theFirst){
				count++;
			}
		}
	}
	if(count==(gridSize*gridSize)){                           //if all cells in the grid are the same colour, return true
		return true;
	}else{
		return false;
	}
}

//see game.h
void Game::init(int n, GameNotification *gameNotification){
    if(theGrid!=NULL){
        clearGame();                                          //clear the before game
    }
	notification=gameNotification;
	gridSize=n;                                               //state that its n*n grid
	for(int i=0;i<=maxNeighbours;i++){                        //initialize all the number of colours to be 0
		colours[i]=0;
	}
	theGrid=new Cell *[gridSize];                             //dynamically create an array of gridSize char *
    for(int i=0;i<gridSize;i++){
        theGrid[i]=new Cell[gridSize];
    }
	for(int i=0;i<gridSize;i++){                              //for each row
		for(int j=0;j<gridSize;j++) {                         //for each column in theDisplay[i]
            theGrid[i][j].setState(0);
			theGrid[i][j].setCoords(i,j);                     //set the cell coords to be the right coord
			theGrid[i][j].setGame(this);                      //set all cell games to be this game
			if(i<(gridSize-1)){                               //every row r less than (gridSize-1) has a right neighbour
				theGrid[i][j].addNeighbour(&theGrid[i+1][j]);
			}
			if(i>0){                                          //every row r greater than 0 has a left neighbour
				theGrid[i][j].addNeighbour(&theGrid[i-1][j]);
			}
			if(j<gridSize-1){
				theGrid[i][j].addNeighbour(&theGrid[i][j+1]);  //every column greater than (gridSize-1) has a downward neighbour
			}
			if(j>0){                                           //every column less than 0 has a upward neighbour
			theGrid[i][j].addNeighbour(&theGrid[i][j-1]);
			}
		}
	}
}

//see game.h
// Changes (0,0) and all appropriate neighbours to c
void Game::change(const int &c){
	theGrid[0][0].notify(c);
}

//see game.h
//Called by Controller:init in response to initialization requests when game is in init mode
void Game::init(int r, int c, int change){
    if((r>=gridSize)||(c>=gridSize)){
        return;
    }
    colours[change]++;
    colours[(int)theGrid[r][c].getState()]--;
    theGrid[r][c].setState(change);
}



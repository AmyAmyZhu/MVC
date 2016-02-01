#include "cell.h"
#include "game.h"
using namespace std;


//see cell.h
void Cell::notifyNeighbours(){
    notify(state,prevState);
}

//see cell.h
void Cell::notifyGame(){
	game->notify(r,c,prevState,state);
}

//see cell.h
Cell::Cell():state(),prevState(),numNeighbours(),neighbours(),r(),c(),game(){}


//see cell.h
char Cell::getState(){
	return state;
}

//see cell.h
void Cell::setState(const int& change){
    prevState=state;                          //store the previous state
    state=change;                             //set the current state to be change
}

//see cell.h
void Cell::setCoords(const int r, const int c){
	this->r=r;
	this->c=c;
}

//see cell.h
void Cell::setGame(Game *game){
	this->game=game;
}

//see cell.h
void Cell::addNeighbour(Cell *neighbour){
	if(numNeighbours>=maxNeighbours) return;    //when one neighbour has more than 4 neighbours, return
	neighbours[numNeighbours]=neighbour;
	numNeighbours++;                            //increase the number of neighbours
}

//see cell.h
//Intended to be called only by the game class for changing the state of the 0 0 cell
void Cell::notify(const int &change){
    if((0==this->r)&&(0==this->c)&&(change!=this->state)){
        setState(change);
        notifyGame();
        notifyNeighbours();
    }
}

//see cell.h
void Cell::notify(const int &current, const int &previous){
    for(int i=0;i<maxNeighbours;i++){
        if ((neighbours[i]!=NULL)&&(neighbours[i]->state==previous)){
            neighbours[i]->prevState=previous;
            neighbours[i]->state=current;
            neighbours[i]->notifyGame();
            neighbours[i]->notifyNeighbours();
        }
    }
}



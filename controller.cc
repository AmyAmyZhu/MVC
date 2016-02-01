#include "controller.h"
#include "game.h"
#include "textdisplay.h"
//#include "graphicdisplay.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

Controller::Controller(){
    game = new Game();
    td = NULL;
// TODO - for part (b)
}

/*
 * Update the View(s) to indicate the new game state
*/
//see controller.h
void Controller::notify(int r, int c, unsigned int state){
// TODO
	td->notify(r,c,state);
}

/*
 * Called when command init is received
*/
//see controller.h
void Controller::init(istream & input, Game & g){
    // TODO
    while (true){
        int r,c,change=0;
        input>>r>>c;
        if(input.eof()) return;
        if((-1==r)&&(-1==c)) return;
        input>>change;
        game->init(r,c,change);
        notify(r,c,change);
    }
}

//see controller.h
bool Controller::checkWin(int movesLeft){
  if(game->isWon() && movesLeft != 0){
    cout << "Won" << endl;
    return true;
  }
  return false;
}

//see controller.h
void Controller::play(){
  srand(time(NULL));
  int moves = 0;
  string cmd;
  bool playing = false;
  while (cin >> cmd) {
    if (cmd == "new") {
      int n;
      cin >> n; 
      game->init(n, this);
      delete td;
      td = new TextDisplay(n);
// Uncomment for part (b)
//      gd = new GraphicDisplay(n);

      moves = 0;
    }
// the ? command is only needed for part (b)
// when graphics command line is enabled
//    else if (cmd == "?"){
//         cout << "White: 0" << endl;
//         cout << "Black: 1" << endl;
//         cout << "Red:   2" << endl;
//         cout << "Green: 3" << endl;
//         cout << "Blue:  4" << endl;
//
//    }

    else if (cmd == "init") {
      init(cin, *game);
      #if DEBUG
      cout << "Done initialization" << endl;
      #endif
      td->print(cout);
      if (checkWin(moves)){
        break;
      }
    }
    else if (cmd == "include"){
       string file;
       cin >> file;
       ifstream input(file.c_str());
       init(input, *game);
       td->print(cout);
       if (checkWin(moves)){
        break;
      }
    }
    else if (cmd == "switch") {
      if (checkWin(moves)){
        break;
      }
      if(moves > 0){
        int next;
        if (cin >> next && (next >= 0 || next <= 4)){
          game->change(next);
          td->print(cout);
          --moves;
	       if (moves == 1) {
          cout << moves << " move left" << endl;
	       }
         else {
          cout << moves << " moves left" << endl;
	       }
         if(game->isWon()){
	         cout << "Won" << endl;
	         break;
	       }
 	       if(moves == 0){
  	         cout << "Lost" << endl;
	         break;
	       }
        }
        else cerr << "Invalid move" << endl;
      }
    }
    else if (cmd == "game" && !playing){
      cin >> moves;
      if (moves < 0) {
        moves = 0;
      } 
      else if (moves == 1) {
        cout << moves << " move left" << endl;
      }
      else { 
        cout << moves << " moves left" << endl;
      }
      if (checkWin(moves)){
        break;
      }
    }
  }
}

//see controller.h
Controller::~Controller(){
// TODO
	delete td;
	delete game;
}


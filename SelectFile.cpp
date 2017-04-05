#include <SelectFile.h>
#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

SelectFile::SelectFile(){
  currentFile = "No file current selected";
  init();

  display();
  while(running){
    input();
  }

  endwin();
}
SelectFile::SelectFile(string fn){
  currentFile = fn;
  init();

  display();
  while(running){
    input();
  }

  endwin();
}


SelectFile::~SelectFile(){

}

void SelectFile::init(){
  // ncurses init stuff
  initscr();
  nodelay(stdscr,TRUE);
  keypad(stdscr,TRUE);
  echo();

  running = true;
  charentered = 0;
}

void SelectFile::display(){
  mvprintw(1,2,"There are several preset configurations included with this project. Type the");
  mvprintw(2,2,"name of the desired configuration below. Further, the user can also create ");
  mvprintw(3,2,"their own configurations if they want. Finally, if no file name is entered, a");
  mvprintw(4,2,"random configuration will be created.");
  mvprintw(6,2,"Enter File Location and Press the Up arrow");
  mvprintw(7,2,"File Location:");
  string output = "Previous Location: " + currentFile;
  mvprintw(8,2,output.c_str());
  mvprintw(22,32,"Press End to go back");
  move(7,17);
}

void SelectFile::input(){
  int ch = getch();
  if(ch == KEY_END){
    movetoSim = false;
    running = false;
  }
  else if(ch == KEY_UP){
    // Get all the characters that have been entered
    currentFile = "";
    for(int i = 0; i <= charentered; i++){
      currentFile += mvinch(7,17+i);
    }
    movetoSim = true;
    running = false;
  }
  else if(ch > 47 && ch < 129){
    charentered++;
  }
}

void SelectFile::logic(){

}

bool SelectFile::getmovetoSim(){
  return movetoSim;
}

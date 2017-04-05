#include <Menu.h>
#include <Simulation.h>
#include <SelectFile.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>

using namespace std;

string getcurrentFile(SelectFile sf);

Menu::Menu(){

  init();

  while(running){
    input();
    logic();
    display();
    usleep(500000);
  }
  endwin();
}

Menu::~Menu(){

}

void Menu::init(){
// ncurses init stuff
  initscr();
  noecho();
  nodelay(stdscr,TRUE);
  keypad(stdscr,TRUE);

// Variable init
  currentFile = "N/A";
  running = true;
  // Get last file used and store in currentFile
  ifstream instream;
  instream.open("config.txt");
  if(instream.fail()){
    currentFile = "N/A";
  }
  else{
    getline(instream,currentFile);
    if(currentFile.length() == 0){
      currentFile = "N/A";
    }
  }
}

void Menu::display(){
  clearscreen();
  displayedge();
  displaytext();
  // move cursor to top left corner
  move(0,0);
}

void Menu::clearscreen(){
  // Clears the screen, the "+ 10" in the for loop is to ensure
  // everything is covered
  for(int i = 0; i < WIDTH + 10; i++){
    for(int j = 0; j < HEIGHT + 10; j++){
      mvaddch(j,i,' ');
    }
  }
}

void Menu::displayedge(){
  // Displays a box around edge of screen
  box(stdscr,HEIGHT,WIDTH);
}

void Menu::displaytext(){
  //The window can display 75 characters
  mvprintw(2,30,"Conway's Game of Life");
  mvprintw(3,28,"Created by Theodore Champ");
  mvprintw(5,2,"The game of life is a fairly simple concept. The \"game\" consists of a grid.");
  mvprintw(6,2,"At each location in the grid, there can either be a living cell, or a dead");
  mvprintw(7,2,"one. In order to determine if a cell should be living or dead in after each");
  mvprintw(8,2,"round, 4 rules are applied for the 8 blocks surrounding the cell of interest.");
  mvprintw(9,3,"1. Any live cell with fewer than two live neighbours dies.");
  mvprintw(10,3,"2. Any live cell with two or three live neighbours lives.");
  mvprintw(11,3,"3. Any live cell with more than three live neighbours dies.");
  mvprintw(12,3,"4. Any dead cell with exactly three live neighbours becomes a live cell.");
  mvprintw(14,27,"Press S to Start Simulation");
  mvprintw(22,32,"Press End to Exit");
}

void Menu::input(){
  // Gets last key press and stores value in ch
  int ch = getch();
  if(ch == KEY_END){

    // Save currentFile to the config.txt
    ofstream out;
    out.open("config.txt");
    if(!out.fail()){
      out << currentFile;
    }
    out.close();

    running = false;
  }
  if(ch == KEY_S){
    clearscreen();
    SelectFile sf(currentFile);
    // Check if program should move onto Simulation
    if(sf.getmovetoSim()){
      // Get file selection from SelectFile object
      currentFile = getcurrentFile(sf);
      if(currentFile.empty()){
        Simulation sim;
      }
      else{
        Simulation sim(currentFile);
      }
    }
  }
}

void Menu::logic(){

}



string getcurrentFile(SelectFile sf){
  return sf.currentFile;
}

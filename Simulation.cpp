#include <Simulation.h>
#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

Simulation::Simulation(){
  // init with no file input
  init(false);

  // Shows initial state and waits for user to press a key
  display();
  mvprintw(10,10,"Press any key to start");
  nodelay(stdscr,FALSE);
  getch();
  // main simulation loop
  nodelay(stdscr,TRUE);
  while(running){
    input();
    logic();
    display();
    usleep(1000000);
  }
  endwin();
}

Simulation::Simulation(string fn){
  currentFile.open(fn.c_str());
  //catch file not found exception
  if(currentFile.fail()){
    // init wiht no file input
    init(false);
  }
  else{
    // init with file input
    init(true);
  }
  currentFile.close();
  // Shows initial state and waits for user to press a key
  display();
  mvprintw(10,10,"Press any key to start");
  nodelay(stdscr,FALSE);
  getch();
  // main simulation loop
  nodelay(stdscr,TRUE);
  while(running){
    input();
    logic();
    display();
    usleep(1000000);
  }
  endwin();
}

Simulation::~Simulation(){

}

void Simulation::init(bool fileInput){
  // init for ncurses
  initscr();
  noecho();
  nodelay(stdscr,TRUE);
  keypad(stdscr,TRUE);

  //start program in running state
  running = true;

  // init culture
  // Random configuration
  if(!fileInput){
    for(int i = 0; i < HEIGHT; i++){
      for(int j = 0; j < WIDTH; j++){
        if(rand()%10 < 4){
          culture[i][j].setAlive(true);
        }
      }
    }
  }
  // Nonrandom configuration
  else{
    for(int i = 0; i < HEIGHT; i++){
      if(currentFile.eof()){
        break;
      }
      string line;
      getline(currentFile,line);
      for(int j = 0; j < line.length(); j++){
        char char1 = line.at(j);
        if(char1 == 'O'){
          culture[i][j].setAlive(true);
        }
      }
    }
  }

}

void Simulation::display(){
  displayclear();
  displayhud();
  displayculture();

  move(0,0);
  refresh();
}

void Simulation::displayclear(){
  // Clears the screen, the "+ 10" in the for loop is to ensure
  // everything is covered
  for(int i = 0; i < WIDTH + 30; i++){
    for(int j = 0; j < HEIGHT + 10; j++){
      mvaddch(j,i,' ');
    }
  }
}

void Simulation::displayhud(){
  // Print border. Simulation occurs from 1 to WIDTH and 1 to HEIGHT.
  // Therefore the border must be at col 0, col WIDTH +1, row 0,
  // and row HEIGHT + 1
  for(int i = 1; i < WIDTH + 1; i++){
    mvaddch(0,i,'-');
    mvaddch(HEIGHT+1,i,'-');
  }
  for(int i = 1; i < HEIGHT + 1; i++){
    mvaddch(i,0,'|');
    mvaddch(i,WIDTH+1,'|');
  }
  mvprintw(22,28,"Press End to go back");
}

void Simulation::displayculture(){
  // Just iterates through culture and prints ALIVE_CHAR if alive and
  // DEAD_CHAR if dead.
  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      if(culture[j][i].getAlive()){
        mvaddch(j+1,i+1,ALIVE_CHAR);
      }
      else{
        mvaddch(j+1,i+1,DEAD_CHAR);
      }
    }
  }
}

void Simulation::logic(){
  // This section basically moves through each entry in the culture array
  // and using conways rules calculates if the cell should be alive or not.
  // It saves this data in a temporary array called tempculture because if it
  // was saved in the culture array, it would be impacting itself
  Cell tempculture[HEIGHT][WIDTH];
  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      int count = calculatecount(i,j);
      if(count < 2){
        tempculture[j][i].setAlive(false);
      }
      if(count == 2 || count == 3){
        if(culture[j][i].getAlive()){
          tempculture[j][i].setAlive(true);
        }
      }
      if(count > 3){
        tempculture[j][i].setAlive(false);
      }
      if(count == 3 && !culture[j][i].getAlive()){
        tempculture[j][i].setAlive(true);
      }
    }
  }

  // Copy data from tempculture to culture, in one mega statement!
  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      culture[j][i].setAlive(tempculture[j][i].getAlive());
    }
  }
}

int Simulation::calculatecount(int i, int j){
  // This manually figures outs the number of living cells around
  // each cell and increases count each time one is found
  int count = 0;
  if(culture[j-1][i-1].getAlive() && (j-1 >= 0 && i-1 >= 0)){
    count++;
  }
  if(culture[j-1][i].getAlive() && (j-1 >= 0)){
    count++;
  }
  if(culture[j-1][i+1].getAlive() && (j-1 >= 0 && i+1 < WIDTH)){
    count++;
  }
  if(culture[j][i-1].getAlive() && (i-1 >= 0)){
    count++;
  }
  if(culture[j][i+1].getAlive() && (i+1 < WIDTH)){
    count++;
  }
  if(culture[j+1][i-1].getAlive() && (j+1 < HEIGHT && i-1 <= 0)){
    count++;
  }
  if(culture[j+1][i].getAlive() && (j+1 < HEIGHT)){
    count++;
  }
  if(culture[j+1][i+1].getAlive() && (j+1 < HEIGHT && i+1 < WIDTH)){
    count++;
  }
  return count;
}


void Simulation::input(){
  int ch = getch();
  if(ch == KEY_END){
    running = false;
  }
}

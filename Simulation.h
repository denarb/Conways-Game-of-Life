#include "Window.h"
#include <string>
#include <fstream>

class Simulation: public Window{
public:
  Simulation();
  Simulation(std::string fn);
  ~Simulation();
  void display();
  void logic();
  void input();

  class Cell{
  public:
    Cell(){
      alive = false;
    }

    Cell(bool a){
      alive = a;
    }

    bool getAlive(){
      return alive;
    }

    void setAlive(bool a){
      alive = a;
    }

  private:
    bool alive;
  };



private:
//functions
  void init(bool fileInput);
  //display functions
  void displayclear();
  void displayhud();
  void displayculture();
  //logic functions
  int calculatecount(int i, int j);

//variables and objects
  static const int WIDTH = 50;
  static const int HEIGHT = 20;
  static const char ALIVE_CHAR = 'O';
  static const char DEAD_CHAR = ' ';

  Cell culture[HEIGHT][WIDTH];
  bool running;
  std::ifstream currentFile;

};

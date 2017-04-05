#include <string>


class Menu{
public:
  Menu();
  Menu(std::string fn);
 ~Menu();

private:
  void display();
  void logic();
  void input();

  void init();
  // displayfunctions
  void clearscreen();
  void displayedge();
  void displaytext();

  bool running;
  std::string currentFile;

  static const int HEIGHT = 20;
  static const int WIDTH = 100;
  static const int KEY_S = 115;
};

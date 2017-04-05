#include <string>

class SelectFile{
public:
  SelectFile();
  SelectFile(std::string fn);
 ~SelectFile();
  friend std::string getcurrentFile(SelectFile sf);
  bool getmovetoSim();

private:
  void display();
  void input();
  void logic();
  void init();

  bool running;
  bool movetoSim;
  int charentered;
  std::string currentFile;

};

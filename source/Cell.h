#include <string>

class Cell {
 public:
  int value;
  bool top;
  bool left;

  Cell();
  Cell(int val);
  std::string writeLeft();
  std::string writeTop();
};

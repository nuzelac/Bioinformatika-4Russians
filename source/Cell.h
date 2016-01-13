/*
 * Cell.h
 * Header file used to describe Cell class
 * Cells are part of Block Class
 */

#include <string>

class Cell {
 public:
  int value;
  bool top;
  bool left;

  Cell();
  Cell(int val);
  
  /*
   * Mathod used for returnig "T" or "F"
   * based on top and left atribute of object
   */
  std::string writeLeft();
  std::string writeTop();
};

/*
 * Cell.cpp
 * Cell class
 * Cell class is consited of main value
 * 
 */ 

#include "Cell.h"
#include <iostream>
#include <string>

using namespace std;

Cell::Cell(){};
Cell::Cell(int val) { value = val; }

string Cell::writeLeft() {
  if (left == true)
    return "T";
  else
    return "F";
}
string Cell::writeTop() {
  if (top == true)
    return "T";
  else
    return "F";
}

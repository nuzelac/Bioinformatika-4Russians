/*
 * Blok.h
 * Header used to describe Blok class
 * Blok class represents one submatrix used in algorithm
 * Each Blok is consisted of Cell
 * 
 */

#include "Cell.h"
#include <vector>
#include <string>

using namespace std;

class Blok {
 public:
  int sumDown = 0;
  Cell** matrix = NULL;
  
  /*
   * Constructors for Blok Class
   * Each Blok is consisted of multiple cells
   * Each Blok is representation of one submatrix
   * Four Russian method splits main matrix in submatrices (Bloks)
   */
  Blok(int tVal, signed char* topS, signed char* leftS, int* topO, int* leftO);
  Blok();
  
  /*
   * Simple method used for printing data
   */ 
  string printOut(vector<string> offsetA, vector<string> offsetB, string topS,
                  string leftS);
  /*
   * Calculation od down offset
   * Part of algorithm 
   */ 
  int calcDownOffsets(int tVal);
  
   /*
    * Calculation od right offset
    * Part of algorithm 
    */ 
  int calcRightOffsets(int tVal);
};

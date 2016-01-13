/*
 * Block.h
 * Header used to describe Block class
 * Block class represents one submatrix used in algorithm
 * Each Block is consisted of Cell
 * 
 */

#include "Cell.h"
#include <vector>
#include <string>

using namespace std;

class Block {
 public:
  int sumDown = 0;
  Cell** matrix = NULL;
  
  /*
   * Constructors for Block Class
   * Each Block is consisted of multiple cells
   * Each Block is representation of one submatrix
   * Four Russian method splits main matrix in submatrices (Bloks)
   */
  Block(int tVal, signed char* topS, signed char* leftS, int* topO, int* leftO);
  Block();
  
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

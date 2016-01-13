/*
 * FourRussians.h
 * Header used to desribes FourRussians header
 * Class describes implemented algorithm
 * 
 */ 

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cmath>
#include <thread>
#include "Block.h"
#include "Hash.h"

using namespace std;

class FourRussians {
 public:
  string text;
  string stringA;
  string stringB;
  int tValue;
  string inputFileName;
  string outputFileName;
  int outputFormat;
  Hash hash;

  signed char* E = new signed char[4];
  int* O = new int[3];

  uint8_t* downOffsets;
  uint8_t* rightOffsets;

  Block* blocks = NULL;

  int* substringA;
  int* substringB;
  
  /*
   * Constructors
   * In constructors all atrubutes which will later be used are set
   */ 	
  FourRussians(string inputFileName, string outputFileName, int outputFormat,
               int tValue);
  /*
   * Generator of submatirces which will be used in algorithm
   */ 
  void generate(int i, int tValue, vector<int>& counters);
  
  /*
   * Calculation of optimal t value for algorithm
   */ 
  int calculateTValue(int lenA, int lenB) noexcept(true);
  
  /*
   * Calculation od edit matrix
   * Whole process of callculation is covered
   * Prints time values to get better perception of algorithm speed
   */
  int** calculateEditMatrix();
  
  /*
   * Method reads strings from input file
   */
  void readStrings();
  
  /*
   * Maethod returns size of Blocks
   */
  size_t getSizeBlocks();
  
  /*
   * Helper method that gets right part of string
   */ 
  void editStrings();
  
  /*
   * Implementation of edit script
   * Parsing option in which format output wll be generated
   * .maf or BLAST
   */ 
  void editScript(int** Matrix, int minDistance);
  
  /*
   * Calculation of minDistance
   */ 
  int calculateMinDistance(int** matrix);
  
  /*
   * Get right part of Array
   */
  void getsubArrays();
  
  /*
   * Implementation of preprocessing
   * Implementation supports parallel execution od preprocessing
   */
  void parallelPreProcessing();
};

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cmath>
#include <thread>
#include "Blok.h"
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

  Blok* blocks = NULL;

  int* substringA;
  int* substringB;

  FourRussians(string inputFileName, string outputFileName, int outputFormat,
               int tValue);
  void generate(int i, int tValue, vector<int>& counters);
  int calculateTValue(int lenA, int lenB) noexcept(true);
  int** calculateEditMatrix();
  void readStrings();
  size_t getSizeBlocks();
  void editStrings();
  void editScript(int** Matrix, int minDistance);
  int calculateMinDistance(int** matrix);
  void getsubArrays();
  void parallelPreProcessing();
};

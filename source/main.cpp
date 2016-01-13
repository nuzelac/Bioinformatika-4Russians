// cppttest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <thread>
#include <stack>
#include "FourRussians.h"

using namespace std;

int main() {
  std::clock_t start;
  double duration;
  FourRussians fourRussians;

  fourRussians.readStrings();
  fourRussians.tValue = fourRussians.calculateTValue((int)fourRussians.stringA.size(), (int)fourRussians.stringB.size());
  fourRussians.tValue = 3;

  fourRussians.threePowTValue = pow(3, fourRussians.tValue);
  fourRussians.fourPowTValue = pow(4, fourRussians.tValue);
  fourRussians.fourPowTValueSquare = fourRussians.fourPowTValue * fourRussians.fourPowTValue;
  fourRussians.K = fourRussians.threePowTValue * fourRussians.fourPowTValueSquare;

  fourRussians.downOffsets = new uint8_t[fourRussians.threePowTValue * fourRussians.threePowTValue *
                            fourRussians.fourPowTValueSquare];
  fourRussians.rightOffsets = new uint8_t[fourRussians.threePowTValue * fourRussians.threePowTValue *
                             fourRussians.fourPowTValueSquare];

  fourRussians.editStrings();
  cout << "Prvi string:" << fourRussians.stringA << endl;
  cout << "Drugi string:" << fourRussians.stringB << endl;

  cout << "T value;" << fourRussians.tValue << endl;
  cout << fourRussians.getSizeBlocks() << endl;

  double memory =
      sizeof(Blok) * fourRussians.getSizeBlocks() +
      fourRussians.getSizeBlocks() * sizeof(Cell) * (fourRussians.tValue + 1) * (fourRussians.tValue + 1);
  cout << "Memmory needed: " << ((memory / 1024) / 1024) << " MB" << endl;
  fourRussians.blocks = new Blok[fourRussians.getSizeBlocks()];

  cout << "Preprocessing STARTED" << endl;

  start = std::clock();

  fourRussians.parallelPreProcessing();

  fourRussians.getsubArrays();
  cout << "Preprocessing DONE" << endl;
  duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

  printf("Maksimalni hash: %d\n", fourRussians.maximum);

  std::cout << "Duration of preprocessing:" << duration << " s\n";
  start = std::clock();

  int** distanceMatrix = fourRussians.calculateEditMatrix(
      (int)fourRussians.stringA.size(), (int)fourRussians.stringB.size(), fourRussians.substringA, fourRussians.substringB);
  duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

  std::cout << "Duration of calculating min distance:" << duration << '\n';

  fourRussians.writeMinDistance(distanceMatrix);

  start = std::clock();

  fourRussians.editScript(distanceMatrix);

  duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

  std::cout << "Duration of calculating edit script:" << duration << '\n';
  fourRussians.outputFile.close();

  delete[] fourRussians.blocks;
  return 0;
}
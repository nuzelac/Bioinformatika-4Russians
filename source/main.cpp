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

int main(int argc, char** argv) {
  std::clock_t start;
  double duration;
  FourRussians fourRussians;
  
  string fileName;
  string outputFileName;
  string tValueString;
  int value;
  int outputFormat;
	
  vector<string> cmdLineArgs(argv, argv+argc);
	
	/*
	 * Arguments passed:
	 * File name - file which is consisted of two string 
	 * 			   (which will be aligned)
	 * 
	 * t - value which will be used in algorithm
	 * 
	 */
	 
  for(auto& arg : cmdLineArgs){
    if(arg == "--help" || arg == "-help") {
		std::cout << "\n";
		std::cout << "To run program: progName inputFile outputFile"; 
		std::cout <<" format tValue\n";
		std::cout <<"Format:\n";
		std::cout <<"--- 0 .maf format\n";
		std::cout <<"--- 1 BLAST\n";
		std::cout << "Tvalue equal or grater than one\n";
		std::cout << "\n";
		exit(0);
		}
	}
	 
  if(argc != 5) {
	std::cout << "\n";
	std::cout << "Run progName --help or progName -help\n";
	std::cout << "To see how to properly run code\n";
	std::cout << "\n";
	exit(1);
  } else {
	 fileName = argv[1];
	 outputFileName = argv[2];
	 outputFormat = atoi(argv[3]);
	 tValueString = argv[4];
	 value = atoi(tValueString.c_str());
	 //std::cout << outputFormat;
		 
	 if(value == 0) {
		std::cout << "\n";
		std::cout << "Tvalue equal or grater than one\n";
		std::cout << "Run progName --help or progName -help\n";
		std::cout << "To see how to properly run code\n";
		std::cout << "\n";
		exit(100);
	}
		 
	if(outputFormat < 0 || outputFormat > 1 ) {
		std::cout << "\n";
		std::cout << "Format can be 0 or 1\n";
		std::cout << "Run progName --help or progName -help\n";
		std::cout << "To see how to properly run code\n";
		std::cout << "\n";
		exit(100);
	}
		 
  }
  
  fourRussians.outputFormat = outputFormat;
  fourRussians.fileName = fileName;
  fourRussians.outputFileName = outputFileName;
  fourRussians.readStrings();
  fourRussians.tValue = fourRussians.calculateTValue((int)fourRussians.stringA.size(), (int)fourRussians.stringB.size());
  fourRussians.tValue = value;

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
  
  delete[] fourRussians.blocks;
  return 0;
}

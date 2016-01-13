#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "Blok.h"
#include <cmath>
#include <thread>

//int tVrijednost;

using namespace std;

class FourRussians {
public:
	std::map<int, string> hashevi;
	string text;
	string stringA;
	string stringB;
	int tValue;
	string inputFileName;
    string outputFileName;
    int outputFormat;

	signed char* E = new signed char[4];
	int* O = new int[3];

	int threePowTValue;
	int fourPowTValue;
	int fourPowTValueSquare;
	uint8_t* downOffsets;
	uint8_t* rightOffsets;

	Blok* blocks = NULL;

	int* substringA;
	int* substringB;

	FourRussians(string inputFileName, string outputFileName, int outputFormat, int tValue);
	int hashOffsetsTop(int* cnters);
	int hashOffsetsLeft(int* cnters);
	int format_offset(string offset);
	inline int format_letters(string& letters);
	inline int merge_hashes(int h1, int h2, int h3, int h4);
	int to_hash(string offset1, string offset2, string& a1, string& a2);
	int to_hash(int h1, string offset2, int h3, int h4);
	int to_hash(string offset1, int h2, int h3, int h4);
	int to_hash(string offset1, string offset2, int h3, int h4);
	int to_hash(int h1, int h2, int h3, int h4);
	void printOut(vector<string> v);
	string getString(vector<string> combo);
	void generate(int i, int tValue, vector<int>& counters);
	int calculateTValue(int lenA, int lenB) noexcept(true);
	int** calculateEditMatrix(int lenA, int lenB, int* substringA,
	                                 int* substringB);
	void readStrings();
	size_t getSizeBlocks();
	void editStrings();
	void editScript(int** Matrix);
	void writeMinDistance(int** matrix);
	int letter_to_num(char c);
	void getsubArrays();
	void parallelPreProcessing();

};


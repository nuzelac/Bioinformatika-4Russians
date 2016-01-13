// cppttest.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <memory.h>
//#include "cppttest.h"
#include <stdlib.h>
#include <cstdio>
#include <ctime>
#include <omp.h>
#include <unordered_map>
#include "Blok.h"

using namespace std;

int tValue;



int num1;
int numx;
int numy;
int* numA;
int* numB;
int hashf(int* cnters) {
	int numLetters = 0;
	int numOffsets = 0;
	for (int i = tValue * 4 - 1; i >= tValue * 2; i--)
		numLetters = numLetters + cnters[i] * numA[i-tValue*2];
	for (int i = tValue * 2 - 1; i >= 0; i--)
		numOffsets = numOffsets + cnters[i] * numB[i];

	return num1*numLetters + numOffsets;
}

int hashOffsetsTop(int* cnters) {

	int numOffsets = 0;
	for (int i = tValue - 1; i >= 0; i--)
		numOffsets = numOffsets + cnters[i] * numB[i];

	return numOffsets;
}
int hashOffsetsLeft(int* cnters) {

	int numOffsets = 0;
	for (int i = tValue - 1; i >= 0; i--)
		numOffsets = numOffsets + cnters[i] * numB[i+tValue];

	return numOffsets;
}
int hashLetters(int* cnters) {

	int numLetters = 0;
	for (int i = tValue * 2 - 1; i >= 0 ; i--)
		numLetters = numLetters + cnters[i] * numA[i];

	return num1*numLetters;
}

void printOut(vector<string> v) {
	for (int i = 0; i < v.size(); i++)
		cout << v[i];
	cout << endl;

}


Blok *blocks = NULL;
string text;
string stringA;
string stringB;

signed char* E = new signed char[4];
int* O = new int[3];
ofstream outputFile("program3data.txt");
//...

string getString(vector<string> combo) {
	string s = "";
	for (int i = 0; i < combo.size(); i++)
		s = s + (string)combo[i];
	return s;
}



void preProcess() {

	blocks = new Blok[(int)(pow(3,tValue*2)*pow(4,tValue*2))];
	E[0] = 'A';
	E[1] = 'C';
	E[2] = 'T';
	E[3] = 'G';
	O[0] = -1;
	O[1] = 0;
	O[2] = 1;
	

	int* counters = new int[tValue*4];
	for (int i = 0; i < tValue* 4; i++)
		counters[i] = 0;
	int start = tValue * 4 - 1;
	int hash = 0;
	int cnter = 0;
	int* topO = new int[tValue];
	int* leftO = new int[tValue];
	signed char* topS = new signed char[tValue];
	signed char* leftS = new signed char[tValue];
	
	std::clock_t timer;
	double duration;

	timer = std::clock();

	while (counters[0] <= 2) {
		cnter++;
		hash = hashf(counters);
		for (int i = 0; i < tValue; i++)
			topO[i] = O[counters[i]];
		for (int i = tValue; i < tValue * 2; i++)
			leftO[i-tValue] = O[counters[i]];
		for (int i = tValue*2; i < tValue*3; i++)
			topS[i-tValue*2] = E[counters[i]];
		for (int i = tValue*3; i < tValue * 4; i++)
			leftS[i-tValue*3] = E[counters[i]];
		blocks[hash] = Blok(tValue,topS, leftS, topO, leftO );
		counters[start]++;
		if (counters[start] > 3) {
			counters[start] = 0;
			bool repeat = true;
			int offset = 1;
			
			while (repeat) {
				if ((start - offset) > (start - 2 * tValue)) {
					if (counters[start - offset] < 3) {
						counters[start - offset]++;
						repeat = false;
					}
					else {
						counters[start - offset] = 0;
						offset++;
					}
				}
				else {
					if (counters[start - offset] < 2) {
						counters[start - offset]++;
						repeat = false;
					}
					else {
						if (start - offset == 0) {
							repeat = false;
							counters[0] = 3;
						}
						else {
							counters[start - offset] = 0;
							offset++;
						}
					}
				}
			}
		}

		
		
		/**/
		if (cnter % 100000 == 0) {
			duration = (std::clock() - timer) / (double)CLOCKS_PER_SEC;

			std::cout << "Duration of 100 000 blocs preprocessed:" << duration << '\n';
			cout << cnter << endl;
		}
		//cout << cnter << endl;
	}
	cout << cnter << endl;
	//blokovi.push_back(Blok());

}
int calculateTValue(int lenA, int lenB) noexcept(true) {
	int len = 0;
	if (lenA > lenB)
		len = lenA;
	else
		len = lenB;
	double t = (log(len) / log(12)) / 2;

	return ((int)t + 1);
}

int** calculateDistanceMatrix(int lenA, int lenB, int* subStringA, int* subStringB) {
	
	int** matrix = NULL;
	matrix = new int*[lenB / tValue];
	const int sizeInt = 4 * tValue;

	/* Your algorithm here */



	int lenb = lenB / tValue;
	int lena = lenA / tValue;
	for (int h = 0; h < lenb; h++)
		matrix[h] = new int[lena];



	int idx = 0;



	int* s = new int[tValue * 4];
	int* sL = new int[tValue * 2];


	
	int cnter = 0;
	double duration = 0;
	std::clock_t start;
	start = std::clock();
	int nizcnter = 0;
	for (int i = 0; i < tValue*2; i++)
		s[i] = 2;	
	for (int i = tValue * 2; i < tValue * 3; i++)
		s[i] = subStringA[nizcnter++];
	nizcnter = 0;
	for (int i = tValue * 3; i < tValue * 4; i++)
		s[i] = subStringB[nizcnter++];
	
	matrix[0][0] = hashf(s);
	
	cout << endl;
	Blok b,bTop,bLeft;
	for (int k = 1; k < lena; k++) {
		idx = k*tValue;
		b = blocks[matrix[0][k - 1]];
		memcpy(s + tValue, b.rightOffsets, sizeInt);
		
		for (int i = tValue * 2; i < tValue * 3; i++)
			s[i] = subStringA[idx++];
		matrix[0][k] = hashf(s);
		
		
	}
	
	
	for (int i = 1; i < lenb; i++) {
		idx = i*tValue;
		
		b = blocks[matrix[i - 1][0]];
		memcpy(s, b.downOffsets, sizeInt);
		
		for (int k = tValue; k < tValue * 2; k++)
			s[k] = 2;
		nizcnter = 0;
		for (int k = tValue * 2; k < tValue * 3; k++)
			s[k] = subStringA[nizcnter++];
		
		for (int k = tValue * 3; k < tValue * 4; k++) {
			s[k] = subStringB[idx++];
			sL[k - tValue * 2] = s[k];
		}
		
		//cout << i << endl;
		matrix[i][0] = hashf(s);
		
		if (cnter % 1000 == 0) {
			cout << cnter << endl;
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			start = std::clock();
			std::cout << "Computation of 1000 blocks takes time:" << duration << " s \n";
		}
		cnter++;

		
		for (int j = 1; j < lena; j++) {
			 idx = j*tValue;
			 //b = blokovi[matrica[i - 1][j]];
			 //memcpy(s, b.downOffsets, sizeInt);
			
			
			 //b = blokovi[matrica[i][j - 1]];
			
			 //memcpy(s+tVrijednost, b.rightOffsets, sizeInt);
			 for (int k = tValue * 2; k < tValue * 3; k++) {
				 s[k] = subStringA[idx++];
				 sL[k - tValue * 2] = s[k];
			 }
			 bTop = blocks[matrix[i - 1][j]];
			 bLeft = blocks[matrix[i][j - 1]];
			 
			 matrix[i][j] = bTop.hashDownOffsets + bLeft.hashRightOffsets + hashLetters(sL);
			// matrica[i][j] = hashf(s);
		}

		//	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

		//	std::cout << "\Computation of All blocks takes time:" << duration * 1000 << " ms \n";

	}
	
	return matrix;
}


void readStrings(string fileName) {
	//ifstream infile("primjer-10000.in");
	ifstream infile(fileName);
	if (!infile.is_open()) {
		cout << " Failed to open file" << endl;
	}
	else {
		cout << "Opened OK" << endl;
	}
	int cnt = 0;
	while (!infile.eof()) // To get you all the lines.
	{
		getline(infile, text); // Saves the line in STRING.
		if (cnt == 0)
			stringA = text;
		else if (cnt == 1)
			stringB = text;
		cnt++;

		//cout << text << endl; // Prints our STRING.
	}
	infile.close();
}

size_t getSizeBlokovi() {
	size_t val = pow(3, tValue * 2)*pow(4, tValue * 2);
	return val;
}

void editStrings() {
	while (stringA.size() % tValue != 0)
		stringA = stringA.substr(0, stringA.size() - 1);
	while (stringB.size() % tValue != 0)
		stringB = stringB.substr(0, stringB.size() - 1);
}
int* subStringA;
int* subStringB;
void editScript(int** Matrix) {
	
	
	

	int i = stringB.size()/tValue-1; // {i = ROWS in int**}
	int j = stringA.size()/tValue-1; // {j = COLS in int**}
	int a = tValue;
	int b = tValue;
	int cnterB = stringB.size()-1;
	int cnterA = stringA.size()-1;
	Cell** matrix;
	//a = 0 -> got top in matrica {a = ROWS in Cell**}
	//b = 0 - > got left in matrica {b = COLS in Cell**}
	int cnter = 0;
	int size;
	if (stringA.size() > stringB.size())
		size = stringA.size();
	else size = stringB.size();
	int val = size * 2;
	vector<char> first(val);
	vector<char> second(val);
	vector<char> middle(val);

	cout << i << " " << j << endl;
	while ( (i+j)!=0 ) 
	{				
		matrix = blocks[Matrix[i][j]].matrix;
		while (true) {
			if (matrix[a][b].top == true && matrix[a][b].left == true) {
				a--;
				b--;
				first.insert(first.begin(), stringA[cnterA]);
				second.insert(second.begin(), stringB[cnterB]);
				if (stringA[cnterA] == stringB[cnterB]) {
					middle.insert(middle.begin(), '|');
				}
				else middle.insert(middle.begin(), '.');
				cnterA--;
				cnterB--;
			}
			else if (matrix[a][b].top == true) {
				a--;
				second.insert(second.begin(), stringB[cnterB]);
				first.insert(first.begin(), '-');
				middle.insert(middle.begin(), ' ');
				cnterB--;
			}
			else {
				b--;
				second.insert(second.begin(), '-');
				first.insert(first.begin(), stringA[cnterA]);
				middle.insert(middle.begin(), ' ');
				cnterA--;
			}
			cnter++;
			if (i == 0 && j != 0) {
				if (a <= 0)
					a = 0;
				if (b == 0)
					break;
			}
			else if (j == 0 && i != 0) {
				if (b <= 0)
					b = 0;
				if (a == 0)
					break;
			}
			else {
				if (a == 0 || b == 0)
					break;
			}
			
		}
		if (a == 0 && b == 0) {
			if (i == 0) {
				j--;
				a = 0;
				b = tValue;
			} else if(j == 0) {
				i--;
				b = 0;
				a = tValue;
			}
			else {
				i--;
				j--;
				a = tValue;
				b = tValue;
			}
			
		}
		else if (a == 0) {
				i--;
				a = tValue;			
		}
		else if (b == 0) {
				j--;
				b = tValue;			
		}
		//cout << i << " " << j << endl;
	}
	
	matrix = blocks[Matrix[0][0]].matrix;
	while (true) {
		if (matrix[a][b].top == true && matrix[a][b].left == true) {
			a--;
			b--;
			first.insert(first.begin(), stringA[cnterA]);
			second.insert(second.begin(), stringB[cnterB]);
			if (stringA[cnterA] == stringB[cnterB]) {
				middle.insert(middle.begin(), '|');
			}
			else middle.insert(middle.begin(), '.');
			cnterA--;
			cnterB--;
		}
		else if (matrix[a][b].top == true) {
			a--;
			second.insert(second.begin(), stringB[cnterB]);
			first.insert(first.begin(), '-');
			middle.insert(middle.begin(), ' ');
			cnterB--;
		}
		else {
			b--;
			second.insert(second.begin(), '-');
			first.insert(first.begin(), stringA[cnterA]);
			middle.insert(middle.begin(), ' ');
			cnterA--;
		}
		cnter++;
		if (a == 0 && b == 0)
			break;
	}
	/*
	for (int i = 0; i < cnter; i++)
		cout << prvi[i];
	cout << endl;
	for (int i = 0; i < cnter; i++)
		cout << srednji[i];
	cout << endl;
	for (int i = 0; i < cnter; i++)
		cout << drugi[i];
	cout << endl;
	*/
	
	int x = 1;
	if (size > 100)
		x = 60;
	else x = cnter;
	for (int j = 0; j < cnter; j = j + x) {
		outputFile << "Lines:" << j << " - " << (j+x) << endl;
		for (int i = j; i < j + x && i < cnter ;i++) {
			outputFile << first[i];
	}
	outputFile << endl;
	for (int i = j; i < j + x && i < cnter; i++) {
		outputFile << middle[i];
	}
	outputFile << endl;
	for (int i = j; i < j + x && i < cnter; i++) {
		outputFile << second[i];
	}
	outputFile << endl;
	}
	outputFile << endl;
	
	
}

void writeMinDistance(int** matrix) {

	int min = 0;

	for (int j = 0; j < stringA.size() / tValue; j++) {
		min = min + blocks[matrix[stringB.size() / tValue - 1][j]].sumaDown;
	}
	min = min + stringB.size();
	cout << "MIN DISTANCE:" << min << endl;

}
int getNumfromString(char s) {
	if (s == 'A')
		return 0;
	else if (s == 'C')
		return 1;
	else if (s == 'T')
		return 2;
	else
		return 3;
}



void getsubArrays() {
	subStringA = new int[stringA.size()];
	subStringB = new int[stringB.size()];
	
	for (int i = 0; i < stringA.size(); i++) {
		subStringA[i] = getNumfromString(stringA[i]);
	}
	for (int i = 0; i < stringB.size(); i++) {
		subStringB[i] = getNumfromString(stringB[i]);
	}
}
int main(int argc, char** argv)
{
	//int c;
	string fileName;
	string tValueString;
	int value;
	vector<string> cmdLineArgs(argv, argv+argc);
	
	/*
	 * Arguments passed:
	 * File name - file which is consisted of two string 
	 * 			   (which will be aligned)
	 * 
	 * t - value which will be used in algorithm
	 * 
	 */
	 
	for(auto& arg : cmdLineArgs)
	{
		if(arg == "--help" || arg == "-help") {
			std::cout << "\n";
			std::cout << "To run program: progName outputFile tValue\n";
			std::cout << "If second value is string 0 will be taken for tValue\n";
			std::cout << "\n";
			exit(0);
		}
	}
	 
	 
	 
	 if(argc != 3) {
		std::cout << "\n";
		std::cout << "Run progName --help or progName -help\n";
		std::cout << "To see how to properly run code\n";
		std::cout << "\n";
		exit(1);
	 } else {
		 fileName = argv[1];
		 tValueString = argv[2];
		 value = atoi(tValueString.c_str());;
		 
		 std::cout << fileName;
		 std::cout << value;
		 //exit(0);
	 }
	
	std::clock_t start;
	double duration;
	

	readStrings(fileName);
	tValue = calculateTValue(stringA.size(), stringB.size());
	tValue = value;
	editStrings();
	//cout << "Prvi string:" << nizA << endl;
	//cout << "Drugi string:" << nizB << endl;

	cout << "T value;" << tValue << endl;
	cout << getSizeBlokovi() << endl;
	//getchar() ;
	double memory = sizeof(Blok) * getSizeBlokovi();
	cout << "Memmory needed: " << ((memory / 1024) / 1024) << " MB" << endl;
	blocks = new Blok[getSizeBlokovi()];

	num1 = (pow(3, tValue * 2));
	numx = tValue * 2 - 1;
	numy = tValue * 2 - 1;
	numA = new int[tValue * 2];
	numB = new int[tValue * 2];
	for (int i = tValue * 2 - 1; i >= 0; i--) 
		numA[i] = pow(4, (numx - i));
	
	for (int i = tValue * 2 - 1; i >= 0; i--)
		numB[i]=pow(3, (numy - i));

	cout << "Preprocessing STARTED" << endl;


	start = std::clock();
	preProcess();
	;
	/*
	string s = "1111ATTC";
	std::hash<string> hash_f;
	cout << blokovi[myMap.find(hash_f(s))->second].ispisi() << endl;
	blokovi[myMap.find(hash_f(s))->second].ispisiSVE();
	getchar();
	*/
	getsubArrays();
	cout << "Preprocessing DONE" << endl;
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "Duration of preprocessing:" << duration << " s\n";
	//getchar();
	start = std::clock();

	/* Your algorithm here */


	int** matricaUdaljenosti = calculateDistanceMatrix(stringA.size(), stringB.size(), subStringA, subStringB);
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "Duration of calculating min distance:" << duration << '\n';
	
	writeMinDistance(matricaUdaljenosti);
	getchar();
	start = std::clock();

	/* Your algorithm here */



	editScript(matricaUdaljenosti);

	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "Duration of calculating edit script:" << duration << '\n';
	outputFile.close();
	getchar();

	// delete all allocated memory
	delete[] blocks;
	return 0;
}

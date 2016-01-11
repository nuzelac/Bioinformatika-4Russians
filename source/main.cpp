// cppttest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "cppttest.h"
#include <cstdio>
#include <ctime>
#include <omp.h>
#include <unordered_map>

using namespace std;

int tVrijednost;


class Cell {

public:	
	int value;
	bool top;
	bool left;
	Cell() {};
	Cell(int val) { value = val; }
	
	string writeLeft() {
		if (left == true)
			return "T";
		else return "F";
	}
	string writeTop() {
		if (top == true)
			return "T";
		else return "F";
	}

};


int num1;
int numx;
int numy;
int* numA;
int* numB;
int hashf(int* cnters) {
	int numLetters = 0;
	int numOffsets = 0;
	for (int i = tVrijednost * 4 - 1; i >= tVrijednost * 2; i--)
		numLetters = numLetters + cnters[i] * numA[i-tVrijednost*2];
	for (int i = tVrijednost * 2 - 1; i >= 0; i--)
		numOffsets = numOffsets + cnters[i] * numB[i];

	return num1*numLetters + numOffsets;
}

int hashOffsetsTop(int* cnters) {

	int numOffsets = 0;
	for (int i = tVrijednost - 1; i >= 0; i--)
		numOffsets = numOffsets + cnters[i] * numB[i];

	return numOffsets;
}
int hashOffsetsLeft(int* cnters) {

	int numOffsets = 0;
	for (int i = tVrijednost - 1; i >= 0; i--)
		numOffsets = numOffsets + cnters[i] * numB[i+tVrijednost];

	return numOffsets;
}
int hashLetters(int* cnters) {

	int numLetters = 0;
	for (int i = tVrijednost * 2 - 1; i >= 0 ; i--)
		numLetters = numLetters + cnters[i] * numA[i];

	return num1*numLetters;
}


class Blok {

public:
	int* downOffsets;
	int* rightOffsets;
	int hashRightOffsets;
	int hashDownOffsets;
	int sumaDown = 0;
	Cell** matrix = NULL;
	Blok() {};
	Blok(int tVal, signed char* topS, signed char* leftS, int* topO, int* leftO) {


		downOffsets = new int[tVal];
		rightOffsets = new int[tVal];
		
		matrix = new Cell*[tVal + 1];

		for (int i = 0; i < tVal + 1; i++) {
			matrix[i] = new Cell[tVal + 1];
		}
		matrix[0][0] = Cell(0);

		for (int i = 1; i < tVal + 1; i++) {
			matrix[0][i] = Cell(matrix[0][i - 1].value + topO[i - 1]);
			matrix[0][i].left = true;
			matrix[0][i].top = false;
			matrix[i][0] = Cell(matrix[i - 1][0].value + leftO[i - 1]);
			matrix[i][0].left = false;
			matrix[i][0].top = true;
		}
		int min = 0;
		for (int i = 1; i < tVal + 1; i++) {
			for (int j = 1; j < tVal + 1; j++) {
				if (topS[j - 1] == leftS[i - 1]) {

					matrix[i][j] = Cell(matrix[i - 1][j - 1].value);
					matrix[i][j].top = true;
					matrix[i][j].left = true;
				}

				else if (matrix[i - 1][j - 1].value <= matrix[i - 1][j].value && matrix[i - 1][j - 1].value <= matrix[i][j - 1].value) {

					matrix[i][j] = Cell(matrix[i - 1][j - 1].value + 1);
					matrix[i][j].top = true;
					matrix[i][j].left = true;
				}
				else if (matrix[i - 1][j].value <= matrix[i - 1][j - 1].value && matrix[i - 1][j].value <= matrix[i][j - 1].value) {

					matrix[i][j] = Cell(matrix[i - 1][j].value + 1);
					matrix[i][j].top = true;
					matrix[i][j].left = false;
				}
				else {

					matrix[i][j] = Cell(matrix[i][j - 1].value + 1);
					matrix[i][j].top = false;
					matrix[i][j].left = true;
				}
			}
		}

		

		//down offsets
		for (int i = 1; i <= tVal; i++) {
			downOffsets[i-1] = (matrix[tVal][i].value - matrix[tVal][i - 1].value+1);
			sumaDown = sumaDown + (matrix[tVal][i].value - matrix[tVal][i - 1].value);
		}
		
		//right offsets
		for (int i = 1; i <= tVal; i++)
			rightOffsets[i-1] = (matrix[i][tVal].value - matrix[i - 1][tVal].value+1);

		hashRightOffsets = hashOffsetsLeft(rightOffsets);
		hashDownOffsets = hashOffsetsTop(downOffsets);
	}
	

	void ispisiMatrixValues(int tVrijednost) {
		for (int i = 0; i <= tVrijednost; i++) {
			for (int j = 0; j <= tVrijednost; j++)
				cout << matrix[i][j].value << " ";
			cout << endl;
		}
		cout << endl;
	}
};
void ispisi(vector<string> v) {
	for (int i = 0; i < v.size(); i++)
		cout << v[i];
	cout << endl;

}


Blok *blokovi = NULL;
string text;
string nizA;
string nizB;

signed char* E = new signed char[4];
int* O = new int[3];
ofstream outputFile("E:\program3data.txt");
//...

string getString(vector<string> combo) {
	string s = "";
	for (int i = 0; i < combo.size(); i++)
		s = s + (string)combo[i];
	return s;
}



void pretprocesiranje() {

	blokovi = new Blok[(int)(pow(3,tVrijednost*2)*pow(4,tVrijednost*2))];
	E[0] = 'A';
	E[1] = 'C';
	E[2] = 'T';
	E[3] = 'G';
	O[0] = -1;
	O[1] = 0;
	O[2] = 1;
	

	int* counters = new int[tVrijednost*4];
	for (int i = 0; i < tVrijednost * 4; i++)
		counters[i] = 0;
	int start = tVrijednost * 4 - 1;
	int hash = 0;
	int cnter = 0;
	int* topO = new int[tVrijednost];
	int* leftO = new int[tVrijednost];
	signed char* topS = new signed char[tVrijednost];
	signed char* leftS = new signed char[tVrijednost];
	
	std::clock_t timer;
	double duration;

	timer = std::clock();

	while (counters[0] <= 2) {
		cnter++;
		hash = hashf(counters);
		for (int i = 0; i < tVrijednost; i++)
			topO[i] = O[counters[i]];
		for (int i = tVrijednost; i < tVrijednost * 2; i++)
			leftO[i-tVrijednost] = O[counters[i]];
		for (int i = tVrijednost*2; i < tVrijednost*3; i++)
			topS[i-tVrijednost*2] = E[counters[i]];
		for (int i = tVrijednost*3; i < tVrijednost * 4; i++)
			leftS[i-tVrijednost*3] = E[counters[i]];
		blokovi[hash] = Blok(tVrijednost,topS, leftS, topO, leftO );
		counters[start]++;
		if (counters[start] > 3) {
			counters[start] = 0;
			bool repeat = true;
			int pomak = 1;
			
			while (repeat) {
				if ((start - pomak) > (start - 2 * tVrijednost)) {
					if (counters[start - pomak] < 3) {
						counters[start - pomak]++;
						repeat = false;
					}
					else {
						counters[start - pomak] = 0;
						pomak++;
					}
				}
				else {
					if (counters[start - pomak] < 2) {
						counters[start - pomak]++;
						repeat = false;
					}
					else {
						if (start - pomak == 0) {
							repeat = false;
							counters[0] = 3;
						}
						else {
							counters[start - pomak] = 0;
							pomak++;
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

int** calculatematricaUdaljenost(int lenA, int lenB, int* podnizA, int* podnizB) {
	
	int** matrica = NULL;
	matrica = new int*[lenB / tVrijednost];
	const int sizeInt = 4 * tVrijednost;

	/* Your algorithm here */



	int lenb = lenB / tVrijednost;
	int lena = lenA / tVrijednost;
	for (int h = 0; h < lenb; h++)
		matrica[h] = new int[lena];



	int idx = 0;



	int* s = new int[tVrijednost * 4];
	int* sL = new int[tVrijednost * 2];


	
	int cnter = 0;
	double duration = 0;
	std::clock_t start;
	start = std::clock();
	int nizcnter = 0;
	for (int i = 0; i < tVrijednost*2; i++)
		s[i] = 2;	
	for (int i = tVrijednost * 2; i < tVrijednost * 3; i++)
		s[i] = podnizA[nizcnter++];
	nizcnter = 0;
	for (int i = tVrijednost * 3; i < tVrijednost * 4; i++)
		s[i] = podnizB[nizcnter++];
	
	matrica[0][0] = hashf(s);
	
	cout << endl;
	Blok b,bTop,bLeft;
	for (int k = 1; k < lena; k++) {
		idx = k*tVrijednost;
		b = blokovi[matrica[0][k - 1]];
		memcpy(s + tVrijednost, b.rightOffsets, sizeInt);
		
		for (int i = tVrijednost * 2; i < tVrijednost * 3; i++)
			s[i] = podnizA[idx++];
		matrica[0][k] = hashf(s);
		
		
	}
	
	
	for (int i = 1; i < lenb; i++) {
		idx = i*tVrijednost;
		
		b = blokovi[matrica[i - 1][0]];
		memcpy(s, b.downOffsets, sizeInt);
		
		for (int k = tVrijednost; k < tVrijednost * 2; k++)
			s[k] = 2;
		nizcnter = 0;
		for (int k = tVrijednost * 2; k < tVrijednost * 3; k++)
			s[k] = podnizA[nizcnter++];
		
		for (int k = tVrijednost * 3; k < tVrijednost * 4; k++) {
			s[k] = podnizB[idx++];
			sL[k - tVrijednost * 2] = s[k];
		}
		
		//cout << i << endl;
		matrica[i][0] = hashf(s);
		
		if (cnter % 1000 == 0) {
			cout << cnter << endl;
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			start = std::clock();
			std::cout << "\Computation of 1000 blocks takes time:" << duration << " s \n";
		}
		cnter++;

		
		for (int j = 1; j < lena; j++) {
			 idx = j*tVrijednost;
			 //b = blokovi[matrica[i - 1][j]];
			 //memcpy(s, b.downOffsets, sizeInt);
			
			
			 //b = blokovi[matrica[i][j - 1]];
			
			 //memcpy(s+tVrijednost, b.rightOffsets, sizeInt);
			 for (int k = tVrijednost * 2; k < tVrijednost * 3; k++) {
				 s[k] = podnizA[idx++];
				 sL[k - tVrijednost * 2] = s[k];
			 }
			 bTop = blokovi[matrica[i - 1][j]];
			 bLeft = blokovi[matrica[i][j - 1]];
			 
			 matrica[i][j] = bTop.hashDownOffsets + bLeft.hashRightOffsets + hashLetters(sL);
			// matrica[i][j] = hashf(s);
		}

		//	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

		//	std::cout << "\Computation of All blocks takes time:" << duration * 1000 << " ms \n";

	}
	
	return matrica;
}


void ucitajNizove() {
	ifstream infile("E:/nizoviBaza.txt");
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
			nizA = text;
		else if (cnt == 1)
			nizB = text;
		cnt++;

		//cout << text << endl; // Prints our STRING.
	}
	infile.close();
}

size_t getSizeBlokovi() {
	size_t val = pow(3, tVrijednost * 2)*pow(4, tVrijednost * 2);
	return val;
}

void urediNizove() {
	while (nizA.size() % tVrijednost != 0)
		nizA = nizA.substr(0, nizA.size() - 1);
	while (nizB.size() % tVrijednost != 0)
		nizB = nizB.substr(0, nizB.size() - 1);
}
int* podnizA;
int* podnizB;
void editScript(int** matrica) {
	
	
	

	int i = nizB.size()/tVrijednost-1; // {i = ROWS in int**}
	int j = nizA.size()/tVrijednost-1; // {j = COLS in int**}
	int a = tVrijednost;
	int b = tVrijednost;
	int cnterB = nizB.size()-1;
	int cnterA = nizA.size()-1;
	Cell** matrix;
	//a = 0 -> got top in matrica {a = ROWS in Cell**}
	//b = 0 - > got left in matrica {b = COLS in Cell**}
	int cnter = 0;
	int size;
	if (nizA.size() > nizB.size())
		size = nizA.size();
	else size = nizB.size();
	int val = size * 2;
	vector<char> prvi(val);
	vector<char> drugi(val);
	vector<char> srednji(val);

	cout << i << " " << j << endl;
	while ( (i+j)!=0 ) 
	{				
		matrix = blokovi[matrica[i][j]].matrix;
		while (true) {
			if (matrix[a][b].top == true && matrix[a][b].left == true) {
				a--;
				b--;
				prvi.insert(prvi.begin(), nizA[cnterA]);
				drugi.insert(drugi.begin(), nizB[cnterB]);
				if (nizA[cnterA] == nizB[cnterB]) {
					srednji.insert(srednji.begin(), '\|');
				}
				else srednji.insert(srednji.begin(), '.');
				cnterA--;
				cnterB--;
			}
			else if (matrix[a][b].top == true) {
				a--;
				drugi.insert(drugi.begin(), nizB[cnterB]);
				prvi.insert(prvi.begin(), '-');
				srednji.insert(srednji.begin(), ' ');
				cnterB--;
			}
			else {
				b--;
				drugi.insert(drugi.begin(), '-');
				prvi.insert(prvi.begin(), nizA[cnterA]);
				srednji.insert(srednji.begin(), ' ');
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
				b = tVrijednost;
			} else if(j == 0) {
				i--;
				b = 0;
				a = tVrijednost;
			}
			else {
				i--;
				j--;
				a = tVrijednost;
				b = tVrijednost;
			}
			
		}
		else if (a == 0) {
				i--;
				a = tVrijednost;			
		}
		else if (b == 0) {
				j--;
				b = tVrijednost;			
		}
		//cout << i << " " << j << endl;
	}
	
	matrix = blokovi[matrica[0][0]].matrix;
	while (true) {
		if (matrix[a][b].top == true && matrix[a][b].left == true) {
			a--;
			b--;
			prvi.insert(prvi.begin(), nizA[cnterA]);
			drugi.insert(drugi.begin(), nizB[cnterB]);
			if (nizA[cnterA] == nizB[cnterB]) {
				srednji.insert(srednji.begin(), '\|');
			}
			else srednji.insert(srednji.begin(), '.');
			cnterA--;
			cnterB--;
		}
		else if (matrix[a][b].top == true) {
			a--;
			drugi.insert(drugi.begin(), nizB[cnterB]);
			prvi.insert(prvi.begin(), '-');
			srednji.insert(srednji.begin(), ' ');
			cnterB--;
		}
		else {
			b--;
			drugi.insert(drugi.begin(), '-');
			prvi.insert(prvi.begin(), nizA[cnterA]);
			srednji.insert(srednji.begin(), ' ');
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
		for (int i = j; i < j + x; i++) {
			outputFile << prvi[i];
	}
	outputFile << endl;
	for (int i = j; i < j + x; i++) {
		outputFile << srednji[i];
	}
	outputFile << endl;
	for (int i = j; i < j + x; i++) {
		outputFile << drugi[i];
	}
	outputFile << endl;
	}
	outputFile << endl;
	
	
}

void writeMinDistance(int** matrica) {

	int min = 0;

	for (int j = 0; j < nizA.size() / tVrijednost; j++) {
		min = min + blokovi[matrica[nizB.size() / tVrijednost - 1][j]].sumaDown;
	}
	min = min + nizB.size();
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
	podnizA = new int[nizA.size()];
	podnizB = new int[nizB.size()];
	
	for (int i = 0; i < nizA.size(); i++) {
		podnizA[i] = getNumfromString(nizA[i]);
	}
	for (int i = 0; i < nizB.size(); i++) {
		podnizB[i] = getNumfromString(nizB[i]);
	}
}
int main()
{
	std::clock_t start;
	double duration;
	

	ucitajNizove();
	tVrijednost = calculateTValue(nizA.size(), nizB.size());
	tVrijednost = 2;
	urediNizove();
	//cout << "Prvi string:" << nizA << endl;
	//cout << "Drugi string:" << nizB << endl;

	cout << "T value;" << tVrijednost << endl;
	cout << getSizeBlokovi() << endl;
	//getchar() ;
	double memory = sizeof(Blok) * getSizeBlokovi();
	cout << "Memmory needed: " << ((memory / 1024) / 1024) << " MB" << endl;
	blokovi = new Blok[getSizeBlokovi()];

	num1 = (pow(3, tVrijednost * 2));
	numx = tVrijednost * 2 - 1;
	numy = tVrijednost * 2 - 1;
	numA = new int[tVrijednost * 2];
	numB = new int[tVrijednost * 2];
	for (int i = tVrijednost * 2 - 1; i >= 0; i--) 
		numA[i] = pow(4, (numx - i));
	
	for (int i = tVrijednost * 2 - 1; i >= 0; i--)
		numB[i]=pow(3, (numy - i));

	cout << "Preprocessing STARTED" << endl;


	start = std::clock();
	pretprocesiranje();
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


	int** matricaUdaljenosti = calculatematricaUdaljenost(nizA.size(), nizB.size(), podnizA, podnizB);
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
	delete[] blokovi;
	return 0;
}
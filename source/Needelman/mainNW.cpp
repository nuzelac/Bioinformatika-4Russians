/*---------------------------------------------------------------
*
*   main.c++ for nw program.
*
*   Implements the Needleman-Wunsch algorithm
*   for global nucleotide sequence alignment.
*
*   Rolf Muertter,  rolf@dslextreme.com
*   9/5/2006
*
---------------------------------------------------------------*/
#include "nw.h"
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;


int  main(int argc, char ** argv)
{
	char *  program = *argv;
	bool    prm = true;

	if (argc > 2)
	{
		cerr << "\n   Usage:   " << program << " inputfile\n";

		exit(1);
	}
	// Sequences to be aligned
	string  seq_1 = "ATTTGGCA";
	string  seq_2 = "TCGGA";
	
	string  seq_1_al;
	string  seq_2_al;
	string text;
	// Aligned sequences
	ifstream infile(argv[1]);
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
			seq_1 = text;
		else if (cnt == 1)
			seq_2 = text;
		cnt++;

	}
	infile.close();
	
	const clock_t begin_time = clock();

	nw(seq_1, seq_2, seq_1_al, seq_2_al, prm);
	std::cout <<"Min distance calculation time:" <<float(clock() - begin_time) / CLOCKS_PER_SEC << "sec";
	
	getchar();
	return  0;
}


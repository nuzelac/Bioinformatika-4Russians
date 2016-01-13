
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

#include "stdafx.h"
#include "nw.h"
#include <time.h>

using namespace std;


int  main(int argc, char ** argv)
{
	char *  program = *argv;
	bool    prm = true;

	/*
	if (argc < 3)
	{
		cerr << "\n   Usage:   " << program << " file1 file2 [-p]\n";
		cerr << "\n   -p:       Print matrices\n";
		cerr << "\n   Output:   alignment\n\n";

		exit(1);
	}
	*/
	// Sequences to be aligned
	string  seq_1 = "ATTTGGCA";
	string  seq_2 = "TCGGA";
	/*
	if (argc == 4)
	{
		string  pr_arg = argv[3];
		if (pr_arg == "-p")  prm = true;   // Print matrices
	}
	*/
#if DEBUG
	cout << "seq_1: " << seq_1 << endl;
	cout << "seq_2: " << seq_2 << endl;
	cout << "-p: " << prm << endl;
#endif

	// Aligned sequences
	string  seq_1_al;
	string  seq_2_al;
	const clock_t begin_time = clock();
	// do something
	
	// Get alignment
	nw(seq_1, seq_2, seq_1_al, seq_2_al, prm);
	std::cout <<"Min distance calculation time:" <<float(clock() - begin_time) / CLOCKS_PER_SEC << "sec";
	// Print alignment
	//print_al(seq_1_al, seq_2_al);
	getchar();
	return  0;
}


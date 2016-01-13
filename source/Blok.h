#include "Cell.h"
#include <vector>
#include <string>

using namespace std;

class Blok {
public:
  uint8_t downOffsets = 0;
  uint8_t rightOffsets = 0;
  int sumDown = 0;
  Cell** matrix = NULL;

  Blok(int tVal, signed char* topS, signed char* leftS, int* topO, int* leftO);
	Blok();
	string printOut(vector<string> offsetA, vector<string> offsetB, string topS, string leftS);
	int getDownOffsets(int tVal);
	int getRightOffsets(int tVal);
};

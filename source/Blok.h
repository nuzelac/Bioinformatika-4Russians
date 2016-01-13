#include "Cell.h"
#include <vector>
#include <string>

using namespace std;

class Blok {
 public:
  int sumDown = 0;
  Cell** matrix = NULL;

  Blok(int tVal, signed char* topS, signed char* leftS, int* topO, int* leftO);
  Blok();
  string printOut(vector<string> offsetA, vector<string> offsetB, string topS,
                  string leftS);
  int calcDownOffsets(int tVal);
  int calcRightOffsets(int tVal);
};

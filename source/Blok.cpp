#include "Blok.h"
#include <iostream>
#include <string>

using namespace std;

Blok::Blok(){};
Blok::Blok(int tVal, signed char* topS, signed char* leftS, int* topO, int* leftO) {
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
  for (int i = 1; i < tVal + 1; i++) {
    for (int j = 1; j < tVal + 1; j++) {
      if (topS[j - 1] == leftS[i - 1]) {
        matrix[i][j] = Cell(matrix[i - 1][j - 1].value);
        matrix[i][j].top = true;
        matrix[i][j].left = true;
      }

      else if (matrix[i - 1][j - 1].value <= matrix[i - 1][j].value &&
               matrix[i - 1][j - 1].value <= matrix[i][j - 1].value) {
        matrix[i][j] = Cell(matrix[i - 1][j - 1].value + 1);
        matrix[i][j].top = true;
        matrix[i][j].left = true;
      } else if (matrix[i - 1][j].value <= matrix[i - 1][j - 1].value &&
                 matrix[i - 1][j].value <= matrix[i][j - 1].value) {
        matrix[i][j] = Cell(matrix[i - 1][j].value + 1);
        matrix[i][j].top = true;
        matrix[i][j].left = false;
      } else {
        matrix[i][j] = Cell(matrix[i][j - 1].value + 1);
        matrix[i][j].top = false;
        matrix[i][j].left = true;
      }
    }
  }

  for (int i = 1; i <= tVal; i++) {
    sumDown = sumDown + (matrix[tVal][i].value - matrix[tVal][i - 1].value);
  }
}

string Blok::printOut(vector<string> offsetA, vector<string> offsetB, string topS,
              string leftS) {
  string s = "";
  for (int i = 0; i < offsetA.size(); i++) s = s + offsetA[i];
  for (int i = 0; i < offsetA.size(); i++) s = s + offsetB[i];
  s = s + topS + leftS;
  return s;
}

int Blok::calcDownOffsets(int tVal) {
  int downOffsets = 0;
  for (int i = 1; i <= tVal; i++) {
    downOffsets = downOffsets * 3 +
                (matrix[tVal][i].value - matrix[tVal][i - 1].value + 1);
  }

  return downOffsets;
}
int Blok::calcRightOffsets(int tVal) {
  int rightOffsets = 0;

  for (int i = 1; i <= tVal; i++) {
    rightOffsets = rightOffsets * 3 +
                   (matrix[i][tVal].value - matrix[i - 1][tVal].value + 1);
  }

  return rightOffsets;
 }





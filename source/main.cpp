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

using namespace std;

std::map<int, string> hashevi;
string text;
string stringA;
string stringB;
int tValue;

signed char* E = new signed char[4];
int* O = new int[3];
ofstream outputFile("bla.txt");

int threePowTValue;
int fourPowTValue;
int fourPowTValueSquare;
uint8_t* downOffsets;
uint8_t* rightOffsets;

int format_offset(string offset) {
  int result = 0;
  int toPower = 3;
  for (int i = 0; i < offset.size(); ++i) {
    int val;
    if (offset[i] == '-') {
      val = 0;
      i++;
    } else if (offset[i] == '0') {
      val = 1;
    } else {
      val = 2;
    }

    result = result * toPower + val;
  }

  return result;
}

inline int format_letters(string& letters) {
  int result = 0;
  int toPower = 4;
  for (int i = 0; i < letters.size(); ++i) {
    int val;
    if (letters[i] == 'A') {
      val = 0;
    } else if (letters[i] == 'C') {
      val = 1;
    } else if (letters[i] == 'T') {
      val = 2;
    } else if (letters[i] == 'G') {
      val = 3;
    }

    result = result * toPower + val;
  }

  return result;
}

int maximum = 0;
int K;

inline int merge_hashes(int h1, int h2, int h3, int h4) {
  return h1 * threePowTValue * fourPowTValueSquare +
         h2 * fourPowTValueSquare + h3 * fourPowTValue + h4;
}

int to_hash(string offset1, string offset2, string& a1, string& a2) {
  int h1 = format_offset(offset1);
  int h2 = format_offset(offset2);
  int h3 = format_letters(a1);
  int h4 = format_letters(a2);

  int h_konacno = merge_hashes(h1, h2, h3, h4);

  return h_konacno;
}

int to_hash(int h1, string offset2, int h3, int h4) {
  int h2 = format_offset(offset2);

  int h_final = merge_hashes(h1, h2, h3, h4);
  return h_final;
}

int to_hash(string offset1, int h2, int h3, int h4) {
  int h1 = format_offset(offset1);

  int h_final = merge_hashes(h1, h2, h3, h4);
  return h_final;
}

int to_hash(string offset1, string offset2, int h3, int h4) {
  int h1 = format_offset(offset1);
  int h2 = format_offset(offset2);

  int h_final = merge_hashes(h1, h2, h3, h4);
  return h_final;
}

int to_hash(int h1, int h2, int h3, int h4) {
  int h_final = merge_hashes(h1, h2, h3, h4);
  return h_final;
}

class Cell {
 public:
  int value;
  bool top;
  bool left;
  Cell(){};
  Cell(int val) { value = val; }

  string writeLeft() {
    if (left == true)
      return "T";
    else
      return "F";
  }
  string writeTop() {
    if (top == true)
      return "T";
    else
      return "F";
  }
};

class Blok {
 public:
  uint8_t downOffsets = 0;
  uint8_t rightOffsets = 0;
  int sumDown = 0;
  Cell** matrix = NULL;
  Blok(){};
  Blok(int tVal, signed char* topS, signed char* leftS, int* topO, int* leftO) {
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

    // down offsets
    for (int i = 1; i <= tVal; i++) {
      downOffsets = downOffsets * 3 +
                    (matrix[tVal][i].value - matrix[tVal][i - 1].value + 1);
      sumDown = sumDown + (matrix[tVal][i].value - matrix[tVal][i - 1].value);
    }

    // right offsets
    for (int i = 1; i <= tVal; i++)
      rightOffsets = rightOffsets * 3 +
                     (matrix[i][tVal].value - matrix[i - 1][tVal].value + 1);
  }

  string printOut(vector<string> offsetA, vector<string> offsetB, string topS,
                string leftS) {
    string s = "";
    for (int i = 0; i < offsetA.size(); i++) s = s + offsetA[i];
    for (int i = 0; i < offsetA.size(); i++) s = s + offsetB[i];
    s = s + topS + leftS;
    return s;
  }

  int getDownOffsets(int tVal) { return downOffsets; }
  int getRightOffsets(int tVal) { return rightOffsets; }
};
void printOut(vector<string> v) {
  for (int i = 0; i < v.size(); i++) cout << v[i];
  cout << endl;
}

string getString(vector<string> combo) {
  string s = "";
  for (int i = 0; i < combo.size(); i++) s = s + (string)combo[i];
  return s;
}

Blok* blocks = NULL;

void generate(int i, int tValue, vector<int>& counters) {
  if (i == tValue * 4) {
    int* topO = new int[tValue];
    int* leftO = new int[tValue];
    signed char* topS = new signed char[tValue];
    signed char* leftS = new signed char[tValue];

    string s[4];
    for (int k = 0; k < 4; ++k) {
      s[k] = "";
      for (int i = tValue * k; i < tValue * (k + 1); ++i) {
        if (k < 2) {
          s[k] += to_string(O[counters[i]]);
        } else {
          s[k] += E[counters[i]];
        }
      }
    }
    int hashed = to_hash(s[0], s[1], s[2], s[3]);

    for (int i = 0; i < tValue; i++) topO[i] = O[counters[i]];
    for (int i = tValue; i < tValue * 2; i++)
      leftO[i - tValue] = O[counters[i]];
    for (int i = tValue * 2; i < tValue * 3; i++)
      topS[i - tValue * 2] = E[counters[i]];
    for (int i = tValue * 3; i < tValue * 4; i++)
      leftS[i - tValue * 3] = E[counters[i]];

    Blok b = Blok(tValue, topS, leftS, topO, leftO);

    blocks[hashed] = b;
    downOffsets[hashed] = b.downOffsets;
    rightOffsets[hashed] = b.rightOffsets;
    printf("%d %d\n", downOffsets[hashed], rightOffsets[hashed]);

    delete[] topO;
    delete[] leftO;
    delete[] topS;
    delete[] leftS;

    return;
  } else {
    bool generate_letters = i >= tValue * 2;
    int k = generate_letters ? 4 : 3;

    for (int l = 0; l < k; ++l) {
      if (generate_letters) {
        counters[i] = l;
      } else {
        counters[i] = l;
      }
      generate(i + 1, tValue, counters);
    }
  }
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

int** calculateEditMatrix(int lenA, int lenB, int* substringA,
                                 int* substringB) {
  int** matrix = NULL;
  matrix = new int*[lenB / tValue];

  /* Your algorithm here */

  int lenb = lenB / tValue;
  int lena = lenA / tValue;
  for (int h = 0; h < lenb; h++) matrix[h] = new int[lena];

  for (int i = 0; i < lenb; i++) {
    for (int j = 0; j < lena; j++) {
      matrix[i][j] = 0;
    }
  }

  //    string s = "";
  //    string &leftS;
  //    string topS;

  int cnter = 0;
  double duration = 0;
  std::clock_t start;
  start = std::clock();
  string sL = "";
  string sT = "";
  for (int k = 0; k < tValue; k++) sT = sT + "1";
  for (int k = 0; k < tValue; k++) sL = sL + "1";
  int leftS = substringB[0];
  int topS = substringA[0];
  //    s = sT + sL + topS + leftS;

  int hashed = to_hash(sT, sL, topS, leftS);

  printf("lena %d lenb %d\n", lena, lenb);

  matrix[0][0] = hashed;
  for (int k = 1; k < lena; k++) {
    topS = substringA[k];
    hashed =
        to_hash(sT, blocks[matrix[0][k - 1]].rightOffsets, topS, leftS);
    matrix[0][k] = hashed;
  }
  int initialtopS = substringA[0];

  int maks = 0;
  for (int i = 0; i < threePowTValue * threePowTValue * fourPowTValue *
                          fourPowTValue;
       ++i) {
    if (blocks[i].downOffsets > maks) {
      maks = blocks[i].rightOffsets;
    }
  }

  for (int i = 1; i < lenb; i++) {
    leftS = substringB[i];

    hashed = to_hash(downOffsets[matrix[i - 1][0]], sL, initialtopS, leftS);
    matrix[i][0] = hashed;
    if (cnter % 1000 == 0) {
      cout << cnter << endl;
      duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
      start = std::clock();
      std::cout << "Computation of 1000 blocks takes time:" << duration
                << " s \n";
    }
    cnter++;

    for (int j = 1; j < lena; j++) {
      matrix[i][j] =
          merge_hashes(downOffsets[matrix[i - 1][j]],
                        rightOffsets[matrix[i][j - 1]], substringA[j], leftS);
    }
  }
  return matrix;
}

void readStrings() {
  ifstream infile("primjer-10000.in");
  if (!infile.is_open()) {
    cout << " Failed to open file" << endl;
  } else {
    cout << "Opened OK" << endl;
  }
  int cnt = 0;
  while (!infile.eof()) {
    getline(infile, text);
    if (cnt == 0)
      stringA = text;
    else if (cnt == 1)
      stringB = text;
    cnt++;
  }
  infile.close();
}

size_t getSizeBlocks() {
  size_t val = pow(3, tValue * 2) * pow(4, tValue * 2);
  return val;
}

void editStrings() {
  while (stringA.size() % tValue != 0) stringA = stringA.substr(0, stringA.size() - 1);
  while (stringB.size() % tValue != 0) stringB = stringB.substr(0, stringB.size() - 1);
}
void editScript(int** Matrix) {
  int i = (int)stringB.size() / tValue - 1;  // {i = ROWS in int**}
  int j = (int)stringA.size() / tValue - 1;  // {j = COLS in int**}
  int a = tValue;
  int b = tValue;
  int cnterB = (int)stringB.size() - 1;
  int cnterA = (int)stringA.size() - 1;
  Cell** matrix;
  // a = 0 -> got top in matrix {a = ROWS in Cell**}
  // b = 0 - > got left in matrix {b = COLS in Cell**}
  int cnter = 0;
  int size;
  if (stringA.size() > stringB.size())
    size = (int)stringA.size();
  else
    size = (int)stringB.size();
  int val = size * 2;
  vector<char> first(val);
  vector<char> second(val);
  vector<char> middle(val);

  cout << i << " " << j << endl;
  while ((i + j) != 0) {
    matrix = blocks[Matrix[i][j]].matrix;
    while (true) {
      if (matrix[a][b].top == true && matrix[a][b].left == true) {
        a--;
        b--;
        first.insert(first.begin(), stringA[cnterA]);
        second.insert(second.begin(), stringB[cnterB]);
        if (stringA[cnterA] == stringB[cnterB]) {
          middle.insert(middle.begin(), '|');
        } else
          middle.insert(middle.begin(), '.');
        cnterA--;
        cnterB--;
      } else if (matrix[a][b].top == true) {
        a--;
        second.insert(second.begin(), stringB[cnterB]);
        first.insert(first.begin(), '-');
        middle.insert(middle.begin(), ' ');
        cnterB--;
      } else {
        b--;
        second.insert(second.begin(), '-');
        first.insert(first.begin(), stringA[cnterA]);
        middle.insert(middle.begin(), ' ');
        cnterA--;
      }
      cnter++;
      if (i == 0 && j != 0) {
        if (a <= 0) a = 0;
        if (b == 0) break;
      } else if (j == 0 && i != 0) {
        if (b <= 0) b = 0;
        if (a == 0) break;
      } else {
        if (a == 0 || b == 0) break;
      }
    }
    if (a == 0 && b == 0) {
      if (i == 0) {
        j--;
        a = 0;
        b = tValue;
      } else if (j == 0) {
        i--;
        b = 0;
        a = tValue;
      } else {
        i--;
        j--;
        a = tValue;
        b = tValue;
      }

    } else if (a == 0) {
      i--;
      a = tValue;
    } else if (b == 0) {
      j--;
      b = tValue;
    }
    // cout << i << " " << j << endl;
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
      } else
        middle.insert(middle.begin(), '.');
      cnterA--;
      cnterB--;
    } else if (matrix[a][b].top == true) {
      a--;
      second.insert(second.begin(), stringB[cnterB]);
      first.insert(first.begin(), '-');
      middle.insert(middle.begin(), ' ');
      cnterB--;
    } else {
      b--;
      second.insert(second.begin(), '-');
      first.insert(first.begin(), stringA[cnterA]);
      middle.insert(middle.begin(), ' ');
      cnterA--;
    }
    cnter++;
    if (a == 0 && b == 0) break;
  }

  int x = 1;
  if (size > 100)
    x = 60;
  else
    x = cnter;
  for (int j = 0; j < cnter; j = j + x) {
    outputFile << "Lines:" << j << " - " << (j + x) << endl;
    for (int i = j; i < j + x && i < cnter; i++) {
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
    min = min + blocks[matrix[stringB.size() / tValue - 1][j]].sumDown;
  }
  min = min + (int)stringB.size();
  cout << "MIN DISTANCE:" << min << endl;
}

int letter_to_num(char c) {
  int val;
  if (c == 'A') {
    val = 0;
  } else if (c == 'C') {
    val = 1;
  } else if (c == 'T') {
    val = 2;
  } else if (c == 'G') {
    val = 3;
  }
  return val;
}

int* substringA;
int* substringB;
void getsubArrays() {
  substringA = new int[stringA.size() / tValue];
  substringB = new int[stringB.size() / tValue];
  for (int i = 0; i < stringA.size() / tValue; i++) {
    substringA[i] = 0;
    for (int j = 0; j < tValue; ++j) {
      substringA[i] = substringA[i] * 4 + letter_to_num(stringA[i * tValue + j]);
    }
  }
  for (int i = 0; i < stringB.size() / tValue; i++) {
    substringB[i] = 0;
    for (int j = 0; j < tValue; ++j) {
      substringB[i] = substringB[i] * 4 + letter_to_num(stringB[i * tValue + j]);
    }
  }
}

void parallelPreProcessing() {
  E[0] = 'A';
  E[1] = 'C';
  E[2] = 'T';
  E[3] = 'G';
  O[0] = -1;
  O[1] = 0;
  O[2] = 1;

  vector<thread> threads;

  for (int c0 = 0; c0 < 3; ++c0) {
    for (int c1 = 0; c1 < 3; ++c1) {
      auto code = [c0, c1]() {
        vector<int> comb;
        comb.resize(tValue * 4);
        comb[0] = c0;
        comb[1] = c1;
        generate(2, tValue, comb);
      };
      threads.push_back(thread(code));
    }
  }

  for (auto& t : threads) {
    t.join();
  }
}

int main() {
  std::clock_t start;
  double duration;

  readStrings();
  tValue = calculateTValue((int)stringA.size(), (int)stringB.size());
  tValue = 3;

  threePowTValue = pow(3, tValue);
  fourPowTValue = pow(4, tValue);
  fourPowTValueSquare = fourPowTValue * fourPowTValue;
  K = threePowTValue * fourPowTValueSquare;

  downOffsets = new uint8_t[threePowTValue * threePowTValue *
                            fourPowTValueSquare];
  rightOffsets = new uint8_t[threePowTValue * threePowTValue *
                             fourPowTValueSquare];

  editStrings();
  cout << "Prvi string:" << stringA << endl;
  cout << "Drugi string:" << stringB << endl;

  cout << "T value;" << tValue << endl;
  cout << getSizeBlocks() << endl;

  double memory =
      sizeof(Blok) * getSizeBlocks() +
      getSizeBlocks() * sizeof(Cell) * (tValue + 1) * (tValue + 1);
  cout << "Memmory needed: " << ((memory / 1024) / 1024) << " MB" << endl;
  blocks = new Blok[getSizeBlocks()];

  cout << "Preprocessing STARTED" << endl;

  start = std::clock();

  parallelPreProcessing();

  getsubArrays();
  cout << "Preprocessing DONE" << endl;
  duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

  printf("Maksimalni hash: %d\n", maximum);

  std::cout << "Duration of preprocessing:" << duration << " s\n";
  start = std::clock();

  int** distanceMatrix = calculateEditMatrix(
      (int)stringA.size(), (int)stringB.size(), substringA, substringB);
  duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

  std::cout << "Duration of calculating min distance:" << duration << '\n';

  writeMinDistance(distanceMatrix);

  start = std::clock();

  editScript(distanceMatrix);

  duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

  std::cout << "Duration of calculating edit script:" << duration << '\n';
  outputFile.close();

  delete[] blocks;
  return 0;
}
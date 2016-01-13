#include "FourRussians.h"

FourRussians::FourRussians(string inputFileName, string outputFileName, int outputFormat, int tValue) {
  this->outputFormat = outputFormat;
  this->inputFileName = inputFileName;
  this->outputFileName = outputFileName;
  this->tValue = tValue;
  this->hash = Hash(tValue);

  int numBlocks = getSizeBlocks();
  downOffsets = new uint8_t[numBlocks];
  rightOffsets = new uint8_t[numBlocks];
  blocks = new Blok[numBlocks];

  readStrings();
  editStrings();
}

void FourRussians::generate(int i, int tValue, vector<int>& counters) {
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
    int hashed = hash.to_hash(s[0], s[1], s[2], s[3]);

    for (int i = 0; i < tValue; i++) topO[i] = O[counters[i]];
    for (int i = tValue; i < tValue * 2; i++)
      leftO[i - tValue] = O[counters[i]];
    for (int i = tValue * 2; i < tValue * 3; i++)
      topS[i - tValue * 2] = E[counters[i]];
    for (int i = tValue * 3; i < tValue * 4; i++)
      leftS[i - tValue * 3] = E[counters[i]];

    Blok b = Blok(tValue, topS, leftS, topO, leftO);

    blocks[hashed] = b;
    downOffsets[hashed] = b.calcDownOffsets(tValue);
    rightOffsets[hashed] = b.calcRightOffsets(tValue);

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

int FourRussians::calculateTValue(int lenA, int lenB) noexcept(true) {
  int len = max(lenA, lenB);
  double t = (log(len) / log(12)) / 2;

  return ((int)t + 1);
}

int** FourRussians::calculateEditMatrix() {
  int lenA = (int)stringA.size();
  int lenB = (int)stringB.size();

  getsubArrays();

  int** matrix = NULL;
  matrix = new int*[lenB / tValue];

  int lenb = lenB / tValue;
  int lena = lenA / tValue;
  for (int h = 0; h < lenb; h++) matrix[h] = new int[lena];

  for (int i = 0; i < lenb; i++) {
    for (int j = 0; j < lena; j++) {
      matrix[i][j] = 0;
    }
  }

  int cnter = 0;
  double duration = 0;
  std::clock_t start;
  start = std::clock();
  string sL, sT;
  for (int k = 0; k < tValue; k++) { sT = sT + "1"; sL = sL + "1"; }
  int leftS = substringB[0];
  int topS = substringA[0];

  matrix[0][0] = hash.to_hash(sT, sL, topS, leftS);
  for (int k = 1; k < lena; k++) {
    topS = substringA[k];
    matrix[0][k] = hash.to_hash(sT, rightOffsets[matrix[0][k - 1]], topS, leftS);
  }
  int initialtopS = substringA[0];

  for (int i = 1; i < lenb; i++) {
    leftS = substringB[i];

    matrix[i][0] = hash.to_hash(downOffsets[matrix[i - 1][0]], sL, initialtopS, leftS);
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
          hash.merge_hashes(downOffsets[matrix[i - 1][j]],
                        rightOffsets[matrix[i][j - 1]], substringA[j], leftS);
    }
  }
  return matrix;
}

void FourRussians::readStrings() {
  ifstream infile(inputFileName);
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

size_t FourRussians::getSizeBlocks() {
  size_t val = pow(3, tValue * 2) * pow(4, tValue * 2);
  return val;
}

void FourRussians::editStrings() {
  while (stringA.size() % tValue != 0) stringA = stringA.substr(0, stringA.size() - 1);
  while (stringB.size() % tValue != 0) stringB = stringB.substr(0, stringB.size() - 1);
}
void FourRussians::editScript(int** Matrix) {
  int i = (int)stringB.size() / tValue - 1;  // {i = ROWS in int**}
  int j = (int)stringA.size() / tValue - 1;  // {j = COLS in int**}
  int a = tValue;
  int b = tValue;
  int cnterB = (int)stringB.size() - 1;
  int cnterA = (int)stringA.size() - 1;
  Cell** matrix;
  ofstream outputFile(outputFileName);
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

void FourRussians::writeMinDistance(int** matrix) {
  int min = 0;

  for (int j = 0; j < stringA.size() / tValue; j++) {
    min = min + blocks[matrix[stringB.size() / tValue - 1][j]].sumDown;
  }
  min = min + (int)stringB.size();
  cout << "MIN DISTANCE:" << min << endl;
}

void FourRussians::getsubArrays() {
  substringA = new int[stringA.size() / tValue];
  substringB = new int[stringB.size() / tValue];
  for (int i = 0; i < stringA.size() / tValue; i++) {
    substringA[i] = 0;
    for (int j = 0; j < tValue; ++j) {
      substringA[i] = substringA[i] * 4 + hash.letterToNum(stringA[i * tValue + j]);
    }
  }
  for (int i = 0; i < stringB.size() / tValue; i++) {
    substringB[i] = 0;
    for (int j = 0; j < tValue; ++j) {
      substringB[i] = substringB[i] * 4 + hash.letterToNum(stringB[i * tValue + j]);
    }
  }
}

void FourRussians::parallelPreProcessing() {
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
      auto code = [this, c0, c1]() {
        vector<int> comb;
        comb.resize(FourRussians::tValue * 4);
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


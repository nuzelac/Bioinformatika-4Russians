/*
 * Hash class
 */  

#include "Hash.h"

using namespace std;

Hash::Hash() {}

Hash::Hash(int tValue) {
  threePowTValue = pow(3, tValue);
  fourPowTValue = pow(4, tValue);
  fourPowTValueSquare = fourPowTValue * fourPowTValue;
}

int Hash::formatOffset(string& offset) {
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

int Hash::formatLetters(string& letters) {
  int result = 0;
  int toPower = 4;
  for (int i = 0; i < letters.size(); ++i) {
    int val = letterToNum(letters[i]);
    result = result * toPower + val;
  }

  return result;
}

int Hash::mergeHashes(int h1, int h2, int h3, int h4) {
  return h1 * threePowTValue * fourPowTValueSquare + h2 * fourPowTValueSquare +
         h3 * fourPowTValue + h4;
}

int Hash::toHash(string& offset1, string& offset2, string& a1, string& a2) {
  int h1 = formatOffset(offset1);
  int h2 = formatOffset(offset2);
  int h3 = formatLetters(a1);
  int h4 = formatLetters(a2);

  int h_konacno = mergeHashes(h1, h2, h3, h4);

  return h_konacno;
}

int Hash::toHash(int h1, string& offset2, int h3, int h4) {
  int h2 = formatOffset(offset2);

  int h_final = mergeHashes(h1, h2, h3, h4);
  return h_final;
}

int Hash::toHash(string& offset1, int h2, int h3, int h4) {
  int h1 = formatOffset(offset1);

  int h_final = mergeHashes(h1, h2, h3, h4);
  return h_final;
}

int Hash::toHash(string& offset1, string& offset2, int h3, int h4) {
  int h1 = formatOffset(offset1);
  int h2 = formatOffset(offset2);

  int h_final = mergeHashes(h1, h2, h3, h4);
  return h_final;
}

int Hash::toHash(int h1, int h2, int h3, int h4) {
  int h_final = mergeHashes(h1, h2, h3, h4);
  return h_final;
}

int Hash::letterToNum(char c) {
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

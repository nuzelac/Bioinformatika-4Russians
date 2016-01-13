#include "Hash.h"

using namespace std;

Hash::Hash() {

}

Hash::Hash(int tValue) {
  threePowTValue = pow(3, tValue);
  fourPowTValue = pow(4, tValue);
  fourPowTValueSquare = fourPowTValue * fourPowTValue;
}

int Hash::format_offset(string& offset) {
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

int Hash::format_letters(string& letters) {
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

int Hash::merge_hashes(int h1, int h2, int h3, int h4) {
  return h1 * threePowTValue * fourPowTValueSquare +
         h2 * fourPowTValueSquare + h3 * fourPowTValue + h4;
}

int Hash::to_hash(string& offset1, string& offset2, string& a1, string& a2) {
  int h1 = format_offset(offset1);
  int h2 = format_offset(offset2);
  int h3 = format_letters(a1);
  int h4 = format_letters(a2);

  int h_konacno = merge_hashes(h1, h2, h3, h4);

  return h_konacno;
}

int Hash::to_hash(int h1, string& offset2, int h3, int h4) {
  int h2 = format_offset(offset2);

  int h_final = merge_hashes(h1, h2, h3, h4);
  return h_final;
}

int Hash::to_hash(string& offset1, int h2, int h3, int h4) {
  int h1 = format_offset(offset1);

  int h_final = merge_hashes(h1, h2, h3, h4);
  return h_final;
}

int Hash::to_hash(string& offset1, string& offset2, int h3, int h4) {
  int h1 = format_offset(offset1);
  int h2 = format_offset(offset2);

  int h_final = merge_hashes(h1, h2, h3, h4);
  return h_final;
}

int Hash::to_hash(int h1, int h2, int h3, int h4) {
  int h_final = merge_hashes(h1, h2, h3, h4);
  return h_final;
}
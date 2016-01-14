/*
 * Hash.h
 * Header used to desribes hash function used in algorithm
 * 
 */

#include <string>
#include <cmath>

using namespace std;

class Hash {
 public:
  int threePowTValue;
  int fourPowTValue;
  int fourPowTValueSquare;
  
  /*
   *Constructors
   */ 
  Hash();
  Hash(int tValue);
  
  /*
   * Returns int value
   * int value is used to describe offset
   */ 
  int formatOffset(string& offset);
  
  /*
   * Returns int value
   * int value is used to describes letters
   * letters can be ACTG
   */
  int formatLetters(string& letters);
  
  /*
   * Merge multiple hashes
   */ 
  int mergeHashes(int h1, int h2, int h3, int h4);
  
  /*
   * Make right hash function
   * Each function returns hashes
   * Multiple function exist to speed up whole process
   */ 
  int toHash(string& offset1, string& offset2, string& a1, string& a2);
  int toHash(int h1, string& offset2, int h3, int h4);
  int toHash(string& offset1, int h2, int h3, int h4);
  int toHash(string& offset1, string& offset2, int h3, int h4);
  int toHash(int h1, int h2, int h3, int h4);
  
  /*
   * Convert letters ACTG to values
   */ 
  int letterToNum(char c);
};

#include <string>
#include <cmath>

using namespace std;

class Hash {
public:
	int threePowTValue;
	int fourPowTValue;
	int fourPowTValueSquare;

	Hash();
	Hash(int tValue);
	int format_offset(string& offset);
	int format_letters(string& letters);
	int merge_hashes(int h1, int h2, int h3, int h4);
	int to_hash(string& offset1, string& offset2, string& a1, string& a2);
	int to_hash(int h1, string& offset2, int h3, int h4);
	int to_hash(string& offset1, int h2, int h3, int h4);
	int to_hash(string& offset1, string& offset2, int h3, int h4);
	int to_hash(int h1, int h2, int h3, int h4);
};
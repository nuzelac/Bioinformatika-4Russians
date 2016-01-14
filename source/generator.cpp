#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;

char alphabet[] = "ACTG";


int n;


void printWord() {
  for(int i = 0; i < n; ++i) {
    printf("%c", alphabet[rand() % 4]);
  }
  printf("\n");
}

int main(int argc, char* argv[]) {
  srand(time(0));
  n = atoi(argv[1]);

  printWord();
  printWord();
}

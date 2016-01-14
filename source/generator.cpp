#include <cstdio>
#include <ctime>
#include <cstdlib>

using namespace std;

char alphabet[] = "ACTG";
int n = 100;

void printWord() {
  for(int i = 0; i < n; ++i) {
    printf("%c", alphabet[rand() % 4]);
  }
  printf("\n");
}

int main() {
  srand(time(0));

  printWord();
  printWord();
}

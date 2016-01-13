#include "Cell.h"
#include "fourRussians.h"

class Blok {

public:
	int* downOffsets;
	int* rightOffsets;
	int hashRightOffsets;
	int hashDownOffsets;
	int sumaDown = 0;
	
	Cell** matrix = NULL;
	Blok();
	Blok(int tVal, signed char* topS, signed char* leftS, int* topO, int* leftO);
	void ispisiMatrixValues(int tVrijednost);
	
	/*Blok() {};
	Blok(int tVal, signed char* topS, signed char* leftS, int* topO, int* leftO) {


		downOffsets = new int[tVal];
		rightOffsets = new int[tVal];
		
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
		int min = 0;
		for (int i = 1; i < tVal + 1; i++) {
			for (int j = 1; j < tVal + 1; j++) {
				if (topS[j - 1] == leftS[i - 1]) {

					matrix[i][j] = Cell(matrix[i - 1][j - 1].value);
					matrix[i][j].top = true;
					matrix[i][j].left = true;
				}

				else if (matrix[i - 1][j - 1].value <= matrix[i - 1][j].value && matrix[i - 1][j - 1].value <= matrix[i][j - 1].value) {

					matrix[i][j] = Cell(matrix[i - 1][j - 1].value + 1);
					matrix[i][j].top = true;
					matrix[i][j].left = true;
				}
				else if (matrix[i - 1][j].value <= matrix[i - 1][j - 1].value && matrix[i - 1][j].value <= matrix[i][j - 1].value) {

					matrix[i][j] = Cell(matrix[i - 1][j].value + 1);
					matrix[i][j].top = true;
					matrix[i][j].left = false;
				}
				else {

					matrix[i][j] = Cell(matrix[i][j - 1].value + 1);
					matrix[i][j].top = false;
					matrix[i][j].left = true;
				}
			}
		}

		

		//down offsets
		for (int i = 1; i <= tVal; i++) {
			downOffsets[i-1] = (matrix[tVal][i].value - matrix[tVal][i - 1].value+1);
			sumaDown = sumaDown + (matrix[tVal][i].value - matrix[tVal][i - 1].value);
		}
		
		//right offsets
		for (int i = 1; i <= tVal; i++)
			rightOffsets[i-1] = (matrix[i][tVal].value - matrix[i - 1][tVal].value+1);

		hashRightOffsets = hashOffsetsLeft(rightOffsets);
		hashDownOffsets = hashOffsetsTop(downOffsets);
	}
	

	void ispisiMatrixValues(int tVrijednost) {
		for (int i = 0; i <= tVrijednost; i++) {
			for (int j = 0; j <= tVrijednost; j++)
				cout << matrix[i][j].value << " ";
			cout << endl;
		}
		cout << endl;
	}*/
};

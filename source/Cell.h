#include <string>


class Cell {

public:	
	int value;
	bool top;
	bool left;
	
	Cell();
	Cell(int val);
	std::string writeLeft();
	std::string writeTop();
	//Cell(int val) { value = val; }
	
/*	string writeLeft() {
		if (left == true)
			return "T";
		else return "F";
	}
	string writeTop() {
		if (top == true)
			return "T";
		else return "F";
	}*/
	
	

};

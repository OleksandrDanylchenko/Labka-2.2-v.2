//ALEXANDER DANILCHENKO 13.03.19 LABKA 2.2 v.2
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <iomanip>
#include "dynamicMatrix.h"

int main() {
	//opens terminal in fullscreen mode
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	//info about student
	std::cout << "Laboratory work 2 - 2 variant 2  Matrix and dynamic arrays VAR: 86" << std::endl;
	std::cout << "Group: K-14" << ' ' << "Danilchenko Alexander" << std::endl;
	
	dynamicMatrix matrix;
	try {
		matrix = input();
		matrix.rotate180Deg();
		output(matrix);
		matrix.~dynamicMatrix();
	}
	catch (std::exception & ex) {
		std::cerr << std::setw(5) << ex.what() << std::endl << std::endl;
		system("pause");
		return -1;
	}
	system("pause");
	return 0;
} 

//creating an input file with a fully filled matrix 500x500
#include <iostream>
#include <fstream>
#include <string>

size_t getSizeOfMatrix();

// get the path or name of the output file
std::string getFilePath();

//fill the "matrix" with elements using formula a(i,j)=i+j.
void fillMatrix(std::ofstream& of, size_t sizeOfMatrix);

int main(void) {
	size_t sizeOfMatrix = getSizeOfMatrix();
	
	std::ofstream outputFile;
	outputFile.open(getFilePath());
	if (outputFile.fail()) {
		std::cerr << "The output file is corrupted!" << std::endl;
		return -1;
	}

	fillMatrix(outputFile, sizeOfMatrix);
	system("pause");
	return 0;
}

size_t getSizeOfMatrix() {
	size_t userSize = 0;
	while (true) {
		std::cout << "Enter the size of matrix (3 < size < 501): ";
		if (!(std::cin >> userSize)) {
			//reset the input
			std::cin.clear();
			//get rid of the bad input before return was pressed
			while (std::cin.get() != '\n');
		}
		else if (userSize < 3 || userSize > 500) {
			std::cin.clear();
			while (std::cin.get() != '\n');
		}
		else
			break;
	}
	return userSize;
}

std::string getFilePath() {
	std::string outputFilePathUser = "";
	std::string outputFilePath = "";
	std::cout << "Enter the path to the output file or desirable name: ";
	std::cin.ignore();
	getline(std::cin, outputFilePathUser);
	if (outputFilePathUser[0] != 'C' && outputFilePathUser[0] != 'D') { //if user didn't provided full adress -> create a new file in the root folder
		std::string outputFilePathDefault = "D:/Studying/Programming/LABS/Labka_2.2_Second_Sem/Labka_2.2_Second_Sem/";
		outputFilePath += outputFilePathDefault + outputFilePathUser + ".txt";
		std::cout << "\nYour file will be stored at: D:" << '\\' << "Studying" << '\\' << "Programming" << '\\' << "LABS" << '\\' << "Labka_2.2_Second_Sem" << '\\' << "Labka_2.2_Second_Sem" << '\\' << outputFilePathUser << ".txt" << std::endl;
	}
	return outputFilePath;
}

void fillMatrix(std::ofstream& of, size_t sizeOfMatrix) {
	//first line with "dimensions"
	of << sizeOfMatrix << ' ' << sizeOfMatrix << std::endl;

	size_t num = 0;
	for (size_t i = 0; i < sizeOfMatrix; ++i) {
		for (size_t j = 0; j < sizeOfMatrix; ++j) {
			num = i + j;
			of << num << ' ';
		}
		//don't put \n on the end of the matrix
		if (i + 1 < sizeOfMatrix)
			of << std::endl;
	}
}

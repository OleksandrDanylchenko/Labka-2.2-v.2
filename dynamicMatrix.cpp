#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "dynamicMatrix.h"

dynamicMatrix::dynamicMatrix() : _width(0), _height(0), _dynMatrix(nullptr) {}

// move assignment constructor
dynamicMatrix::dynamicMatrix(dynamicMatrix&& otherMatr) noexcept: _width(0), _height(0), _dynMatrix(nullptr) {
	// copy the data pointer and its dimensions from the source object
	_width = otherMatr._width;
	_height = otherMatr._height;
	_dynMatrix = otherMatr._dynMatrix;
	// Release the data pointer from the source object so that the destructor does not free the memory multiple times
	otherMatr._width = otherMatr._height = 0;
	otherMatr._dynMatrix = nullptr;
}

dynamicMatrix& dynamicMatrix::operator=(dynamicMatrix&& otherMatr) noexcept {
	if (this != &otherMatr) {
		// free the existing resource
		for (size_t l = 0; l < _height; ++l) {
			delete[] _dynMatrix[l];
			_dynMatrix[l] = nullptr;
		}
		delete[] _dynMatrix;
		_dynMatrix = nullptr;

		// copy the data pointer and its dimensions from the source object
		_width = otherMatr._width;
		_height = otherMatr._height;
		_dynMatrix = otherMatr._dynMatrix;

		// Release the data pointer from the source object so that the destructor does not free the memory multiple times
		otherMatr._width = otherMatr._height = 0;
		otherMatr._dynMatrix = nullptr;
	}
	return *this;
}

dynamicMatrix::dynamicMatrix(const size_t& height, const size_t& width) : _width(width), _height(height) {
	_dynMatrix = new int* [_height];
	for (size_t i = 0; i < _height; ++i)
		_dynMatrix[i] = new int[_width];
}

dynamicMatrix::~dynamicMatrix() {
	if (_dynMatrix != nullptr) {
		for (size_t l = 0; l < _height; ++l) {
			delete[] _dynMatrix[l];
			_dynMatrix[l] = nullptr;
		}
		delete[] _dynMatrix;
		_dynMatrix = nullptr;
	}
}

int& dynamicMatrix::elem(const size_t& y, const size_t& x) {
	if (y < _height && x < _width)
		return _dynMatrix[y][x];
	else
		throw std::out_of_range("<<<OUT OF RANGE>>>");
}

size_t dynamicMatrix::getWidth() const { return _width; }

size_t dynamicMatrix::getHeight() const { return _height; }

void dynamicMatrix::rotate180Deg() {
	for (int i = 1; i < _width / 2; ++i)
		for (int j = _width / 2 + _width % 2 - 1; j > _width / 2 + _width % 2 - i - 1; --j) {
			std::swap(elem(i, j), elem(_width - i - 1, _width - j - 1));
			std::swap(elem(j, _width - i - 1), elem(_width - j - 1, i));
		}
}

dynamicMatrix input() {
	// get an input file path
	std::string inputFilePath = "";
	std::ifstream inputFile;
	while (true) {
		std::cout << "\nEnter the path to the input file: ";
		std::cin.clear(); //clears the stream if ^z is pushed
		getline(std::cin, inputFilePath);
		inputFile.open(inputFilePath);
		if (inputFile.fail()) {
			inputFilePath.clear();
			continue;
		}
		else
			break;
	}

	//check whether the matrix is fully filled
	size_t tempWidth = 0, tempHeight = 0;
	inputFile >> tempWidth >> tempHeight;
	if (tempWidth != tempHeight)
		throw std::logic_error("\nMatrix is not square!");
	else if (tempWidth < 0 || tempWidth > 500)
		throw std::logic_error("<<<" + inputFilePath + ": INPUT ERROR>>>");
	inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 	//skip the first line until delimiter
	size_t expectedAmountOfElements = tempWidth * tempHeight;
	size_t realAmountOfElements = 1;

	dynamicMatrix temp(tempWidth, tempHeight);
	//reads a file until it reaches the end
	for (size_t i = 0; i < tempWidth; ++i)
		for (size_t j = 0; j < tempHeight; ++j) {
			inputFile >> temp.elem(i, j);
			if (temp.elem(i, j) > 0) // we have real numbers if just scanned element has positive value
				++realAmountOfElements;
		}
	if (expectedAmountOfElements != realAmountOfElements)
		throw std::logic_error("<<<" + inputFilePath + ": INPUT ERROR>>>");
	else {
		inputFile.close();
		return temp;
	}
}

void output(dynamicMatrix & m) {
	std::string outputFilePath = "";
	std::ofstream outputFile;
	while (true) {
		std::cout << "\nEnter the path to the output file: ";
		getline(std::cin, outputFilePath);
		if (outputFilePath.find('\\') == std::string::npos and outputFilePath.find('/') == std::string::npos) { //if user didn't provided full adress -> create a new file in the root folder
			outputFilePath += ".txt";
			std::cout << "\nYour file will be stored at: D:" << '\\' << "Studying" << '\\'
				<< "Programming" << '\\' << "LABS" << '\\' << "Labka_2.2_Second_Sem" << '\\'
				<< "Labka_2.2_Second_Sem" << '\\' << outputFilePath << std::endl;
		}
		outputFile.open(outputFilePath);
		if (outputFile.fail())
			continue;
		else
			break;
	}

	//writes to the output file new representation of matrix
	outputFile << std::setw(4) << m.getWidth() << ' ' << m.getHeight() << std::endl;
	for (size_t i = 0; i < m.getWidth(); ++i) {
		for (size_t j = 0; j < m.getHeight(); ++j)
			outputFile << std::setw(4) << m.elem(i, j);
		outputFile << std::endl;
	}
	outputFile.close();
}

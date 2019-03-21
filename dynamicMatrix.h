#pragma once
class dynamicMatrix {
public:
	dynamicMatrix();
	dynamicMatrix(dynamicMatrix&& otherMatr) noexcept; // move constructor
	dynamicMatrix(const size_t& height, const size_t& width); // create "matrix" with given dimensions
	dynamicMatrix& operator = (dynamicMatrix&& otherMatr) noexcept;
	~dynamicMatrix();

	int& elem(const size_t& y, const size_t& x);
	void processing(); // looks if the matrix is odd or even and calls other specified methods
	size_t getWidth() const;
	size_t getHeight() const;
private:
	size_t _width;
	size_t _height;
	int** _dynMatrix;
	void rotate180DegODD();
	void rotate180DegEVEN();
};

dynamicMatrix input();
void output(dynamicMatrix& m);
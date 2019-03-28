#pragma once
class dynamicMatrix {
public:
	dynamicMatrix();
	dynamicMatrix(dynamicMatrix&& otherMatr) noexcept; // move constructor
	dynamicMatrix(const size_t& height, const size_t& width); // create "matrix" with given dimensions
	dynamicMatrix& operator = (dynamicMatrix&& otherMatr) noexcept;
	~dynamicMatrix();

	int& elem(const size_t& y, const size_t& x);
	void rotate180Deg();
	size_t getWidth() const;
	size_t getHeight() const;
private:
	size_t _width;
	size_t _height;
	int** _dynMatrix;
};

dynamicMatrix input();
void output(dynamicMatrix& m);

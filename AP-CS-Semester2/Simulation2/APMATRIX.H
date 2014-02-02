#ifndef _APMATRIX_H
#define _APMATRIX_H

//****************************************************************
//
// apmatrix class template
//
// Implements dynamically-allocated 2-D arrays
//   with subscript range checking.
//
// The template data type parameter itemType must be either a built-in
//   type or support a default constructor and assignment.
//
//****************************************************************

#include <vector>

template <class itemType>
class apmatrix {

public:

	// Constructors/destructor:

	// Default constructor: builds an empty matrix with rows = cols = 0
	apmatrix() 
		: mRows(0), mCols(0), mMatrix(0)
	{}

	// Builds a matrix with given dimensions
	// rows, cols must be >= 0.
	apmatrix(int rows, int cols)
	: mRows(rows), mCols(cols), mMatrix(rows)
	{
		int r;

		for (r = 0; r < rows; r++)
			mMatrix[r].resize(cols);
	}

	// Builds a matrix with given dimensions and sets
	// all its elements to fillValue
	// rows, cols must be >= 0.
	apmatrix(int rows, int cols, const itemType &fillValue)
		: mRows(rows), mCols(cols), mMatrix(rows)
	{
		int r, c;
		for (r = 0; r < rows; r++) {
			mMatrix[r].resize(cols);
			for (c = 0; c < cols; c++)
				mMatrix[r][c] = fillValue;
		}
	}

	// Copy constructor: builds a matrix equal to
	//  a given matrix
	apmatrix(const apmatrix &m)
		: mRows(m.mRows), mCols(m.mCols), mMatrix(m.mRows)
	{
		int r;

		for (r = 0; r < mRows; r++)
			mMatrix[r] = m.mMatrix[r];
	}

	// Destructor
	~apmatrix()
	{
		// Nothing to do: vector destructor frees everything
	}

	// Assignment:
	const apmatrix &operator= (const apmatrix &m)
	{
		if (this != &m) {          // Avoid assignment to itself
			mMatrix.resize(m.mRows);
			mRows = m.mRows;
			mCols = m.mCols;

			int r;
			for (r = 0; r < mRows; r++)
				mMatrix[r] = m.mMatrix[r];
		}
		return *this;
	}

	// Overloaded subscripting operators (perform subscript range checking):
	// Verifies that 0 <= r <= mRows - 1.
	std::vector<itemType> &operator[] (int r)
	{
		if (r < 0 || r >= mRows) {
			cerr << "Illegal matrix index: " << r << " max index = "
				<< (mRows - 1) << endl;
			abort();
		}
		return mMatrix[r];
	}

	// Verifies that 0 <= r <= mRows - 1.
	const std::vector<itemType> &operator[] (int r) const
	{
		if (r < 0 || r >= mRows) {
			cerr << "Illegal matrix index: " << r << " max index = "
				<< (mRows - 1) << endl;
			abort();
		}
		return mMatrix[r];
	}

	// numrows(), numcols(), and resize(...) member functions:
	int numrows() const   // Returns the current number of rows
	{
		return mRows;
	}

	int numcols() const   // Returns the current number of columns
	{
		return mCols;
	}

	// Changes the dimensions to specified new
	//   number of rows and columns.
	//   (can result in losing values if a new dimension
	//   is smaller than the old one.
	void resize(int newRows, int newCols)
	{
		int r;

		mMatrix.resize(newRows);

		for (r = 0; r < newRows; r++)
			mMatrix[r].resize(newCols);

		mRows = newRows;
		mCols = newCols;
	}

private:

	int mRows;             // Number of rows in the matrix
	int mCols;             // Number of columns in the matrix
	std::vector<std::vector<itemType>> mMatrix;
	// Pointer to the array of vectors, where
	//   each vector represents one row
};

#endif // _APMATRIX_H
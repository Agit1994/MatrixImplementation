/*
 * Matrix.hpp
 *
 *  Created on: Mar 5, 2017
 *      Author: Agit
 */

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <array>
#include <iostream>
#include <algorithm>
#include <cmath>

/**
 * The Matrix class is an implementation of the mathematical concept of a matrix.
 * @See https://en.wikipedia.org/wiki/Matrix_(mathematics) for more information.
 *
 * typename T: T must be an arithmetic type, i.e. an integral or floating point type
 * const std::size_t ROWS: height, the height/number of rows of the matrix
 * const std::size_t COLS: width, the width/number of columns of the matrix
 */
//ROWS = hoe hoog de matrix wordt (height)
//COLS = hoe breedt de matrix wordt (width)
//3x4 matrix betekent dus 3 rows en 4 columns dus 3 hoog en 4 breed
template <const std::size_t ROWS = 0 ,const std::size_t COLS = 0, typename T =long>
class Matrix
{
public:
	//intergal is gehele getalen
	static_assert(std::is_arithmetic<T>::value,"T must be integral type or a floating-point type");

	Matrix(T defaultValue = 0);

	Matrix(const std::initializer_list<T>& list);

	Matrix(const std::initializer_list<std::initializer_list<T>>& list);

	Matrix(const Matrix<ROWS,COLS,T>& aMatrix);


    /************************************************************
     * Matrix operators: asign and comparison
     ************************************************************/
	const Matrix<ROWS,COLS,T>& operator=(const Matrix<ROWS,COLS,T>& aMatrix);

	bool operator==(const Matrix<ROWS,COLS,T>& aMatrix) const;

    /************************************************************
     * Matrix operators for scalars
     ************************************************************/
	template<typename T2> //moet ook voor rhs een type geven want anders kan je bijv geen int * double doen.
	Matrix<ROWS,COLS,T>& operator*=(const T2& scalar);

	template<typename T2>
	Matrix<ROWS,COLS,T> operator*(const T2& scalar) const;

	template<typename T2>
	Matrix<ROWS,COLS,T>& operator/=(const T2& scalar);

	template<typename T2>
	Matrix<ROWS,COLS,T> operator/(const T2& scalar) const;

    /************************************************************
     * Matrix operators for matrix
     ************************************************************/
	template<std::size_t COLS2, typename T2>
	Matrix<ROWS,COLS2,T> operator*(const Matrix<COLS,COLS2,T2>& aMatrix) const; //copy

	Matrix<ROWS,COLS,T>& operator+=(const Matrix<ROWS,COLS,T>& aMatrix); //no copy

	Matrix<ROWS,COLS,T>& operator-=(const Matrix<ROWS,COLS,T>& aMatrix); //no copy

    Matrix<ROWS,COLS,T> operator+(const Matrix<ROWS,COLS,T>& aMatrix) const; //copy

    Matrix<ROWS,COLS,T> operator-(const Matrix<ROWS,COLS,T>& aMatrix) const; //copy


    /************************************************************
     * Matrix functions
     ************************************************************/
    Matrix<COLS,ROWS,T> transpose() const;

	//no bounds check
	std::array<T,COLS>& operator[](const std::size_t rowIndex);

	//bounds check
	std::array<T,COLS>& at(const std::size_t rowIndex);

	//copy
	T at(const std::size_t rowIndex, const std::size_t columIndex) const;

    const std::size_t getRowSize() const;

    const std::size_t getColumnSize() const ;

    const  std::size_t getMatrixSize() const;

    const std::string to_string() const;

    Matrix<ROWS,ROWS,T> identity() const;

    bool approxEqual(Matrix<ROWS,COLS,T>& rhs,double precision);

    Matrix<ROWS,COLS,T> inverse();

private:
	std::array<std::array<T,COLS>,ROWS> matrix; //matrix COLS als inner array omdat ROWS bepaald hoevaak je een array wilt


	template <const std::size_t,const std::size_t, typename>
	friend class Matrix;

    /************************************************************
     * The following private functions are being used by the inverse functions
     ************************************************************/
	//paste identity matrix on the object who calls this object and return the result
    Matrix<ROWS,2*COLS,T> concatenate ();

	//find the top row
	std::size_t findTopRow(std::size_t rowPos);
	//swap the currentRow with the top row
	void swapRows(std::size_t currentRowPos,std::size_t targetRowPos);
	//transform the top row to the correct echolon form
	void correctRowType(std::size_t targetRowPos);
	//transform all the other rows in the matrix to the correct echolon form
	void echolonForm(std::size_t startPos);

	//cut the identity matrix from the object who calls this function an return the result
	//this function must be called last in the inverse() function. This function will result the inverse matrix.
    Matrix<ROWS,COLS/2,T> deconcatenate ();


    //this function finds the determinant by using the Gaussian elimination
    bool isDeterminant();

    //this function is being used by the isDeterminant();
    //this function sets the Matrix in echelon form
    void echolonRowForm(std::size_t startPos);

};

template <std::size_t ROWS, std::size_t COLS ,typename T >
Matrix<ROWS,COLS,T>::Matrix(T defaultValue)
{
	for(std::size_t i = 0; i<ROWS; ++i) matrix.at(i).fill(defaultValue);
}

template <std::size_t ROWS, std::size_t COLS ,typename T >
Matrix<ROWS,COLS,T>::Matrix(const std::initializer_list<T>& list)
{
    if (list.size() != ROWS * COLS) throw std::runtime_error{"list size is not equal to the matrix size"};

    size_t i = 0;
	for(const T* it = list.begin(); it != list.end(); ++it)
	{
		size_t pos = std::distance(list.begin(),it);
		matrix.at(i).at(pos % COLS) = *it;
		if((pos+1)%COLS==0) ++i;  //check of de volgende pos in een nieuwe rij hoort.
	}
}

template <std::size_t ROWS, std::size_t COLS ,typename T >
Matrix<ROWS,COLS,T>::Matrix(const std::initializer_list<std::initializer_list<T>>& list)
{
	if(list.size()!=ROWS) throw std::runtime_error{"amount of given rows in list is not equal to the row size of the matrix"};

	for(const std::initializer_list<T>* row = list.begin(); row != list.end(); ++row)
	{
		if(row->size() != COLS) throw std::runtime_error{"amount of given columns in list is not equal to the column size of the matrix"};
		size_t rowPos = std::distance(list.begin(), row);

		for(const T* col = row->begin(); col!=row->end(); ++col)
		{
			size_t colPos = std::distance(row->begin(),col);

			matrix.at(rowPos).at(colPos) = *col;
		}
	}
}

template <std::size_t ROWS, std::size_t COLS ,typename T >
Matrix<ROWS,COLS,T>::Matrix(const Matrix<ROWS,COLS,T>& aMatrix):matrix(aMatrix.matrix){}


/************************************************************
 * Matrix operators: asign and comparison
 ************************************************************/

template <std::size_t ROWS, std::size_t COLS ,typename T >
const Matrix<ROWS,COLS,T>& Matrix<ROWS,COLS,T>::operator=(const Matrix<ROWS,COLS,T>& aMatrix)
{
	if(this!=&aMatrix)
	{
		matrix = aMatrix.matrix;
	}
	return *this;
}


//ongelijke matrixen hoef je niet te comparen dus alleen op inhoud
template <std::size_t ROWS, std::size_t COLS ,typename T >
bool Matrix<ROWS,COLS,T>::operator==(const Matrix<ROWS,COLS,T>& aMatrix) const
{
	return matrix == aMatrix.matrix;
}

/************************************************************
 * output operator
 ************************************************************/
template <std::size_t ROWS, std::size_t COLS ,typename T >
std::ostream& operator<<(std::ostream& os,const Matrix<ROWS,COLS,T>& rhs)
{
	return os<<rhs.to_string();
}

/************************************************************
 * Matrix operators for scalars
 ************************************************************/


template <std::size_t  ROWS, std::size_t  COLS ,typename T >
template<typename T2>
Matrix<ROWS,COLS,T>& Matrix<ROWS,COLS,T>::operator*=(const T2& scalar)
{
	for(std::size_t  i = 0; i<ROWS; ++i)
	{
		for(std::size_t  j = 0; j<COLS; ++j)
		{
			matrix.at(i).at(j) *=scalar;
		}
	}
	return *this;
}

template <std::size_t ROWS, std::size_t  COLS ,typename T >
template<typename T2>
Matrix<ROWS,COLS,T> Matrix<ROWS,COLS,T>::operator*(const T2& scalar) const
{
	Matrix<ROWS,COLS,T> m(*this);

	for(std::size_t  i = 0; i<ROWS; ++i)
	{
		for(std::size_t  j=0; j<COLS; ++j)
		{
			m.at(i).at(j) =  scalar * matrix.at(i).at(j);
		}
	}
	return m;
}

template <std::size_t ROWS, std::size_t COLS ,typename T >
template<typename T2>
Matrix<ROWS,COLS,T>& Matrix<ROWS,COLS,T>::operator/=(const T2& scalar)
{
	for(std::size_t i = 0; i<ROWS; ++i)
	{
		for(std::size_t j = 0; j<COLS; ++j)
		{
			this->at(i).at(j)/=scalar;
		}
	}
	return *this;
}

template <std::size_t ROWS, std::size_t COLS ,typename T >
template<typename T2>
Matrix<ROWS,COLS,T> Matrix<ROWS,COLS,T>::operator/(const T2& scalar) const
{
	Matrix<ROWS,COLS,T> m;

	for(std::size_t i = 0; i<ROWS; ++i)
	{
		for(std::size_t j = 0; j<COLS; ++j)
		{
			m.at(i).at(j) = matrix.at(i).at(j)/scalar;
		}
	}
	return m;
}


/************************************************************
 * Matrix operators for matrix
 ************************************************************/
template <std::size_t ROWS, std::size_t COLS ,typename T >
template<std::size_t COLS2, typename T2>
Matrix<ROWS,COLS2,T> Matrix<ROWS,COLS,T>::operator*(const Matrix<COLS,COLS2,T2>& aMatrix) const
{
    Matrix<COLS,COLS2,T2> tempMatrix(aMatrix);

    Matrix<ROWS,COLS2,T> newMatrix;

    for (std::size_t i = 0; i < ROWS; ++i)
    {
        for (std::size_t j = 0; j < COLS2; ++j)
        {
        	T2 rowValue = 0;
            for (std::size_t k = 0; k < COLS; ++k)
            {
            	rowValue+= matrix.at(i).at(k) * tempMatrix.at(k).at(j);
            }
            newMatrix.at(i).at(j) = static_cast<T>(rowValue);
        }
    }

	return newMatrix;
}


template <std::size_t ROWS, std::size_t COLS ,typename T >
Matrix<ROWS,COLS,T>& Matrix<ROWS,COLS,T>::operator+=(const Matrix<ROWS,COLS,T>& aMatrix)
{

	for(std::size_t i =0; i<ROWS; ++i)
	{
		for(std::size_t j=0; j<COLS; ++j)
		{
			this->at(i).at(j) += aMatrix.at(i,j);
		}
	}
	return *this;
}


template <std::size_t ROWS, std::size_t COLS ,typename T >
Matrix<ROWS,COLS,T> Matrix<ROWS,COLS,T>::operator+(const Matrix<ROWS,COLS,T>& aMatrix) const
{
	Matrix<ROWS,COLS,T> m;

	for(std::size_t i =0; i<ROWS; ++i)
	{
		for(std::size_t j=0; j<COLS; ++j)
		{
			m.at(i).at(j) = matrix.at(i).at(j) + aMatrix.at(i,j);
		}
	}
	return m;
}

template <std::size_t ROWS, std::size_t COLS ,typename T >
Matrix<ROWS,COLS,T>& Matrix<ROWS,COLS,T>::operator-=(const Matrix<ROWS,COLS,T>& aMatrix)
{

	for(std::size_t i =0; i<ROWS; ++i)
	{
		for(std::size_t j=0; j<COLS; ++j)
		{
			this->at(i).at(j) -= aMatrix.at(i,j);
		}
	}
	return *this;
}

template <std::size_t ROWS, std::size_t COLS ,typename T >
Matrix<ROWS,COLS,T> Matrix<ROWS,COLS,T>::operator-(const Matrix<ROWS,COLS,T>& aMatrix) const
{
	Matrix<ROWS,COLS,T> m;

	for(std::size_t i =0; i<ROWS; ++i)
	{
		for(std::size_t j=0; j<COLS; ++j)
		{
			m.at(i).at(j) = this->at(i,j) - aMatrix.at(i,j);
		}
	}
	return m;
}

/************************************************************
 * Matrix functions
 ************************************************************/

template <std::size_t ROWS, std::size_t COLS ,typename T >
Matrix<COLS,ROWS,T> Matrix<ROWS,COLS,T>::transpose() const
{
	Matrix<COLS,ROWS,T> m;
	for(std::size_t i=0; i<ROWS; ++i)
	{
		for(std::size_t j=0; j<COLS; ++j)
		{
			m.at(j).at(i) = matrix.at(i).at(j);
		}
	}
	return m;
}


template<const std::size_t ROWS, const std::size_t COLS, typename T>
const std::size_t Matrix<ROWS,COLS,T>::getRowSize() const
{
	return ROWS;
}

template<const std::size_t ROWS, const std::size_t COLS ,typename T>
const std::size_t Matrix<ROWS,COLS,T>::getColumnSize() const
{
	return COLS;
}

template<const std::size_t ROWS, const std::size_t COLS ,typename T>
const std::size_t Matrix<ROWS,COLS,T>::getMatrixSize() const
{
	return ROWS*COLS;
}

template <std::size_t ROWS, std::size_t COLS ,typename T >
const std::string Matrix<ROWS,COLS,T>::to_string() const
{
	std::string output = "[Matrix]<" + std::to_string(ROWS) + "," + std::to_string(COLS) + ">\n{\n\t";

	for(std::size_t i=0; i<ROWS; ++i)
	{
		output+="{";
		for(std::size_t j=0; j<COLS; ++j)
		{
			output+=std::to_string(matrix.at(i).at(j));
			output+= (j==COLS-1) ? ("}") : (",");
		}
		output+=(i==ROWS-1) ? ("\n") : (",\n\t");
	}
	output+="}";
	return output;
}


template <std::size_t ROWS, std::size_t COLS ,typename T >
std::array<T,COLS>& Matrix<ROWS,COLS,T>::at(const std::size_t rowIndex)
{
	return matrix.at(rowIndex);
}

template <std::size_t ROWS, std::size_t COLS ,typename T >
T Matrix<ROWS,COLS,T>::at(const std::size_t rowIndex, const std::size_t columIndex) const
{
	return matrix.at(rowIndex).at(columIndex);
}

template <std::size_t ROWS, std::size_t COLS ,typename T >
std::array<T, COLS>& Matrix<ROWS,COLS,T>::operator [](const std::size_t rowIndex)
{
	return matrix[rowIndex];
}

template<const std::size_t ROWS , const std::size_t COLS ,typename T>
Matrix<ROWS, ROWS, T> Matrix<ROWS,COLS,T>::identity() const
{
	Matrix<ROWS, ROWS, T> m;

	for(std::size_t i = 0; i<ROWS; ++i)
	{
		m.at(i).at(i) = 1;
	}
	return m;
}

template<const std::size_t ROWS, const std::size_t COLS,typename T>
bool Matrix<ROWS,COLS,T>::approxEqual(Matrix<ROWS, COLS, T>& rhs, double precision)
{
	for(std::size_t i=0; i<rhs.getRowSize(); ++i)
	{
		for(std::size_t j=0; j<rhs.getColumnSize(); ++j)
		{
			if(std::abs((this->at(i).at(j) - rhs.at(i).at(j))) > precision) return false;
		}
	}

	return true;
}

template <const std::size_t ROWS, const std::size_t COLS, typename T>
Matrix<ROWS,COLS,T> Matrix<ROWS,COLS,T>::inverse()
{
	if(ROWS!=COLS) throw std::runtime_error("ROWS and COLS must be equal to calculate the inverse of the matrix");

	Matrix<ROWS,2*COLS,T> inputConcatenated = this->concatenate();

	//GAUSSIAN elimination
	if(!inputConcatenated.isDeterminant()) throw std::runtime_error("this matrix is not invertible, the determinant is 0 ");

	for(std::size_t row = 0; row<inputConcatenated.getRowSize(); ++row)
	{
		inputConcatenated.correctRowType(row); //set row to correct form (reduced echelon form where the first non-zero element is 1)
		inputConcatenated.echolonForm(row); //GAUSSE-JORDAN elimination (forward and backwards elimination)
	}

	Matrix<ROWS,COLS,T> result = inputConcatenated.deconcatenate();

	return result;
}

template<const std::size_t ROWS , const std::size_t COLS ,typename T>
Matrix<ROWS, 2*COLS, T> Matrix<ROWS,COLS,T>::concatenate()
{
	Matrix<ROWS,COLS,T> i =this->identity();
	Matrix<ROWS,2*COLS,T> m;

	for(std::size_t j =0; j<ROWS; ++j)
	{
		for(std::size_t k =0; k<2*COLS; ++k)
		{
			m.at(j).at(k) = (k<COLS) ? (matrix.at(j).at(k)) : (i.at(j).at(k-COLS));
		}
	}

	return m;
}


template<const std::size_t ROWS , const std::size_t COLS ,typename T>
Matrix<ROWS,COLS/2,T> Matrix<ROWS,COLS,T>::deconcatenate ()
{
	Matrix<ROWS,COLS/2,T> m;
	std::size_t startRowPos = COLS/2;

	for(std::size_t j =0; j<ROWS; ++j)
	{
		for(std::size_t k =startRowPos; k<COLS; ++k)
		{
			m.at(j).at(k-startRowPos) = this->at(j).at(k);
		}
	}

	return m;
}


template <std::size_t ROWS, std::size_t COLS, typename T>
std::size_t Matrix<ROWS,COLS,T>::findTopRow(std::size_t rowPos)
{
	std::size_t highestPriorityPos = 0;
	bool isNumberOneFound = false;
	T highestValue= 0;
	for(std::size_t i = rowPos; i<this->getRowSize(); ++i)
	{
		if(std::abs(this->at(i).at(rowPos)) == 1)
		{
			if(!isNumberOneFound)
			{
				highestPriorityPos = i;
				isNumberOneFound = true;
			}
			else
			{
				for(std::size_t j =0 ; j<this->getColumnSize(); ++j)
				{
					if(std::abs(this->at(i).at(j)) > std::abs(this->at(highestPriorityPos).at(j)))
					{

						highestPriorityPos = i;
						break;
					}
				}
			}
		}
		else if(!isNumberOneFound)
		{
			if(std::abs(this->at(i).at(rowPos)) > highestValue)
			{
				highestValue = std::abs(this->at(i).front());
				highestPriorityPos = i;
			}
			else if(std::abs(this->at(i).at(rowPos)) == highestValue)
			{
				for(std::size_t j =0 ; j<this->getColumnSize(); ++j)
				{
					if(std::abs(this->at(i).at(j)) > std::abs(this->at(highestPriorityPos).at(j)))
					{
						highestPriorityPos = i;
						break;
					}
				}
			}
		}
	}
	return highestPriorityPos;
}

template <std::size_t ROWS, std::size_t COLS, typename T>
void Matrix<ROWS,COLS,T>::swapRows(std::size_t currentRowPos,std::size_t targetRowPos)
{
	this->at(currentRowPos).swap(this->at(targetRowPos));
}

template <std::size_t ROWS, std::size_t COLS, typename T>
void Matrix<ROWS,COLS,T>::correctRowType(std::size_t targetRowPos)
{
	T factor =(1/this->at(targetRowPos).at(targetRowPos));
	std::for_each(this->at(targetRowPos).begin(),this->at(targetRowPos).end(),[&factor](T& number){number*=factor;});
}


template <std::size_t ROWS, std::size_t COLS, typename T>
void Matrix<ROWS,COLS,T>::echolonForm(std::size_t startPos)
{
	T factor = 0;

	std::array<T,COLS> firstRow = this->at(startPos);

	for(std::size_t row =0; row<this->getRowSize(); ++row)
		{
			factor = this->at(row).at(startPos);
			if(startPos!=row)
			{

				for(std::size_t col = 0; col<this->getColumnSize(); ++col)
				{
					this->at(row).at(col) -= (factor*firstRow.at(col));
				}
			}

		}
}


template <std::size_t ROWS, std::size_t COLS, typename T>
void Matrix<ROWS,COLS,T>::echolonRowForm(std::size_t startPos)
{
	T factor = 0;


	std::array<T,COLS> firstRow = this->at(startPos);

	for(std::size_t row =startPos; row<this->getRowSize(); ++row)
		{
			factor = (this->at(row).at(startPos))/firstRow.at(startPos);
			if(startPos!=row)
			{

				for(std::size_t col = 0; col<this->getColumnSize(); ++col)
				{
					this->at(row).at(col) -= (factor*firstRow.at(col));
				}
			}

		}
}


//for the row-echelon form used in this function
//see the theory here https://www.physicsforums.com/threads/determinants-by-row-reduction-row-echelon-form.416298/
template<const std::size_t ROWS, const std::size_t COLS,typename T>
bool Matrix<ROWS,COLS,T>::isDeterminant()
{
	T sum = 1;
	std::size_t nZeroColumns = 0;
	std::size_t nZeroRows = 0;

	for(std::size_t row = 0; row<getRowSize(); ++row)
	{
		for(std::size_t col = 0; col<getColumnSize()/2; ++col)
		{
			if(this->at(row).at(col)==0) ++nZeroColumns;
			if(this->at(col).at(row)==0) ++nZeroRows;
		}

		if(nZeroColumns == COLS/2 || nZeroRows == ROWS) return false;
	}

	for(std::size_t row = 0; row<getRowSize(); ++row)
	{
		std::size_t foundRowPos = findTopRow(row);
		swapRows(row,foundRowPos);
		echolonRowForm(row); //row-echelon form
		sum*=this->at(row).at(row);
	}

	return sum!=0;
}


#endif /* MATRIX_HPP_ */

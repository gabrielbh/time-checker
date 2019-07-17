//
// Created by gabriel on 16/01/2018.
//

#ifndef EX3_MATRIX_HPP
#define EX3_MATRIX_HPP

#endif //EX3_MATRIX_HPP

#include "iostream"
#include <exception>

#define DEFAULT_ROWS 1
#define DEFAULT_COLS 1
#define INITIAL_CELL 0

#include "ostream"
#include <vector>
#include <unordered_map>
#include "Complex.h"

using namespace std;
static const char *const DIFF_ROW_COL_SIZE = "Wrong input: row size not equal to col size";
static const char *const DIMENSIONS = "Two matrix have different dimensions";
static const char *const OUT_OF_BOUND = "index out of bound";


template<class T>

/**
 * generic matrix class
 */
class Matrix
{
public:
    /**
     * default constructor.
     */
    Matrix();

    /**
     * constructor.
     */
    Matrix(unsigned int rows, unsigned int cols);

    /**
     * copy constructor.
     */
    Matrix(const Matrix<T> &matrix);

    /**
     * move constructor.
     */
    Matrix(Matrix<T> && matrix);

    /**
     * destructor.
     */
    ~Matrix();

    /**
     * constructor that initialize a matrix size with certain objects in a specific place.
     */
    Matrix(unsigned int rows, unsigned int cols, const vector<T> &cells);

    /**
     * operator "=" implementation.
     */
    Matrix<T> &operator=(const Matrix<T> &matrix);

    /**
     * operator "+" implementation.
     */
    Matrix<T> &operator+(const Matrix<T> &matrix);

    /**
     * operator "-" implementation.
     */
    Matrix<T> &operator-(const Matrix<T> &matrix);

    /**
     * operator "*" implementation.
     */
    Matrix<T> &operator*(const Matrix<T> &matrix);

    /**
     * operator "==" implementation.
     */
    bool operator==(const Matrix<T> &matrix);

    /**
     * operator "!=" implementation.
     */
    bool operator!=(const Matrix<T> &matrix);


    /**
     * operator "<<" implementation.
     */
    template<class A>
    friend ostream &operator<<(ostream &os, const Matrix<A> &matrix);

    /**
     * returns a Transpose matrix of the current one.
     */
    Matrix<T> trans();

    /**
     * function that checks if the matrix is squared.
     */
    bool isSquareMatrix() const;

    /**
     * operator "()" implementation.
     */
    T operator()(unsigned int row, unsigned int col);

    /**
     * const operator "()" implementation.
     */
    T operator()(unsigned int row, unsigned int col) const;

    typedef typename vector<T>::const_iterator const_iterator;

    /**
     * iterator from the beginning to the end.
     */
    const_iterator begin() const
    {
        return _matrix.cbegin();
    }

    /**
     * iterator from the end to the beginning.
     */
    const_iterator end() const
    {
        return _matrix.cend();
    }

    /**
     * _row getter
     */
    unsigned int rows() const;

    /**
     * _col getter
     */
    unsigned int cols() const;


private:
    unsigned int _rows;
    unsigned int _cols;
    vector<T> _matrix;


    /**
     * nested class for exceptions.
     */
    class Exceptions : public exception
    {
    public:
        explicit Exceptions(const char *error_message) : _message(error_message)
        {

        }

        const char *what() const noexcept override
        {
            return _message;
        }

    private:
        const char *_message;
    };
};


/**
 * default constructor.
 * @tparam T
 */
template<class T>
Matrix<T>::Matrix()
{
    _rows = DEFAULT_ROWS;
    _cols = DEFAULT_COLS;
    _matrix = {DEFAULT_ROWS * DEFAULT_COLS, INITIAL_CELL};
}


/**
 * constructor.
 */
template<class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols):
        _rows(rows), _cols(cols), _matrix(rows * cols, T(INITIAL_CELL))
{
}


/**
 * copy constructor.
 */
template<class T>
Matrix<T>::Matrix(const Matrix<T> &matrix)
{
    _rows = matrix._rows;
    _cols = matrix._cols;
    _matrix = matrix._matrix;
}


/**
 * move constructor.
 */
template<class T>
Matrix<T>::Matrix(Matrix<T> && matrix)
{
    _rows = matrix._rows;
    _cols = matrix._cols;
    _matrix = std::move(matrix._matrix);

}


/**
 * constructor that initialize a matrix size with certain objects in a specific place.
 */
template<class T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols, const vector<T> &cells)
{
    _rows = rows;
    _cols = cols;
    _matrix = cells;
}


/**
 * destructor.
 */
template<class T>
Matrix<T>::~Matrix() = default;


/**
 * operator "=" implementation.
 */
template<class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix)
{

    if (this != &matrix)
    {
        _rows = matrix._rows;
        _cols = matrix._cols;
        _matrix = matrix._matrix;
    }
    return *this;
}


/**
 * operator "+" implementation.
 */
template<class T>
Matrix<T> &Matrix<T>::operator+(const Matrix<T> &matrix)
{
    if (_rows != matrix._rows || _cols != matrix._cols)
    {
        throw Exceptions(DIMENSIONS);
    }

    for (unsigned int rows = 0; rows < _rows; ++rows)
    {
        for (unsigned int cols = 0; cols < _cols; ++cols)
        {
            _matrix[rows * _cols + cols] += matrix._matrix[rows * matrix._cols + cols];
        }
    }
    return *this;
}


/**
 * operator "-" implementation.
 */
template<class T>
Matrix<T> &Matrix<T>::operator-(const Matrix<T> &matrix)
{
    if (_rows != matrix._rows || _cols != matrix._cols)
    {
        throw Exceptions(DIMENSIONS);
    }

    for (unsigned int rows = 0; rows < _rows; ++rows)
    {
        for (unsigned int cols = 0; cols < _cols; ++cols)
        {
            _matrix[rows * _cols + cols] -= matrix._matrix[rows * matrix._cols + cols];
        }
    }
    return *this;
}


/**
 * operator "*" implementation.
 */
template<class T>
Matrix<T> &Matrix<T>::operator*(const Matrix<T> &matrix)
{
    if (_cols != matrix._rows)
    {
        throw Exceptions(DIFF_ROW_COL_SIZE);
    }
    Matrix<T> newMatrix = Matrix(_rows, matrix._cols);
    for (unsigned int rows = 0; rows < _rows; ++rows)
    {
        for (unsigned int cols = 0; cols < matrix._cols; ++cols)
        {
            T sum = T(0);
            for (unsigned int k = 0; k < _cols; ++k)
            {
                sum += _matrix[rows * _cols + k] * matrix._matrix[k * _cols + cols];
            }
            newMatrix._matrix[rows * newMatrix._cols + cols] = sum;
        }
    }
    *this = newMatrix;
    return *this;
}


/**
 * operator "==" implementation.
 */
template<class T>
bool Matrix<T>::operator==(const Matrix<T> &matrix)
{
    if (_rows != matrix._rows || _cols != matrix._cols)
    {
        return false;
    }
    for (unsigned int row = 0; row < _rows; ++row)
    {
        for (unsigned int col = 0; col < _cols; ++col)
        {
            if (_matrix[row * _cols + col] != matrix._matrix[row * _cols + col])
            {
                return false;
            }
        }
    }
    return true;
}


/**
 * operator "!=" implementation.
 */
template<class T>
bool Matrix<T>::operator!=(const Matrix<T> &matrix)
{
    return !(*this == matrix);
}


/**
 * operator "<<" implementation.
 */
template<class T>
ostream &operator<<(ostream &os, const Matrix<T> &matrix)
{
    for (unsigned int row = 0; row < matrix._rows; ++row)
    {
        for (unsigned int col = 0; col < matrix._cols; ++col)
        {
            os << matrix._matrix[row * matrix._cols + col] << "\t";
        }
        os << "\n";
    }
    return os;
}


/**
 * returns a Transpose matrix of the current one.
 */
template<class T>
Matrix<T> Matrix<T>::trans()
{
    if (!this->isSquareMatrix())
    {
        throw Exceptions(DIFF_ROW_COL_SIZE);
    }
    Matrix transMatrix = Matrix(_rows, _cols);
    for (unsigned int row = 0; row < _rows; ++row)
    {
        for (unsigned int col = 0; col < _cols; ++col)
        {
            transMatrix._matrix[col * _rows + row] = _matrix[row * _cols + col];
        }
    }
    return transMatrix;
}


/**
 * function that checks if the matrix is squared.
 */
template<class T>
bool Matrix<T>::isSquareMatrix() const
{
    return _rows == _cols;
}


/**
 * operator "()" implementation.
 */
template<class T>
T Matrix<T>::operator()(unsigned int row, unsigned int col)
{
    if (row > _rows || col > _cols)
    {
        throw exception();
    }
    return _matrix[row * _cols + col];
}


/**
 * const operator "()" implementation.
 */
template<class T>
T Matrix<T>::operator()(unsigned int row, unsigned int col) const
{
    if (row > _rows || col > _cols)
    {
        throw Exceptions(OUT_OF_BOUND);
    }
    return _matrix[row * _cols + col];
}


/**
 * _row getter
 */
template<class T>
unsigned int Matrix<T>::rows() const
{
    return _rows;
}


/**
 * _col getter
 */
template<class T>
unsigned int Matrix<T>::cols() const
{
    return _cols;
}


/**
 * returns a Conjugate Transpose matrix of the current complex one.
 */
template<>
Matrix<Complex> Matrix<Complex>::trans()
{
    if (!this->isSquareMatrix())
    {
        throw Exceptions(DIFF_ROW_COL_SIZE);
    }
    Matrix<Complex> newComplexMatrix(_rows, _cols);
    for (unsigned int row = 0; row < _rows; ++row)
    {
        for (unsigned int col = 0; col < _cols; ++col)
        {
            newComplexMatrix._matrix[col * _rows + row] = _matrix.at(row * _cols + col).conj();
        }
    }
    return newComplexMatrix;
}


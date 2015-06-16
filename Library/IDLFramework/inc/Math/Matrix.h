/******************************************************************************
* File Name          : Matrix.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 7/8/2013
* Description        : Matrix math
*
*******************************************************************************/
#ifndef MATRIX_H
#define MATRIX_H

#include "Generic/GenericTypeDef.h"

enum MATRIX_MATH{
  MATRIX_MATH_FAIL 		= 0,
  MATRIX_MATH_SUCCESS 	= 1,
};

template <class T, uint16_t  nRows, uint16_t nCols>
class Matrix{
public:
  Matrix();
  ~Matrix(){};
  Matrix(const Matrix &A);
  Matrix<T,nRows,nCols>& operator=(const Matrix<T,nRows,nCols> &B);
  T& operator()(const unsigned& row, const unsigned& col);
	Matrix<T,nRows,nCols>& operator+=(const Matrix<T,nRows,nCols> &B);
	Matrix<T,nRows,nCols>& operator-=(const Matrix<T,nRows,nCols> &B);
  
  void fill(T val);
  
private:
  T mat[nRows][nCols];
  uint16_t nRows_;
  uint16_t nCols_;
  uint32_t nElements_;
};

//Constructor
template<class T,uint16_t nRows,uint16_t nCols> 
Matrix<T,nRows,nCols>::Matrix(){
  nRows_ = nRows;
  nCols_ = nCols;
  nElements_ = nRows * nCols;
  this->fill(0);
}

//Fill with value
template<class T,uint16_t nRows,uint16_t nCols> 
void Matrix<T,nRows,nCols>::fill(T val){
  for(uint32_t r=0;r<nRows_;r++){
	for(uint32_t c=0;c<nCols_;c++){ 
	 mat[r][c] = val;
	}
  }
}

//Access individual element
template<class T,uint16_t nRows,uint16_t nCols> 
T& Matrix<T,nRows,nCols>::operator()(const unsigned& row, const unsigned& col) {
  return this->mat[row][col];
}

//Assignment Operator (whole matrix)
template<class T,uint16_t nRows,uint16_t nCols> 
Matrix<T,nRows,nCols>& Matrix<T,nRows,nCols>::operator=(const Matrix<T,nRows,nCols> &A){
  for(uint32_t r=0;r<nRows_;r++){
	for(uint32_t c=0;c<nCols_;c++){ 
	 mat[r][c] = A[r][c];
	}
  }
  return *this;
}

//Override += operator
template<class T,uint16_t nRows,uint16_t nCols> 
Matrix<T,nRows,nCols>& Matrix<T,nRows,nCols>::operator+=(const Matrix<T,nRows,nCols> &A){
  for(uint32_t r=0;r<nRows_;r++){
	for(uint32_t c=0;c<nCols_;c++){ 
	 mat[r][c] += A[r][c];
	}
  }
  return *this;
}

//Override -= operator
template<class T,uint16_t nRows,uint16_t nCols> 
Matrix<T,nRows,nCols>& Matrix<T,nRows,nCols>::operator-=(const Matrix<T,nRows,nCols> &A){
  for(uint32_t r=0;r<nRows_;r++){
	for(uint32_t c=0;c<nCols_;c++){ 
	 mat[r][c] -= A[r][c];
	}
  }
  return *this;
}

#endif





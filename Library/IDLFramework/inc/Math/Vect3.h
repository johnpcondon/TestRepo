/******************************************************************************
* File Name          : Vect3.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : 3 element vector
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef VECT3_H
#define VECT3_H

#include "Generic/GenericTypeDef.h"
#include <math.h>

template <class T>
class Vect3{
public:
  Vect3();
  ~Vect3(){};
  Vect3(const Vect3 &A);
  Vect3<T>& operator=(const Vect3<T> &B);
  T& operator[](const uint16_t i);
  T& operator()(const uint16_t i);
	Vect3<T>& operator+=(const Vect3<T> &B);
	Vect3<T>& operator-=(const Vect3<T> &B);
  Vect3<T>& operator/=(const T& val);
	Vect3<T>& operator*=(const T& val);

  void fill(T val);
  T norm();
  
private:
	static const uint16_t numElements = 3;
  T Data[numElements];
	
};

//Constructor
template<class T> 
Vect3<T>::Vect3(){
  this->fill(0);
}



//Access individual element
template<class T> 
T& Vect3<T>::operator[](const uint16_t i) {
  return this->Data[i];
}


//Access individual element
template<class T> 
T& Vect3<T>::operator()(const uint16_t i) {
  return this->Data[i];
}

//Assignment Operator (whole vector)
template<class T> 
Vect3<T>& Vect3<T>::operator=(const Vect3<T> &A){
	for(uint16_t i=0;i<numElements;i++){ 
	 this->Data[i] = A.Data[i];
	}
  return *this;
}

//Override += operator
template<class T> 
Vect3<T>& Vect3<T>::operator+=(const Vect3<T> &A){
	for(uint16_t i=0;i<numElements;i++){ 
	 this->Data[i] += A.Data[i];
	}
  return *this;
}

//Override += operator
template<class T> 
Vect3<T>& Vect3<T>::operator-=(const Vect3<T> &A){
	for(uint16_t i=0;i<numElements;i++){ 
	 this->Data[i] -= A.Data[i];
	}
  return *this;
}

//Divide by scaler (element by element)
template<class T> 
Vect3<T>& Vect3<T>::operator/=(const T& val){
	for(uint16_t i=0;i<numElements;i++){
	 this->Data[i] /= val;
	}
  return *this;  
}

//Multiply by scaler (element by element)
template<class T> 
Vect3<T>& Vect3<T>::operator*=(const T& val){
	for(uint16_t i=0;i<numElements;i++){
	 this->Data[i] *= val;
	}
  return *this;  
}

//Fill with value
template<class T> 
void Vect3<T>::fill(T val){
  for(uint16_t i=0;i<numElements;i++){
	 Data[i] = val;
	}
}


//Find Vector Norm
template<class T> 
T Vect3<T>::norm(){
  T result = 0;
  
  for(uint16_t i=0;i<numElements;i++){
	 result += Data[i] * Data[i];
	}
  
  result = sqrt(result);
  
  return result;
}

#endif

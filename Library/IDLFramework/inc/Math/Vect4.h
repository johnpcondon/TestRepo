/******************************************************************************
* File Name          : Vect4.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 7/8/2013
* Description        : 3 element vector
*
*******************************************************************************/
#ifndef VECT4_H
#define VECT4_H

#include "Generic/GenericTypeDef.h"
#include "math.h"

template <class T>
class Vect4{
public:
  Vect4();
  ~Vect4(){};
  Vect4(const Vect4 &A);
  Vect4<T>& operator=(const Vect4<T> &B);
  T& operator[](const uint16_t i);
  T& operator()(const uint16_t i);
	Vect4<T>& operator+=(const Vect4<T> &B);
	Vect4<T>& operator-=(const Vect4<T> &B);
  Vect4<T>& operator/=(const T& val);
	Vect4<T>& operator*=(const T& val);
	
	
  void fill(T val);
  T norm();
  
private:
  T* pData;
	static const uint8_t numElements = 4;
};

//Constructor
template<class T> 
Vect4<T>::Vect4(){
	pData = new T[numElements];
  this->fill(0);
}



//Access individual element
template<class T> 
T& Vect4<T>::operator[](const uint16_t i) {
  return this->pData[i];
}


//Access individual element
template<class T> 
T& Vect4<T>::operator()(const uint16_t i) {
  return this->pData[i];
}

//Assignment Operator (whole vector)
template<class T> 
Vect4<T>& Vect4<T>::operator=(const Vect4<T> &A){
	for(uint16_t i=0;i<numElements;i++){ 
	 this->pData[i] = A.pData[i];
	}
  return *this;
}

//Override += operator
template<class T> 
Vect4<T>& Vect4<T>::operator+=(const Vect4<T> &A){
	for(uint16_t i=0;i<numElements;i++){ 
	 this->pData[i] += A.pData[i];
	}
  return *this;
}

//Override += operator
template<class T> 
Vect4<T>& Vect4<T>::operator-=(const Vect4<T> &A){
	for(uint16_t i=0;i<numElements;i++){ 
	 this->pData[i] -= A.pData[i];
	}
  return *this;
}

//Divide by scaler (element by element)
template<class T> 
Vect4<T>& Vect4<T>::operator/=(const T& val){
	for(uint16_t i=0;i<numElements;i++){
	 this->pData[i] /= val;
	}
  return *this;  
}

//Multiply by scaler (element by element)
template<class T> 
Vect4<T>& Vect4<T>::operator*=(const T& val){
	for(uint16_t i=0;i<numElements;i++){
	 this->pData[i] *= val;
	}
  return *this;  
}

//Fill with value
template<class T> 
void Vect4<T>::fill(T val){
  for(uint16_t i=0;i<numElements;i++){
	 pData[i] = val;
	}
}


//Find Vector Norm
template<class T> 
T Vect4<T>::norm(){
  T result = 0;
  
  for(uint16_t i=0;i<numElements;i++){
	 result += pData[i] * pData[i];
	}
  
  //result = isqrt(result);
  //Not implimented yet
  
  return result;
}

#endif

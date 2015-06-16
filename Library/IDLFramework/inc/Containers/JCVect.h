/******************************************************************************
* File Name          : JCvector.h
* Author             : John Condon
* Version            : V 1.0
* Date               : 6/3/2015
* Description        : Custom list Class with fixed sizes
*
* Copyright (C) Innovative Design Labs, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* This file is subject to the terms and conditions defined in
* file 'LICENSE.txt', which is part of this source code package.
******************************************************************************/
#ifndef JCVECT_H
#define JCVECT_H

template <class T>
class vector{
public:
  vector(int32_t num_elements);
  ~vector();
  T& operator[](const unsigned& i);
  T& operator()(const unsigned& i);
  T& get(const unsigned& i);
	T& end(void);
		
  void push_back(T val);
  bool remove(int i);
	void clear();
  int find(T val); //Returns index of location
  int getCnt(void){return cnt;};
  int getCapacity(void){return nElements;};
	int getFree(){return (nElements - cnt);};
  
private:
  T* pData; //Pointer to array of data
  int nElements;
  int cnt;
};

//Constructor
template<class T>
vector<T>::vector(int32_t num_elements){
  nElements = num_elements;
  cnt = 0;
	pData = new T[num_elements];
}

//Destructor
template<class T>
vector<T>::~vector(){
  delete pData;
}

//Access individual element
template<class T>
T& vector<T>::operator[](const unsigned& i) {
  if(i < cnt)
  	return this->pData[i];
  else
	 while(1); //Out of bounds access
}

//Access individual element
template<class T>
T& vector<T>::operator()(const unsigned& i) {
  if(i < cnt)
  	return this->pData[i];
  else
	 while(1);
}

//Access individual element
template<class T>
T& vector<T>::get(const unsigned& i) {
  if(i < cnt)
  	return this->pData[i];
  else
	 while(1); //Out of bounds access
}


template<class T>
T& vector<T>::end(void) {
	int iEnd = this->cnt - 1;
	return this->pData[iEnd];
}
//Push Back, adds a pointer to the list
template<class T>
void vector<T>::push_back(T val)
{
  if( (cnt) < nElements)
  	pData[cnt++] = val;
  else
	 while(1); //Overran vector
}

//Delete an element reshuffles order
template<class T>
bool vector<T>::remove(int i)
{
	int j;
  if(i>=cnt){
	 return false; //tried to delete bad index
  }

  //Consecutively move elements up to repopulate the whole
	
  for(j=i; j<(cnt-2); j++)
  {
	 pData[j] = pData[j+1];
  }
	
  pData[j]=0;
  cnt--;
  
  return true;
}

//Delete all elements
template<class T>
void vector<T>::clear()
{
	cnt = 0;
}

//Find an element with a specified value (only returns first result)
//If it can't find the value, -1 is returned
template<class T>
int vector<T>::find(T val)
{
  int i=0;
  while(i<cnt)
  {
	 if(pData[i] == val){
		return i;
	 }
	 i++;
  }
  return -1;
  
}

#endif




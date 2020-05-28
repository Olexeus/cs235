

#ifndef vector_cpp
#define vector_cpp

#include "vector.h"

using namespace custom;

template<class T>
inline vector<T>::vector()
{
   numCapacity = 0;
   numElements = 0;
   buffer = NULL;
}

template<class T>
inline vector<T>::vector(int numElements) : vector()
{
   if (numElements <= 0) throw "Error: vector sizes must be greater than 0.";
   this->numElements = numElements;
   this->resize(this->numElements);

   for (int i = 0; i < this->numCapacity; i++)
   {
      buffer[i] = 0;
   }
}

template<class T>
inline vector<T>::vector(int numElements, T t) : vector(numElements)
{
   if (numElements <= 0) throw "Error: vector sizes must be greater than 0.";
   this->numElements = numElements;
   this->resize(this->numElements);

   for (int i = 0; i < this->numCapacity; i++)
   {
      buffer[i] = t;
   }
}

template<class T>
vector<T>::vector(const vector& rhs)
{
}

template<class T>
inline vector<T>::~vector()
{
   if (buffer != NULL) delete[] buffer;
   this->numElements = this->numElements = 0;
   buffer = NULL;
}

template<class T>
inline void vector<T>::clear()
{
   this->numElements = 0;
}

template<class T>
vector<T>& vector<T>::operator=(const vector& rhs)
{
   this->numElements = 0;
   if (rhs.size() > this->numCapacity)
   {
      this->resize(rhs.size());
   }
   this->numElements = rhs.size();
   for (int i = 0; i < this->numElements - 1; i++)
   {
      buffer[i] = rhs.buffer[i];
   }
   return *this;
}

template<class T>
inline void vector<T>::push_back(T t)
{
   if (this->numElements == this->numCapacity)
   {
      this->resize(this->numCapacity + 1);
   }
   buffer[this->numElements++] = t;
}

template<class T>
const T vector<T>::operator[](int index) const
{
   if (index < 0 || index >= this->numElements) throw char('e');
   return buffer[index];
}

template<class T>
T& vector<T>::operator[](int index)
{
   if (index < 0 || index >= this->numElements) throw char('e');
   return buffer[index];
}

template<class T>
inline void vector<T>::resize(int numCapacity)
{
   //if (numCapacity <= 0) throw "Error: vector sizes must be greater than 0.";
   if (numCapacity > 0)
   {
      int currentCapacity = this->numCapacity;
      while (currentCapacity < numCapacity)
      {
         currentCapacity = (1 < currentCapacity * 2) ? currentCapacity * 2 : 1;
      }
      T* newArray = new T[currentCapacity];

      if (buffer != NULL)
      {
         for (int i = 0; i < this->numElements; i++)
         {
            newArray[i] = buffer[i];
         }
         delete[] buffer;
      }
      buffer = newArray;
      this->numCapacity = currentCapacity;
   }
   
}

#endif
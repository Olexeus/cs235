#include "vector.h"
#include <stddef.h>

using namespace custom;

/* custom vector implementation 
 ******************************************************************************/

template <class T>
vector<T>::vector()
{
   numCapacity = 0;
   numElements = 0;
   buffer = NULL;
}

template <class T>
vector<T>::vector(int numElements)
{
   if (numElements <= 0) 
      throw "Error: vector sizes must be greater than 0.";

   this->numCapacity = numElements;
   this->numElements = numElements;
   this->buffer = new T[numElements];
   for (int i = 0; i < numElements; i++)
      this->buffer[i] = T();
}

template <class T>
vector<T>::vector(int numElements, const T & t)
{
   if (numElements <= 0) 
      throw "Error: vector sizes must be greater than 0.";

   this->numCapacity = numElements;
   this->numElements = numElements;
   this->buffer = new T[numElements];
   for (int i = 0; i < numElements; i++)
      this->buffer[i] = t;
}

template <class T>
vector<T>::vector(const vector <T> & rhs)
{
   *this = rhs;
}

template <class T>
vector<T>::~vector()
{
   delete [] buffer;
}

template <class T>
vector<T>& vector<T>::operator = (const vector <T> & rhs)
{
   numCapacity = rhs.numElements;
   numElements = rhs.numElements;
   buffer = new T[rhs.numElements];
   for (int i = 0; i < rhs.numElements; i++)
      buffer[i] = rhs.buffer[i];
   return *this;
}

template <class T>
int vector<T>::size() const
{
   return numElements;
}

template <class T>
int vector<T>::capacity() const
{
   return numCapacity;
}

template <class T>
bool vector<T>::empty() const
{
   return (numElements == 0);
}

template <class T>
void vector<T>::clear()
{
   numElements = 0;
}

template <class T>
void vector<T>::push_back(const T & t)
{
   if (numElements == numCapacity)
      resize((numCapacity == 0) ? 1 : numCapacity  * 2);
   buffer[numElements++] = t;
}

template <class T>
T& vector<T>::operator [] (int index)
{
   if (buffer == NULL || index < 0 || index > numElements)
      throw "Error: indices must be greater than zero and less than size().";
   return buffer[index];
}

template <class T>
typename vector<T>::iterator vector<T>::begin()
{
   return iterator(buffer);
}

template <class T>
typename vector<T>::iterator vector<T>::end()
{
   return iterator(buffer + numElements);
}

template <class T>
void vector<T>::resize(int newCapacity)
{
   if (newCapacity == 0)
   {
      numCapacity = 0;
      numElements = 0;
      delete [] buffer;
      buffer = NULL;
   }
   
   if (newCapacity > 0)
   {
      T* newBuffer = new T[newCapacity];
      for (int i = 0; i < numElements; i++)
         newBuffer[i] = buffer[i];
      delete [] buffer;
      buffer = newBuffer;
      numCapacity = newCapacity;
      if (newCapacity < numElements) // we're shrinking
         numElements = newCapacity;
   }
}

/* custom vector::iterator implementation 
 ******************************************************************************/

template <class T>
vector<T>::iterator::iterator()
{
   ptr = NULL;
}

template <class T>
vector<T>::iterator::iterator(T * p)
{
   ptr = p;
}

template <class T>
vector<T>::iterator::iterator(const iterator & rhs)
{
   *this = rhs;
}

template <class T>
typename vector<T>::iterator& vector<T>::iterator::operator = (const iterator & rhs)
{
   ptr = rhs.ptr;
   return *this;
}

template <class T>
bool vector<T>::iterator::operator != (const iterator & rhs) const 
{ 
   return rhs.ptr != this->ptr;
}

template <class T>
bool vector<T>::iterator::operator == (const iterator & rhs) const 
{ 
   return rhs.ptr == this->ptr;
}

template <class T>
T& vector<T>::iterator::operator * ()
{
   return *ptr;
}

template <class T>
typename vector<T>::iterator& vector<T>::iterator::operator ++ ()
{
   if (ptr != NULL) 
      ptr++;
   return *this;
}

template <class T>
typename vector<T>::iterator vector<T>::iterator::operator ++ (int postfix)
{
   iterator original(*this);
   if (ptr != NULL) 
      ptr++;
   return original;
}

template <class T>
typename vector<T>::iterator& vector<T>::iterator::operator -- ()
{
   if (ptr != NULL)
      ptr--;
   return *this;
}

template <class T>
typename vector<T>::iterator vector<T>::iterator::operator -- (int postfix)
{
   iterator tmp(*this);
   if (ptr != NULL)
      ptr--;
   return tmp;
}

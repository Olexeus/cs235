/*
 * Custom vector implementation with iterator and const iterator.
 * 
 * @author Matt Manley
 * @since 19 Sep 2019
 */

#ifndef VECTOR_H
#define VECTOR_H

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom
{

   /*
    * Custom implementation of vector.
    */
   template <class T>
   class vector
   { 
      public:

         #ifdef UNIT_TESTING
         friend int ::main(int argc, const char* argv[]);
         #endif

         vector();
         vector(int numElements);
         vector(int numElements, const T & t);
         vector(const vector <T> & rhs);
         ~vector();
         
         vector <T> & operator = (const vector <T> & rhs);

         int size() const;
         int capacity() const;
         bool empty() const;
         void clear();

         void push_back(const T & t);
         T & operator [] (int index);
         
         class iterator;
      
         iterator begin();
         iterator end();
      
      private:

         void resize(int newCapacity);

         T * buffer;
         int numCapacity;
         int numElements;
        
         
   };

   /*
    * Read-write iterator for vector
    */
   template <class T>
   class vector <T> :: iterator
   {
      public:
         
         #ifdef UNIT_TESTING
         friend int ::main(int argc, const char* argv[]);
         #endif
         
         iterator();
         iterator(T * p);
         iterator(const iterator & rhs);
         iterator& operator = (const iterator & rhs);
         bool operator != (const iterator & rhs) const;
         bool operator == (const iterator & rhs) const;
         T & operator * ();
         iterator & operator ++ ();
         iterator operator ++ (int postfix);
         iterator & operator -- ();
         iterator operator -- (int postfix);
         
      private:

         T * ptr;
   
   };

}

#include "vector.cpp"

#endif
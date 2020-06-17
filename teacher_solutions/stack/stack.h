/*
 * Custom stack implementation.
 * 
 * @author Matt Manley
 * @since 30 Sep 2019
 */

#ifndef STACK_H
#define STACK_H

#ifdef UNIT_TESTING
int main(int argc, const char* argv[]);
#endif

namespace custom
{

   /*
    * Custom implementation of vector.
    */
   template <class T>
   class stack
   { 
      public:

         #ifdef UNIT_TESTING
         friend int ::main(int argc, const char* argv[]);
         #endif

         stack();
         stack(int numElements);
         stack(int numElements, const T & t);
         stack(const stack <T> & rhs);
         ~stack();
         
         stack <T> & operator = (const stack <T> & rhs);

         int size() const;
         int capacity() const;
         bool empty() const;
         void clear();

         void push(const T & t);
         void pop();
         T& top();
               
      private:

         void resize(int newCapacity);

         T * buffer;
         int numCapacity;
         int numElements;
         
   };

}

#include "stack.cpp"

#endif
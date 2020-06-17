/***********************************************************************
 * Header:
 *    Array
 * Summary:
 *    This class contains the notion of an array: an ordered constainer for
 *    holding data. This is a starting-point and pattern for you to follow
 *    as you create the more advanced constainers you will build later this
 *    semester such as the vector, set, stack, queue, deque, map, tree, and
 *    graph.
 *
 * Author:
 *    James Helfrich
 * Modified Beyond Recognition By:
 *    Lee Barney
 ***********************************************************************
 *  Copyright (c) 2019 Lee Barney
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <new>

int main(int argc, const char* argv[]);
namespace custom {
    /************************************************
     * ARRAY
     * An ordered, non-resizable container for data
     ***********************************************/
    template< typename T > class array{
#ifdef UNIT_TESTING
        friend int ::main(int argc, const char* argv[]);
#endif
    private:
        T* buffer;        // dynamically allocated array of T
        int numCapacity;  // both the capacity and the number of elements in the Array
    public:
        /*
         * Constructors
         */
        
        //default constructor
        array(){
            buffer = NULL;
            numCapacity = 0;
        }
        
        //non-default constructor
        array(int aCapacity) throw (const char *){
            
            // check for error conditions in the paramters passed.
            if (aCapacity <= 0){
                throw "Error: array sizes must be greater than zero.";
            }
            
            // assigne the size tracker
            numCapacity = aCapacity;
            
            // attempt to allocate
            try{
                buffer = new T[numCapacity];
            }
            catch (std::bad_alloc){
                throw "Error: Unable to allocate buffer";
            }
        }
        //copy constructor
        array(const array & arrayToCopy) throw (const char *){
            // do nothing if the array to copy is faulty
            if(arrayToCopy.numCapacity == 0){
                throw "Error: copying an Array with no size";
            }
            // copy over the capacity
            numCapacity = arrayToCopy.numCapacity;
            // attempt to allocate RAM for the new array
            try{
                buffer = new T[arrayToCopy.numCapacity];
            }
            catch (std::bad_alloc){
                throw "Error: Unable to allocate data buffer";
            }
            
            // copy the items over one at a time
            for (int i = 0; i < numCapacity; i++){
                buffer[i] = arrayToCopy.buffer[i];
            }
        }
        
        /*
         * Destructor
         */
        ~array(){
            delete [] buffer;
        }
        
        // standard Container interface methods that are found in all Containers
        // this version of Array treats size and capacity the same
        int  size() const {
            return numCapacity;
        }
        int  capacity() const {
            return numCapacity;
        }
        int empty() const {
            return numCapacity == 0;
        }
        
        /*
         * Operators
         */
        
        //equality operator
        
        bool operator == (const array& anArray) {
            bool comparisonResult = false;
            if (numCapacity == anArray.numCapacity &&
                buffer != NULL && anArray.buffer != NULL) {
                bool piecewiseComparison = true;
                int i = 0;
                while(piecewiseComparison && i < numCapacity){
                    piecewiseComparison = buffer[i] == anArray.buffer[i];
                    i++;
                }
                comparisonResult = piecewiseComparison;
            }
            return comparisonResult;
        }
        
        //assignment operator
        //all standard data structures implement this operator
        array<T> & operator = (const array<T> & arrayToAssign) throw (const char *){
            // we can only copy arrays of equal size. Vectors are not this way!
            if(numCapacity != arrayToAssign.numCapacity){
                throw "Error: attempting to assign arrays of different sizes";
            }
            if(arrayToAssign.numCapacity <= 0){
                throw "Error: attempting to assign array with invalid size";
            }
            for(int i = 0; i < numCapacity; i++){
                buffer[i] = arrayToAssign.buffer[i];
            }
            return *this;
        }
        // array-specific operators
        // observe what happens if index >= numCapacity
        // or index < 0
        
        //getter/setter that allows mutation
        T& operator [] (int index) throw (const char *){
            if(index < 0){
                throw "Error: index must be greater than or equal to zero.";
            }
            if(index >= numCapacity){
                throw "Error: index must be less than the capacity of the array.";
            }
            return buffer[index];
        }
        //getter that does not allow mutation
        const T& operator [] (int index) const throw (const char *){
            if(index < 0){
                throw "Error: index must be greater than zero.";
            }
            if(index >= numCapacity){
                throw "Error: index must be less than the capacity of the array.";
            }
            return buffer[index];
        }
        
        /**************************************************
         * ARRAY ITERATOR
         * A class that eases iteration over the array
         *************************************************/
        class iterator{
#ifdef UNIT_TESTING
            friend int ::main(int argc, const char* argv[]);
#endif
        private:
            T* dataPtr;
        public:
            // constructors
            iterator():dataPtr(NULL){}// more modern constructor code
            iterator(T* aPtr):dataPtr(aPtr){}
            //copy constructor
            iterator(const iterator & iteratorToCopy){
                *this = iteratorToCopy;
            }
            //destructor
            ~iterator(){}
            
            /*
             * Iterator Operators
             */
            //Assignment operator
            iterator & operator = (const iterator & iteratorToCopy){
                this->dataPtr = iteratorToCopy.dataPtr;
                return *this;
            }
            
            //Not equals operator
            //compare the dataPtr for this instance to the one of the
            //comparedTo instance
            bool operator != (const iterator & comparedTo) const {
                return dataPtr != comparedTo.dataPtr;
            }
            //Equals operator
            bool operator == (const iterator & comparedTo) const {
                return dataPtr == comparedTo.dataPtr;
            }
            
            //Dereference mutator operator
            T & operator *() throw (const char*){
                if(dataPtr == NULL){
                    throw "Error: dereferencing null data in iterator.";
                }
                return *dataPtr;
            }
            //Dereference accessor operator
            const T & operator *() const {
                if(dataPtr == NULL){
                    throw "Error: dereferencing null data in iterator.";
                }
                return *dataPtr;
            }
            
            //Prefix increment operator
            iterator & operator ++ (){
                if(dataPtr != NULL){
                    dataPtr++;
                }
                return *this;
            }
            
            //Postfix increment operator
            iterator operator ++ (int postfix){
                iterator tmpIterator(*this);
                if(dataPtr != NULL){
                    dataPtr++;
                }
                return tmpIterator;
            }
            
        };// end of array::iterator class
        
        /*
         * array methods to retrieve the beginning
         * and end of the array as iterators
         */
        //begin iterator
        array <T> :: iterator begin(){
            return iterator(buffer);
        }
        //end iterator
        array <T> :: iterator end(){
            return iterator(buffer+numCapacity);
        }
    };//end of array class
}; // end of namespace custom
#endif // ARRAY_H


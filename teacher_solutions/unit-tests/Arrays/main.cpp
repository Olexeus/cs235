/*
 * main.cpp
 *
 *  Created by Lee Barney on 3/13/2019.
 *  Copyright (c) 2018 Lee Barney
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

/* !!!!GRADING INSTRUCTIONS!!!!
 *
 * When you report your score for this test set, report
 * the percentage of asserts found in this test code that
 * your data structure code passed.
 */
#define UNIT_TESTING

/*#ifdef defined(_WIN32) || defined(WIN32)

#define OS_Windows
#endif*/

//Do not change the next line without instructor approval.
//To do so is cheating and, when found, will result in consequences.
int asserts_existing = 75;

#include <cstring>
#include "array.h"
#include "unit_testing.h"

using namespace custom;



int main(int argc, const char* argv[]) {
    /*
     * Testing default constructor
     */
    startTestSet("Default Constructor");
    array <int> defaultArray;
    assertTrue(defaultArray.buffer == NULL,__LINE__);
    assertTrue(defaultArray.numCapacity == 0,__LINE__);
    //cout << "Default Constructor Test Passed" << endl;
    
    /*
     * Testing sized array constructor
     */
    startTestSet("Sized Constructor");
    try{
        array<int> badSizeArray(-3);
        assertTrue(false,__LINE__);
    } catch(const char* exceptionMessage){
        assertTrue(strcmp(exceptionMessage,"Error: array sizes must be greater than zero.") == 0,__LINE__);
    }
    array<int> sizedArray(4);
    assertTrue(sizedArray.buffer != NULL,__LINE__);
    assertTrue(sizedArray.numCapacity == 4,__LINE__);
    
    /*
     * Testing Size
     */
    startTestSet("Size");
    array<int> sizeTestArray;
    
    sizeTestArray.numCapacity = 8;
    assertTrue(sizeTestArray.size() == 8,__LINE__);
    /*
     * Testing Capacity
     */
    startTestSet("Capacity");
    assertTrue(sizeTestArray.capacity() == 8,__LINE__);
    sizeTestArray.numCapacity = 0;
    assertTrue(sizeTestArray.capacity() == 0,__LINE__);
    
    /*
     * Testing Empty
     */
    startTestSet("Empty");
    sizeTestArray.numCapacity = 8;
    
    assertTrue(!sizeTestArray.empty(),__LINE__);
    
    sizeTestArray.numCapacity = 0;
    
    assertTrue(sizeTestArray.empty(),__LINE__);
    
   
    
    /*
     * Testing copy constructor
     */
    startTestSet("Copy Constructor");
    array<int> copyTestArray;
    copyTestArray.numCapacity = 5;
    copyTestArray.buffer = new int[copyTestArray.numCapacity];
    copyTestArray.buffer[0] = 1;
    copyTestArray.buffer[1] = 5;
    copyTestArray.buffer[2] = 10;
    copyTestArray.buffer[3] = 0;
    copyTestArray.buffer[4] = -2;
   
    array<int> arrayCopy(copyTestArray);
    assertTrue(arrayCopy.numCapacity == copyTestArray.numCapacity,__LINE__);
    assertTrue(arrayCopy.buffer != copyTestArray.buffer,__LINE__);
    assertTrue(arrayCopy.buffer[0] == 1,__LINE__);
    assertTrue(arrayCopy.buffer[1] == 5,__LINE__);
    assertTrue(arrayCopy.buffer[2] == 10,__LINE__);
    assertTrue(arrayCopy.buffer[3] == 0,__LINE__);
    assertTrue(arrayCopy.buffer[4] == -2,__LINE__);
    
    /*
     * Testing destructor
     */
    startTestSet("Destructor");
    //resetting counter
    unit_testing_delete_call_counter = 0;
    array<int>* arrayToDestroy = new array<int>();
    delete arrayToDestroy;
    assertTrue(unit_testing_delete_call_counter == 1,__LINE__);
    
    //resetting counter
    unit_testing_delete_call_counter = 0;
    arrayToDestroy = new array<int>(4);
    delete arrayToDestroy;
    assertTrue(unit_testing_delete_call_counter == 2,__LINE__);
    
    
    //resetting counter
    unit_testing_delete_call_counter = 0;
    array<int>* filledArrayToDestroy = new array<int>(4);
    filledArrayToDestroy->buffer[0] = 3;
    filledArrayToDestroy->buffer[1] = 5;
    filledArrayToDestroy->buffer[2] = 7;
    filledArrayToDestroy->buffer[3] = 1;
    delete filledArrayToDestroy;
    assertTrue(unit_testing_delete_call_counter == 2,__LINE__);
    
    /*
     * Testing = operator
     */
    startTestSet("Assignment Operator =");
    array<int> arrayAssignedTo = copyTestArray;
    assertTrue(arrayAssignedTo.numCapacity == copyTestArray.numCapacity,__LINE__);
    assertTrue(arrayAssignedTo.buffer != copyTestArray.buffer,__LINE__);
    assertTrue(arrayAssignedTo.buffer[0] == 1,__LINE__);
    assertTrue(arrayAssignedTo.buffer[1] == 5,__LINE__);
    assertTrue(arrayAssignedTo.buffer[2] == 10,__LINE__);
    assertTrue(arrayAssignedTo.buffer[3] == 0,__LINE__);
    assertTrue(arrayAssignedTo.buffer[4] == -2,__LINE__);
    
    /*
     * Testing == operator
     */
    startTestSet("Equality Operator");
    array<int> equalityTestArray;
    equalityTestArray.numCapacity = 5;
    equalityTestArray.buffer = new int[5];
    equalityTestArray.buffer[0] = 1;
    equalityTestArray.buffer[1] = 5;
    equalityTestArray.buffer[2] = 10;
    equalityTestArray.buffer[3] = 0;
    equalityTestArray.buffer[4] = -2;
    assertTrue(equalityTestArray == equalityTestArray,__LINE__);
    assertTrue(equalityTestArray == copyTestArray,__LINE__);
    
    array<int> notEqualTestArray;
    //testing differing capacities
    notEqualTestArray.numCapacity = 3;
    assertTrue(!(equalityTestArray == notEqualTestArray),__LINE__);
    notEqualTestArray.numCapacity = 10;
    assertTrue(!(equalityTestArray == notEqualTestArray),__LINE__);
    notEqualTestArray.numCapacity = INT_MAX;
    assertTrue(!(equalityTestArray == notEqualTestArray),__LINE__);
    
    //testing same capacity, different values
    notEqualTestArray.numCapacity = 5;
    //null buffer test
    assertTrue(!(equalityTestArray == notEqualTestArray),__LINE__);
    
    //last different
    notEqualTestArray.buffer = new int[notEqualTestArray.numCapacity];
    notEqualTestArray.buffer[0] = 1;
    notEqualTestArray.buffer[1] = 5;
    notEqualTestArray.buffer[2] = 10;
    notEqualTestArray.buffer[3] = 0;
    notEqualTestArray.buffer[4] = 3;
    assertTrue(!(equalityTestArray == notEqualTestArray),__LINE__);
    
    //first different
    notEqualTestArray.buffer = new int[notEqualTestArray.numCapacity];
    notEqualTestArray.buffer[0] = 7;
    notEqualTestArray.buffer[1] = 5;
    notEqualTestArray.buffer[2] = 10;
    notEqualTestArray.buffer[3] = 0;
    notEqualTestArray.buffer[4] = -2;
    assertTrue(!(equalityTestArray == notEqualTestArray),__LINE__);
    
    //all different
    notEqualTestArray.buffer = new int[notEqualTestArray.numCapacity];
    notEqualTestArray.buffer[0] = 8;
    notEqualTestArray.buffer[1] = 6;
    notEqualTestArray.buffer[2] = 9;
    notEqualTestArray.buffer[3] = -100;
    notEqualTestArray.buffer[4] = 54;
    assertTrue(!(equalityTestArray == notEqualTestArray),__LINE__);
    
    
    /*
     * Testing [] operator
     */
    startTestSet("[] Operator");
    array<int> randomAccessTestArray;
    try{
        //size zero and buffer NULL
        randomAccessTestArray[0];
        assertTrue(false,__LINE__);
    } catch(const char* exceptionMessage){
        assertTrue(strcmp(exceptionMessage,"Error: index must be less than the capacity of the array.") == 0,__LINE__);
    }
    randomAccessTestArray.numCapacity = 5;
    randomAccessTestArray.buffer = new int[randomAccessTestArray.numCapacity];
    randomAccessTestArray.buffer[0] = 8;
    randomAccessTestArray.buffer[1] = 6;
    randomAccessTestArray.buffer[2] = 9;
    randomAccessTestArray.buffer[3] = -100;
    randomAccessTestArray.buffer[4] = 54;
    try{
        //invalid index
        randomAccessTestArray[-1];
        assertTrue(false,__LINE__);
    } catch(const char* exceptionMessage){
        assertTrue(strcmp(exceptionMessage,"Error: index must be greater than or equal to zero.") == 0,__LINE__);
    }
    try{
        //invalid index
        randomAccessTestArray[5];
        assertTrue(false,__LINE__);
    } catch(const char* exceptionMessage){
        assertTrue(strcmp(exceptionMessage,"Error: index must be less than the capacity of the array.") == 0,__LINE__);
    }
    try{
        //invalid index assignment
        randomAccessTestArray[6] = 13;
        assertTrue(false,__LINE__);
    } catch(const char* exceptionMessage){
        assertTrue(strcmp(exceptionMessage,"Error: index must be less than the capacity of the array.") == 0,__LINE__);
    }
    //testing accessor operator
    const int fixedResult = randomAccessTestArray[4];
    assertTrue(fixedResult == randomAccessTestArray.buffer[4],__LINE__);
    
    //testing mutator operator
    randomAccessTestArray[4] = 32;
    assertTrue(randomAccessTestArray.buffer[4] == 32,__LINE__);
    
    
    
    /*
     * Testing Iterator
     */
    startTestSet("Iterator Constructor");
    int* aDataPointer = new int(3);
    
    //testing default constructor
    array<int>::iterator anIterator;
    assertTrue(anIterator.dataPtr == NULL,__LINE__);
    
    array<int>::iterator* iteratorPtr = new array<int>::iterator();
    assertTrue(iteratorPtr->dataPtr == NULL,__LINE__);
    
    //testing non-default constructor
    array<int>::iterator iteratorWithData(aDataPointer);
    assertTrue(aDataPointer == iteratorWithData.dataPtr,__LINE__);
    
    array<int>::iterator* iteratorWithDataPtr = new array<int>::iterator(aDataPointer);
    assertTrue(aDataPointer == iteratorWithDataPtr->dataPtr,__LINE__);
    
    startTestSet("Iterator Copy Constructor");
    //testing copy constructor for default iterator
    array<int>::iterator iteratorToCopy;
    array<int>::iterator copiedIterator(iteratorToCopy);
    assertTrue(copiedIterator.dataPtr == NULL,__LINE__);
    assertTrue(copiedIterator.dataPtr == iteratorToCopy.dataPtr,__LINE__);
    
    //testing copy constructor iterator with data pointer
    iteratorToCopy.dataPtr = aDataPointer;
    array<int>::iterator copiedDataIterator(iteratorToCopy);
    assertTrue(copiedDataIterator.dataPtr == aDataPointer,__LINE__);
    
    startTestSet("Iterator Destructor");
    //testing iterator destructor
    unit_testing_delete_call_counter = 0;
    delete iteratorPtr;
    assertTrue(unit_testing_delete_call_counter == 1,__LINE__);
    
    unit_testing_delete_call_counter = 0;
    delete iteratorWithDataPtr;
    assertTrue(unit_testing_delete_call_counter == 1,__LINE__);
    
    
    /*
     * Testing iterator operators
     */
    
    startTestSet("Iterator Assignment Operator");
    //testing assignment operator
    array<int>::iterator iteratorToAssign;
    array<int>::iterator assignedToIterator = iteratorToAssign;
    assertTrue(assignedToIterator.dataPtr == NULL,__LINE__);
    assertTrue(assignedToIterator.dataPtr == iteratorToAssign.dataPtr,__LINE__);
    
    iteratorToAssign.dataPtr = aDataPointer;
    array<int>::iterator assignedToIteratorWithData(iteratorToAssign);
    assertTrue(assignedToIteratorWithData.dataPtr == aDataPointer,__LINE__);

    startTestSet("Iterator Equality Operator");
    //testing iterator equality operator
    array<int>::iterator comparisonOperatorIterator;
    assertTrue(iteratorToAssign == iteratorToAssign,__LINE__);
    assertTrue(iteratorToAssign == assignedToIteratorWithData,__LINE__);
    assertTrue(!(comparisonOperatorIterator == iteratorToAssign),__LINE__);
    
    startTestSet("Iterator Inequality Operator");
    //testing inequality operator
    assertTrue(comparisonOperatorIterator != iteratorToAssign,__LINE__);
    //reset
    int* someOtherDataPtr = new int(4);
    comparisonOperatorIterator.dataPtr = someOtherDataPtr;
    assertTrue(!(iteratorToAssign != assignedToIteratorWithData),__LINE__);
    /*
     * Testing Dereference Operator
     */
    startTestSet("Iterator Dereference Operator");
    array<int>::iterator nullIt;
    try {
        *nullIt;
        assertTrue(false,__LINE__);
    } catch(const char* exceptionMessage){
        assertTrue(strcmp(exceptionMessage,"Error: dereferencing null data in iterator.") == 0,__LINE__);
    }
    assertTrue(*comparisonOperatorIterator == 4,__LINE__);
    
    *comparisonOperatorIterator = 7;
    assertTrue(*(comparisonOperatorIterator.dataPtr) == 7,__LINE__);
    
    startTestSet("Iterator Pre and Post-increment");
    /*
     * Testing iterator incrementor
     */
    assertTrue((nullIt++).dataPtr == NULL,__LINE__);
    assertTrue((++nullIt).dataPtr == NULL,__LINE__);
    
    array<int> incrementorTestArray;
    incrementorTestArray.buffer = new int[5];
    incrementorTestArray.buffer[0] = 1;
    incrementorTestArray.buffer[1] = -456;
    incrementorTestArray.buffer[2] = 2;
    incrementorTestArray.buffer[3] = 15;
    incrementorTestArray.buffer[4] = -3;
    //setting to the beginning of buffer
    array<int>::iterator fakeBeginIt = array<int>::iterator();
    fakeBeginIt.dataPtr = incrementorTestArray.buffer;
    
    assertTrue((fakeBeginIt++).dataPtr == incrementorTestArray.buffer,__LINE__);
    //reset
    fakeBeginIt.dataPtr = incrementorTestArray.buffer;
    assertTrue((++fakeBeginIt).dataPtr == incrementorTestArray.buffer+1,__LINE__);

    
    /*
     * Testing Array begin And end Methods
     */
    startTestSet("Array Begin and End");
    array<int> emptyArray;
    emptyArray.buffer = NULL;
    
    assertTrue(emptyArray.begin().dataPtr == NULL,__LINE__);
    assertTrue(emptyArray.end().dataPtr == NULL,__LINE__);
    
    
    array<int> beginEndTestArray;
    beginEndTestArray.numCapacity = 5;
    beginEndTestArray.buffer = new int[beginEndTestArray.numCapacity];
    beginEndTestArray.buffer[0] = 1;
    beginEndTestArray.buffer[1] = -456;
    beginEndTestArray.buffer[2] = 2;
    beginEndTestArray.buffer[3] = 15;
    beginEndTestArray.buffer[4] = -3;
    
    assertTrue(beginEndTestArray.begin().dataPtr != NULL,__LINE__);
    assertTrue(beginEndTestArray.begin().dataPtr == beginEndTestArray.buffer,__LINE__);
    assertTrue(beginEndTestArray.end().dataPtr == beginEndTestArray.buffer+5,__LINE__);
    
    
    /*
     * Testing assignment operator for Non-Integer Array Behavior (Just to Make Sure array Works For Other Types)
     */
    startTestSet("Can Hold Strings");
    array<std::string> sString(3);
    
    sString[0]="Hello";
    sString[1]="It's me";
    sString[2]="I was wondering";
    assertTrue(sString.buffer[0].compare("Hello") == 0,__LINE__);
    assertTrue(sString.buffer[1].compare("It's me") == 0,__LINE__);
    assertTrue(sString.buffer[2].compare("I was wondering") == 0,__LINE__);
    //resetting counter
    unit_testing_delete_call_counter = 0;
    array<std::string>* stringArrayToDestroy = new array<std::string>(4);
    stringArrayToDestroy->buffer[0] = *new std::string("bob");
    stringArrayToDestroy->buffer[1] = *new std::string("sue");
    stringArrayToDestroy->buffer[2] = *new std::string("sven");
    stringArrayToDestroy->buffer[3] = *new std::string("jessie");
    delete stringArrayToDestroy;
    
    assertTrue(unit_testing_delete_call_counter == 2,__LINE__);
    
    generateTestingReport();
    return 0;
}



/* This program deomonstrates pointers and arrays.

   Written by: Li Liang
   Date: 09/29/2009

   Sources: None
*/

//memory leak detection tool headers
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>                 
#include <cctype>

#include "AddressEntry.h"
#include "InputTools.h"

using namespace std;     

void arrayAndPointer();

void morePointers();
void populateArray(AddressEntry ** list, int size);
void printArray(AddressEntry ** list, int size);
void releaseArray(AddressEntry ** list, int size);

void arrayOfArrays();

int main()
{
	//enable memory leak detection tools
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	arrayAndPointer();
	morePointers();
	arrayOfArrays();
}

/* This function explores the [] operator and pointer arithmetic with array.
*/
void arrayAndPointer()
{
	//intArray is a const pointer to the first element of the intArray
	int intArray[3];

	//dereference the intArray gets you to the first element of the intArray
	*intArray = 1;

	//the familiar subscript operator []
	intArray[1] = 2;

	//using pointer arithmetic. The following is the same as intArray[2]
	*(intArray+2) = 3;

	//display the contents of the array
	int index;
	int size = sizeof(intArray)/sizeof(int);
	for(index=0; index<size; index++)
		cout << "intArray[" << index << "] = " << intArray[index] << endl;
}
	

/* This function tests an array of pointers to AddressEntry.
*/
void morePointers()
{
	//individual element of the array happens to be a pointer
	AddressEntry ** arrayOfPointers;	
	int size = readInt("Please enter the preferred size for the AddressEntry array: ");
    arrayOfPointers = new AddressEntry*[size];

	populateArray(arrayOfPointers, size);
	printArray(arrayOfPointers, size);
	releaseArray(arrayOfPointers, size);

	delete [] arrayOfPointers;
}

/* This function populates the passed in array.
   list: out
*/
void populateArray(AddressEntry ** list, int size)
{
	int index;
	for(index=0; index<size; index++)
	{
		//you can populate it with real data here
		//by using the other constructor of AddressEntry
		list[index] = new AddressEntry;
	}
}

/* This function prints the AddressEntry to the stdout.
   list: in
*/
void printArray(AddressEntry ** list, int size)
{
	int index;
	for(index=0; index<size; index++)
	{
		list[index]->print();
	}
}

/* This function deallocates the memory for the AddressEntries.
   list: in/out
*/
void releaseArray(AddressEntry ** list, int size)
{
	int index;
	for(index=0; index<size; index++)
	{
		delete list[index];
	}
}

/* This function uses an array of int arrays.
*/
void arrayOfArrays()
{
	int **	intTable;
	int		rows, cols;
	int		curRow, curCol;
	int		counter = 1;

	rows = readInt("Please enter the preferred number of rows for the int table: ");
	cols = readInt("Please enter the preferred number of cols for the int table: ");

	//allocate the rows
	intTable = new int*[rows];	

	//allocate the cols
	for(curRow=0; curRow<rows; curRow++)
		intTable[curRow] = new int[cols];

	//populate the table
	for(curRow=0; curRow<rows; curRow++)
		for(curCol=0; curCol<cols; curCol++)
			intTable[curRow][curCol] = counter++;

	//display the table
	for(curRow=0; curRow<rows; curRow++)
	{
		for(curCol=0; curCol<cols; curCol++)
		{
			cout << intTable[curRow][curCol] << '\t';
			if (curCol == cols-1)
				cout << endl;
		}
	}

	//release the memory
	for(curRow=0; curRow<rows; curRow++)
		delete [] intTable[curRow];

	delete [] intTable;
}
	
#include "MemoryReferenceTable.h"
#include <iostream>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <stdbool.h>
#include<fstream>
#include<vector>
#include<algorithm>
#include<iomanip>

#define NUMBER_OF_BLOCKS(memorySize, blockSize)(memorySize/blockSize)


void MemoryReferenceTable::setTageNum(int blockSize, int cacheSets)
{
	tagNum=memoryRef/(blockSize*cacheSets);     //sets tagNum
}

void MemoryReferenceTable::set(char op,int ref, int mmNum, int cacheSet, string cacheBlock,  string stat)
{
	operation=op;
	memoryRef=ref;
	MMBlockNum=mmNum;
	cacheSetNum=cacheSet;
	cacheBlockNum=cacheBlock;
	status=stat;
}
void MemoryReferenceTable::setStatus(string stat)
{
	status=stat;         //set status
}

void MemoryReferenceTable::setOperation(char op)
{
	operation=op;         //sets operation
}

void MemoryReferenceTable::setMemoryRef(int ref)
{
	memoryRef=ref;      //sets memory adrress
}

char MemoryReferenceTable::getOperation()
{
	return operation;   // returns operation
}

int MemoryReferenceTable::getBlockNum()
{
	return MMBlockNum;  //returns main memory block
}

int MemoryReferenceTable::getCacheSetNum()
{
	return  cacheSetNum;  //returns cache set number
}

int MemoryReferenceTable::getTagNum()
{
	return tagNum;      //returns tag number
}

int MemoryReferenceTable::getmemoryRef()
{
	return memoryRef;    //returns memory address
}

string MemoryReferenceTable::getStatus()
{
	return status;      //returns status
}
/*	void get()
{
	cout<<operation<<" "<<memoryRef<<" "<<MMBlockNum<<" "<<cacheSetNum<<" "<<tagNum<<" "<<cacheBlockNum<<" "<<status<<endl;
}*/

/************************************************************
* Name: update()
* Inputs: int blockSize, int totalCacheSets, int degree(set-
		  associativity)
* Return values: none.
* Function: Updates the main block number, cache set number,
			cache block number for the particular memory address.
*************************************************************/	
void MemoryReferenceTable::update(int blocksize, int totalCacheSets, int degree)
{
	MMBlockNum=NUMBER_OF_BLOCKS(memoryRef,blocksize);
	cacheSetNum=MMBlockNum%totalCacheSets;
	if(degree==1)
		cacheBlockNum=to_string(cacheSetNum);
	else
	{
		int minBlockNum=cacheSetNum*degree;
		int maxBlockNum=minBlockNum+degree-1;
		cacheBlockNum=to_string(minBlockNum)+"-"+ to_string(maxBlockNum);
	}
}
void MemoryReferenceTable::updateStatus(string stat)
{
	status=stat;      //updates status 
}

/************************************************************
* Name: printMemoryReferenceTableContent()
* Inputs: none.
* Return values: none.
* Function: prints the memory refrence contents.
*************************************************************/	
void MemoryReferenceTable::printMemoryReferenceTableContent()
{
	cout << left << setw(25) << setfill(' ') <<memoryRef;
	cout << left << setw(25) << setfill(' ') << MMBlockNum;
	cout << left << setw(25) << setfill(' ') << cacheSetNum;
	cout << left << setw(25) << setfill(' ') << cacheBlockNum;
	cout << left << setw(25) << setfill(' ') << status;
	cout<<endl;
}	
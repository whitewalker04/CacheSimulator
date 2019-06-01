#ifndef MEMORYREFERENCETABLE_H
#define MEMORYREFERENCETABLE_H

#include<string>

using namespace std;


/*************************************************************
 * Name: MemoryReferenceTable
 * Members: char operation(R/W), int memoryRef(address of memory),
			int MMBlockNum(main memory block Number), int cacheSetNum
			(cache set number), int tagNum(tagNumber), string 
			cacheBlockNum(blocks range), string status(HIT/MISS).
 * Function: 
 *************************************************************/
class MemoryReferenceTable
{
	char operation;
	int memoryRef;
	int MMBlockNum;
	int cacheSetNum;
	int tagNum;
	string cacheBlockNum;
	string status=" ";
	public:
	void setTageNum(int blockSize, int cacheSets);
	
	void set(char op,int ref, int mmNum, int cacheSet, string cacheBlock,  string stat);
	
	void setStatus(string stat);
	
	void setOperation(char op);
	
	void setMemoryRef(int ref);
	
	char getOperation();
	
	int getBlockNum();
	
	int getCacheSetNum();
	
	int getTagNum();
	
	int getmemoryRef();
	
	string getStatus();
	
	void update(int blocksize, int totalCacheSets, int degree);
	
	void updateStatus(string stat);
	
	void printMemoryReferenceTableContent();
	
};
#endif
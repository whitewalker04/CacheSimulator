#ifndef CACHESTATUS_H
#define CACHESTATUS_H

#include<string>

using namespace std;

/*************************************************************
 * Name: CacheStatus
 * Members: int numCacheBlock(value for cacheBlock), char dityBit
            (for dityBit), int validBit, string tagNumber(tag),
			string data.
			(value for main memory block), vector<TrackBlock>
			TrackBlockVector(adds up new entry if the cache set
			has empty blocks). 
 * Function: It updates the cache status if the cache set for the
			 corressponding block is full based on policy. It also
			 calls contructors and intialize the default values for
			 the data members.
 *************************************************************/
class CacheStatus
{   
	int numCacheBlock;
	char dirtyBit;
	int validBit;
    string tagNumber;
    string data;
	public:
	CacheStatus(string tag, int index);
	
	void getStatus();
	
	void setTagNumber(string tag);
	
	void setDirtyBit(char op);
	
	void update(char dirty, int valid, string tag, int mBlock, int replaced);
	
	void printCacheContent();

};

#endif
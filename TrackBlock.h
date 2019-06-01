#ifndef TRACKBLOCK_H
#define TRACKBLOCK_H
#include <vector>

using namespace std;

/*************************************************************
 * Name: TrackBlock
 * Members: int cacheBlockNum(value for cacheBlock), int bb
			(value for main memory block), vector<TrackBlock>
			TrackBlockVector(adds up new entry if the cache set
			has empty blocks). 
 * Function: It keeps tracks on cache memory block and main 
			 memory block inside the cache set. It caclulates
			 the new cache block number for the incoming main
			 memory block based on the cache set number and
			 policy.
 *************************************************************/
 
 class TrackBlock
{
	int cacheBlockNum;
	int bb;
	vector<TrackBlock>TrackBlockVector;
	public:
	/************************************************************
	* Name: set()
	* Inputs: int cache(cache number), int bNum(block number).
	* Return values: none
	* Function: Sets up the data members values.
	*************************************************************/
	void set(int cache, int bNum);
	int getCacheBlockNum();
	int getBlockNum();
	int empty();
	int found(int blockNum);
	int getBlockNum(int b,int cSet, int degree, char p, int *replaced);
	void updateTracker(int exist);
	void get();
	void getVectorDetails();
};

#endif
#include "TrackBlock.h"
#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <stdbool.h>
#include<fstream>
#include<algorithm>
#include<iomanip>




/************************************************************
* Name: set()
* Inputs: int cache(cache number), int bNum(block number).
* Return values: none
* Function: Sets up the data members values.
*************************************************************/

void TrackBlock::set(int cache, int bNum)
{
	cacheBlockNum=cache;
	bb=bNum;
}
int TrackBlock::getCacheBlockNum()
{
	return cacheBlockNum;   //returns the cacheBlockNum
}
int TrackBlock::getBlockNum()
{
	return bb;             //returns the block number 
}
/************************************************************
* Name: empty()
* Inputs: none.
* Return values: 0 or 1
* Function: Checks if the TrackBlockVector is empty or not.
*************************************************************/
int TrackBlock::empty()
{
	if(TrackBlockVector.empty())
		return 1;
	else
		return 0;
}
/************************************************************
* Name: found()
* Inputs: int blockNum(block number of incoming block).
* Return values: i(blockNumber) or -1.
* Function: Checks if the block number found in cache set.
			If found returns the cache block number for the
			main memory block otherwise returns -1.
*************************************************************/
int TrackBlock::found(int blockNum)
{
	if(!empty())
	{
		for(int i=0;i<TrackBlockVector.size();i++)
		{
			if(TrackBlockVector[i].getBlockNum()==blockNum)
			{
				return i;
			}
		}
	}
	return -1;
}
/************************************************************
* Name: getBlockNum()
* Inputs: int b(block number of incoming block), uint cSet(
				cache set num for that block), int degree(
				set associativity degree), char p(policy), int 
				*replaced(address of int variable replaced).
* Return values: 
* Function: Checks if the block number found in cache set.
			If found returns the cache block number for the
			main memory block otherwise returns -1.
*************************************************************/
int TrackBlock::getBlockNum(int b,int cSet, int degree, char p, int *replaced)
{
	int none=empty();
	int exist;
	int allocNum;
	string stat;
	*replaced=0;
	TrackBlock add;
	if(none)
	{
		this->cacheBlockNum=cSet*degree+0;
		add.set(this->cacheBlockNum, b);
		TrackBlockVector.push_back(add);
		stat="MISS";
		allocNum=this->cacheBlockNum;
		return allocNum;
	}
	exist=found(b);
	if(exist!=-1)
	{
		stat="HIT";
		if(TrackBlockVector.size()<=degree)
		{
			this->cacheBlockNum=TrackBlockVector[0].getCacheBlockNum();
			if(p=='L')
				updateTracker(exist);
		}
		allocNum=this->cacheBlockNum;
	}
	else
	{	
		 if(TrackBlockVector.size()<degree)
		{
			this->cacheBlockNum=(cSet*degree)+TrackBlockVector.size();
			add.set(this->cacheBlockNum, b);
			TrackBlockVector.push_back(add);
			
		}
		else
		{
			this->cacheBlockNum=TrackBlockVector[0].getCacheBlockNum();
			TrackBlockVector.erase(TrackBlockVector.begin()+0);
			add.set(this->cacheBlockNum, b);
			TrackBlockVector.push_back(add);
			*replaced=1;
			
		}
	}
	allocNum=this->cacheBlockNum;
	return allocNum;
}
/************************************************************
* Name: updateTracker()
* Inputs: int exist(position at which main memory exist in cache 
		  set).
* Return values: none.
* Function: Restores the TrackBlock object and remove it from 
			previous position. It then pushes the restored object
			to the end.
*************************************************************/
void TrackBlock::updateTracker(int exist)
{
	TrackBlock add=TrackBlockVector[exist];
	TrackBlockVector.erase(TrackBlockVector.begin()+exist);
	TrackBlockVector.push_back(add);
}
void TrackBlock::get()
{
	cout<<bb<<" "<<cacheBlockNum<<endl;     //printing values
}
void TrackBlock::getVectorDetails()
{
	for(int i=0;i<TrackBlockVector.size();i++)
	{
		cout << "Vector"<<i<<" ";
		TrackBlockVector[i].get();
	}
}


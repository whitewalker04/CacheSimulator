/******************************************************
 * NAME: Raghav R Agarwal
 * CWID: 11770535
 * ECE 587 LAB 7 (Cache Memory Simulator)
 * Date: April, 17, 2019
 ******************************************************/
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
#include <stdbool.h>
#include<fstream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include "TrackBlock.h"
#include "MemoryReferenceTable.h"
#include "CacheStatus.h"
#include "HelperFunctions.h"

using namespace std;

#define ERROR -1
#define NUMBER_OF_BLOCKS(memorySize, blockSize)(memorySize/blockSize)

int main(int argc, char *argv[] )
{
	int sizeMM, sizeCM, sizeBlock, setDegree, numOffBits, numCacheBits, numAddrLines, numMMBlocks, numCMBlocks, numIndexBits, numTagBits, totalCacheSize, totalNumOfMemRef, 
	numTotalCacheSets, countRepeats,countHits,isReplaced;
	char replacementPolicy;
	string filename;
	MemoryReferenceTable *mref;
	TrackBlock *bref;
	string tag;
	char ch;
	CacheStatus **cref;
	do
	{
		printf("Press 'q' at any time to quit at any input prompt \n");
		//calling all validation functions and validating inputs
		validate(&sizeMM,4,32768, &numAddrLines,"size of main memory in bytes", 32768);
		validate(&sizeCM,2,32768,&numCacheBits,"size of the cache in bytes",sizeMM);
		validate(&sizeBlock,2,32768,&numOffBits,"cache block/lines size",sizeCM);
		numCMBlocks=NUMBER_OF_BLOCKS(sizeCM,sizeBlock);
		validateAssociativeDegree(&setDegree,numCMBlocks);	
		validate(&replacementPolicy);
		
		mref=validateFile(&totalNumOfMemRef, sizeMM);
		
		numMMBlocks=NUMBER_OF_BLOCKS(sizeMM,sizeBlock);                   //calculating number of blocks
		numTotalCacheSets=numCMBlocks/setDegree;                          //calculating total number of cache sets
		numIndexBits=numberOfBits(numCMBlocks/setDegree);                 //calculating totalNumber of Index bits
		numTagBits=numAddrLines-(numOffBits+numIndexBits);                //calculating total number of tag bits.
		totalCacheSize=calCacheSize(sizeBlock,numCMBlocks, numTagBits);   //calculating total cache size
		bref=new TrackBlock[numTotalCacheSets];                           //creating TrackBlock instances. Num of instances =possible cache sets.
		for(int i=0;i<totalNumOfMemRef;i++)
		{
			mref[i].update(sizeBlock,numTotalCacheSets,setDegree);        //updating memory reference entry
			mref[i].setTageNum(sizeBlock,numTotalCacheSets);              //setting tag for the memory reference.
		}

		tag=initializeTag(numTagBits);                                    //to get the tag for initializing.
		cout<<"Simulator output :"<<endl;
		cout<<"Total number of address lines required = "<<numAddrLines<<endl;
		cout<<"Number of bits for offset = "<<numOffBits<<endl;
		cout<<"Number of bits for index = "<<numIndexBits<<endl;
		cout<<"Number of bits for tag = "<<numTagBits<<endl;
		cout<<"Total cache size required = "<<totalCacheSize<<" bytes"<<endl<<endl;

		cref=new CacheStatus*[numCMBlocks];                                //creating CacheStatus instances. Num of instances= memory references entries.
		for(int i=0;i<numCMBlocks;i++)
		{
			cref[i]=new CacheStatus(tag,i);
		}
		for(int i=0;i<totalNumOfMemRef;i++)
		{
			int blockNum=mref[i].getBlockNum();                            //getting block number
			int cacheSetNum=mref[i].getCacheSetNum();                      //getting cache set number
			int tagNumBinary=convert(mref[i].getTagNum());                 //getting tag
			int memoryRef=mref[i].getmemoryRef();                          //getting memory reference
			char op=mref[i].getOperation();                                //converting tag to string
			string tag=to_string(tagNumBinary);                            //converting tag string of length equal to the number of tag bits.
			tag=tagInString(numTagBits,tag);
			int exist=bref[cacheSetNum].found(blockNum);
			string stat=computeMissOrHit(exist);
			mref[i].updateStatus(stat);
			int cacheBlockNumber=bref[cacheSetNum].getBlockNum(blockNum,cacheSetNum,setDegree,replacementPolicy,&isReplaced);
			cref[cacheBlockNumber]->update(op,1,tag,blockNum,isReplaced);
		}
		printMemoryReferenceTableHeader();
		for(int i=0;i<totalNumOfMemRef;i++)
			mref[i].printMemoryReferenceTableContent();
		cout<<endl;
		countRepeats=computeNumberOfRepeats(mref,totalNumOfMemRef);
		float percentage =((float)(countRepeats*100))/totalNumOfMemRef;
		cout<<fixed<<setprecision(2)<<"Highest Possible Hit Rate= "<<countRepeats<<"/"<<totalNumOfMemRef<<" = "<<percentage<<"%"<<endl;
		cout<<endl;
		countHits=computeNumberOfHits(mref,totalNumOfMemRef);
		percentage =((float)(countHits*100))/totalNumOfMemRef;
		cout<<fixed<<setprecision(2)<<"Actual Hit Rate= "<<countHits<<"/"<<totalNumOfMemRef<<" = "<<percentage<<"%"<<endl;
		cout<<endl;
		printCacheStatusHeader();
		for(int i=0;i<numCMBlocks;i++)
			cref[i]->printCacheContent();
		validateChoice(&ch);
	} while (ch!='n') ;
	return 0;
}
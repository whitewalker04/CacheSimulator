#include "CacheStatus.h"
#include <iostream>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <stdbool.h>
#include<fstream>
#include<vector>
#include<algorithm>
#include<iomanip>



CacheStatus::CacheStatus(string tag, int index)
{
	numCacheBlock=index;
	dirtyBit='X';
	validBit=0;
	tagNumber=tag;
	data="X";	
}

void CacheStatus::getStatus()
{
	cout<<numCacheBlock<<" "<<dirtyBit<<" "<<validBit<<" "<<tagNumber<<" "<< " "<<data<<endl;
}

void CacheStatus::setTagNumber(string tag)
{
	tagNumber=tag;
}

void CacheStatus::setDirtyBit(char op)
{
	if(op=='W')
		dirtyBit='1';
	if(op=='R')
		dirtyBit='0';
}

void CacheStatus::update(char dirty, int valid, string tag, int mBlock, int replaced)
{
	if(replaced)
		setDirtyBit(dirty);
	else
	{
		if(dirtyBit!='1')
			setDirtyBit(dirty);
	}
	validBit=valid;
	tagNumber=tag;
	data="Main Memory Block #"+to_string(mBlock);
}

void CacheStatus::printCacheContent()
{
	cout << left << setw(25) << setfill(' ') <<numCacheBlock;
	cout << left << setw(25) << setfill(' ') << dirtyBit;
	cout << left << setw(25) << setfill(' ') << validBit;
	cout << left << setw(25) << setfill(' ') << tagNumber;
	cout << left << setw(25) << setfill(' ') << data;
	cout<<endl;
}

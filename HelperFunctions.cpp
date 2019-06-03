#include "HelperFunctions.h"
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <stdbool.h>
#include<fstream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include "TrackBlock.h"
#include "CacheStatus.h"

using namespace std;

#define ERROR -1

/************** USER FUNCTIONS ******************************
*************************************************************/

/************************************************************
* Name: numberOfBits()
* Inputs: int n(any number)
* Return values: bits(integer) or -1.
* Function: It checks if the number is in power of 2.
*************************************************************/
int numberOfBits(int n) 
{  
	int bits=ERROR;
	if(ceil(log2(n)) == floor(log2(n)))
	   bits=ceil(log2(n));
	return bits;
} 
/************************************************************
* Name: calCacheSize()
* Inputs: int size(cacjhe size), int block(number of blocks),
		  int tagBits(number of tag bits).
* Return values: memory(integer).
* Function: It returns the cache memory size based on the inputs.
*************************************************************/
int calCacheSize(int size, int block, int tagBits)
{
	int memory;
	memory= 2*(block/8) + ((tagBits*block)/8) + size *block;
	return memory;
}
/************************************************************
* Name: checkCharacters()
* Inputs: char ch(any character).
* Return values: 0 or -1.
* Function: It checks if the character is in between [0-9] or
			' ' or '\n'. If not returns -1 else 0.
*************************************************************/
int checkCharacters(char ch)
{
	int error=ERROR;
	if(ch==' '|| ch =='\n'|| ch=='\r'||(ch>=48 && ch<=57))
	{
		error=0;
	}
	return error;
}
/************************************************************
* Name: tagInString()
* Inputs: int tagBits(number of tagBits), string tag()
* Return values: add(string).
* Function: It adds 0's to 'tag' if the numbe of tagBits is
			less than length of tag.
*************************************************************/
string tagInString(int tagBits, string tag)
{
	string add="";
	if(tagBits==0)
		return add="NO TAG";
	if(tag.length()<tagBits)
	{
		int diff=tagBits-tag.length();
		for(int i=0;i<diff;i++)
		{
			add=add+"0";
		}
		add=add+tag;
	}
	else
		add=tag;
	return add;
}
/************************************************************
* Name: convert()
* Inputs: int dec(decimal number).
* Return values: binary value as int.
* Function: Converts the decimal into binary form.
*************************************************************/
int convert(int dec)
{
    if (dec == 0)
    {
        return 0;
    }
    else
    {
        return (dec % 2 + 10 * convert(dec / 2));
    }
}

char *initializeTag(int tagBits)
{
	char *s;
	int i;
	s=(char *)malloc((tagBits)*sizeof(char));
	for(i=0;i<tagBits;i++)
	{
		s[i]='X';
	}
	s[i]='\0';
	return s;
}
/************************************************************
* Name: printMemoryReferenceTableHeader()
* Inputs: none.
* Return values: none.
* Function: prints the header for the Memory Reference table.
*************************************************************/
void printMemoryReferenceTableHeader()
{
	cout << left << setw(25) << setfill(' ') << "Main Meory Address";
	cout << left << setw(25) << setfill(' ') << "MM Block #";
	cout << left << setw(25) << setfill(' ') << "CM Set #";
	cout << left << setw(25) << setfill(' ') << "CM Block #";
	cout << left << setw(25) << setfill(' ') << "HIT/MISS";
	cout<<endl;
	cout<<left<<setw(130)<<setfill('_')<<" ";
	cout<<endl;
}
/************************************************************
* Name: printCacheStatusHeader()
* Inputs: none.
* Return values: none.
* Function: prints the header for the cache status.
*************************************************************/
void printCacheStatusHeader()
{
	cout << left << setw(25) << setfill(' ') << "Cache Block #";
	cout << left << setw(25) << setfill(' ') << "Dirty Bit";
	cout << left << setw(25) << setfill(' ') << "Valid Bit";
	cout << left << setw(25) << setfill(' ') << "Tag";
	cout << left << setw(25) << setfill(' ') << "Data";
	cout<<endl;
	cout<<left<<setw(130)<<setfill('_')<<" ";
	cout<<endl;
}
/************************************************************
* Name: computeMissOrHit()
* Inputs: int found(index at which the )
* Return values: none.
* Function: validates the inputs for the main memory, cache ,
			memory and cache block size. If valid sets the 
			number of bits to the *numBits.
*************************************************************/
string computeMissOrHit(int found)
{
	string stat;
	if(found!=-1)
		stat="HIT";
	else
		stat="MISS";
	return stat;
}
/************************************************************
* Name: computeNumberOfRepeats()
* Inputs: MemoryReferenceTable *mref(memory refrences objects),
          int len(number of references).
* Return values: count(int).
* Function: Counts the number of repeats of main memory block
			and returns the count.
*************************************************************/
int computeNumberOfRepeats(MemoryReferenceTable *mref, int len)
{
	int count=0;
	int blocks[len];
	for(int i=0;i<len;i++)
	{
		blocks[i]=mref[i].getBlockNum();
	}
	for (int i = 0; i < len; i++)            
	{
		for (int j = i+1; j < len; j++)           
		{
			if (blocks[j] > blocks[i])            
			{
				int tmp = blocks[i];         
				blocks[i] = blocks[j];            
				blocks[j] = tmp;            
			}  
		}
	}
	int a=0;
	while(len)
	{
		if(blocks[a]==blocks[a+1])
			count++;
		a++;
		len--;
	}
	return count;
}
/************************************************************
* Name: computeNumberOfHits()
* Inputs: MemoryReferenceTable *mref(memory refrences objects),
          int len(number of references).
* Return values: count(int).
* Function: Counts the number of HITs in the MemoryReference list.
			It returns the count.
*************************************************************/
int computeNumberOfHits(MemoryReferenceTable *mref, int len)
{
	int count=0;
	for(int i=0;i<len;i++)
	{
		if(mref[i].getStatus()=="HIT")
			count++;
	}
	return count;
}
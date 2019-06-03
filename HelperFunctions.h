#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H
#include "MemoryReferenceTable.h"
#include <string>

using namespace std;

/************** USER FUNCTIONS ******************************
*************************************************************/

/************************************************************
* Name: numberOfBits()
* Inputs: int n(any number)
* Return values: bits(integer) or -1.
* Function: It checks if the number is in power of 2.
*************************************************************/
int numberOfBits(int n);

/************************************************************
* Name: calCacheSize()
* Inputs: int size(cacjhe size), int block(number of blocks),
		  int tagBits(number of tag bits).
* Return values: memory(integer).
* Function: It returns the cache memory size based on the inputs.
*************************************************************/
int calCacheSize(int size, int block, int tagBits);

/************************************************************
* Name: checkCharacters()
* Inputs: char ch(any character).
* Return values: 0 or -1.
* Function: It checks if the character is in between [0-9] or
			' ' or '\n'. If not returns -1 else 0.
*************************************************************/
int checkCharacters(char ch);

/************************************************************
* Name: tagInString()
* Inputs: int tagBits(number of tagBits), string tag()
* Return values: add(string).
* Function: It adds 0's to 'tag' if the numbe of tagBits is
			less than length of tag.
*************************************************************/
string tagInString(int tagBits, string tag);

/************************************************************
* Name: convert()
* Inputs: int dec(decimal number).
* Return values: binary value as int.
* Function: Converts the decimal into binary form.
*************************************************************/
int convert(int dec);

/************************************************************
* Name: validateFile()
* Inputs: int *totalNumOfMemRef(address of totalNumOfMemRef), 
`		  int range(size of main memory).
* Return values: objects of type MemoryReferenceTable.
* Function: validates the entries in file. It checks if the memory
			addresse in the file are valid and within the size of 
			[0-main memory size]. It exits the program if user enters
			'q' and keep prompting to ask user to input the file untill
			the valid file is provided.
*************************************************************/
MemoryReferenceTable * validateFile(int  *totalNumOfMemRef, int range);

/************************************************************
* Name: validate()
* Inputs: int *input(address of int variable), int min(minimum
		   range i.e 2), int max(maximum range), int *numBits(
		   address for variable that stores number of bits),
		   string str(string to be displayed), int range(for
		   MM<=CM<=Block size).
* Return values: none.
* Function: validates the inputs for the main memory, cache ,
			memory and cache block size. If valid sets the 
			number of bits to the *numBits.
*************************************************************/
void validate(int *input, int min, int max, int *numBits, string str, int range);

/************************************************************
* Name: validateChoice()
* Inputs: char *ch(address of char variable).
* Return values: none.
* Function: validates the inputs for the choice(y or no). If valid sets the 
			value to the *ch. It exits the program if user enters "q".
*************************************************************/
void validateChoice(char *ch);

/************************************************************
* Name: validate()
* Inputs: char *policy(address of char variable).
* Return values: none.
* Function: validates the inputs for the policy(L or F). If valid sets the 
			value to the *policy. It exits the program if user enters "q".
*************************************************************/
void validate(char *policy);

/************************************************************
* Name: validateAssociativeDegree()
* Inputs: int *degree(address of int variable), int range()
* Return values: none.
* Function:validates the inputs for the degree. If valid sets the 
			value to the *degree. It exits the program if user enters "q".
*************************************************************/
void validateAssociativeDegree(int *degree, int range);

char *initializeTag(int tagBits);

/************************************************************
* Name: printMemoryReferenceTableHeader()
* Inputs: none.
* Return values: none.
* Function: prints the header for the Memory Reference table.
*************************************************************/
void printMemoryReferenceTableHeader();

/************************************************************
* Name: printCacheStatusHeader()
* Inputs: none.
* Return values: none.
* Function: prints the header for the cache status.
*************************************************************/
void printCacheStatusHeader();

/************************************************************
* Name: computeMissOrHit()
* Inputs: int found(index at which the )
* Return values: none.
* Function: validates the inputs for the main memory, cache ,
			memory and cache block size. If valid sets the 
			number of bits to the *numBits.
*************************************************************/
string computeMissOrHit(int found);

/************************************************************
* Name: computeNumberOfRepeats()
* Inputs: MemoryReferenceTable *mref(memory refrences objects),
          int len(number of references).
* Return values: count(int).
* Function: Counts the number of repeats of main memory block
			and returns the count.
*************************************************************/
int computeNumberOfRepeats(MemoryReferenceTable *mref, int len);

/************************************************************
* Name: computeNumberOfHits()
* Inputs: MemoryReferenceTable *mref(memory refrences objects),
          int len(number of references).
* Return values: count(int).
* Function: Counts the number of HITs in the MemoryReference list.
			It returns the count.
*************************************************************/
int computeNumberOfHits(MemoryReferenceTable *mref, int len);

#endif
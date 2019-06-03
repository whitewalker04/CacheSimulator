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
#include "Validation.h"
#include "HelperFunctions.h"

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
MemoryReferenceTable * validateFile(int  *totalNumOfMemRef, int range)
{   
	MemoryReferenceTable *mref;
    int error=ERROR;
	int entries=0;
	int ok=0;
	int numEntry, time, i;
    char filename[100];
	ifstream fp;
	char line[100];
	char *token;
	char op;
	do
	{
		time=0;
		i=0;
		entries=0;
		printf("Enter the file name :");
        scanf("%s", filename);
		//printf("%s", filename);
		if(strlen(filename)==1 && (strcmp(filename,"q")==0))
			exit(0);
		fp.open(filename);
		if(!fp)
		{
			error=ERROR;
			printf("Error>>>> Cannot open file.\n");
		}
		else
		{    
			error=0;
			//parseFile(&fp);
			while (fp.getline(line,50))
			{  
				time++;
				if(time==2)
					continue;
				//printf("%s\n", line);
				if(time==1)
				{
					*totalNumOfMemRef=atoi(line);
					if(*totalNumOfMemRef>0)
					{
						mref = new MemoryReferenceTable[*totalNumOfMemRef] ;
					}
					else
					{
						error=ERROR;
						printf("Error>>>> File does not contain valid number for total entries \n");
						break;
					}
				}
				else
				{
					error=0;
					entries++;
					token=strtok(line, " ");
					int in=2;
					while(token[in]!='\0')
					{
						error=checkCharacters(token[in]);
						if(error==ERROR)
						{
							printf("Error>>>> Memory reference addresses are not valid.\n");
							break;
						}
						in++;
					}
					//cout<<error<<endl;
					//cout<<token;
					if((strcmp(token,"R")==0 || strcmp(token,"W")==0) && error!=ERROR)
					{
						char op=token[0];
						mref[i].setOperation(op);
					}
					else
					{
						printf("Error>>>> File does not contain valid opaeration R/W\n");
						error=ERROR;
						break;
					}
					while(token!=NULL)
					{ 	
						token=strtok(NULL," ");
						if(token==NULL)
							break;
						if(token[0]=='0' && strlen(token)==2)
							ok=1;
						int n=atoi(token);
						if((n>0 || ok==1) && n<range)
						{
							mref[i].setMemoryRef(n);
							ok=0;
						}
					    else
						{
							error=ERROR;
							printf("Error>>>>File memory references are invalid values\n");
						}
						if(entries>*totalNumOfMemRef)
						{
							error=ERROR;
							printf("Error>>>> File contains more entries than specified length.\n");
						}
					}
					i++;
					if(error==ERROR)
						break;
				}
			}
		}
		fp.close();
    }while(error==ERROR);
	return mref;
}
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
void validate(int *input, int min, int max, int *numBits, string str, int range)
{
	int error=ERROR; 
	char *ch;
	do
	{
		printf("Enter the  %s : ", str.c_str());
		scanf("%s",ch);
		if(strlen(ch)==1 and (strcmp(ch,"q")==0))
			exit(0);
		*input=atoi(ch);
		if(*input>=min && *input<=max && *input<=range)
		{
			*numBits=numberOfBits(*input);
			if(*numBits!=ERROR)
				error=0;
			else
				printf("Error>>>> input should be in power of 2.\n");
		}
		else
		{
			printf("Error>>>>  Out of range exception. Enter number between %d-%d. Also MM <= CM<= BlockSize.\n ", min, max);
			error=ERROR;
		}
	}while(error==ERROR);
}
/************************************************************
* Name: validateChoice()
* Inputs: char *ch(address of char variable).
* Return values: none.
* Function: validates the inputs for the choice(y or no). If valid sets the 
			value to the *ch. It exits the program if user enters "q".
*************************************************************/
void validateChoice(char *ch)
{
	int error;
	char input[20];
	do
	{
		error=ERROR;
		cout<<"Continue? (y=yes, n=no) :";
		scanf("%s",input);
		if(strlen(input)==1 and (strcmp(input,"q")==0))
			exit(0);
		if(strlen(input)==1 && (strcmp(input,"y")==0) || (strcmp(input,"n")==0))
		{
			error=0;
			*ch=input[0];
		}
	} while(error==ERROR);
}
/************************************************************
* Name: validate()
* Inputs: char *policy(address of char variable).
* Return values: none.
* Function: validates the inputs for the policy(L or F). If valid sets the 
			value to the *policy. It exits the program if user enters "q".
*************************************************************/
void validate(char *policy)
{
	char input[20];
	int error=ERROR;
	do
	{
		printf("Enter replacement policy(Least recently Used[LRU=L], First In First Out[FIFO=F]) : ");
		fflush(NULL);
		scanf("%s",input);
		if(strlen(input)==1 and (strcmp(input,"q")==0))
			exit(0);
		if(strlen(input)==1 && (strcmp(input,"L")==0) || (strcmp(input,"F")==0))
		{
			error=0;
			*policy=input[0];
		}
		else
		{
			cout<<"Enter valid character (L/F)"<<endl;
		}
		
	}while(error==ERROR);	
}
/************************************************************
* Name: validateAssociativeDegree()
* Inputs: int *degree(address of int variable), int range()
* Return values: none.
* Function:validates the inputs for the degree. If valid sets the 
			value to the *degree. It exits the program if user enters "q".
*************************************************************/
void validateAssociativeDegree(int *degree, int range)
{
	int error=ERROR;
	char input[20];
	int deg;
	do
	{
		printf("Enter degree of set-associativity(input n for an n-way set-associative mapping) : ");
		scanf("%s",input);
		if(strlen(input)==1 and (strcmp(input,"q")==0))
			exit(0);
		deg=atoi(input);
		if(deg>0 && deg<=range)
		{
			if(numberOfBits(deg)!=ERROR)
			{
				error=0;
		   		*degree=deg;
			}
			else
			{
				error=ERROR;
				cout<<"Error>>>> Associativity not in power in 2."<<endl;
			}
		}
		else
		{
			cout<<"Error>>>> Associativity range error. It must be in range of [1-numberofCacheBlocks] i.e. [1-"<<range<<"]."<<endl;
			error=ERROR;
		}
	}while(error==ERROR);
}

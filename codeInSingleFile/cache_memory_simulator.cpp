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

using namespace std;

#define ERROR -1
#define NUMBER_OF_BLOCKS(memorySize, blockSize)(memorySize/blockSize)
/********************** CLASSES SECTION ******************************
**********************************************************************/

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
	void set(int cache, int bNum)
	{
		cacheBlockNum=cache;
		bb=bNum;
	}
	int getCacheBlockNum()
	{
		return cacheBlockNum;   //returns the cacheBlockNum
	}
	int getBlockNum()
	{
		return bb;             //returns the block number 
	}
	/************************************************************
	* Name: empty()
	* Inputs: none.
	* Return values: 0 or 1
	* Function: Checks if the TrackBlockVector is empty or not.
	*************************************************************/
	int empty()
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
	int found(int blockNum)
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
	int getBlockNum(int b,int cSet, int degree, char p, int *replaced)
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
	void updateTracker(int exist)
	{
		TrackBlock add=TrackBlockVector[exist];
		TrackBlockVector.erase(TrackBlockVector.begin()+exist);
		TrackBlockVector.push_back(add);
	}
	void get()
	{
		cout<<bb<<" "<<cacheBlockNum<<endl;     //printing values
	}
	void getVectorDetails()
	{
		for(int i=0;i<TrackBlockVector.size();i++)
		{
			cout << "Vector"<<i<<" ";
			TrackBlockVector[i].get();
		}
	}
	
};

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
	void setTageNum(int blockSize, int cacheSets)
	{
		tagNum=memoryRef/(blockSize*cacheSets);     //sets tagNum
	}
	void set(char op,int ref, int mmNum, int cacheSet, string cacheBlock,  string stat)
	{
		operation=op;
		memoryRef=ref;
		MMBlockNum=mmNum;
		cacheSetNum=cacheSet;
		cacheBlockNum=cacheBlock;
		status=stat;
	}
	void setStatus(string stat)
	{
		status=stat;         //set status
	}
	void setOperation(char op)
	{
		operation=op;         //sets operation
	}
	
	void setMemoryRef(int ref)
	{
		memoryRef=ref;      //sets memory adrress
	}
	char getOperation()
	{
		return operation;   // returns operation
	}
	int getBlockNum()
	{
		return MMBlockNum;  //returns main memory block
	}
	int getCacheSetNum()
	{
		return  cacheSetNum;  //returns cache set number
	}
	int getTagNum()
	{
		return tagNum;      //returns tag number
	}
	int getmemoryRef()
	{
		return memoryRef;    //returns memory address
	}
	string getStatus()
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
	void update(int blocksize, int totalCacheSets, int degree)
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
	void updateStatus(string stat)
	{
		status=stat;      //updates status 
	}

	/************************************************************
	* Name: printMemoryReferenceTableContent()
	* Inputs: none.
	* Return values: none.
	* Function: prints the memory refrence contents.
	*************************************************************/	
	void printMemoryReferenceTableContent()
	{
		cout << left << setw(25) << setfill(' ') <<memoryRef;
		cout << left << setw(25) << setfill(' ') << MMBlockNum;
		cout << left << setw(25) << setfill(' ') << cacheSetNum;
		cout << left << setw(25) << setfill(' ') << cacheBlockNum;
		cout << left << setw(25) << setfill(' ') << status;
		cout<<endl;
	}
};
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
	CacheStatus(string tag, int index)
	{
		numCacheBlock=index;
		dirtyBit='X';
		validBit=0;
		tagNumber=tag;
		data="X";	
	}
	void getStatus()
	{
		cout<<numCacheBlock<<" "<<dirtyBit<<" "<<validBit<<" "<<tagNumber<<" "<< " "<<data<<endl;
	}
	void setTagNumber(string tag)
	{
		tagNumber=tag;
	}
	
	void setDirtyBit(char op)
	{
		if(op=='W')
			dirtyBit='1';
		if(op=='R')
			dirtyBit='0';
	}
	
	void update(char dirty, int valid, string tag, int mBlock, int replaced)
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
	
	void printCacheContent()
	{
		cout << left << setw(25) << setfill(' ') <<numCacheBlock;
		cout << left << setw(25) << setfill(' ') << dirtyBit;
		cout << left << setw(25) << setfill(' ') << validBit;
		cout << left << setw(25) << setfill(' ') << tagNumber;
		cout << left << setw(25) << setfill(' ') << data;
		cout<<endl;
	}

};
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
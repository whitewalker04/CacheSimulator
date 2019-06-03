TrackBlock.o : TrackBlock.h TrackBlock.cpp
	g++ -c TrackBlock.cpp

MemoryReferenceTable.o : MemoryReferenceTable.h MemoryReferenceTable.cpp
	g++ -c MemoryReferenceTable.cpp

CacheStatus.o : CacheStatus.h CacheStatus.cpp
	g++ -c CacheStatus.cpp

main.o : main.cpp
	g++ -c main.cpp
HelperFunctions.o : HelperFunctions.h HelperFunctions.cpp
	g++ -c HelperFunctions.cpp
Validation.o : Validation.h Validation.cpp
	g++ -c Validation.cpp

all : result

result : TrackBlock.o MemoryReferenceTable.o CacheStatus.o HelperFunctions.o Validation.o main.o
	g++ main.o TrackBlock.o MemoryReferenceTable.o CacheStatus.o HelperFunctions.o Validation.o -o res 

clean :
	rm -rf *o res

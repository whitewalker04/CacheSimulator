TrackBlock.o : TrackBlock.h TrackBlock.cpp
	g++ -c TrackBlock.cpp

MemoryReferenceTable.o : MemoryReferenceTable.h MemoryReferenceTable.cpp
	g++ -c MemoryReferenceTable.cpp

CacheStatus.o : CacheStatus.h CacheStatus.cpp
	g++ -c CacheStatus.cpp

main.o : main.cpp
	g++ -c main.cpp

all : result

result : TrackBlock.o MemoryReferenceTable.o CacheStatus.o main.o
	g++ main.o TrackBlock.o MemoryReferenceTable.o CacheStatus.o -o res 

clean :
	rm -rf *o res

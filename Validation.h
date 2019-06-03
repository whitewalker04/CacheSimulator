#ifndef VALIDATION_H
#define VALIDATION_H
#include "MemoryReferenceTable.h"

#define ERROR -1

MemoryReferenceTable * validateFile(int  *totalNumOfMemRef, int range);
void validate(int *input, int min, int max, int *numBits, string str, int range);
void validateChoice(char *ch);
void validate(char *policy);
void validateAssociativeDegree(int *degree, int range);

#endif
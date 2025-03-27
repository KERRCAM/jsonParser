// LIBRARY IMPORTS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//-----------------------------------------------------------------------------------------------//
//CONSTANTS

enum error {
    INVALID_NUMBER,
    NUMBER_NEVER_CLOSED,
    STRING_NEVER_CLOSED,
    ARRAY_NEVER_CLOSED,
    INVALID_OBJECT,
    INCOMPLETE_JSON,
    INVALID_JSON,
    INVALID_STRING
};

enum error crash;

//-----------------------------------------------------------------------------------------------//
//STRUCTS

typedef struct VALIDATOR_STRUCT{
    int i;
    char* rawJSON;
    char currChar;
    int lineCrash;
    int column;
} validatorS;

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

validatorS* initValidator(char* jsonContent);

char* loadJSON(char* filename);

char* loadJsonStaggered(char* filename, int lastRead);

void charAdvance(validatorS* validator);

void consumeWhiteSpace(validatorS* validator);

int consumeString(validatorS* validator);

int consumeInt(validatorS* validator);

int consumeNumber(validatorS* validator);

int consumeKeyword(validatorS* validator, int length);

int consumeValue(validatorS* validator);

int consumeObject(validatorS* validator);

int consumeArray(validatorS* validator);

int validateJSON(validatorS* validator);

//-----------------------------------------------------------------------------------------------//

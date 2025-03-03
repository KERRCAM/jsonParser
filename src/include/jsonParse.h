#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct VALIDATOR_STRUCT{
    int i;
    char* rawJSON;
    char currChar;
} validatorS;

typedef struct JSON_STRUCT{
    // define json structure that can then be easily referenced / queried for info
} JSON;

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

int main();


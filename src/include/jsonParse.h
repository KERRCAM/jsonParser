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

char* loadJSONStaggered(char* filename, int lastRead);

void charAdvance(validatorS* validator);

void consumeWhiteSpace(validatorS* validator);

void consumeString(validatorS* validator);

void consumeInt(validatorS* validator);

void consumeNumber(validatorS* validator);

void consumeBool(validatorS* validator);

void consumeNull(validatorS* validator);

void consumeValue(validatorS* validator);

void consumeObject(validatorS* validator);

void consumeArray(validatorS* validator);

void validateJSON(validatorS* validator);

int main();


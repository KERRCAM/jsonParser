// LOCAL IMPORTS
#include "include/validator.h"
#include "include/parser.h"

//-----------------------------------------------------------------------------------------------//

parserS* initParser(char* jsonContent){

    parserS* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser -> i = 0;
    parser -> rawJSON = jsonContent;
    parser -> currChar = jsonContent[0];

    return parser;

}

//-----------------------------------------------------------------------------------------------//

void charAdvanceP(parserS* parser){

    // Increments validator position and column and updates the current char

    parser -> i += 1;
    parser -> currChar = parser -> rawJSON[parser -> i];

}

//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//

struct jsonS* parseJSON(parserS* parser){

    struct jsonS* json;

    

    return json;

}

//-----------------------------------------------------------------------------------------------//

int main(){

    bool valid = false;

    double time, diff;
    time = (double) clock();
    time = time / CLOCKS_PER_SEC;

    // char* filename = "src/testFiles/test.json";
    char* filename = "src/testFiles/Streaming_History_Audio_2023_13.json";

    char* jsonContent = loadJSON(filename);

    validatorS* validator = initValidator(jsonContent);

    if (validateJSON(validator) != -1){
        printf(
            "ERROR: %s at line %d, column %d\n",
            errorMessage[crash], validator -> lineCrash, validator -> column
        );
    } else {
        valid = true;
        printf("%s\n", "Input JSON is valid");
    }

    if (valid == true){
        parserS* parser = initParser(jsonContent);
        struct jsonS* json = parseJSON(parser);
    }

    diff = ( ((double) clock()) / CLOCKS_PER_SEC) - time;
    printf("Program run time = %lf seconds\n", diff);

    return 0;

}

//-----------------------------------------------------------------------------------------------//

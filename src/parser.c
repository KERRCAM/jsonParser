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

void parserAdvance(parserS* parser){

    // Increments parser position and updates the current char

    parser -> i += 1;
    parser -> currChar = parser -> rawJSON[parser -> i];

}

//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------------//

struct jsonNode* newNode(struct jsonNode* parent, char* data[]){

    // takes all data as the full char* i.e. string still has the quotes
    // determine type in this func, then strip anything like quotes
    // store data as void with a char* type specifier
    // when data is pulled it will look at type then cast appropriately

}

//-----------------------------------------------------------------------------------------------//

struct jsonNode* parseJSON(parserS* parser){

    struct jsonNode* json;

    // initial type check -> call corresponding funcs
    /*
    for potential node in layer:
        recursive call
    */

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

    if (validateFile(validator) != -1){
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
    }

    diff = ( ((double) clock()) / CLOCKS_PER_SEC) - time;
    printf("Program run time = %lf seconds\n", diff);

    return 0;

}

//-----------------------------------------------------------------------------------------------//

// TODO
// Build up json as a tree structure adding info at each part
// Can then be pretty easily navigated with tree operations and not bad searches, sorts etc.

/*
- new node
- add node ?
- not all nodes have values -> lists, objects
Either have a node be the atomic pieces or have a node store the whole object, arrray etc as various structs
*/
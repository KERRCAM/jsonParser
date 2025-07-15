// LIBRARY IMPORTS


// LOCAL IMPORTS


//-----------------------------------------------------------------------------------------------//
//CONSTANTS

const char errorMessage[8][20] = {
    "Invalid number",
    "Number never closed",
    "String never closed",
    "Array never closed",
    "Invalid object",
    "Incomplete JSON",
    "Invalid JSON",
    "Invalid string"
};

//-----------------------------------------------------------------------------------------------//
//STRUCTS

typedef struct PARSER_STRUCT{
    int i;
    char* rawJSON;
    char currChar;
    int lineCrash;
    int column;
} parserS;

struct jsonNode{
    char* type;
    char* value;
    int nodeType; // -1 is root, 0 is default, 1 is leaf
    struct jsonNode* parent;
    struct jsonNode* children[10]; // TBD
};

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS



//-----------------------------------------------------------------------------------------------//

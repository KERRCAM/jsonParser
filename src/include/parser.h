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

struct jsonV{
    char* type;
    char* value;
    int parent;
};

struct jsonS{
    char* type;
    char* value;
    struct jsonV nodes[];
};

//-----------------------------------------------------------------------------------------------//
// FUNCTIONS



//-----------------------------------------------------------------------------------------------//

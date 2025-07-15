// LIBRARY IMPORTS


// LOCAL IMPORTS
#include "validator.h"
#include "parser.h"

//-----------------------------------------------------------------------------------------------//
//CONSTANTS



//-----------------------------------------------------------------------------------------------//
//STRUCTS



//-----------------------------------------------------------------------------------------------//
// FUNCTIONS

char* loadJSON(char *filename); // reads json file to a char array (will move this function here later)

int validateJSON(char* filePath); // returns 0 for an invalid json file and 1 for a valid json file

jsonNode* parseJSON(char* filePath); // returns the root node of a parsed json struct

int getMaxDepth();

int getDepthAt();

jsonNode* sortJSON();

jsonNode* searchJSON();

//-----------------------------------------------------------------------------------------------//

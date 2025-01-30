#include "jsonParse.h"

//TODO -> all methods currently void -> not their actual types, just a temporary placeholder

// ------------------------------------------------------------------------ //

validatorS* initValidator(char* jsonContent){

    validatorS* validator = calloc(1, sizeof(struct VALIDATOR_STRUCT));
    validator -> i = 0;
    validator -> rawJSON = jsonContent;
    validator -> currChar = jsonContent[validator -> i];

    return validator;
}

// ------------------------------------------------------------------------ //

char* loadJSON(char* filename){ // could do with some refactoring

    char * buffer = 0;
    long length;
    FILE * fp = fopen (filename, "rb");
    char* jsonContent;

    if (fp){
        fseek (fp, 0, SEEK_END);
        length = ftell (fp);
        fseek (fp, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer){
            fread (buffer, 1, length, fp);
        }
        fclose (fp);
    }

    if (buffer){
        jsonContent = buffer;
    }

    return jsonContent;
}

// ------------------------------------------------------------------------ //

char* loadJSONStaggered(char* filename, int lastRead){ // maybe needed maybe not

    // read only one chunk at once that could be valid and pass it to validation

    return filename;

}

// ------------------------------------------------------------------------ //

void charAdvance(validatorS* validator){ //make it get rawJSOn and not it be a param

    //currPos + 1
    //update currChar

    validator -> i += 1;
    validator -> currChar = validator -> rawJSON[validator -> i];

}

// ------------------------------------------------------------------------ //

void consumeWhiteSpace(validatorS* validator){

    // (space* linefeed* carriageReturn* horizontalTab*)*

    char c = validator -> currChar;

    while (c == ' ' || c == '\n' || c == '\r' || c == '\t'){ //need to fix types
        charAdvance(validator);
    }

}

// ------------------------------------------------------------------------ //

void consumeString(){

    // startQuote (anyCharBut\* (\ any of -> quotes / \ b n f r t (u 4 hex digits)))  endQuote
    //\b = backspace
    //\n = new line -> linefeed
    //\f = formfeed
    //\r = carriage return
    //\t = horizontal tab
    //\u = hex?

}

// ------------------------------------------------------------------------ //

void consumeNumber(){

    // number = -? [1..9] [0..9]* (. [0..9]*)? (e or E - or + [0..9]*)

}

// ------------------------------------------------------------------------ //

void consumeBool(){

   //bool = true or false

}

// ------------------------------------------------------------------------ //

void consumeNull(){

    //null = null

}

// ------------------------------------------------------------------------ //

void consumeObject(){

    //object = startCurly whitespace or (whitespace string whitespace? colon whitespace? value comma object*) endCurly

}

// ------------------------------------------------------------------------ //

void consumeArray(){

    //array = startSquare whitespace or (value comma)* endSquare

}

// ------------------------------------------------------------------------ //

void consumeValue(){

    //value = whitespace? object or array or string or number or bool or null whitespace?

}

// ------------------------------------------------------------------------ //

void validateJSON(validatorS* validator){

    /*
    follow general json BNF diagrams for validation
    -> also can work similarly to code lexing for efficient processing later
    -> avoid regex if possible -> take more manual approach
    */

    /*
    if first char is a { then check for object feed
    if first char is a [ then check for array feed
    */

    //validJSON = whitespace? (array or object) whitespace? validJSON*

    char c = validator -> currChar;

    if (c == ' ' || c == '\n' || c == '\r' || c == '\t'){ //need to fix types
        consumeWhiteSpace(validator);
    }

}

// ------------------------------------------------------------------------ //

int main(){

    char* filename = "test.json";

    char* jsonContent = loadJSON(filename);

    validatorS* validator = initValidator(jsonContent);

    validateJSON(validator);

    printf("%s\n", jsonContent);

    return 0;

}

// ------------------------------------------------------------------------ //
#include "include/jsonParse.h"

enum error {
    INVALID_NUMBER,
    INVALID_STRING,
};

// TODO -> add license once there is a working version, remove vs code folder too
// Will get everything working initially then refactor everything for clarity and efficiency

// --------------------------------------------------------------------------------------------- //

validatorS* initValidator(char* jsonContent){

    validatorS* validator = calloc(1, sizeof(struct VALIDATOR_STRUCT));
    validator -> i = 0;
    validator -> rawJSON = jsonContent;
    validator -> currChar = jsonContent[validator -> i];

    return validator;
}

// --------------------------------------------------------------------------------------------- //

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

// --------------------------------------------------------------------------------------------- //

char* loadJSONStaggered(char* filename, int lastRead){ // maybe needed maybe not

    // read only one chunk at once that could be valid and pass it to validation

    return filename;

}

// --------------------------------------------------------------------------------------------- //

void charAdvance(validatorS* validator){ //make it get rawJSOn and not it be a param

    //currPos + 1
    //update currChar

    validator -> i += 1;
    validator -> currChar = validator -> rawJSON[validator -> i];

}

// --------------------------------------------------------------------------------------------- //

void consumeWhiteSpace(validatorS* validator){

    // (space* linefeed* carriageReturn* horizontalTab*)*

    while (    validator -> currChar == ' '
            || validator -> currChar == '\n'
            || validator -> currChar == '\r'
            || validator -> currChar == '\t'){ //need to fix types
        charAdvance(validator);
    }

}

// --------------------------------------------------------------------------------------------- //

void consumeString(validatorS* validator){

    // startQuote (anyCharBut\* (\ any of -> quotes / \ b n f r t (u 4 hex digits)))  endQuote
    // \b = backspace
    // \n = new line -> linefeed
    // \f = formfeed
    // \r = carriage return
    // \t = horizontal tab
    // \u = hex?

}

// --------------------------------------------------------------------------------------------- //

void consumeInt(validatorS* validator){

    while(isdigit(validator -> currChar)){
        charAdvance(validator);
    }

}

// --------------------------------------------------------------------------------------------- //

void consumeNumber(validatorS* validator){ // GETTING COMPILER WARNING

    // number = -? [1..9] [0..9]* (. [0..9]*)? (e or E - or + [0..9]*)
    if (validator -> currChar == '-'){
        charAdvance(validator);

        if (isdigit(validator -> currChar) == false){
            //throw numerical error
        } else{
            consumeInt(validator);
        }
    }

    consumeInt(validator);

    if (validator -> currChar == 'e' || validator -> currChar == 'E'){
        charAdvance(validator);

        if (validator -> currChar != '+' || validator -> currChar != '-'){
            //throw numerical error
        } else{
            charAdvance(validator);
        }

        if (isdigit(validator -> currChar) == false){
            //throw numerical error
        } else{
            consumeInt(validator);
        }

    }

    // return error if one occurred

}

// --------------------------------------------------------------------------------------------- //

void consumeBool(validatorS* validator){

   //bool = true or false

}

// --------------------------------------------------------------------------------------------- //

void consumeNull(validatorS* validator){

    //null = null

}

// --------------------------------------------------------------------------------------------- //

void consumeValue(validatorS* validator){

    //value = whitespace? object or array or string or number or bool or null whitespace?

    consumeWhiteSpace(validator);

    switch (validator -> currChar){
    case ('"'):
        consumeString(validator);
        break;
    case ('{'):
        consumeObject(validator);
        break;
    case ('['):
        consumeArray(validator);
        break;
    case ('t' | 'f'):
        consumeBool(validator);
        break;
    case ('n'):
        consumeNull(validator);
        break;
    default:
        consumeNumber(validator);
        break;
    }

    consumeWhiteSpace(validator);

}

// --------------------------------------------------------------------------------------------- //

void consumeObject(validatorS* validator){

    //object = startCurly whitespace or (whitespace string whitespace? colon whitespace? value comma object*) endCurly

}

// --------------------------------------------------------------------------------------------- //

void consumeArray(validatorS* validator){

    //array = startSquare whitespace or (value comma)* endSquare

    consumeWhiteSpace(validator); // check for first char being '[' has already been done
    while (validator -> currChar != ']'){
        consumeValue(validator);
        if (validator -> currChar == ','){
            charAdvance(validator);
        }
    }

}

// --------------------------------------------------------------------------------------------- //

void validateJSON(validatorS* validator){

    //validJSON = whitespace? (array or object) whitespace? validJSON*

    consumeWhiteSpace(validator);

    if (validator -> currChar == '{'){
        consumeObject(validator);
    } else if (validator -> currChar == '['){
        consumeArray(validator);
    }

    consumeWhiteSpace(validator);

}

// --------------------------------------------------------------------------------------------- //

int main(){

    char* filename = "src/testFiles/test.json";

    char* jsonContent = loadJSON(filename);

    validatorS* validator = initValidator(jsonContent);

    validateJSON(validator);

    printf("%s\n", jsonContent);

    return 0;

}

// --------------------------------------------------------------------------------------------- //
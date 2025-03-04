#include "include/jsonParse.h"

enum error { // need error handling for closing an array or object or string that was never opened
    INVALID_NUMBER,
    NUMBER_NEVER_CLOSED,
    STRING_NEVER_CLOSED,
    ARRAY_NEVER_CLOSED,
    INVALID_OBJECT,
    INCOMPLETE_JSON,
    INVALID_JSON
};

enum error crash;

// TODO -> add license once there is a working version, remove vs code folder too
// Will get everything working initially then refactor everything for clarity and efficiency

// --------------------------------------------------------------------------------------------- //

validatorS* initValidator(char* jsonContent){

    validatorS* validator = calloc(1, sizeof(struct VALIDATOR_STRUCT));
    validator -> i = 0;
    validator -> rawJSON = jsonContent;
    validator -> currChar = jsonContent[0];

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

    //free(buffer);

    return jsonContent;
}

// --------------------------------------------------------------------------------------------- //

char* loadJsonStaggered(char* filename, int lastRead){ // maybe needed maybe not

    // read only one chunk at once that could be valid and pass it to validation

    return filename;

}

// --------------------------------------------------------------------------------------------- //

void charAdvance(validatorS* validator){ //make it get rawJSON and not it be a param

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

int consumeString(validatorS* validator){

    // startQuote (anyCharBut\* (\ any of -> quotes / \ b n f r t (u 4 hex digits)))  endQuote
    // \b = backspace
    // \n = new line -> linefeed
    // \f = formfeed
    // \r = carriage return
    // \t = horizontal tab
    // \u = hex?

    /*
    while (  validator -> currChar != '"'
        || validator -> currChar != '\b'
        || validator -> currChar != '\n'
        || validator -> currChar != '\f'
        || validator -> currChar != '\r'
        || validator -> currChar != '\t'
    )*/

    charAdvance(validator);

    while (true){
        if (validator -> currChar == EOF){ return crash = STRING_NEVER_CLOSED;}
        if (validator -> currChar != '"'){
            charAdvance(validator);
        } else {
            break;
        }
    }

    charAdvance(validator);

    return -1;

}

// --------------------------------------------------------------------------------------------- //

int consumeInt(validatorS* validator){

    while(isdigit(validator -> currChar)){
        if (validator -> currChar == EOF){ return crash = NUMBER_NEVER_CLOSED;}
        charAdvance(validator);
        }

    return -1;

}

// --------------------------------------------------------------------------------------------- //

int consumeNumber(validatorS* validator){

    // number = -? [1..9] [0..9]* (. [0..9]*)? (e or E - or + [0..9]*)
    if (validator -> currChar == '-'){
        charAdvance(validator);

        if (isdigit(validator -> currChar) == false){
            return crash = INVALID_NUMBER;
        } else{
            consumeInt(validator);
        }
    }

    consumeInt(validator);

    if (validator -> currChar == 'e' || validator -> currChar == 'E'){
        charAdvance(validator);

        if (validator -> currChar != '+' || validator -> currChar != '-'){
            return crash = INVALID_NUMBER;
        } else{
            charAdvance(validator);
        }

        if (isdigit(validator -> currChar) == false){
            return crash = INVALID_NUMBER;
        } else{
            consumeInt(validator);
        }

    }

    return -1;

}

// --------------------------------------------------------------------------------------------- //

int consumeKeyword(validatorS* validator, int length){

   //bool = true or false

    for (int i = 0; i < length; i++){
        if (validator -> currChar == EOF){
            return crash = INCOMPLETE_JSON;
        } else{
            charAdvance(validator);
        }
    }

    return -1;

}

// --------------------------------------------------------------------------------------------- //

int consumeValue(validatorS* validator){

    //value = whitespace? object or array or string or number or bool or null whitespace?

    consumeWhiteSpace(validator);

    switch (validator -> currChar){
        case ('"'):
            if (consumeString(validator) != -1){ return crash;};
            break;
        case ('{'):
            if (consumeObject(validator) != -1){ return crash;};
            break;
        case ('['):
            if (consumeArray(validator) != -1){ return crash;};
            break;
        case ('t'):
        if (consumeKeyword(validator, 4) != -1){ return crash;};
            break;
        case ('f'):
        if (consumeKeyword(validator, 5) != -1){ return crash;};
            break;
        case ('n'):
            if (consumeKeyword(validator, 4) != -1){ return crash;};
            break;
        default:
            if (consumeNumber(validator) != -1){ return crash;};
            break;
    }

    consumeWhiteSpace(validator);

    return -1;

}

// --------------------------------------------------------------------------------------------- //

int consumeObject(validatorS* validator){

    //object = startCurly whitespace or
    //         (whitespace string whitespace? colon whitespace? value comma object*) endCurly

    charAdvance(validator);
    consumeWhiteSpace(validator);

    if (validator -> currChar == '}'){
        charAdvance(validator);
        return -1;
    }

    while (true){
        if (consumeString(validator) != -1){ return crash;};
        consumeWhiteSpace(validator);

        if (validator -> currChar == ':'){
            charAdvance(validator);
        } // else throw invalid object error

        consumeWhiteSpace(validator);
        if (consumeValue(validator) != -1){ return crash;};

        if (validator -> currChar == ','){
            charAdvance(validator);
            consumeWhiteSpace(validator);
        } else if (validator -> currChar == '}'){
            consumeWhiteSpace(validator);
            charAdvance(validator);
            return -1;
        } else{
            return crash = INVALID_OBJECT;
        }
    }

}

// --------------------------------------------------------------------------------------------- //

int consumeArray(validatorS* validator){

    //array = startSquare whitespace or (value comma)* endSquare

    charAdvance(validator);
    consumeWhiteSpace(validator); // check for first char being '[' has already been done
    while (true){
        if (consumeValue(validator) != -1){ return crash;};
        if (validator -> currChar == ','){
            charAdvance(validator);
            consumeWhiteSpace(validator);
        }
        if (validator -> currChar == ']'){
            return -1;
        } else {
            return crash = ARRAY_NEVER_CLOSED;
        }
    }

    charAdvance(validator);

    return -1;

}

// --------------------------------------------------------------------------------------------- //

int validateJSON(validatorS* validator){

    //validJSON = whitespace? (array or object) whitespace? validJSON*

    consumeWhiteSpace(validator);

    if (validator -> currChar == '{'){
        if (consumeObject(validator) != -1){ return crash;};
    } else if (validator -> currChar == '['){
        if (consumeArray(validator) != -1){ return crash;};
    }

    consumeWhiteSpace(validator);

    return -1;

}

// --------------------------------------------------------------------------------------------- //

int main(){

    char* filename = "src/testFiles/test.json";

    char* jsonContent = loadJSON(filename);

    validatorS* validator = initValidator(jsonContent);

    if (validateJSON(validator) != -1){
        printf("%d\n", crash);
    } else {
        printf("%s\n", "Input JSON is valid");
    }

    printf("%s\n", jsonContent);

    return 0;

}

// --------------------------------------------------------------------------------------------- //
#include "jsonParse.h"



//TODO -> all methods currently void -> not their actual types, just a temporary placeholder



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


void validateJSON(char* rawJSON){

    /*
    follow general json BNF diagrams for validation
    -> also can work similarly to code lexing for efficient processing later
    -> avoid regex if possible -> take more manual approach
    */

    /*
    if first char is a { then check for object feed
    if first char is a [ then check for array feed
    */

}


void charAdvance(){

    //currPos + 1
    //update currChar

}


void consumeWhiteSpace(){

    // (space* or linefeed* or carriageReturn* or horizontalTab*)*

}


void consumeString(){

    // startQuote (anyCharBut\* (\ any of -> quotes / \ b n f r t (u 4 hex digits)))  endQuote
    //\b = backspace
    //\n = new line -> linefeed
    //\f = formfeed
    //\r = carriage return
    //\t = horizontal tab
    //\u = hex?

}


void consumeNumber(){

    // number = -? [1..9] [0..9]* (. [0..9]*)? (e or E - or + [0..9]*)

}


void consumeBool(){

   //bool = true or false

}


void consumeNull(){

    //null = null

}


void consumeObject(){

    //object = startCurly whitespace or (whitespace string whitespace? colon whitespace? value comma object*) endCurly

}


void consumeArray(){

    //array = startSquare whitespace or (value comma)* endSquare

}


void consumeValue(){

    //value = whitespace? object or array or string or number or bool or null whitespace?

}


int main(){

    char* filename = "test.json";

    char* jsonContent = loadJSON(filename);

    printf("%s\n", jsonContent);

    return 0;

}
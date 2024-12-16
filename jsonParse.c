#include "jsonParse.h"
#include <stdlib.h>



char* loadJSON(char* filename){

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






int main(){

    char* filename = "test.json";

    char* jsonContent = loadJSON(filename);

    printf("%s\n", jsonContent);

    return 0;

}
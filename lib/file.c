/**
 * @file file.c
 * @brief File operations library source.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the file.h file.
 */
#include "mem-manager.h"
#include "file.h"

FILE* openFile(char filename[255], char* mode) {
    FILE* fp;
    if ((fp = fopen(filename, mode)) == NULL) {
        printf("Error opening the file!Terminating...\n");
    }
    return fp;
}

u1* get(FILE* fp, int offset, int bytes) {
    u1* content;

    // Alocate with file size
    content = (u1*) allocate(sizeof(u1) * bytes);

    // Read file
    fseek(fp, offset, SEEK_SET);
    fread(content, sizeof(u1), bytes, fp);

    return content;
}

u1 getByte(FILE* fp, int offset) {
    u1 byte;

    // Read byte
    fseek(fp, offset, SEEK_SET);
    fread(&byte, sizeof(u1), 1, fp);

    return byte;
}

u2 getWord(FILE* fp, int offset) {
    u2 word;

    // Read word
    fseek(fp, offset, SEEK_SET);
    fread(&word, sizeof(u2), 1, fp);

    return word;
}

u4 getDoubleWord(FILE* fp, int offset) {
    u4 doubleWord;

    // Read double word
    fseek(fp, offset, SEEK_SET);
    fread(&doubleWord, sizeof(u4), 1, fp);

    return doubleWord;
}

int fileSize(FILE* fp) {
    fseek(fp, 0, SEEK_END);
    return ftell(fp);
}

void closeFile(FILE** fp) {
    fclose((*fp));
    (*fp) = NULL;
}

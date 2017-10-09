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

int fileSize(FILE* fp) {
    fseek(fp, 0, SEEK_END);
    return ftell(fp);
}

void closeFile(FILE** fp) {
    fclose((*fp));
    (*fp) = NULL;
}

uint8_t* get(FILE* fp, int offset, int bytes) {
    uint8_t* content;

    content = (uint8_t*) set_mem(bytes * sizeof(uint8_t));

    fseek(fp, offset, SEEK_SET);
    fread(content, sizeof(uint8_t), bytes, fp);

    return content;
}

uint8_t getByte(FILE* fp, int offset) {
    uint8_t byte;

    fseek(fp, offset, SEEK_SET);
    fread(&byte, sizeof(uint8_t), 1, fp);

    return byte;
}

uint16_t getWord(FILE* fp, int offset) {
    uint16_t word;

    fseek(fp, offset, SEEK_SET);
    fread(&word, sizeof(uint16_t), 1, fp);

    return word;
}

uint32_t getDoubleWord(FILE* fp, int offset) {
    uint32_t doubleWord;

    fseek(fp, offset, SEEK_SET);
    fread(&doubleWord, sizeof(uint32_t), 1, fp);

    return doubleWord;
}

/**
 * @file utils.c
 * @brief File operations library source.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the utils.h file.
 */
#include <string.h>
#include "mem-manager.hpp"
#include "utils.hpp"

const char *names[] = {" public", " private", " protected", " static", " final",
 " super", " volatile", " transient", " interface", " abstract", " synthetic",
 " annotation", " enum", " synchronized", " bridge", " varargs", " native", " strict"};

const char *array_types[] = {"boolean", "char", "float", "double", "byte", "short",
"int", "long"};

const char *methods_handle_types[] = {"REF_getField", "REF_getStatic", "REF_putField",
"REF_putStatic", "REF_invokeVirtual", "REF_invokeStatic", "REF_invokeSpecial",
"REF_newInvokeSpecial", "REF_invokeInterface"};

char* map_methods_handle_types(uint8_t type){
  switch (type) {
    case REF_getField:
      return ((char*)methods_handle_types[0]);
    case REF_getStatic:
      return ((char*)methods_handle_types[1]);
    case REF_putField:
      return ((char*)methods_handle_types[2]);
    case REF_putStatic:
      return ((char*)methods_handle_types[3]);
    case REF_invokeVirtual:
      return ((char*)methods_handle_types[4]);
    case REF_invokeStatic:
      return ((char*)methods_handle_types[5]);
    case REF_invokeSpecial:
      return ((char*)methods_handle_types[6]);
    case REF_newInvokeSpecial:
      return ((char*)methods_handle_types[7]);
    case REF_invokeInterface:
      return ((char*)methods_handle_types[8]);
    default:
      return NULL;
  }
}

 char* map_method_flags(uint16_t access_flags){
     char** tokens = (char**) malloc(12 * 15);
     char* string = (char*) set_mem(250 * sizeof(char));
     string[250] = '\0';
     int i = 0;

     // Map the access flags into strings.
     while (access_flags != 0) {
        if (access_flags >= (uint16_t)ACC_SYNTHETIC){
             access_flags -= ACC_SYNTHETIC;
             tokens[i] = (char*)names[10];
             i++;
         }
         else if (access_flags >= (uint16_t)ACC_STRICT){
             access_flags -= ACC_STRICT;
             tokens[i] = (char*)names[17];
             i++;
         }
         else if (access_flags >= (uint16_t)ACC_ABSTRACT){
             access_flags -= ACC_ABSTRACT;
             tokens[i] = (char*)names[9];
             i++;
         }
         else if (access_flags >= (uint16_t)ACC_NATIVE){
             access_flags -= ACC_NATIVE;
             tokens[i] = (char*)names[16];
             i++;
         }
         else if (access_flags >= (uint16_t)ACC_VARARGS){
             access_flags -= ACC_VARARGS;
             tokens[i] = (char*)names[15];
             i++;
         }
         else if (access_flags >= (uint16_t)ACC_BRIDGE){
             access_flags -= ACC_BRIDGE;
             tokens[i] = (char*)names[14];
             i++;
         }
         else if (access_flags >= (uint16_t)ACC_SYNCHRONIZED){
             access_flags -= ACC_SYNCHRONIZED;
             tokens[i] = (char*)names[13];
             i++;
         }
         else if (access_flags >= (uint16_t)ACC_FINAL){
             access_flags -= ACC_FINAL;
             tokens[i] = (char*)names[4];
             i++;
         }
         else if (access_flags >= (uint16_t)ACC_STATIC){
             access_flags -= ACC_STATIC;
             tokens[i] = (char*)names[3];
             i++;
         }
         else if (access_flags >= (uint16_t)ACC_PROTECTED){
             access_flags -= ACC_PROTECTED;
             tokens[i] = (char*)names[2];
             i++;
         }
         else if (access_flags >= (uint16_t)ACC_PRIVATE){
             access_flags -= ACC_PRIVATE;
             tokens[i] = (char*)names[1];
             i++;
         }
         else if (access_flags >= (uint16_t)ACC_PUBLIC){
             access_flags -= ACC_PUBLIC;
             tokens[i] = (char*)names[0];
             i++;
             break;
         }
         else{
             strcpy(string, "invalid argument!");
             break;
         }
     }
     strcpy(string, tokens[i - 1]);

     if (i > 1) {
         for (int j = i - 2; j >= 0 ; j--){
             strcat(string, tokens[j]);
         }
     }

     free(tokens);
     tokens = NULL;

     return string;
 }

char* map_flags(uint16_t access_flags){
    char** tokens = (char**) malloc(13 * 15);
    char* string = (char*) set_mem(250 * sizeof(char));
    string[250] = '\0';
    int i = 0;

    // Map the access flags into strings.
    while (access_flags != 0) {
        if (access_flags >= (uint16_t)ACC_ENUM){
            access_flags -= ACC_ENUM;
            tokens[i] = (char*)names[12];
            i++;
        }
        else if (access_flags >= (uint16_t)ACC_ANNOTATION){
            access_flags -= ACC_ANNOTATION;
            tokens[i] = (char*)names[11];
            i++;
        }
        else if (access_flags >= (uint16_t)ACC_SYNTHETIC){
            access_flags -= ACC_SYNTHETIC;
            tokens[i] = (char*)names[10];
            i++;
        }
        else if (access_flags >= (uint16_t)ACC_ABSTRACT){
            access_flags -= ACC_ABSTRACT;
            tokens[i] = (char*)names[9];
            i++;
        }
        else if (access_flags >= (uint16_t)ACC_INTERFACE){
            access_flags -= ACC_INTERFACE;
            tokens[i] = (char*)names[8];
            i++;
        }
        else if (access_flags >= (uint16_t)ACC_TRANSIENT){
            access_flags -= ACC_TRANSIENT;
            tokens[i] = (char*)names[7];
            i++;
        }
        else if (access_flags >= (uint16_t)ACC_VOLATILE){
            access_flags -= ACC_VOLATILE;
            tokens[i] = (char*)names[6];
            i++;
        }
        else if (access_flags >= (uint16_t)ACC_SUPER){
            access_flags -= ACC_SUPER;
            tokens[i] = (char*)names[5];
            i++;
        }
        else if (access_flags >= (uint16_t)ACC_FINAL){
            access_flags -= ACC_FINAL;
            tokens[i] = (char*)names[4];
            i++;
        }
        else if (access_flags >= (uint16_t)ACC_STATIC){
            access_flags -= ACC_STATIC;
            tokens[i] = (char*)names[3];
            i++;
        }
        else if (access_flags >= (uint16_t)ACC_PROTECTED){
            access_flags -= ACC_PROTECTED;
            tokens[i] = (char*)names[2];
            i++;
        }
        else if (access_flags >= (uint16_t)ACC_PRIVATE){
            access_flags -= ACC_PRIVATE;
            tokens[i] = (char*)names[1];
            i++;
        }
        else if (access_flags >= (uint16_t)ACC_PUBLIC){
            access_flags -= ACC_PUBLIC;
            tokens[i] = (char*)names[0];
            i++;
            break;
        }
        else{
            strcpy(string, "invalid argument!");
            break;
        }
    }
    strcpy(string, tokens[i - 1]);

    if (i > 1) {
        for (int j = i - 2; j >= 0 ; j--){
            strcat(string, tokens[j]);
        }
    }

    free(tokens);
    tokens = NULL;

    return string;
}

char* map_array_type(int type) {
     switch (type) {
          case T_BOOLEAN:
               return ((char*)array_types[0]);
          case T_CHAR:
               return ((char*)array_types[1]);
          case T_FLOAT:
               return ((char*)array_types[2]);
          case T_DOUBLE:
               return ((char*)array_types[3]);
          case T_BYTE:
               return ((char*)array_types[4]);
          case T_SHORT:
               return ((char*)array_types[5]);
          case T_INT:
               return ((char*)array_types[6]);
          case T_LONG:
               return ((char*)array_types[7]);
          default:
               return NULL;
     }
}

uint16_t to2Bytes(uint16_t src) {
    // Mask for the upper byte
    return (src << 8) | ((src & 0xFF00) >> 8);
}

uint32_t to4Bytes(uint32_t src) {
    // Apply maks for upper and lower bytes and return them concatenated
    uint32_t low = to2Bytes( (uint16_t)( ( src & 0xFFFF0000 ) >> 16 ) );
    uint32_t high = to2Bytes( (uint16_t)( src & 0x0000FFFF ) );

    return (high << 16) | low;
}

char* utf8ToString(uint8_t* src, uint16_t length)  {
    char* retorno = (char*) set_mem((length + 1) * sizeof(char));
    char *auxretorno = retorno;

    for (uint8_t *aux = src; aux < (src + length); aux++){
        *(auxretorno++) = (char) *aux;
    }
    *auxretorno = '\0';

    return retorno;
}

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

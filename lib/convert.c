/**
 * @file convert.c
 * @brief Convertion operations library source.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the convert.h file.
 */
#include <stdio.h>
#include <string.h>
#include "mem-manager.h"
#include "convert.h"

const char *names[] = {" public", " final", " super", " interface", " abstract", " synthetic", " annotation", "enum"};

char* map_flags(uint16_t access_flags){
    char* string = (char*) set_mem(100 * sizeof(char));;
    string[100] = '\0';
    // Map the access flags into strings.
    while (access_flags != 0) {
        if (access_flags >= (uint16_t)ACC_ENUM){
            access_flags -= ACC_ENUM;
            strcpy(string, names[7]);
        }
        else if (access_flags >= (uint16_t)ACC_ANNOTATION){
            access_flags -= ACC_ANNOTATION;
            strncat(string, names[6], strlen(names[6]));
        }
        else if (access_flags >= (uint16_t)ACC_SYNTHETIC){
            access_flags -= ACC_SYNTHETIC;
            strncat(string, names[5], strlen(names[5]));
        }
        else if (access_flags >= (uint16_t)ACC_ABSTRACT){
            access_flags -= ACC_ABSTRACT;
            strncat(string, names[4], strlen(names[4]));
        }
        else if (access_flags >= (uint16_t)ACC_INTERFACE){
            access_flags -= ACC_INTERFACE;
            strncat(string, names[3], strlen(names[3]));
        }
        else if (access_flags >= (uint16_t)ACC_SUPER){
            access_flags -= ACC_SUPER;
            strncat(string, names[2], strlen(names[2]));
        }
        else if (access_flags >= (uint16_t)ACC_FINAL){
            access_flags -= ACC_FINAL;
            strncat(string, names[1], strlen(names[1]));
        }
        else if (access_flags >= (uint16_t)ACC_PUBLIC){
            access_flags -= ACC_PUBLIC;
            strncat(string, names[0], strlen(names[0]));
            break;
        }
        else{
            strcpy(string, "invalid argument!");
            break;
        }
    }
    string[strlen(string)] = '\0';
    return string;
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

char* utf8ToString(uint8_t* src, uint16_t length, bool isRef)  {
    int i, count;
    for (i = 0, count = 0; i < length; i++) {
        if (src[i] >> 7 == 0x0) {
            count++;
        } else if (src[i] >> 5 == 0x6) {
            count++;
            i++;
        } else if (src[i] >> 4 == 0xC) {
            count++;
            i = i + 2;
        } else {
            printf("Occured some error on decoding UTF-8 string\n");
        }
    }

    char* string = NULL;
    if (isRef) {
        string  = (char*) set_mem((count + 3) * sizeof(char));
        int j;
        string[0] = '<';
        for (i = 1, j = 0; i < count + 2 && j < length; i++, j++) {
            if (src[i] >> 7 == 0x0) {
                string[i] = (char) src[j];
            } else if (src[i] >> 5 == 0x6) {
                uint8_t x = src[j++];
                uint8_t y = src[j];
                string[i] = (char) ( ( ( x & 0x1F ) << 6 ) | ( y & 0x3F ) );
            } else if (src[i] >> 4 == 0xC) {
                uint8_t x = src[j++];
                uint8_t y = src[j++];
                uint8_t z = src[j];
                string[i] = (char) ( ( ( x & 0xF ) << 12 ) | ( ( y & 0x3F ) << 6 ) | ( z & 0x3F ) );
            } else {
                printf(" Occured some error on decoding UTF-8 string\n");
            }
        }

        string[count + 1] = '>';
        string[count + 2] = '\0';
    } else {
        string  = (char*) set_mem((count + 1) * sizeof(char));
        int j;
        for (i = 0, j = 0; i < count && j < length; i++, j++) {
            if (src[i] >> 7 == 0x0) {
                string[i] = (char) src[j];
            } else if (src[i] >> 5 == 0x6) {
                uint8_t x = src[j++];
                uint8_t y = src[j];
                string[i] = (char) ( ( ( x & 0x1F ) << 6 ) | ( y & 0x3F ) );
            } else if (src[i] >> 4 == 0xC) {
                uint8_t x = src[j++];
                uint8_t y = src[j++];
                uint8_t z = src[j];
                string[i] = (char) ( ( ( x & 0xF ) << 12 ) | ( ( y & 0x3F ) << 6 ) | ( z & 0x3F ) );
            } else {
                printf("Error on decoding!\n");
            }
        }
        string[count] = '\0';
    }
    return string;
}

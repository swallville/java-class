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
#include "mem-manager.h"
#include "convert.h"

u2 smallEndianToBigEndian2Bytes(u2 src) {
    // Mask for the upper byte
    return (src << 8) | ((src & 0xFF00) >> 8);
}

u4 smallEndianToBigEndian4Bytes(u4 src) {
    // Apply maks for upper and lower bytes and return them concatenated
    u4 low = smallEndianToBigEndian2Bytes( (u2)( ( src & 0xFFFF0000 ) >> 16 ) );
    u4 high = smallEndianToBigEndian2Bytes( (u2)( src & 0x0000FFFF ) );

    return (high << 16) | low;
}

char* utf8ToString(u1* src, u2 length, bool isRef)  {
    // Verify how many characters the string has
    int i, count;
    for (i = 0, count = 0; i < length; i++) {
        if (src[i] >> 7 == 0x0) {
            count++;
        } else if (src[i] >> 5 == 0x6) {
            count++;
            // Jump one extra-byte
            i++;
        } else if (src[i] >> 4 == 0xC) {
            count++;
            // Jump two extra-byte
            i = i + 2;
        } else {
            printf("Occured some error on decoding UTF-8 string\n");
        }
    }

    // Allocate the space of memory for the string
    char* string = NULL;
    if (isRef) {
        string  = (char*) allocate((count + 3) * sizeof(char));

        // Read each byte of the string
        int j;
        string[0] = '<';
        for (i = 1, j = 0; i < count + 1 && j < length; i++, j++) {
            if (src[i] >> 7 == 0x0) {
                string[i] = (char) src[j];
            } else if (src[i] >> 5 == 0x6) {
                u1 x = src[j++];
                u1 y = src[j];
                string[i] = (char) ( ( ( x & 0x1F ) << 6 ) | ( y & 0x3F ) );
            } else if (src[i] >> 4 == 0xC) {
                u1 x = src[j++];
                u1 y = src[j++];
                u1 z = src[j];
                string[i] = (char) ( ( ( x & 0xF ) << 12 ) | ( ( y & 0x3F ) << 6 ) | ( z & 0x3F ) );
            } else {
                printf("Occured some error on decoding UTF-8 string\n");
            }
        }

        string[count + 1] = '>';
        string[count + 2] = '\0';
    } else {
        string  = (char*) allocate((count + 1) * sizeof(char));

        // Read each byte of the string
        int j;
        for (i = 0, j = 0; i < count && j < length; i++, j++) {
            if (src[i] >> 7 == 0x0) {
                string[i] = (char) src[j];
            } else if (src[i] >> 5 == 0x6) {
                u1 x = src[j++];
                u1 y = src[j];
                string[i] = (char) ( ( ( x & 0x1F ) << 6 ) | ( y & 0x3F ) );
            } else if (src[i] >> 4 == 0xC) {
                u1 x = src[j++];
                u1 y = src[j++];
                u1 z = src[j];
                string[i] = (char) ( ( ( x & 0xF ) << 12 ) | ( ( y & 0x3F ) << 6 ) | ( z & 0x3F ) );
            } else {
                printf("Occured some error on decoding UTF-8 string\n");
            }
        }

        string[count] = '\0';
    }
    return string;
}

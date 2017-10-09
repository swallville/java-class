/**
 * @file convert.h
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * @todo Description
 */

#ifndef _CONVERT_H
#define _CONVERT_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Enum with a type name assignment with the access flag's name.
 * Contains the constants types matching with its flag.
 */
enum {
    ACC_PUBLIC = 1,
    ACC_FINAL = 16,
    ACC_SUPER = 32,
    ACC_INTERFACE = 512,
    ACC_ABSTRACT = 1024,
    ACC_SYNTHETIC = 4096,
    ACC_ANNOTATION = 8192,
    ACC_ENUM = 16384
} ACC_flags;

/**
 * @brief Map with strings the access flags
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
char* map_flags(uint16_t access_flags);

/**
 * @brief Transform a little Endian to a Big Endian in 2 bytes
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
uint16_t to2Bytes(uint16_t src);

/**
 * @brief Transform a little Endian to a Big Endian in 4 bytes
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
uint32_t to4Bytes(uint32_t src);

/**
 * @brief Transform a UTF8 to a string
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
char* utf8ToString(uint8_t* src, uint16_t length, bool isRef);

#endif //_CONVERT_H

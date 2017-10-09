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
#include "utils.h"

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
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
char* map_flags(u2 access_flags);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u2 smallEndianToBigEndian2Bytes(u2 src);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u4 smallEndianToBigEndian4Bytes(u4 src);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
char* utf8ToString(u1* src, u2 length, bool isRef);

#endif //_CONVERT_H

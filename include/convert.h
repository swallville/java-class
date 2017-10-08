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

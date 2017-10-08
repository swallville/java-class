/**
 * @file file.h
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * @todo Description
 */

#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>
#include <stdint.h>
#include "utils.h"

/**
 * @brief Opens some file in a specific mode.
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
FILE* openFile(char filename[255], char* mode);

/**
 * @brief Reads a specific amount of bytes in a specific offset of a file pointer.
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u1* get(FILE* fp, int offset, int bytes);

/**
 * @todo Brief
 * @todo Description
 * @todo Params
 * @todo Return
 */
u1 getByte(FILE* fp, int offset);

/**
 * @todo Brief
 * @todo Description
 * @todo Params
 * @todo Return
 */
u2 getWord(FILE* fp, int offset);

 /**
 * @todo Brief
 * @todo Description
 * @todo Params
 * @todo Return
 */
u4 getDoubleWord(FILE* fp, int offset);

/**
 * @brief Returns the size of some file.
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
int fileSize(FILE* fp);

/**
 * @brief Closes a file pointer and removes the pointer reference.
 *
 * @todo Description
 * @todo Parameters
 */
void closeFile(FILE**);

#endif

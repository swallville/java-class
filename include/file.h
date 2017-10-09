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

/**
 * @brief Opens a file into a specific mode
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
FILE* openFile(char filename[255], char* mode);

/**
 * @brief Get the file's size
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
int fileSize(FILE* fp);

/**
 * @brief Close and Remove a file pointer
 *
 * @todo Description
 * @todo Parameters
 */
void closeFile(FILE**);

/**
 * @brief Reads bytes in a specific offset of a file pointer.
 *
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
uint8_t* get(FILE* fp, int offset, int bytes);

/**
 * @brief Reads a byte in a file pointer.
 *
 * @todo Brief
 * @todo Description
 * @todo Params
 * @todo Return
 */
uint8_t getByte(FILE* fp, int offset);

/**
 * @brief Reads a word in a file pointer.
 *
 * @todo Brief
 * @todo Description
 * @todo Params
 * @todo Return
 */
uint16_t getWord(FILE* fp, int offset);

 /**
 * @brief Reads a double word in a file pointer.
 *
 * @todo Brief
 * @todo Description
 * @todo Params
 * @todo Return
 */
uint32_t getDoubleWord(FILE* fp, int offset);

#endif // _FILE_H

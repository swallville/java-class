/**
 * @file execute.h
 * @brief Execution operations library header.
 * @authors Lukas Ferreira Machado (12/0127377))
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * Signatures of instruction's functions
 */

#ifndef _EXECUTE_H
#define _EXECUTE_H

#include <stdint.h>
#include "class.h"
#include "instruction.h"

/**
 * @Brief Set Instruction parmams by its opcode
 * @Description
 * Through a switch case, it sets an Instruction depending on
 * the number of arguments.
 * @Parameters char *byteCode and an int offset
 * @Return Instruction*
 */
Instruction* decode(uint8_t* byteCode, int* offset);

/**
 * @Brief Set the Instruction instance with no arguments.
 * @Description
 * Sets all fields of the instance Instruction to be returned.
 * @Parameters char *bytecode, int offset, int pc, int opcode, char name(from the instruction), int (*func) Instruction
 * @Return Instruction*
 */
Instruction* readNoArgs(uint8_t* bytecode, int* offset, int pc, int opcode, char* name);


/**
 * @Brief Set the Instruction instance with one argument.
 * Sets all fields of the instance Instruction to be returned.
 * @Parameters char *bytecode, int offset, int pc, int opcode, char name(from the instruction), int (*func) Instruction
 * @Return Instruction*
 */
Instruction* readOneArg(uint8_t* bytecode, int* offset, int pc, int opcode, char* name);

/**
 * @Brief Set the Instruction instance with two arguments.
 * @Description
 * Sets all fields of the instance Instruction to be returned.
 * @Parameters char *bytecode, int offset, int pc, int opcode, char name(from the instruction), int (*func) Instruction
 * @Return Instruction*
 */
Instruction* readTwoArgs(uint8_t* bytecode, int* offset, int pc, int opcode, char* name);

#endif // _EXECUTE_H

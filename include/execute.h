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
 * @Brief Returns the instruction to be executed from the offset.
 * @Description
 * Through a switch case of all types of functions, it returns a call to another
 * function depending on the number of arguments of each function.
 * @Parameters char *byteCode and an int offset
 * @Return Instruction*
 */
Instruction* decode(uint8_t* byteCode, int* offset);

/**
 * @Brief It initializes the struct instruction with all its variables. In this case, no arguments.
 * @Description
 * The function allocates memory for the instructions and sets its variables with the parameters passed throught the
 * the function parameters.
 * @Parameters char *bytecode, int offset, int pc, int opcode, char name(from the instruction), int (*func) Instruction
 * @Return Instruction*
 */
Instruction* getNoArgsInstr(uint8_t* bytecode, int* offset, int pc, int opcode, char* name);


/**
 * @Brief It initializes the struct instruction with all its variables. In this case, one arguments.
 * The function allocates memory for the instructions and sets its variables with the parameters passed throught the
 * the function parameters.
 * @Parameters char *bytecode, int offset, int pc, int opcode, char name(from the instruction), int (*func) Instruction
 * @Return Instruction*
 */
Instruction* getOneArgInstr(uint8_t* bytecode, int* offset, int pc, int opcode, char* name);

/**
 * @Brief It initializes the struct instruction with all its variables. In this case, two arguments.
 * @Description
 * The function allocates memory for the instructions and sets its variables with the parameters passed throught the
 * the function parameters.
 * @Parameters char *bytecode, int offset, int pc, int opcode, char name(from the instruction), int (*func) Instruction
 * @Return Instruction*
 */
Instruction* getTwoArgsInstr(uint8_t* bytecode, int* offset, int pc, int opcode, char* name);

#endif // _EXECUTE_H

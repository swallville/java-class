/**
 * @file execute.h
 * @brief Execution operations library header.
 * @authors Lukas Ferreira Machado (12/0127377))
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * @todo Description
 */

#ifndef _EXECUTE_H
#define _EXECUTE_H

#include "class.h"
#include "instruction.h"

/**
 * @Brief From the offset (Program Counter) it returns the instruction to be executed.
 * @Description
 * The function contains an switch case function containing all the structions implemented. It returns a call to another
 * function, depending on the type of the instruction: if it was no arguments, one argument or 2 arguments. This call is to
 * initialize the variables inside de instruction struct.
 * @Parameters char *byteCode and an int offset
 * @Return Struct instructions with their arguments.
 */
Instruction* decode(u1* byteCode, int* offset);

/**
 * @Brief It initializes the struct instruction with all its variables. In this case, the arguments variable it set to NULL.
 * @Description
 * The function simply allocates memory space for the instructions and sets its variables with the parameters passed throught the
 * the function parameters. The arguments (2 byte array) are set to null because there is no need to use.
 * The funct variable recieves the instruction to be executed.
 * @Parameters char *bytecode, int offset, int pc, int opcode, char name(from the instruction), int (*func) Instruction
 * @Return Struct Instruction with all the arguments initialized
 */
Instruction* getNoArgsInstr(u1* bytecode, int* offset, int pc, int opcode, char* name);


/**
 * @Brief It initializes the struct instruction with all its variables. In this case, the arguments[0] is one byte read from the bytecode.
 * @Description
 * The function simply allocates memory space for the instructions and sets its variables with the parameters passed throught the
 * the function parameters. There is only one argument that needs to be used, so the arguments[0] recieves from the bytecode+offset
 * one byte. The funct variable recieves the instruction to be executed.
 * @Parameters char *bytecode, int offset, int pc, int opcode, char name(from the instruction), int (*func) Instruction
 * @Return Struct Instruction with all the arguments initialized
 */
Instruction* getOneArgInstr(u1* bytecode, int* offset, int pc, int opcode, char* name);

/**
 * @Brief It initializes the struct instruction with all its variables. In this case, the arguments[0] and arguments[1] are one byte read from the bytecode each.
 * @Description
 * The function simply allocates memory space for the instructions and sets its variables with the parameters passed throught the
 * the function parameters. The instruction needs 2 arguments, so the arguments[0] recieves from the bytecode+offset
 * one byte and and arguments[1] recieves from the bytecode+offset+1 one byte aswell.
 * The funct variable recieves the instruction to be executed.
 * @Parameters char *bytecode, int offset, int pc, int opcode, char name(from the instruction), int (*func) Instruction
 * @Return Struct Instruction with all the arguments initialized
 */
Instruction* getTwoArgsInstr(u1* bytecode, int* offset, int pc, int opcode, char* name);

#endif // _EXECUTE_H

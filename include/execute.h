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
 * @Brief Run the JVM
 * @Description
 * Through a loop, execute all the methods into the .class
 * @Parameters the .class class
 * @Return
 */
void run(Class class);

/**
 * @Brief Return a method into the constant pool by its name
 * @Description
 * Through a loop, get the methods into the .class constant pool if exists, else
 * returns NULL
 * @Parameters Class* class, char* methodName
 * @Return Method* representing the method
 */
Method* getMethod(Class *class, char *methodName);

/**
 * @Brief Return the code of a method
 * @Description
 * Through a loop, get the method's code into the .class constant pool if exists, else
 * returns NULL
 * @Parameters Method* method, ConstPool* constantPool
 * @Return CodeAttribute* representing the method's code
 */
CodeAttribute* getCodeAttr(Method* method, ConstPool* constantPool);

/**
 * @Brief Execute a method
 * @Description
 * Through a loop, execute all the instructions of the method
 * @Parameters Method *method and the .class class
 * @Return
 */
void executeMethod(Method* method, Class class);

/**
 * @Brief Set Instruction parmams by its opcode
 * @Description
 * Through a switch case, it sets an Instruction depending on
 * the number of arguments.
 * @Parameters char *byteCode, an int offset and an int mode
 * @Return Instruction*
 */
Instruction* decode(uint8_t* byteCode, int* offset, int mode);

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

/**
 * @Brief Set the Instruction instance with three arguments.
 * @Description
 * Sets all fields of the instance Instruction to be returned.
 * @Parameters char *bytecode, int offset, int pc, int opcode, char name(from the instruction), int (*func) Instruction
 * @Return Instruction*
 */

Instruction* readThreeArgs(uint8_t* bytecode, int* offset, int pc, int opcode, char* name);

/**
 * @Brief Set the Instruction instance with four arguments.
 * @Description
 * Sets all fields of the instance Instruction to be returned.
 * @Parameters char *bytecode, int offset, int pc, int opcode, char name(from the instruction), int (*func) Instruction
 * @Return Instruction*
 */
Instruction* readFourArgs(uint8_t* bytecode, int* offset, int pc, int opcode, char* name);

#endif // _EXECUTE_H

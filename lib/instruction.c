 /**
 * @file instruction.c
 * @brief Source file of instruction.h.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * @todo Description
 */

#include "instruction.h"

Frame* createFrame(Class* currentClass, CodeAttribute* codeAttribute, Heap* heap) {

	Frame* frame = (Frame*) set_mem(sizeof(Frame));

	frame->localVariables = (uint32_t*) set_mem(codeAttribute->max_locals * sizeof(uint32_t));

	frame->operandStack = (Stack*) set_mem(sizeof(Stack));

	frame->framesStack = (Stack*) set_mem(sizeof(Stack));

	frame->runtimeConstantPool = currentClass->constant_pool;

	frame->codeAttribute = codeAttribute;

	frame->currentClass = currentClass;

	frame->heap = heap;

	return frame;
}

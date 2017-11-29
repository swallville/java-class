 /**
 * @file instruction.c
 * @brief Source file of instruction.h.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * @todo Description
 */

#include "instruction.hpp"

Frame* createFrame(Class* currentClass, CodeAttribute* codeAttribute, Heap* heap) {

	Frame* frame = (Frame*) set_mem(sizeof(Frame));

	frame->runtimeConstantPool = currentClass->constant_pool;

	frame->codeAttribute = codeAttribute;

	frame->currentClass = currentClass;

	frame->heap = heap;

	frame->codeIndexRef = 0;

	return frame;
}

/**
 * @file execute.c
 * @brief Execution operations library source.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * Definitions for all the execute.h functions
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "execute.hpp"
#include "mem-manager.hpp"
#include "all-instructions.hpp"

void run(Class classe){
	/*Method* initMethod = getMethod(&classe, (char*)"<init>");
	if (initMethod != NULL) {
		heap = InicializaHeap();
		(void)InsereListaDeClasses(&heap->listaDeClasses, &classe);

		prepareMethod(initMethod, &classe, frames_stack, &heap);

		if (!frames_stack.empty()) {
			executeMethod(initMethod, classe, frames_stack);
		}

		while (!frames_stack.empty())
	  {
	     frames_stack.pop();
	  }

		desalocaHeap(heap);

		heap = NULL;
	}

	initMethod = getMethod(&classe, (char*)"<clinit>");

	if(initMethod != NULL){
<<<<<<< HEAD:lib/execute.cpp
		prepareMethod(initMethod, &classe, frames_stack, &heap);
		(void)InsereListaDeClasses(&heap->listaDeClasses, &classe);

		if (!frames_stack.empty()) {
			executeMethod(initMethod, classe, frames_stack);
		}

		while (!frames_stack.empty())
	  {
	     frames_stack.pop();
	  }

		desalocaHeap(heap);
		heap = NULL;
	}*/

	Method* mainMethod = getMethod(&classe, (char*)"main");

	if (mainMethod != NULL) {
		Heap* heap = InicializaHeap();

		std::stack<Frame*> frames_stack;

		(void)InsereListaDeClasses(&heap->listaDeClasses, &classe);

		prepareMethod(mainMethod, &classe, frames_stack, &heap);

		if (!frames_stack.empty()) {
			executeMethod(mainMethod, classe, frames_stack);
		}

		while (!frames_stack.empty())
	  {
	     frames_stack.pop();
	  }
	}

	printf("|==============================================================|\n");
	printf(" Program exited with CODE 0\n");

	return;
}

Method* getMethod(Class *classe, char *methodName){
	for (int i = 0; i < classe->methods_count; i++) {
		char* name = getUtf8FromConstantPool(classe->methods[i].name_index, classe->constant_pool);

		if (strcmp(methodName, name) == 0) {
			free_mem((void **) &name);
			return &classe->methods[i];
		}

		free_mem((void **) &name);
	}

	return NULL;
}

CodeAttribute* getCodeAttr(Method* method, ConstPool* constantPool) {

	CodeAttribute* code = NULL;

	for (int attrIndex = 0; attrIndex < method->attributes_count; attrIndex++) {

		char* name = getUtf8FromConstantPool(method->attributes[attrIndex].attributeName_index, constantPool);

		if (strcmp(name, "Code") == 0) {
			code = (CodeAttribute*) method->attributes[attrIndex].specific_info;
		}
	}

	return code;
}

void prepareMethod(Method* method, Class *classe, std::stack<Frame*> &framesStack, Heap **heap){
	CodeAttribute* code = getCodeAttr(method, classe->constant_pool);

	Frame* frame = createFrame(classe, code, (*heap));

	if (frame != NULL) {
		framesStack.push(frame);

		//printf("Frame created with codeIndexRef %d\n", framesStack.top()->codeIndexRef);
	}
}

void executeMethod(Method* method, Class classe, std::stack<Frame*> &frames_stack) {
		//int codeIndex = 0;
		int end = 0;

		while (!end) {
			Frame* current = frames_stack.top();
			frames_stack.pop();

			//printf("frame->codeIndexRef - %d\n", current->codeIndexRef);

			//if (!frames_stack.empty()) {
				//printf("frame->codeIndexRef at top - %d\n", frames_stack.top()->codeIndexRef);
			//}

			end = run_instr(current->codeAttribute->code, &current->codeIndexRef, current, frames_stack);

			if(!end) {
				frames_stack.push(current);
				//printf("Pushing back into stack\n");
      } else {
				free_mem( (void**) &current);
				//printf("destroying the frame\n");
      }

			/*if (end) {
				//frames_stack.pop();
				free_mem( (void**) &current);
				printf("destroying the frame\n");
			}*/

		}

	return;
}

int run_instr(uint8_t* code, int* offset, Frame *frame, std::stack<Frame*> &framesStack) {
	// OBS: codeIndexRef act as the frame PC + 1 (the actual index into the CodeAttribute).
	while (frame->codeIndexRef < frame->codeAttribute->codeLength) {
        Instruction* instr = decode(frame->codeAttribute->code, &frame->codeIndexRef, 0, frame, framesStack);
				//printf("Name - %s\n", instr->name);
				if (instr != NULL) {
					free_mem( (void**) &instr);
				}
  }
	return 1;
}


Instruction* decode(uint8_t* bytecode, int* offset, int mode, Frame *frame, std::stack<Frame*> &framesStack) {
	Instruction* runtime_instr = NULL;

	uint32_t nuint32_t = 0;
  uint16_t nu2 = 0;
  uint8_t index = 0, index2 = 0, inc = 0, type = 0, constbyte1 = 0, constbyte2 = 0;
  uint8_t branch1 = 0, branch2 = 0, branch3 = 0, branch4 = 0, dimensions = 0;
  int contagem = 0, zero = 0, zero_1 = 0, zero_2 = 0, opcode1 = 0;

	int32_t defaultbyte;
	uint32_t i, byte1, byte2, byte3, byte4;

	int pc = (*offset);
	int position = (*offset)++;

	//printf("Position - %d\n", frame->codeIndexRef);

	int opcode = bytecode[position];

	ConstPool *constant_pool = NULL;

	if (mode == 0) {
		constant_pool = frame->runtimeConstantPool;
	}

	switch (opcode) {
		case NOP:
		{
			if (mode == 0) {
				i_nop();
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"nop");
		}

		case ACONST_NULL:
		{
			if (mode == 0) {
				i_aconst_null(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"aconst_null");
		}

		case ICONST_M1:
		{
			if (mode == 0) {
				i_iconst_m1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iconst_m1");
		}

		case ICONST_0:
		{
			if (mode == 0) {
				i_iconst_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iconst_0");
		}

		case ICONST_1:
		{
			if (mode == 0) {
				i_iconst_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iconst_1");
		}

		case ICONST_2:
		{
			if (mode == 0) {
				i_iconst_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iconst_2");
		}

		case ICONST_3:
		{
			if (mode == 0) {
				i_iconst_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iconst_3");
		}

		case ICONST_4:
		{
			if (mode == 0) {
				i_iconst_4(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iconst_4");
		}

		case ICONST_5:
		{
			if (mode == 0) {
				i_iconst_5(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iconst_5");
		}

		case LCONST_0:
		{
			if (mode == 0) {
				i_lconst_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lconst_0");
		}

		case LCONST_1:
		{
			if (mode == 0) {
				i_lconst_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lconst_1");
		}

		case FCONST_0:
		{
			if (mode == 0) {
				i_fconst_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fconst_0");
		}

		case FCONST_1:
		{
			if (mode == 0) {
				i_fconst_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fconst_1");
		}

		case FCONST_2:
		{
			if (mode == 0) {
				i_fconst_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fconst_2");
		}

		case DCONST_0:
		{
			if (mode == 0) {
				i_dconst_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dconst_0");
		}

		case DCONST_1:
		{
			if (mode == 0) {
				i_dconst_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dconst_1");
		}

		case BIPUSH:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"bipush");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				nuint32_t = (uint32_t) (index);

				i_bipush(frame, &nuint32_t);
			}

			return runtime_instr;
		}

		case SIPUSH:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"sipush");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];
				nu2 = ((uint8_t)index << 8 | (uint8_t)index2);

				i_sipush(frame, &nu2);
			}

			return runtime_instr;
		}

		case LDC:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"ldc");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

	    	i_ldc(frame, index, constant_pool);
			}

			return runtime_instr;
		}

		case LDC_W:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"ldc_w");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
	      index2 = runtime_instr->arguments[1];

	      i_ldc_w(frame, index, index2, constant_pool);
			}

			return runtime_instr;
		}

		case LDC2_W:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"ldc2_w");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
	      index2 = runtime_instr->arguments[1];

	      i_ldc2_w(frame, index, index2, constant_pool);
			}

			return runtime_instr;
		}

		case ILOAD:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"iload");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_iload(frame, index);
			}

			return runtime_instr;
		}

		case LLOAD:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"lload");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_lload(frame, index);
			}

			return runtime_instr;
		}

		case FLOAD:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"fload");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_fload(frame, index);
			}

			return runtime_instr;
		}

		case DLOAD:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"dload");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_dload(frame, index);
			}

			return runtime_instr;
		}

		case ALOAD:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"aload");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_aload(frame, index);
			}

			return runtime_instr;
		}

		case ILOAD_0:
		{
			if (mode == 0) {
				i_iload_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iload_0");
		}

		case ILOAD_1:
		{
			if (mode == 0) {
				i_iload_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iload_1");
		}

		case ILOAD_2:
		{
			if (mode == 0) {
				i_iload_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iload_2");
		}

		case ILOAD_3:
		{
			if (mode == 0) {
				i_iload_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iload_3");
		}

		case LLOAD_0:
		{
			if (mode == 0) {
				i_lload_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lload_0");
		}

		case LLOAD_1:
		{
			if (mode == 0) {
				i_lload_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lload_1");
		}

		case LLOAD_2:
		{
			if (mode == 0) {
				i_lload_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lload_2");
		}

		case LLOAD_3:
		{
			if (mode == 0) {
				i_lload_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lload_3");
		}

		case FLOAD_0:
		{
			if (mode == 0) {
				i_fload_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fload_0");
		}

		case FLOAD_1:
		{
			if (mode == 0) {
				i_fload_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fload_1");
		}

		case FLOAD_2:
		{
			if (mode == 0) {
				i_fload_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fload_2");
		}

		case FLOAD_3:
		{
			if (mode == 0) {
				i_fload_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fload_3");
		}

		case DLOAD_0:
		{
			if (mode == 0) {
				i_dload_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dload_0");
		}

		case DLOAD_1:
		{
			if (mode == 0) {
				i_dload_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dload_1");
		}

		case DLOAD_2:
		{
			if (mode == 0) {
				i_dload_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dload_2");
		}

		case DLOAD_3:
		{
			if (mode == 0) {
				i_dload_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dload_3");
		}

		case ALOAD_0:
		{
			if (mode == 0) {
				i_aload_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"aload_0");
		}

		case ALOAD_1:
		{
			if (mode == 0) {
				i_aload_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"aload_1");
		}

		case ALOAD_2:
		{
			if (mode == 0) {
				i_aload_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"aload_2");
		}

		case ALOAD_3:
		{
			if (mode == 0) {
				i_aload_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"aload_3");
		}

		case IALOAD:
		{
			if (mode == 0) {
				i_iaload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iaload");
		}

		case LALOAD:
		{
			if (mode == 0) {
				i_laload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"laload");
		}

		case FALOAD:
		{
			if (mode == 0) {
				i_faload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"faload");
		}

		case DALOAD:
		{
			if (mode == 0) {
				i_daload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"daload");
		}

		case AALOAD:
		{
			if (mode == 0) {
				i_aaload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"aaload");
		}

		case BALOAD:
		{
			if (mode == 0) {
				i_baload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"baload");
		}

		case CALOAD:
		{
			if (mode == 0) {
				i_caload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"caload");
		}

		case SALOAD:
		{
			if (mode == 0) {
				i_saload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"saload");
		}

		case ISTORE:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"istore");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_istore(frame, index);
			}

			return runtime_instr;
		}

		case LSTORE:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"lstore");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_lstore(frame, index);
			}

			return runtime_instr;
		}

		case FSTORE:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"fstore");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_fstore(frame, index);
			}

			return runtime_instr;
		}

		case DSTORE:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"dstore");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_dstore(frame, index);
			}

			return runtime_instr;
		}

		case ASTORE:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"astore");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_astore(frame, index);
			}

			return runtime_instr;
		}

		case ISTORE_0:
		{
			if (mode == 0) {
				i_istore_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"istore_0");
		}

		case ISTORE_1:
		{
			if (mode == 0) {
				i_istore_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"istore_1");
		}

		case ISTORE_2:
		{
			if (mode == 0) {
				i_istore_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"istore_2");
		}

		case ISTORE_3:
		{
			if (mode == 0) {
				i_istore_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"istore_3");
		}

		case LSTORE_0:
		{
			if (mode == 0) {
				i_lstore_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lstore_0");
		}

		case LSTORE_1:
		{
			if (mode == 0) {
				i_lstore_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lstore_1");
		}

		case LSTORE_2:
		{
			if (mode == 0) {
				i_lstore_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lstore_2");
		}

		case LSTORE_3:
		{
			if (mode == 0) {
				i_lstore_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lstore_3");
		}

		case FSTORE_0:
		{
			if (mode == 0) {
				i_fstore_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fstore_0");
		}

		case FSTORE_1:
		{
			if (mode == 0) {
				i_fstore_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fstore_1");
		}

		case FSTORE_2:
		{
			if (mode == 0) {
				i_fstore_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fstore_2");
		}

		case FSTORE_3:
		{
			if (mode == 0) {
				i_fstore_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fstore_3");
		}

		case DSTORE_0:
		{
			if (mode == 0) {
				i_dstore_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dstore_0");
		}

		case DSTORE_1:
		{
			if (mode == 0) {
				i_dstore_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dstore_1");
		}

		case DSTORE_2:
		{
			if (mode == 0) {
				i_dstore_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dstore_2");
		}

		case DSTORE_3:
		{
			if (mode == 0) {
				i_dstore_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dstore_3");
		}

		case ASTORE_0:
		{
			if (mode == 0) {
				i_astore_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"astore_0");
		}

		case ASTORE_1:
		{
			if (mode == 0) {
				i_astore_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"astore_1");
		}

		case ASTORE_2:
		{
			if (mode == 0) {
				i_astore_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"astore_2");
		}

		case ASTORE_3:
		{
			if (mode == 0) {
				i_astore_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"astore_3");
		}

		case IASTORE:
		{
			if (mode == 0) {
				i_iastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iastore");
		}

		case LASTORE:
		{
			if (mode == 0) {
				i_lastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lastore");
		}

		case FASTORE:
		{
			if (mode == 0) {
				i_fastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fastore");
		}

		case DASTORE:
		{
			if (mode == 0) {
				i_dastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dastore");
		}

		case AASTORE:
		{
			if (mode == 0) {
				i_aastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"aastore");
		}

		case BASTORE:
		{
			if (mode == 0) {
				i_bastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"bastore");
		}

		case CASTORE:
		{
			if (mode == 0) {
				i_castore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"castore");
		}

		case SASTORE:
		{
			if (mode == 0) {
				i_sastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"sastore");
		}

		case POP:
		{
			if (mode == 0) {
				i_pop(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"pop");
		}

		case POP2:
		{
			if (mode == 0) {
				i_pop2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"pop2");
		}

		case DUP:
		{
			if (mode == 0) {
				i_dup(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dup");
		}

		case DUP_X1:
		{
			if (mode == 0) {
				i_dup_x1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dup_x1");
		}

		case DUP_X2:
		{
			if (mode == 0) {
				i_dup_x2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dup_x2");
		}

		case DUP2:
		{
			if (mode == 0) {
				i_dup2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dup2");
		}

		case DUP2_X1:
		{
			if (mode == 0) {
				i_dup2_x1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dup2_x1");
		}

		case DUP2_X2:
		{
			if (mode == 0) {
				i_dup2_x2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dup2_x2");
		}

		case SWAP:
		{
			if (mode == 0) {
				i_swap(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"swap");
		}

		case IADD:
		{
			if (mode == 0) {
				i_iadd(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iadd");
		}

		case LADD:
		{
			if (mode == 0) {
				i_ladd(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"ladd");
		}

		case FADD:
		{
			if (mode == 0) {
				i_fadd(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fadd");
		}

		case DADD:
		{
			if (mode == 0) {
				i_dadd(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dadd");
		}

		case ISUB:
		{
			if (mode == 0) {
				i_isub(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"isub");
		}

		case LSUB:
		{
			if (mode == 0) {
				i_lsub(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lsub");
		}

		case FSUB:
		{
			if (mode == 0) {
				i_fsub(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fsub");
		}

		case DSUB:
		{
			if (mode == 0) {
				i_dsub(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dsub");
		}

		case IMUL:
		{
			if (mode == 0) {
				i_imul(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"imul");
		}

		case LMUL:
		{
			if (mode == 0) {
				i_lmul(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lmul");
		}

		case FMUL:
		{
			if (mode == 0) {
				i_fmul(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fmul");
		}

		case DMUL:
		{
			if (mode == 0) {
				i_dmul(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dmul");
		}

		case IDIV:
		{
			if (mode == 0) {
				i_idiv(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"idiv");
		}

		case LDIV:
		{
			if (mode == 0) {
				i_ldiv(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"ldiv");
		}

		case FDIV:
		{
			if (mode == 0) {
				i_fdiv(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fdiv");
		}

		case DDIV:
		{
			if (mode == 0) {
				i_ddiv(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"ddiv");
		}

		case IREM:
		{
			if (mode == 0) {
				i_irem(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"irem");
		}

		case LREM:
		{
			if (mode == 0) {
				i_lrem(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lrem");
		}

		case FREM:
		{
			if (mode == 0) {
				i_frem(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"frem");
		}

		case DREM:
		{
			if (mode == 0) {
				i_drem(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"drem");
		}

		case INEG:
		{
			if (mode == 0) {
				i_ineg(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"ineg");
		}

		case LNEG:
		{
			if (mode == 0) {
				i_lneg(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lneg");
		}

		case FNEG:
		{
			if (mode == 0) {
				i_fneg(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fneg");
		}

		case DNEG:
		{
			if (mode == 0) {
				i_dneg(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dneg");
		}

		case ISHL:
		{
			if (mode == 0) {
				i_ishl(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"ishl");
		}

		case LSHL:
		{
			if (mode == 0) {
				i_lshl(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lshl");
		}

		case ISHR:
		{
			if (mode == 0) {
				i_ishr(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"ishr");
		}

		case LSHR:
		{
			if (mode == 0) {
				i_lshr(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lshr");
		}

		case IUSHR:
		{
			if (mode == 0) {
				i_iushr(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iushr");
		}

		case LUSHR:{
			if (mode == 0) {
				i_lushr(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lushr");
		}

		case IAND:
		{
			if (mode == 0) {
				i_iand(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"iand");
		}

		case LAND:
		{
			if (mode == 0) {
				i_land(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"land");
		}

		case IOR:
		{
			if (mode == 0) {
				i_ior(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"ior");
		}

		case LOR:
		{
			if (mode == 0) {
				i_lor(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lor");
		}

		case IXOR:
		{
			if (mode == 0) {
				i_ixor(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"ixor");
		}

		case LXOR:
		{
			if (mode == 0) {
				i_lxor(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lxor");
		}

		case IINC:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"iinc");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				inc = runtime_instr->arguments[1];

				i_iinc(frame, index, inc);
			}

			return runtime_instr;
		}

		case I2L:
		{
			if (mode == 0) {
				i_i2l(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"i2l");
		}

		case I2F:
		{
			if (mode == 0) {
				i_i2f(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"i2f");
		}

		case I2D:
		{
			if (mode == 0) {
				i_i2d(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"i2d");
		}

		case L2I:
		{
			if (mode == 0) {
				i_l2i(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"l2i");
		}

		case L2F:
		{
			if (mode == 0) {
				i_l2f(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"l2f");
		}

		case L2D:
		{
			if (mode == 0) {
				i_l2d(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"l2d");
		}

		case F2I:
		{
			if (mode == 0) {
				i_f2i(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"f2i");
		}

		case F2L:
		{
			if (mode == 0) {
				i_f2l(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"f2l");
		}

		case F2D:
		{
			if (mode == 0) {
				i_f2d(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"f2d");
		}

		case D2I:
		{
			if (mode == 0) {
				i_d2i(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"d2i");
		}

		case D2L:
		{
			if (mode == 0) {
				i_d2l(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"d2l");
		}

		case D2F:
		{
			if (mode == 0) {
				i_d2f(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"d2f");
		}

		case I2B:
		{
			if (mode == 0) {
				i_i2b(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"i2b");
		}

		case I2C:
		{
			if (mode == 0) {
				i_i2c(frame);
			}
			return readNoArgs(bytecode, offset, pc, opcode, (char*)"i2c");
		}

		case I2S:
		{
			if (mode == 0) {
				i_i2s(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"i2s");
		}

		case LCMP:
		{
			if (mode == 0) {
				i_lcmp(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lcmp");
		}

		case FCMPL:
		{
			if (mode == 0) {
				i_fcmpl(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fcmpl");
		}

		case FCMPG:
		{
			if (mode == 0) {
				i_fcmpg(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"fcmpg");
		}

		case DCMPL:
		{
			if (mode == 0) {
				i_dcmpl(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dcmpl");
		}

		case DCMPG:
		{
			if (mode == 0) {
				i_dcmpg(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dcmpg");
		}

		case IFEQ:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"ifeq");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_ifeq(frame, index, index2);
			}

			return runtime_instr;
		}

		case IFNE:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"ifne");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_ifne(frame, index, index2);
			}

			return runtime_instr;
		}

		case IFLT:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"iflt");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_iflt(frame, index, index2);
			}

			return runtime_instr;
		}

		case IFGE:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"ifge");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_ifge(frame, index, index2);
			}

			return runtime_instr;
		}

		case IFGT:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"ifgt");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_ifgt(frame, index, index2);
			}

			return runtime_instr;
		}

		case IFLE:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"ifle");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_ifle(frame, index, index2);
			}

			return runtime_instr;
		}

		case IF_ICMPEQ:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"if_icmpeq");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_icmpeq(frame, index, index2);
			}

			return runtime_instr;
		}

		case IF_ICMPNE:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"if_icmpne");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_icmpne(frame, index, index2);
			}

			return runtime_instr;
		}

		case IF_ICMPLT:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"if_icmplt");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_icmplt(frame, index, index2);
			}

			return runtime_instr;
		}

		case IF_ICMPGE:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"if_icmpge");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_icmpge(frame, index, index2);
			}

			return runtime_instr;
		}

		case IF_ICMPGT:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"if_icmpgt");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_icmpgt(frame, index, index2);
			}

			return runtime_instr;
		}

		case IF_ICMPLE:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"if_icmple");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_icmple(frame, index, index2);
			}

			return runtime_instr;
		}

		case IF_ACMPEQ:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"if_acmpeq");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_acmpeq(frame, index, index2);
			}

			return runtime_instr;
		}

		case IF_ACMPNE:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"if_acmpne");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_acmpne(frame, index, index2);
			}

			return runtime_instr;
		}

		case GOTO:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"goto");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_goto(frame, index, index2);
			}

			return runtime_instr;
		}

		case JSR:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"jsr");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_jsr(frame, index, index2);
			}

			return runtime_instr;
		}

		case RET:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"ret");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_ret(frame, index);
			}

			return runtime_instr;
		}

		case TABLESWITCH:
		{
			runtime_instr = (Instruction*) set_mem(sizeof(Instruction));
			runtime_instr->pc = pc;
			runtime_instr->opcode = opcode;
			runtime_instr->name = (char*)"tableswitch";

			int32_t high, low;
			int32_t *tableswitch;
			uint32_t enderecotable = (*offset);
			int32_t tableSize;

			while(((*offset) + 1) % 4 != 0) {
			 (*offset)++;
			}

			(*offset)++;

			byte1 = bytecode[(*offset)++];
			byte2 = bytecode[(*offset)++];
			byte3 = bytecode[(*offset)++];
			byte4 = bytecode[(*offset)++];
			defaultbyte = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));

			byte1 = bytecode[(*offset)++];
			byte2 = bytecode[(*offset)++];
			byte3 = bytecode[(*offset)++];
			byte4 = bytecode[(*offset)++];
			low = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));

			byte1 = bytecode[(*offset)++];
			byte2 = bytecode[(*offset)++];
			byte3 = bytecode[(*offset)++];
			byte4 = bytecode[(*offset)++];
			high = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));

			tableSize = high - low + 1;
			tableswitch = (int32_t*)calloc(sizeof(int32_t), tableSize);

			runtime_instr->arguments_count = tableSize + 1;
			runtime_instr->arguments = NULL;
			runtime_instr->dynamic_arguments = (int32_t*) set_mem((tableSize + 1) * sizeof(int32_t));

			runtime_instr->dynamic_arguments[tableSize] = defaultbyte;

			for(i = 0; i < tableSize; i++) 	{
				byte1 = bytecode[(*offset)++];
				byte2 = bytecode[(*offset)++];
				byte3 = bytecode[(*offset)++];
				byte4 = bytecode[(*offset)++];

				tableswitch[i] = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));
				runtime_instr->dynamic_arguments[i] = tableswitch[i];
			}

			if (mode == 0) {
				i_tableswitch(frame, enderecotable, high, low, defaultbyte, tableswitch);
			}

			free(tableswitch);

			return runtime_instr;
		}

		case LOOKUPSWITCH:
		{
			runtime_instr = (Instruction*) set_mem(sizeof(Instruction));
			runtime_instr->pc = pc;
			runtime_instr->opcode = opcode;
			runtime_instr->name = (char*)"lookupswitch";

			int32_t npairs;
			int32_t *match, *offset_table;
			uint32_t enderecolookup = (*offset);

			while(((*offset) + 1) % 4 != 0) {
				(*offset)++;
			}
			(*offset)++;

			byte1 = bytecode[(*offset)++];
			byte2 = bytecode[(*offset)++];
			byte3 = bytecode[(*offset)++];
			byte4 = bytecode[(*offset)++];
			defaultbyte = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));

			byte1 = bytecode[(*offset)++];
			byte2 = bytecode[(*offset)++];
			byte3 = bytecode[(*offset)++];
			byte4 = bytecode[(*offset)++];
			npairs = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));

			match = (int32_t*)calloc(sizeof(int32_t), npairs);
			offset_table = (int32_t*)calloc(sizeof(int32_t), npairs);

			runtime_instr->arguments_count = (2 * npairs) + 1;
			runtime_instr->arguments = NULL;
			runtime_instr->dynamic_arguments = (int32_t*) set_mem(((2 * npairs) + 1) * sizeof(int32_t));

			runtime_instr->dynamic_arguments[(2 * npairs)] = defaultbyte;

			int j = 0;

			for(i = 0; i < npairs; i++, j++) {
				byte1 = bytecode[(*offset)++];
				byte2 = bytecode[(*offset)++];
				byte3 = bytecode[(*offset)++];
				byte4 = bytecode[(*offset)++];
				match[i] = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));
				runtime_instr->dynamic_arguments[j] = match[i];

				byte1 = bytecode[(*offset)++];
				byte2 = bytecode[(*offset)++];
				byte3 = bytecode[(*offset)++];
				byte4 = bytecode[(*offset)++];
				offset_table[i] = (int32_t)(((byte1) << 24) |((byte2) << 16) |((byte3) << 8) |(byte4));
				j++;
				runtime_instr->dynamic_arguments[j] = offset_table[i];
			}

			if (mode == 0) {
				i_lookupswitch(frame, npairs, enderecolookup, defaultbyte, match, offset_table);
			}

			free(match);
			free(offset_table);

			return runtime_instr;
		}

		case IRETURN:
		{
			if (mode == 0) {
				i_ireturn(frame, framesStack);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"ireturn");
		}

		case LRETURN:
		{
			if (mode == 0) {
				i_lreturn(frame, framesStack);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"lreturn");
		}

		case FRETURN:
		{
			if (mode == 0) {
				i_freturn(frame, framesStack);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"freturn");
		}

		case DRETURN:
		{
			if (mode == 0) {
				i_dreturn(frame, framesStack);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"dreturn");
		}

		case ARETURN:
		{
			if (mode == 0) {
				i_areturn(frame, framesStack);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"areturn");
		}

		case RETURN:
		{
			if (mode == 0) {
				i_return(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"return");
		}

		case GETSTATIC:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"getstatic");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_getstatic(frame, frame->heap->listaStaticField, frame->heap->listaDeClasses, index, index2);
			}

			return runtime_instr;
		}

		case PUTSTATIC:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"putstatic");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_putstatic(frame, frame->heap->listaStaticField, frame->heap->listaDeClasses, index, index2);
			}

			return runtime_instr;
		}

		case GETFIELD:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"getfield");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_getfield(frame, index, index2);
			}

			return runtime_instr;
		}

		case PUTFIELD:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"putfield");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_putfield(frame, index, index2);
			}

			return runtime_instr;
		}

		case INVOKEVIRTUAL:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"invokevirtual");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_invokevirtual(frame, framesStack, frame->heap->listaDeClasses, index, index2, frame->heap);
			}

			return runtime_instr;
		}

		case INVOKESPECIAL:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"invokespecial");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_invokespecial(frame, framesStack, frame->heap->listaDeClasses, index, index2, frame->heap);
			}

			return runtime_instr;
		}

		case INVOKESTATIC:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"invokestatic");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_invokestatic(frame, framesStack, frame->heap->listaDeClasses, index, index2, frame->heap);
			}

			return runtime_instr;
		}

		case INVOKEINTERFACE:
		{
			runtime_instr = readFourArgs(bytecode, offset, pc, opcode, (char*)"invokeinterface");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];
				contagem = runtime_instr->arguments[2];
				zero = runtime_instr->arguments[3];

				i_invokeinterface(frame, framesStack, frame->heap->listaDeClasses, index, index2, contagem, zero, frame->heap);
			}

			return runtime_instr;
		}

		case INVOKEDYNAMIC:
		{
			runtime_instr = readFourArgs(bytecode, offset, pc, opcode, (char*)"invokedynamic");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];
				zero_1 = runtime_instr->arguments[2];
				zero_2 = runtime_instr->arguments[3];

				i_invokedynamic(frame, framesStack, frame->heap->listaDeClasses, index, index2, zero_1, zero_2, frame->heap);
			}

			return runtime_instr;
		}

		case NEW:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"new");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_new(frame, index, index2, frame->heap->listaDeClasses);
			}

			return runtime_instr;
		}

		case NEWARRAY:
		{
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, (char*)"newarray");

			if (mode == 0) {
				type = runtime_instr->arguments[0];

			 	i_newarray(frame, type);
			}

			return runtime_instr;
		}

		case ANEWARRAY:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"anewarray");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_anewarray(frame, index, index2);
			}

			return runtime_instr;
		}

		case ARRAYLENGTH:
		{
			if (mode == 0) {
				i_arraylength(frame);
			}
			return readNoArgs(bytecode, offset, pc, opcode, (char*)"arraylength");
		}

		case ATHROW:
		{
			if (mode == 0) {
				i_athrow(frame);
			}
			return readNoArgs(bytecode, offset, pc, opcode, (char*)"athrow");
		}

		case CHECKCAST:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"checkcast");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_checkcast(frame, index, index2);
			}

			return runtime_instr;
		}

		case INSTANCEOF:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"instanceof");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_instanceof(frame, index, index2);
			}

			return runtime_instr;
		}

		case MONITORENTER:
		{
			if (mode == 0) {
				i_monitorenter(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"monitorenter");
		}

		case MONITOREXIT:
		{
			if (mode == 0) {
				i_monitorexit(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, (char*)"monitorexit");
		}

		case WIDE:
		{
			runtime_instr = readFourArgs(bytecode, offset, pc, opcode, (char*)"wide");

			if (mode == 0) {
				opcode1 = runtime_instr->opcode;
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];
				constbyte1 = runtime_instr->arguments[2];
				constbyte2 = runtime_instr->arguments[3];

				i_wide(frame, opcode1, index, index2, constbyte1, constbyte2);
			}

			return runtime_instr;
		}

		case MULTIANEWARRAY:
		{
			runtime_instr = readThreeArgs(bytecode, offset, pc, opcode, (char*)"multianewarray");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];
				dimensions = runtime_instr->arguments[2];

				i_multianewarray(frame, index, index2, dimensions);
			}

			return runtime_instr;
		}

		case IFNULL:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"ifnull");

			if (mode == 0) {
				branch1 = runtime_instr->arguments[0];
				branch2 = runtime_instr->arguments[1];

				i_ifnull(frame, branch1, branch2);
			}

			return runtime_instr;
		}

		case IFNONNULL:
		{
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, (char*)"ifnonnull");

			if (mode == 0) {
				branch1 = runtime_instr->arguments[0];
				branch2 = runtime_instr->arguments[1];

				i_ifnonnull(frame, branch1, branch2);
			}

			return runtime_instr;
		}

		case GOTO_W:
		{
			runtime_instr = readFourArgs(bytecode, offset, pc, opcode, (char*)"goto_w");

			if (mode == 0) {
				branch1 = runtime_instr->arguments[0];
				branch2 = runtime_instr->arguments[1];
				branch3 = runtime_instr->arguments[2];
				branch4 = runtime_instr->arguments[3];

				i_goto_w(frame, branch1, branch2, branch3, branch4);
			}

			return runtime_instr;
		}

		case JSR_W:
		{
			runtime_instr = readFourArgs(bytecode, offset, pc, opcode, (char*)"jsr_w");

			if (mode == 0) {
				branch1 = runtime_instr->arguments[0];
				branch2 = runtime_instr->arguments[1];
				branch3 = runtime_instr->arguments[2];
				branch4 = runtime_instr->arguments[3];

				i_jsr_w(frame, branch1, branch2, branch3, branch4);
			}

			return runtime_instr;
		}
		default:
		{
			return NULL;
		}
	}
}

Instruction* readNoArgs(uint8_t* bytecode, int* offset, int pc, int opcode, char* name) {
	Instruction* instr = (Instruction*) set_mem(sizeof(Instruction));
	instr->pc = pc;
	instr->opcode = opcode;
	instr->name = name;
	instr->arguments_count = 0;
	instr->dynamic_arguments = NULL;
	instr->arguments = NULL;
	return instr;
}

Instruction* readOneArg(uint8_t* bytecode, int* offset, int pc, int opcode, char* name) {
	Instruction* instr = (Instruction*) set_mem(sizeof(Instruction));
	instr->pc = pc;
	instr->opcode = opcode;
	instr->name = name;
	instr->arguments_count = 1;
	instr->dynamic_arguments = NULL;
	instr->arguments = (int8_t*) set_mem(1 * sizeof(int8_t));
	instr->arguments[0] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	return instr;
}

Instruction* readTwoArgs(uint8_t* bytecode, int* offset, int pc, int opcode, char* name) {
	Instruction* instr = (Instruction*) set_mem(sizeof(Instruction));
	instr->pc = pc;
	instr->opcode = opcode;
	instr->name = name;
	instr->arguments_count = 2;
	instr->dynamic_arguments = NULL;
	instr->arguments = (int8_t*) set_mem(2 * sizeof(int8_t));
	instr->arguments[0] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	instr->arguments[1] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	return instr;
}

Instruction* readThreeArgs(uint8_t* bytecode, int* offset, int pc, int opcode, char* name) {
	Instruction* instr = (Instruction*) set_mem(sizeof(Instruction));
	instr->pc = pc;
	instr->opcode = opcode;
	instr->name = name;
	instr->arguments_count = 3;
	instr->dynamic_arguments = NULL;
	instr->arguments = (int8_t*) set_mem(3 * sizeof(int8_t));
	instr->arguments[0] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	instr->arguments[1] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	instr->arguments[2] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	return instr;
}

Instruction* readFourArgs(uint8_t* bytecode, int* offset, int pc, int opcode, char* name) {
	Instruction* instr = (Instruction*) set_mem(sizeof(Instruction));
	instr->pc = pc;
	instr->opcode = opcode;
	instr->name = name;
	instr->arguments_count = 4;
	instr->dynamic_arguments = NULL;
	instr->arguments = (int8_t*) set_mem(4 * sizeof(int8_t));
	instr->arguments[0] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	instr->arguments[1] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	instr->arguments[2] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	instr->arguments[3] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	return instr;
}

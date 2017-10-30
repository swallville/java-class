/**
 * @file execute.c
 * @brief Execution operations library source.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * Definitions for all the execute.h functions
 */

#include <stdio.h>
#include <string.h>
#include "execute.h"
#include "mem-manager.h"
#include "all-instructions.h"

Frame *frame;

void run(Class class){
	for (int i = (class.methods_count - 1); i != -1; i--) {
		executeMethod(&(class.methods[i]), class);
	}
	printf("|==============================================================|\n");
	printf(" Program exited with CODE 0\n");
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

void executeMethod(Method* method, Class class) {

	CodeAttribute* code = getCodeAttr(method, class.constant_pool);

	Heap* heap = InicializaHeap();

	frame = createFrame(&class, code, heap);

	int codeIndex = 0;

	frame->codeIndexRef = &codeIndex;

	push(frame, &(frame->framesStack));
	// OBS: codeIndex act as the frame PC.
	while (codeIndex < code->codeLength) {
        Instruction* instr = decode(code->code, &codeIndex, 0);
				//printf("Name - %s\n", instr->name);
        free_mem( (void**) &instr);
  }

	free_mem( (void**) &frame);
}


Instruction* decode(uint8_t* bytecode, int* offset, int mode) {
	Instruction* runtime_instr = NULL;

	uint32_t nu4 = 0;
  uint16_t nu2 = 0;
  uint8_t index = 0, index2 = 0, inc = 0, type = 0, constbyte1 = 0, constbyte2 = 0;
  uint8_t branch1 = 0, branch2 = 0, branch3 = 0, branch4 = 0, dimensions = 0;
  int contagem = 0, zero = 0, zero_1 = 0, zero_2 = 0, opcode1 = 0;

	int pc = (*offset);
	int position = (*offset)++;
	//printf("Position - %d\n", *(frame->codeIndexRef));
	int opcode = bytecode[position];

	ConstPool *constant_pool = NULL;

	if (mode == 0) {
		constant_pool = frame->runtimeConstantPool;
	}

	switch (opcode) {
		case NOP:
			if (mode == 0) {
				i_nop();
			}

			return readNoArgs(bytecode, offset, pc, opcode, "nop");

		case ACONST_NULL:
			if (mode == 0) {
				i_aconst_null(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "aconst_null");

		case ICONST_M1:
			if (mode == 0) {
				i_iconst_m1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iconst_m1");

		case ICONST_0:
			if (mode == 0) {
				i_iconst_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iconst_0");

		case ICONST_1:
			if (mode == 0) {
				i_iconst_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iconst_1");

		case ICONST_2:
			if (mode == 0) {
				i_iconst_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iconst_2");

		case ICONST_3:
			if (mode == 0) {
				i_iconst_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iconst_3");

		case ICONST_4:
			if (mode == 0) {
				i_iconst_4(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iconst_4");

		case ICONST_5:
			if (mode == 0) {
				i_iconst_5(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iconst_5");

		case LCONST_0:
			if (mode == 0) {
				i_lconst_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lconst_0");

		case LCONST_1:
			if (mode == 0) {
				i_lconst_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lconst_1");

		case FCONST_0:
			if (mode == 0) {
				i_fconst_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fconst_0");

		case FCONST_1:
			if (mode == 0) {
				i_fconst_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fconst_1");

		case FCONST_2:
			if (mode == 0) {
				i_fconst_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fconst_2");

		case DCONST_0:
			if (mode == 0) {
				i_dconst_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dconst_0");

		case DCONST_1:
			if (mode == 0) {
				i_dconst_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dconst_1");

		case BIPUSH:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "bipush");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				nu4 = (uint32_t) (index);

				i_bipush(frame, &nu4);
			}

			return runtime_instr;

		case SIPUSH:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "sipush");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];
				nu2 = ((uint8_t)index << 8 | (uint8_t)index2);

				i_sipush(frame, &nu2);
			}

			return runtime_instr;

		case LDC:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "ldc");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

	    	i_ldc(frame, index, constant_pool);
			}

			return runtime_instr;

		case LDC_W:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "ldc_w");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
	      index2 = runtime_instr->arguments[1];

	      i_ldc_w(frame, index, index2, constant_pool);
			}

			return runtime_instr;

		case LDC2_W:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "ldc2_w");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
	      index2 = runtime_instr->arguments[1];

	      i_ldc2_w(frame, index, index2, constant_pool);
			}

			return runtime_instr;

		case ILOAD:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "iload");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_iload(frame, index);
			}

			return runtime_instr;

		case LLOAD:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "lload");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_lload(frame, index);
			}

			return runtime_instr;

		case FLOAD:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "fload");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_fload(frame, index);
			}

			return runtime_instr;

		case DLOAD:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "dload");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_dload(frame, index);
			}

			return runtime_instr;

		case ALOAD:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "aload");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_aload(frame, index);
			}

			return runtime_instr;

		case ILOAD_0:
			if (mode == 0) {
				i_iload_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iload_0");

		case ILOAD_1:
			if (mode == 0) {
				i_iload_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iload_1");

		case ILOAD_2:
			if (mode == 0) {
				i_iload_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iload_2");

		case ILOAD_3:
			if (mode == 0) {
				i_iload_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iload_3");

		case LLOAD_0:
			if (mode == 0) {
				i_lload_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lload_0");

		case LLOAD_1:
			if (mode == 0) {
				i_lload_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lload_1");

		case LLOAD_2:
			if (mode == 0) {
				i_lload_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lload_2");

		case LLOAD_3:
			if (mode == 0) {
				i_lload_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lload_3");

		case FLOAD_0:
			if (mode == 0) {
				i_fload_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fload_0");

		case FLOAD_1:
			if (mode == 0) {
				i_fload_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fload_1");

		case FLOAD_2:
			if (mode == 0) {
				i_fload_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fload_2");

		case FLOAD_3:
			if (mode == 0) {
				i_fload_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fload_3");

		case DLOAD_0:
			if (mode == 0) {
				i_dload_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dload_0");

		case DLOAD_1:
			if (mode == 0) {
				i_dload_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dload_1");

		case DLOAD_2:
			if (mode == 0) {
				i_dload_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dload_2");

		case DLOAD_3:
			if (mode == 0) {
				i_dload_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dload_3");

		case ALOAD_0:
			if (mode == 0) {
				i_aload_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "aload_0");

		case ALOAD_1:
			if (mode == 0) {
				i_aload_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "aload_1");

		case ALOAD_2:
			if (mode == 0) {
				i_aload_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "aload_2");

		case ALOAD_3:
			if (mode == 0) {
				i_aload_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "aload_3");

		case IALOAD:
			if (mode == 0) {
				i_iaload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iaload");

		case LALOAD:
			if (mode == 0) {
				i_laload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "laload");

		case FALOAD:
			if (mode == 0) {
				i_faload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "faload");

		case DALOAD:
			if (mode == 0) {
				i_daload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "daload");

		case AALOAD:
			if (mode == 0) {
				i_aaload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "aaload");

		case BALOAD:
			if (mode == 0) {
				i_baload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "baload");

		case CALOAD:
			if (mode == 0) {
				i_caload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "caload");

		case SALOAD:
			if (mode == 0) {
				i_saload(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "saload");

		case ISTORE:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "istore");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_istore(frame, index);
			}

			return runtime_instr;

		case LSTORE:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "lstore");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_lstore(frame, index);
			}

			return runtime_instr;

		case FSTORE:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "fstore");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_fstore(frame, index);
			}

			return runtime_instr;

		case DSTORE:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "dstore");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_dstore(frame, index);
			}

			return runtime_instr;

		case ASTORE:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "astore");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_astore(frame, index);
			}

			return runtime_instr;

		case ISTORE_0:
			if (mode == 0) {
				i_istore_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode,"istore_0");

		case ISTORE_1:
			if (mode == 0) {
				i_istore_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode,"istore_1");

		case ISTORE_2:
			if (mode == 0) {
				i_istore_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode,"istore_2");

		case ISTORE_3:
			if (mode == 0) {
				i_istore_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode,"istore_3");

		case LSTORE_0:
			if (mode == 0) {
				i_lstore_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lstore_0");

		case LSTORE_1:
			if (mode == 0) {
				i_lstore_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lstore_1");

		case LSTORE_2:
			if (mode == 0) {
				i_lstore_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lstore_2");

		case LSTORE_3:
			if (mode == 0) {
				i_lstore_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lstore_3");

		case FSTORE_0:
			if (mode == 0) {
				i_fstore_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fstore_0");

		case FSTORE_1:
			if (mode == 0) {
				i_fstore_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fstore_1");

		case FSTORE_2:
			if (mode == 0) {
				i_fstore_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fstore_2");

		case FSTORE_3:
			if (mode == 0) {
				i_fstore_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fstore_3");

		case DSTORE_0:
			if (mode == 0) {
				i_dstore_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dstore_0");

		case DSTORE_1:
			if (mode == 0) {
				i_dstore_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dsotre_1");

		case DSTORE_2:
			if (mode == 0) {
				i_dstore_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dstore_2");

		case DSTORE_3:
			if (mode == 0) {
				i_dstore_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dstore_3");

		case ASTORE_0:
			if (mode == 0) {
				i_astore_0(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "astore_0");

		case ASTORE_1:
			if (mode == 0) {
				i_astore_1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "asotre_1");

		case ASTORE_2:
			if (mode == 0) {
				i_astore_2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "astore_2");

		case ASTORE_3:
			if (mode == 0) {
				i_astore_3(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "astore_3");

		case IASTORE:
			if (mode == 0) {
				i_iastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iastore");

		case LASTORE:
			if (mode == 0) {
				i_lastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lastore");

		case FASTORE:
			if (mode == 0) {
				i_fastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fastore");

		case DASTORE:
			if (mode == 0) {
				i_dastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dastore");

		case AASTORE:
			if (mode == 0) {
				i_aastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "aastore");

		case BASTORE:
			if (mode == 0) {
				i_bastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "bastore");

		case CASTORE:
			if (mode == 0) {
				i_castore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "castore");

		case SASTORE:
			if (mode == 0) {
				i_sastore(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "sastore");

		case POP:
			if (mode == 0) {
				i_pop(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "pop");

		case POP2:
			if (mode == 0) {
				i_pop2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "pop2");

		case DUP:
			if (mode == 0) {
				i_dup(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dup");

		case DUP_X1:
			if (mode == 0) {
				i_dup_x1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dup_x1");

		case DUP_X2:
			if (mode == 0) {
				i_dup_x2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dup_x2");

		case DUP2:
			if (mode == 0) {
				i_dup2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dup2");

		case DUP2_X1:
			if (mode == 0) {
				i_dup2_x1(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dup2_x1");

		case DUP2_X2:
			if (mode == 0) {
				i_dup2_x2(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dup2_x2");

		case SWAP:
			if (mode == 0) {
				i_swap(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "swap");

		case IADD:
			if (mode == 0) {
				i_iadd(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iadd");

		case LADD:
			if (mode == 0) {
				i_ladd(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "ladd");

		case FADD:
			if (mode == 0) {
				i_fadd(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fadd");

		case DADD:
			if (mode == 0) {
				i_dadd(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dadd");

		case ISUB:
			if (mode == 0) {
				i_isub(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "isub");

		case LSUB:
			if (mode == 0) {
				i_lsub(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lsub");

		case FSUB:
			if (mode == 0) {
				i_fsub(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fsub");

		case DSUB:
			if (mode == 0) {
				i_dsub(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dsub");

		case IMUL:
			if (mode == 0) {
				i_imul(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "imul");

		case LMUL:
			if (mode == 0) {
				i_lmul(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lmul");

		case FMUL:
			if (mode == 0) {
				i_fmul(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fmul");

		case DMUL:
			if (mode == 0) {
				i_dmul(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dmul");

		case IDIV:
			if (mode == 0) {
				i_idiv(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "idiv");

		case LDIV:
			if (mode == 0) {
				i_ldiv(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "ldiv");

		case FDIV:
			if (mode == 0) {
				i_fdiv(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fdiv");

		case DDIV:
			if (mode == 0) {
				i_ddiv(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "ddiv");

		case IREM:
			if (mode == 0) {
				i_irem(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "irem");

		case LREM:
			if (mode == 0) {
				i_lrem(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lrem");

		case FREM:
			if (mode == 0) {
				i_frem(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "frem");

		case DREM:
			if (mode == 0) {
				i_drem(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "drem");

		case INEG:
			if (mode == 0) {
				i_ineg(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "ineg");

		case LNEG:
			if (mode == 0) {
				i_lneg(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lneg");

		case FNEG:
			if (mode == 0) {
				i_fneg(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fneg");

		case DNEG:
			if (mode == 0) {
				i_dneg(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dneg");

		case ISHL:
			if (mode == 0) {
				i_ishl(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "ishl");

		case LSHL:
			if (mode == 0) {
				i_lshl(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lshl");

		case ISHR:
			if (mode == 0) {
				i_ishr(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "ishr");

		case LSHR:
			if (mode == 0) {
				i_lshr(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lshr");

		case IUSHR:
			if (mode == 0) {
				i_iushr(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iushr");

		case LUSHR:
			if (mode == 0) {
				i_lushr(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lushr");

		case IAND:
			if (mode == 0) {
				i_iand(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "iand");

		case LAND:
			if (mode == 0) {
				i_land(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "land");

		case IOR:
			if (mode == 0) {
				i_ior(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "ior");

		case LOR:
			if (mode == 0) {
				i_lor(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lor");

		case IXOR:
			if (mode == 0) {
				i_ixor(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "ixor");

		case LXOR:
			if (mode == 0) {
				i_lxor(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lxor");

		case IINC:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "iinc");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				inc = runtime_instr->arguments[1];

				i_iinc(frame, index, inc);
			}

			return runtime_instr;

		case I2L:
			if (mode == 0) {
				i_i2l(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "i2l");

		case I2F:
			if (mode == 0) {
				i_i2f(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "i2f");

		case I2D:
			if (mode == 0) {
				i_i2d(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "i2d");

		case L2I:
			if (mode == 0) {
				i_l2i(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "l2i");

		case L2F:
			if (mode == 0) {
				i_l2f(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "l2f");

		case L2D:
			if (mode == 0) {
				i_l2d(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "l2d");

		case F2I:
			if (mode == 0) {
				i_f2i(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "f2i");

		case F2L:
			if (mode == 0) {
				i_f2l(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "f2l");

		case F2D:
			if (mode == 0) {
				i_f2d(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "f2d");

		case D2I:
			if (mode == 0) {
				i_d2i(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "d2i");

		case D2L:
			if (mode == 0) {
				i_d2l(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "d2l");

		case D2F:
			if (mode == 0) {
				i_d2f(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "d2f");

		case I2B:
			if (mode == 0) {
				i_i2b(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "i2b");

		case I2C:
			if (mode == 0) {
				i_i2c(frame);
			}
			return readNoArgs(bytecode, offset, pc, opcode, "i2c");

		case I2S:
			if (mode == 0) {
				i_i2s(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "i2s");

		case LCMP:
			if (mode == 0) {
				i_lcmp(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lcmp");

		case FCMPL:
			if (mode == 0) {
				i_fcmpl(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fcmpl");

		case FCMPG:
			if (mode == 0) {
				i_fcmpg(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "fcmpg");

		case DCMPL:
			if (mode == 0) {
				i_dcmpl(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dcmpl");

		case DCMPG:
			if (mode == 0) {
				i_dcmpg(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dcmpg");


		case IFEQ:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "ifeq");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_ifeq(frame, index, index2);
			}

			return runtime_instr;

		case IFNE:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "ifne");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_ifne(frame, index, index2);
			}

			return runtime_instr;

		case IFLT:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "iflt");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_iflt(frame, index, index2);
			}

			return runtime_instr;

		case IFGE:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "ifge");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_ifge(frame, index, index2);
			}

			return runtime_instr;

		case IFGT:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "ifgt");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_ifgt(frame, index, index2);
			}

			return runtime_instr;

		case IFLE:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "ifle");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_ifle(frame, index, index2);
			}

			return runtime_instr;

		case IF_ICMPEQ:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "if_icmpeq");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_icmpeq(frame, index, index2);
			}

			return runtime_instr;

		case IF_ICMPNE:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "if_icmpne");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_icmpne(frame, index, index2);
			}

			return runtime_instr;

		case IF_ICMPLT:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "if_icmplt");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_icmplt(frame, index, index2);
			}

			return runtime_instr;

		case IF_ICMPGE:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "if_icmpge");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_icmpge(frame, index, index2);
			}

			return runtime_instr;

		case IF_ICMPGT:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "if_icmpgt");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_icmpgt(frame, index, index2);
			}

			return runtime_instr;

		case IF_ICMPLE:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "if_icmple");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_icmple(frame, index, index2);
			}

			return runtime_instr;

		case IF_ACMPEQ:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "if_acmpeq");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_acmpeq(frame, index, index2);
			}

			return runtime_instr;

		case IF_ACMPNE:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "if_acmpne");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_if_acmpne(frame, index, index2);
			}

			return runtime_instr;

		case GOTO:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "goto");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_goto(frame, index, index2);
			}

			return runtime_instr;

		case JSR:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "jsr");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_jsr(frame, index, index2);
			}

			return runtime_instr;

		case RET:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "ret");

			if (mode == 0) {
				index = runtime_instr->arguments[0];

				i_ret(frame, index);
			}

			return runtime_instr;

		case TABLESWITCH:
			if (mode == 0) {
				i_tableswitch(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "tableswitch");

		case LOOKUPSWITCH:
			if (mode == 0) {
				i_lookupswitch(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lookupswitch");

		case IRETURN:
			if (mode == 0) {
				i_ireturn(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "ireturn");

		case LRETURN:
			if (mode == 0) {
				i_lreturn(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "lreturn");

		case FRETURN:
			if (mode == 0) {
				i_freturn(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "freturn");

		case DRETURN:
			if (mode == 0) {
				i_dreturn(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "dreturn");

		case ARETURN:
			if (mode == 0) {
				i_areturn(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "areturn");

		case RETURN:
			if (mode == 0) {
				i_return(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "return");

		case GETSTATIC:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "getstatic");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_getstatic(frame, frame->heap->listaStaticField, frame->heap->listaDeClasses, index, index2);
			}

			return runtime_instr;

		case PUTSTATIC:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "putstatic");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_putstatic(frame, frame->heap->listaStaticField, frame->heap->listaDeClasses, index, index2);
			}

			return runtime_instr;

		case GETFIELD:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "getfield");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_getfield(frame, index, index2);
			}

			return runtime_instr;

		case PUTFIELD:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "putfield");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_putfield(frame, index, index2);
			}

			return runtime_instr;

		case INVOKEVIRTUAL:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "invokevirtual");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_invokevirtual(frame, frame->framesStack, frame->heap->listaDeClasses, index, index2, frame->heap);
			}

			return runtime_instr;

		case INVOKESPECIAL:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "invokespecial");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_invokespecial(frame, frame->framesStack, frame->heap->listaDeClasses, index, index2, frame->heap);
			}

			return runtime_instr;

		case INVOKESTATIC:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "invokestatic");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_invokestatic(frame, frame->framesStack, frame->heap->listaDeClasses, index, index2, frame->heap);
			}

			return runtime_instr;

		case INVOKEINTERFACE:
			runtime_instr = readFourArgs(bytecode, offset, pc, opcode, "invokeinterface");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];
				contagem = runtime_instr->arguments[2];
				zero = runtime_instr->arguments[3];

				i_invokeinterface(frame, frame->framesStack, frame->heap->listaDeClasses, index, index2, contagem, zero, frame->heap);
			}

			return runtime_instr;

		case INVOKEDYNAMIC:
			runtime_instr = readFourArgs(bytecode, offset, pc, opcode, "invokedynamic");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];
				zero_1 = runtime_instr->arguments[2];
				zero_2 = runtime_instr->arguments[3];

				i_invokedynamic(frame, frame->framesStack, frame->heap->listaDeClasses, index, index2, zero_1, zero_2, frame->heap);
			}

			return runtime_instr;

		case NEW:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "new");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_new(frame, index, index2, frame->heap->listaDeClasses);
			}

			return runtime_instr;

		case NEWARRAY:
			runtime_instr = readOneArg(bytecode, offset, pc, opcode, "newarray");

			if (mode == 0) {
				type = runtime_instr->arguments[0];

			 	i_newarray(frame, type);
			}

			return runtime_instr;

		case ANEWARRAY:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "anewarray");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_anewarray(frame, index, index2);
			}

			return runtime_instr;

		case ARRAYLENGTH:
			if (mode == 0) {
				i_arraylength(frame);
			}
			return readNoArgs(bytecode, offset, pc, opcode, "arraylength");

		case ATHROW:
			if (mode == 0) {
				i_athrow(frame);
			}
			return readNoArgs(bytecode, offset, pc, opcode, "athrow");

		case CHECKCAST:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "checkcast");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_checkcast(frame, index, index2);
			}

			return runtime_instr;

		case INSTANCEOF:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "instanceof");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];

				i_instanceof(frame, index, index2);
			}

			return runtime_instr;

		case MONITORENTER:
			if (mode == 0) {
				i_monitorenter(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "monitorenter");

		case MONITOREXIT:
			if (mode == 0) {
				i_monitorexit(frame);
			}

			return readNoArgs(bytecode, offset, pc, opcode, "monitorexit");

		case WIDE:
			runtime_instr = readFourArgs(bytecode, offset, pc, opcode, "wide");

			if (mode == 0) {
				opcode1 = runtime_instr->opcode;
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];
				constbyte1 = runtime_instr->arguments[2];
				constbyte2 = runtime_instr->arguments[3];

				i_wide(frame, opcode1, index, index2, constbyte1, constbyte2);
			}

			return runtime_instr;

		case MULTIANEWARRAY:
			runtime_instr = readThreeArgs(bytecode, offset, pc, opcode, "multianewarray");

			if (mode == 0) {
				index = runtime_instr->arguments[0];
				index2 = runtime_instr->arguments[1];
				dimensions = runtime_instr->arguments[2];

				i_multianewarray(frame, index, index2, dimensions);
			}

			return runtime_instr;

		case IFNULL:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "ifnull");

			if (mode == 0) {
				branch1 = runtime_instr->arguments[0];
				branch2 = runtime_instr->arguments[1];

				i_ifnull(frame, branch1, branch2);
			}

			return runtime_instr;

		case IFNONNULL:
			runtime_instr = readTwoArgs(bytecode, offset, pc, opcode, "ifnonnull");

			if (mode == 0) {
				branch1 = runtime_instr->arguments[0];
				branch2 = runtime_instr->arguments[1];

				i_ifnonnull(frame, branch1, branch2);
			}

			return runtime_instr;

		case GOTO_W:
			runtime_instr = readFourArgs(bytecode, offset, pc, opcode, "goto_w");

			if (mode == 0) {
				branch1 = runtime_instr->arguments[0];
				branch2 = runtime_instr->arguments[1];
				branch3 = runtime_instr->arguments[2];
				branch4 = runtime_instr->arguments[3];

				i_goto_w(frame, branch1, branch2, branch3, branch4);
			}

			return runtime_instr;

		case JSR_W:
			runtime_instr = readFourArgs(bytecode, offset, pc, opcode, "jsr_w");

			if (mode == 0) {
				branch1 = runtime_instr->arguments[0];
				branch2 = runtime_instr->arguments[1];
				branch3 = runtime_instr->arguments[2];
				branch4 = runtime_instr->arguments[3];

				i_jsr_w(frame, branch1, branch2, branch3, branch4);
			}

			return runtime_instr;

		default:
			return NULL;
	}
}

Instruction* readNoArgs(uint8_t* bytecode, int* offset, int pc, int opcode, char* name) {
	Instruction* instr = (Instruction*) set_mem(sizeof(Instruction));
	instr->pc = pc;
	instr->opcode = opcode;
	instr->name = name;
	instr->arguments_count = 0;
	instr->arguments = NULL;
	return instr;
}

Instruction* readOneArg(uint8_t* bytecode, int* offset, int pc, int opcode, char* name) {
	Instruction* instr = (Instruction*) set_mem(sizeof(Instruction));
	instr->pc = pc;
	instr->opcode = opcode;
	instr->name = name;
	instr->arguments_count = 1;
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
	instr->arguments = (int8_t*) set_mem(4 * sizeof(int8_t));
	instr->arguments[0] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	instr->arguments[1] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	instr->arguments[2] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	instr->arguments[3] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	return instr;
}

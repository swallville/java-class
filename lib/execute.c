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

Instruction* decode(uint8_t* bytecode, int* offset) {
	int pc = (*offset);
	int position = (*offset)++;
	int opcode = bytecode[position];
	switch (opcode) {
		// With No arguments
		case AALOAD:
			return readNoArgs(bytecode, offset, pc, opcode, "aaload");
		case AASTORE:
			return readNoArgs(bytecode, offset, pc, opcode, "aastore");
		case ACONST_NULL:
			return readNoArgs(bytecode, offset, pc, opcode, "aconst_null");
		case ALOAD_0:
			return readNoArgs(bytecode, offset, pc, opcode, "aload_0");
		case ALOAD_1:
			return readNoArgs(bytecode, offset, pc, opcode, "aload_1");
		case ALOAD_2:
			return readNoArgs(bytecode, offset, pc, opcode, "aload_2");
		case ALOAD_3:
			return readNoArgs(bytecode, offset, pc, opcode, "aload_3");
		case ARETURN:
			return readNoArgs(bytecode, offset, pc, opcode, "areturn");
		case ASTORE_1:
			return readTwoArgs(bytecode, offset, pc, opcode, "astore_1");
		case DLOAD_0:
			return readNoArgs(bytecode, offset, pc, opcode, "dload_0");
		case DLOAD_1:
			return readNoArgs(bytecode, offset, pc, opcode, "dload_1");
		case DLOAD_2:
			return readNoArgs(bytecode, offset, pc, opcode, "dload_2");
		case DLOAD_3:
			return readNoArgs(bytecode, offset, pc, opcode, "dload_3");
		case DMUL:
			return readNoArgs(bytecode, offset, pc, opcode, "dmul");
		case DREM:
			return readNoArgs(bytecode, offset, pc, opcode, "drem");
		case DRETURN:
			return readNoArgs(bytecode, offset, pc, opcode, "dreturn");
		case DSTORE_0:
			return readNoArgs(bytecode, offset, pc, opcode, "dstore_0");
		case DSTORE_1:
			return readNoArgs(bytecode, offset, pc, opcode, "dsotre_1");
		case DSTORE_2:
			return readNoArgs(bytecode, offset, pc, opcode, "dstore_2");
		case DSTORE_3:
			return readNoArgs(bytecode, offset, pc, opcode, "dstore_3");
		case DSUB:
			return readNoArgs(bytecode, offset, pc, opcode, "dsub");
		case DUP:
			return readNoArgs(bytecode, offset, pc, opcode, "dup");
		case DUP_X1:
			return readNoArgs(bytecode, offset, pc, opcode, "dup_x1");
		case DUP_X2:
			return readNoArgs(bytecode, offset, pc, opcode, "dup_x2");
		case DUP2:
			return readNoArgs(bytecode, offset, pc, opcode, "dup2");
		case DUP2_X1:
			return readNoArgs(bytecode, offset, pc, opcode, "dup2_x1");
		case DUP2_X2:
			return readNoArgs(bytecode, offset, pc, opcode, "dup2_x2");
		case F2D:
			return readNoArgs(bytecode, offset, pc, opcode, "f2d");
		case F2I:
			return readNoArgs(bytecode, offset, pc, opcode, "f2i");
		case F2L:
			return readNoArgs(bytecode, offset, pc, opcode, "f2l");
		case FADD:
			return readNoArgs(bytecode, offset, pc, opcode, "fadd");
	  case DADD:
			return readNoArgs(bytecode, offset, pc, opcode, "dadd");
		case FALOAD:
			return readNoArgs(bytecode, offset, pc, opcode, "faload");
		case FASTORE:
			return readNoArgs(bytecode, offset, pc, opcode, "fastore");
		case FCMPG:
			return readNoArgs(bytecode, offset, pc, opcode, "fcmpg");
		 case FCMPL:
			return readNoArgs(bytecode, offset, pc, opcode, "fcmpl");
		case FCONST_0:
			return readNoArgs(bytecode, offset, pc, opcode, "fconst_0");
		case FCONST_1:
			return readNoArgs(bytecode, offset, pc, opcode, "fconst_1");
		case FCONST_2:
			return readNoArgs(bytecode, offset, pc, opcode, "fconst_2");
		case FDIV:
			return readNoArgs(bytecode, offset, pc, opcode, "fdiv");
		case DDIV:
			return readNoArgs(bytecode, offset, pc, opcode, "ddiv");
		case FLOAD_0:
			return readNoArgs(bytecode, offset, pc, opcode, "fload_0");
		case FLOAD_1:
			return readNoArgs(bytecode, offset, pc, opcode, "fload_1");
		case FLOAD_2:
			return readNoArgs(bytecode, offset, pc, opcode, "fload_2");
		case FLOAD_3:
			return readNoArgs(bytecode, offset, pc, opcode, "fload_3");
		case FMUL:
			return readNoArgs(bytecode, offset, pc, opcode, "fmul");
		case FNEG:
			return readNoArgs(bytecode, offset, pc, opcode, "fneg");
		case DNEG:
			return readNoArgs(bytecode, offset, pc, opcode, "dneg");
		case FREM:
			return readNoArgs(bytecode, offset, pc, opcode, "frem");
		case FRETURN:
			return readNoArgs(bytecode, offset, pc, opcode, "freturn");
		case FSTORE_0:
			return readNoArgs(bytecode, offset, pc, opcode, "fstore_0");
		case FSTORE_1:
			return readNoArgs(bytecode, offset, pc, opcode, "fstore_1");
		case FSTORE_2:
			return readNoArgs(bytecode, offset, pc, opcode, "fstore_2");
		case FSTORE_3:
			return readNoArgs(bytecode, offset, pc, opcode, "fstore_3");
		case FSUB:
			return readNoArgs(bytecode, offset, pc, opcode, "fsub");
		case I2B:
			return readNoArgs(bytecode, offset, pc, opcode, "i2b");
		case I2C:
			return readNoArgs(bytecode, offset, pc, opcode, "i2c");
		case I2S:
			return readNoArgs(bytecode, offset, pc, opcode, "i2s");
		case IADD:
			return readNoArgs(bytecode, offset, pc, opcode, "iadd");
		case IALOAD:
			return readNoArgs(bytecode, offset, pc, opcode, "iaload");
		case IAND:
			return readNoArgs(bytecode, offset, pc, opcode, "iand");
		case IASTORE:
			return readNoArgs(bytecode, offset, pc, opcode, "iastore");
		case ICONST_0:
			return readNoArgs(bytecode, offset, pc, opcode, "iconst_0");
		case ICONST_1:
			return readNoArgs(bytecode, offset, pc, opcode, "iconst_1");
		case ICONST_2:
			return readNoArgs(bytecode, offset, pc, opcode, "iconst_2");
		case ICONST_3:
			return readNoArgs(bytecode, offset, pc, opcode, "iconst_3");
		case ICONST_4:
			return readNoArgs(bytecode, offset, pc, opcode, "iconst_4");
		case ICONST_5:
			return readNoArgs(bytecode, offset, pc, opcode, "iconst_5");
		case IDIV:
			return readNoArgs(bytecode, offset, pc, opcode, "idiv");
		case ILOAD_0:
			return readNoArgs(bytecode, offset, pc, opcode, "iload_0");
		case ILOAD_1:
			return readNoArgs(bytecode, offset, pc, opcode, "iload_1");
		case ILOAD_2:
			return readNoArgs(bytecode, offset, pc, opcode, "iload_2");
		case ILOAD_3:
			return readNoArgs(bytecode, offset, pc, opcode, "iload_3");
		case IMPDEP1:
			return readNoArgs(bytecode, offset, pc, opcode, "impdep1");
		case IMPDEP2:
			return readNoArgs(bytecode, offset, pc, opcode, "impdep2");
		case IMUL:
			return readNoArgs(bytecode, offset, pc, opcode, "imul");
		case INEG:
			return readNoArgs(bytecode, offset, pc, opcode, "ineg");
		case IOR:
			return readNoArgs(bytecode, offset, pc, opcode, "ior");
		case IREM:
			return readNoArgs(bytecode, offset, pc, opcode, "irem");
		case IRETURN:
			return readNoArgs(bytecode, offset, pc, opcode, "ireturn");
		case ISHL:
			return readNoArgs(bytecode, offset, pc, opcode, "ishl");
		case ISHR:
			return readNoArgs(bytecode, offset, pc, opcode, "ishr");
		case ISTORE_0:
			return readNoArgs(bytecode, offset, pc, opcode,"istore_0");
		case ISTORE_1:
			return readNoArgs(bytecode, offset, pc, opcode,"istore_1");
		case ISTORE_2:
			return readNoArgs(bytecode, offset, pc, opcode,"istore_2");
		case ISTORE_3:
			return readNoArgs(bytecode, offset, pc, opcode,"istore_3");
		case ISUB:
			return readNoArgs(bytecode, offset, pc, opcode, "isub");
		case IUSHR:
			return readNoArgs(bytecode, offset, pc, opcode, "iushr");
		case IXOR:
			return readNoArgs(bytecode, offset, pc, opcode, "ixor");
		case LADD:
			return readNoArgs(bytecode, offset, pc, opcode, "ladd");
		case LALOAD:
			return readNoArgs(bytecode, offset, pc, opcode, "laload");
		case LAND:
			return readNoArgs(bytecode, offset, pc, opcode, "land");
		case LASTORE:
			return readNoArgs(bytecode, offset, pc, opcode, "lastore");
		case LCMP:
			return readNoArgs(bytecode, offset, pc, opcode, "lcmp");
		case LCONST_0:
			return readNoArgs(bytecode, offset, pc, opcode, "lconst_0");
		case LCONST_1:
			return readNoArgs(bytecode, offset, pc, opcode, "lconst_1");
		case LDIV:
			return readNoArgs(bytecode, offset, pc, opcode, "ldiv");
		case LLOAD_0:
			return readNoArgs(bytecode, offset, pc, opcode, "lload_0");
		case LLOAD_1:
			return readNoArgs(bytecode, offset, pc, opcode, "lload_1");
		case LLOAD_2:
			return readNoArgs(bytecode, offset, pc, opcode, "lload_2");
		case LLOAD_3:
			return readNoArgs(bytecode, offset, pc, opcode, "lload_3");
		case LMUL:
			return readNoArgs(bytecode, offset, pc, opcode, "lmul");
		case LNEG:
			return readNoArgs(bytecode, offset, pc, opcode, "lneg");
		case LREM:
			return readNoArgs(bytecode, offset, pc, opcode, "lrem");
		case LRETURN:
			return readNoArgs(bytecode, offset, pc, opcode, "lreturn");
		case LSHL:
			return readNoArgs(bytecode, offset, pc, opcode, "lshl");
		case LSHR:
			return readNoArgs(bytecode, offset, pc, opcode, "lshr");
		case LSTORE_0:
			return readNoArgs(bytecode, offset, pc, opcode, "lstore_0");
		case LSTORE_1:
			return readNoArgs(bytecode, offset, pc, opcode, "lstore_1");
		case LSTORE_2:
			return readNoArgs(bytecode, offset, pc, opcode, "lstore_2");
		case LSTORE_3:
			return readNoArgs(bytecode, offset, pc, opcode, "lstore_3");
		case LSUB:
			return readNoArgs(bytecode, offset, pc, opcode, "lsub");
		case LUSHR:
			return readNoArgs(bytecode, offset, pc, opcode, "lushr");
		case MONITORENTER:
			return readNoArgs(bytecode, offset, pc, opcode, "monitorenter");
		case MONITOREXIT:
			return readNoArgs(bytecode, offset, pc, opcode, "monitorexit");
		case NOP:
			return readNoArgs(bytecode, offset, pc, opcode, "nop");
		case POP:
			return readNoArgs(bytecode, offset, pc, opcode, "pop");
		case POP2:
			return readNoArgs(bytecode, offset, pc, opcode, "pop2");
		case RETURN:
			return readNoArgs(bytecode, offset, pc, opcode, "return");
		case SALOAD:
			return readNoArgs(bytecode, offset, pc, opcode, "saload");
		case SASTORE:
			return readNoArgs(bytecode, offset, pc, opcode, "sastore");
		case SWAP:
			return readNoArgs(bytecode, offset, pc, opcode, "swap");
		// One argument
		case BIPUSH:
			return readOneArg(bytecode, offset, pc, opcode, "bipush");
		case LDC:
			return readOneArg(bytecode, offset, pc, opcode, "ldc");
		case ILOAD:
			return readOneArg(bytecode, offset, pc, opcode, "iload");
		case LLOAD:
			return readOneArg(bytecode, offset, pc, opcode, "lload");
		case FLOAD:
			return readOneArg(bytecode, offset, pc, opcode, "fload");
		case ISTORE:
			return readOneArg(bytecode, offset, pc, opcode, "istore");
		case LSTORE:
			return readOneArg(bytecode, offset, pc, opcode, "lstore");
		case NEWARRAY:
			return readOneArg(bytecode, offset, pc, opcode, "newarray");
		// Two arguments
		case GOTO:
			return readTwoArgs(bytecode, offset, pc, opcode, "goto");
		case IF_ICMPEQ:
			return readTwoArgs(bytecode, offset, pc, opcode, "if_acmpeq");
		case IF_ICMPGE:
			return readTwoArgs(bytecode, offset, pc, opcode, "if_acmpge");
		case IF_ICMPGT:
			return readTwoArgs(bytecode, offset, pc, opcode, "if_icmpgt");
		case IF_ICMPLE:
			return readTwoArgs(bytecode, offset, pc, opcode, "if_acmple");
		case IF_ICMPLT:
			return readTwoArgs(bytecode, offset, pc, opcode, "if_acmplt");
		case IF_ICMPNE:
			return readTwoArgs(bytecode, offset, pc, opcode, "if_acmpne");
		case IFEQ:
			return readTwoArgs(bytecode, offset, pc, opcode, "ifeq");
		case IFGE:
			return readTwoArgs(bytecode, offset, pc, opcode, "ifge");
		case IFGT:
			return readTwoArgs(bytecode, offset, pc, opcode, "ifgt");
		case IFLT:
			return readTwoArgs(bytecode, offset, pc, opcode, "iflt");
		case IFNE:
			return readTwoArgs(bytecode, offset, pc, opcode, "ifne");
		case IFNONNULL:
			return readTwoArgs(bytecode, offset, pc, opcode, "ifnonnull");
		case IFNULL:
			return readTwoArgs(bytecode, offset, pc, opcode, "ifnull");
		case JSR:
			return readTwoArgs(bytecode, offset, pc, opcode, "jsr");
		case SIPUSH:
			return readTwoArgs(bytecode, offset, pc, opcode, "sipush");
		case IINC:
			return readTwoArgs(bytecode, offset, pc, opcode, "iinc");
		case ANEWARRAY:
			return readTwoArgs(bytecode, offset, pc, opcode, "anewarray");
		case CHECKCAST:
			return readTwoArgs(bytecode, offset, pc, opcode, "checkcast");
		case GETFIELD:
			return readTwoArgs(bytecode, offset, pc, opcode, "getfield");
		case GETSTATIC:
			return readTwoArgs(bytecode, offset, pc, opcode, "getstatic");
		case INSTANCEOF:
			return readTwoArgs(bytecode, offset, pc, opcode, "instanceof");
		case INVOKESPECIAL:
			return readTwoArgs(bytecode, offset, pc, opcode, "invokespecial");
		case INVOKESTATIC:
			return readTwoArgs(bytecode, offset, pc, opcode, "invokestatic");
		case INVOKEVIRTUAL:
			return readTwoArgs(bytecode, offset, pc, opcode, "invokevirtual");
		case LDC_W:
			return readTwoArgs(bytecode, offset, pc, opcode, "ldc_w");
		case LDC2_W:
			return readTwoArgs(bytecode, offset, pc, opcode, "ldc2_w");
		case NEW:
			return readTwoArgs(bytecode, offset, pc, opcode, "new");
		case PUTFIELD:
			return readTwoArgs(bytecode, offset, pc, opcode, "putfield");
		case PUTSTATIC:
			return readTwoArgs(bytecode, offset, pc, opcode, "putstatic");
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

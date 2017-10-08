/**
 * @file execute.c
 * @brief Execution operations library source.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * @todo Description
 */

#include <stdio.h>
#include <string.h>
#include "execute.h"
#include "mem-manager.h"
#include "utils.h"

Instruction* decode(u1* bytecode, int* offset) {
	int pc = (*offset);
	int opcode = bytecode[(*offset)++];
	// Instruction functions' opcodes with:
	switch (opcode) {
		// No arguments
		case AALOAD:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "aaload");
		case AASTORE:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "aastore");
		case ACONST_NULL:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "aconst_null");
		case ALOAD_0:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "aload_0");
		case ALOAD_1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "aload_1");
		case ALOAD_2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "aload_2");
		case ALOAD_3:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "aload_3");
		case ARETURN:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "areturn");
		case ASTORE_1:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "astore_1");
		case DLOAD_0:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dload_0");
		case DLOAD_1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dload_1");
		case DLOAD_2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dload_2");
		case DLOAD_3:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dload_3");
		case DMUL:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dmul");
		case DNEG:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dneg");
		case DREM:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "drem");
		case DRETURN:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dreturn");
		case DSTORE_0:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dstore_0");
		case DSTORE_1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dsotre_1");
		case DSTORE_2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dstore_2");
		case DSTORE_3:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dstore_3");
		case DSUB:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dsub");
		case DUP:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dup");
		case DUP_X1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dup_x1");
		case DUP_X2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dup_x2");
		case DUP2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dup2");
		case DUP2_X1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dup2_x1");
		case DUP2_X2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "dup2_x2");
		case F2D:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "f2d");
		case F2I:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "f2i");
		case F2L:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "f2l");
		case FADD:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fadd");
		case FALOAD:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "faload");
		case FASTORE:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fastore");
		case FCMPG:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fcmpg");
		 case FCMPL:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fcmpl");
		case FCONST_0:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fconst_0");
		case FCONST_1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fconst_1");
		case FCONST_2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fconst_2");
		case FDIV:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fdiv");
		case FLOAD_0:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fload_0");
		case FLOAD_1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fload_1");
		case FLOAD_2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fload_2");
		case FLOAD_3:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fload_3");
		case FMUL:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fmul");
		case FNEG:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fneg");
		case FREM:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "frem");
		case FRETURN:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "freturn");
		case FSTORE_0:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fstore_0");
		case FSTORE_1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fstore_1");
		case FSTORE_2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fstore_2");
		case FSTORE_3:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fstore_3");
		case FSUB:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "fsub");
		case I2B:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "i2b");
		case I2C:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "i2c");
		case I2S:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "i2s");
		case IADD:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iadd");
		case IALOAD:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iaload");
		case IAND:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iand");
		case IASTORE:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iastore");
		case ICONST_0:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iconst_0");
		case ICONST_1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iconst_1");
		case ICONST_2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iconst_2");
		case ICONST_3:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iconst_3");
		case ICONST_4:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iconst_4");
		case ICONST_5:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iconst_5");
		case IDIV:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "idiv");
		case ILOAD_0:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iload_0");
		case ILOAD_1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iload_1");
		case ILOAD_2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iload_2");
		case ILOAD_3:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iload_3");
		case IMPDEP1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "impdep1");
		case IMPDEP2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "impdep2");
		case IMUL:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "imul");
		case INEG:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "ineg");
		case IOR:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "ior");
		case IREM:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "irem");
		case IRETURN:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "ireturn");
		case ISHL:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "ishl");
		case ISHR:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "ishr");
		case ISTORE_0:
			return getNoArgsInstr(bytecode, offset, pc, opcode,"istore_0");
		case ISTORE_1:
			return getNoArgsInstr(bytecode, offset, pc, opcode,"istore_1");
		case ISTORE_2:
			return getNoArgsInstr(bytecode, offset, pc, opcode,"istore_2");
		case ISTORE_3:
			return getNoArgsInstr(bytecode, offset, pc, opcode,"istore_3");
		case ISUB:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "isub");
		case IUSHR:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "iushr");
		case IXOR:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "ixor");
		case LADD:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "ladd");
		case LALOAD:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "laload");
		case LAND:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "land");
		case LASTORE:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lastore");
		case LCMP:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lcmp");
		case LCONST_0:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lconst_0");
		case LCONST_1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lconst_1");
		case LDIV:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "ldiv");
		case LLOAD_0:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lload_0");
		case LLOAD_1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lload_1");
		case LLOAD_2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lload_2");
		case LLOAD_3:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lload_3");
		case LMUL:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lmul");
		case LNEG:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lneg");
		case LREM:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lrem");
		case LRETURN:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lreturn");
		case LSHL:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lshl");
		case LSHR:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lshr");
		case LSTORE_0:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lstore_0");
		case LSTORE_1:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lstore_1");
		case LSTORE_2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lstore_2");
		case LSTORE_3:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lstore_3");
		case LSUB:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lsub");
		case LUSHR:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "lushr");
		case MONITORENTER:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "monitorenter");
		case MONITOREXIT:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "monitorexit");
		case NOP:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "nop");
		case POP:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "pop");
		case POP2:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "pop2");
		case RETURN:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "return");
		case SALOAD:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "saload");
		case SASTORE:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "sastore");
		case SWAP:
			return getNoArgsInstr(bytecode, offset, pc, opcode, "swap");
		// One argument
		case BIPUSH:
			return getOneArgInstr(bytecode, offset, pc, opcode, "bipush");
		case LDC:
			return getOneArgInstr(bytecode, offset, pc, opcode, "ldc");
		case ILOAD:
			return getOneArgInstr(bytecode, offset, pc, opcode, "iload");
		case LLOAD:
			return getOneArgInstr(bytecode, offset, pc, opcode, "lload");
		case FLOAD:
			return getOneArgInstr(bytecode, offset, pc, opcode, "fload");
		case ISTORE:
			return getOneArgInstr(bytecode, offset, pc, opcode, "istore");
		case LSTORE:
			return getOneArgInstr(bytecode, offset, pc, opcode, "lstore");
		case NEWARRAY:
			return getOneArgInstr(bytecode, offset, pc, opcode, "newarray");
		// Two arguments
		case GOTO:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "goto");
		case IF_ICMPEQ:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "if_acmpeq");
		case IF_ICMPGE:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "if_acmpge");
		case IF_ICMPGT:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "if_icmpgt");
		case IF_ICMPLE:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "if_acmple");
		case IF_ICMPLT:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "if_acmplt");
		case IF_ICMPNE:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "if_acmpne");
		case IFEQ:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "ifeq");
		case IFGE:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "ifge");
		case IFGT:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "ifgt");
		case IFLT:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "iflt");
		case IFNE:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "ifne");
		case IFNONNULL:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "ifnonnull");
		case IFNULL:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "ifnull");
		case JSR:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "jsr");
		case SIPUSH:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "sipush");
		case IINC:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "iinc");
		case ANEWARRAY:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "anewarray");
		case CHECKCAST:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "checkcast");
		case GETFIELD:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "getfield");
		case GETSTATIC:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "getstatic");
		case INSTANCEOF:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "instanceof");
		case INVOKESPECIAL:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "invokespecial");
		case INVOKESTATIC:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "invokestatic");
		case INVOKEVIRTUAL:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "invokevirtual");
		case LDC_W:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "ldc_w");
		case LDC2_W:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "ldc2_w");
		case NEW:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "new");
		case PUTFIELD:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "putfield");
		case PUTSTATIC:
			return getTwoArgsInstr(bytecode, offset, pc, opcode, "putstatic");
		default:
			return NULL;
	}
}

Instruction* getNoArgsInstr(u1* bytecode, int* offset, int pc, int opcode, char* name) {
	Instruction* instr = (Instruction*) allocate(sizeof(Instruction));
	instr->pc = pc;
	instr->opcode = opcode;
	instr->name = name;
	instr->argumentsCount = 0;
	instr->arguments = NULL;
	return instr;
}

Instruction* getOneArgInstr(u1* bytecode, int* offset, int pc, int opcode, char* name) {
	Instruction* instr = (Instruction*) allocate(sizeof(Instruction));
	instr->pc = pc;
	instr->opcode = opcode;
	instr->name = name;
	instr->argumentsCount = 1;
	instr->arguments = (int8_t*) allocate(1 * sizeof(int8_t));
	instr->arguments[0] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	return instr;
}

Instruction* getTwoArgsInstr(u1* bytecode, int* offset, int pc, int opcode, char* name) {
	Instruction* instr = (Instruction*) allocate(sizeof(Instruction));
	instr->pc = pc;
	instr->opcode = opcode;
	instr->name = name;
	instr->argumentsCount = 2;
	instr->arguments = (int8_t*) allocate(2 * sizeof(int8_t));
	instr->arguments[0] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	instr->arguments[1] = (int8_t)get1bytesFromByteArray(bytecode, (*offset)++);
	return instr;
}

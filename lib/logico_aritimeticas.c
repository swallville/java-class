#include "logico_aritimeticas.h"

void i_iadd(Frame* frame){
	int32_t elem1 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t sresult = elem1 + elem2;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_ladd(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem1 + elem2;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_fadd(Frame* frame){
	int32_t elem1 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2 = *((int32_t*)pop(&(frame->operandStack))->value);
	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = f1 + f2;
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_dadd(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = d1 + d2;
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_isub(Frame* frame){
	int32_t elem1 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t sresult = elem1 - elem2;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_lsub(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem1 - elem2;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_fsub(Frame* frame){
	int32_t elem1 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2 = *((int32_t*)pop(&(frame->operandStack))->value);
	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = f1 - f2;
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_dsub(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = d1 - d2;
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_imul(Frame* frame){
	int32_t elem1 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t sresult = elem1 * elem2;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_lmul(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem1 * elem2;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_fmul(Frame* frame){
	int32_t elem1 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2 = *((int32_t*)pop(&(frame->operandStack))->value);
	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = f1 * f2;
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_dmul(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = d1 * d2;
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_idiv(Frame* frame){
	int32_t elem1 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t sresult = elem1 / elem2;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_ldiv(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem1 / elem2;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}


void i_fdiv(Frame* frame){
	int32_t elem1 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2 = *((int32_t*)pop(&(frame->operandStack))->value);
	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = f1 / f2;
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_ddiv(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = d1 / d2;
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_irem(Frame* frame){
	int32_t elem1 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t sresult = elem1 % elem2;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_lrem(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem1 % elem2;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_frem(Frame* frame){
	int32_t elem1 = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2 = *((int32_t*)pop(&(frame->operandStack))->value);
	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = fmodf(f1,f2);
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_drem(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem2l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = fmod(d1,d2);
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_ineg(Frame* frame){
	int32_t elem = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t nelem = ~elem;
	uint32_t result;
	memcpy(&result, &nelem, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_lneg(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem = (((int64_t)elem1h) << 32) | elem1l;
	int64_t nelem = ~elem;
	uint64_t result;
	memcpy(&result, &nelem, sizeof(uint64_t));
	
	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_fneg(Frame* frame){
	int32_t elem = *((int32_t*)pop(&(frame->operandStack))->value);
	float f;
	memcpy(&f, &elem, sizeof(int32_t));
	float nelem = f*(-1);
	uint32_t result;
	memcpy(&result, &nelem, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_dneg(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem = (((int64_t)elem1h) << 32) | elem1l;
	double d;
	memcpy(&d, &elem, sizeof(int64_t));
	double nelem = d*(-1);
	uint64_t result;
	memcpy(&result, &nelem, sizeof(uint64_t));
	
	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_ishl(Frame* frame){
	int32_t elem = *((int32_t*)pop(&(frame->operandStack))->value);
	uint32_t shift = *((uint32_t*)pop(&(frame->operandStack))->value);
	shift &= 0x1F;
	elem = (elem << shift);
	uint32_t result;
	memcpy(&result, &elem, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_lshl(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem = (((int64_t)elem1h) << 32) | elem1l;
	uint64_t shift = *((uint64_t*)pop(&(frame->operandStack))->value);
	shift &= 0x1F;
	elem = (elem << shift);
	uint64_t result;
	memcpy(&result, &elem, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_ishr(Frame* frame){
	int32_t elem = *((int32_t*)pop(&(frame->operandStack))->value);
	uint32_t shift = *((uint32_t*)pop(&(frame->operandStack))->value);
	shift &= 0x1F;
	elem = (elem >> shift);
	uint32_t result;
	memcpy(&result, &elem, sizeof(uint32_t));
	push(&(result), &(frame->operandStack));
}

void i_lshr(Frame* frame){
	int32_t elem1h = *((int32_t*)pop(&(frame->operandStack))->value);
	int32_t elem1l = *((int32_t*)pop(&(frame->operandStack))->value);
	int64_t elem = (((int64_t)elem1h) << 32) | elem1l;
	uint64_t shift = *((uint64_t*)pop(&(frame->operandStack))->value);
	shift &= 0x1F;
	elem = (elem >> shift);
	uint64_t result;
	memcpy(&result, &elem, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_iushr(Frame* frame){
	uint32_t elem = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t shift = *((uint32_t*)pop(&(frame->operandStack))->value);
	shift &= 0x1F;
	elem = (elem >> shift);
	push(&(elem), &(frame->operandStack));
}

void i_lushr(Frame* frame){
	uint32_t elemh = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t eleml = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint64_t elem = (((uint64_t)elemh) << 32) | eleml;
	uint32_t shift = *((uint32_t*)pop(&(frame->operandStack))->value);
	shift &= 0x1F;
	elem = (elem >> shift);

	uint32_t low = (uint32_t)(elem & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(elem >> 32);
	push(&(high), &(frame->operandStack));
}

void i_iand(Frame* frame){
	uint32_t elem1 = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t elem2 = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t result = (elem1 & elem2);
	push(&(result), &(frame->operandStack));
}

void i_land(Frame* frame){
	uint32_t elem1h = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t elem1l = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t elem2h = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t elem2l = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint64_t elem1 = (((uint64_t)elem1h) << 32) | elem1l;
	uint64_t elem2 = (((uint64_t)elem2h) << 32) | elem2l;
	uint64_t result = (elem1 & elem2);

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_ior(Frame* frame){
	uint32_t elem1 = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t elem2 = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t result = (elem1 | elem2);
	push(&(result), &(frame->operandStack));
}

void i_lor(Frame* frame){
	uint32_t elem1h = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t elem1l = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t elem2h = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t elem2l = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint64_t elem1 = (((uint64_t)elem1h) << 32) | elem1l;
	uint64_t elem2 = (((uint64_t)elem2h) << 32) | elem2l;
	uint64_t result = (elem1 | elem2);

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_ixor(Frame* frame){
	uint32_t elem1 = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t elem2 = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t result = (elem1 ^ elem2);
	push(&(result), &(frame->operandStack));
}

void i_lxor(Frame* frame){
	uint32_t elem1h = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t elem1l = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t elem2h = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint32_t elem2l = *((uint32_t*)pop(&(frame->operandStack))->value);
	uint64_t elem1 = (((uint64_t)elem1h) << 32) | elem1l;
	uint64_t elem2 = (((uint64_t)elem2h) << 32) | elem2l;
	uint64_t result = (elem1 ^ elem2);

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
}

void i_iinc(Frame* frame, uint8_t index, uint8_t inc){
	frame->localVariables[index] += inc;
}

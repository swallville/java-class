#include "logico_aritimeticas.hpp"

void i_iadd(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t sresult = elem1 + elem2;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));

	frame->operandStack.push(result);
}

void i_ladd(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem1 + elem2;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_fadd(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = f1 + f2;
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));

	frame->operandStack.push(result);
}

void i_dadd(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = d1 + d2;
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_isub(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t sresult = elem1 - elem2;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));

	frame->operandStack.push(result);
}

void i_lsub(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem1 - elem2;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_fsub(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = f1 - f2;
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));
	frame->operandStack.push(result);
}

void i_dsub(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = d1 - d2;
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_imul(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t sresult = elem1 * elem2;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));

	frame->operandStack.push(result);
}

void i_lmul(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem1 * elem2;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_fmul(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = f1 * f2;
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));

	frame->operandStack.push(result);
}

void i_dmul(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = d1 * d2;
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_idiv(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t sresult = elem1 / elem2;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));

	frame->operandStack.push(result);
}

void i_ldiv(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem1 / elem2;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}


void i_fdiv(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = f1 / f2;
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));

	frame->operandStack.push(result);
}

void i_ddiv(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = d1 / d2;
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_irem(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t sresult = elem1 % elem2;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));

	frame->operandStack.push(result);
}

void i_lrem(Frame* frame){
	int32_t elem1h =(int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem1 % elem2;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_frem(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = fmodf(f1,f2);
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));

	frame->operandStack.push(result);
}

void i_drem(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = fmod(d1,d2);
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_ineg(Frame* frame){
	int32_t elem = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t nelem = ~elem;
	uint32_t result;
	memcpy(&result, &nelem, sizeof(uint32_t));
	frame->operandStack.push(result);
}

void i_lneg(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem = (((int64_t)elem1h) << 32) | elem1l;
	int64_t nelem = ~elem;
	uint64_t result;
	memcpy(&result, &nelem, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_fneg(Frame* frame){
	int32_t elem = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	float f;
	memcpy(&f, &elem, sizeof(int32_t));
	float nelem = f*(-1);
	uint32_t result;
	memcpy(&result, &nelem, sizeof(uint32_t));

	frame->operandStack.push(result);
}

void i_dneg(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem = (((int64_t)elem1h) << 32) | elem1l;
	double d;
	memcpy(&d, &elem, sizeof(int64_t));
	double nelem = d*(-1);
	uint64_t result;
	memcpy(&result, &nelem, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_ishl(Frame* frame){
	int32_t elem = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t shift = frame->operandStack.top();
  frame->operandStack.pop();

	shift &= 0x1F;
	elem = (elem << shift);
	uint32_t result;
	memcpy(&result, &elem, sizeof(uint32_t));

	frame->operandStack.push(result);
}

void i_lshl(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem = (((int64_t)elem1h) << 32) | elem1l;
	uint64_t shift = (uint64_t)frame->operandStack.top();
  frame->operandStack.pop();

	shift &= 0x1F;
	elem = (elem << shift);
	uint64_t result;
	memcpy(&result, &elem, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_ishr(Frame* frame){
	int32_t elem = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t shift = frame->operandStack.top();
  frame->operandStack.pop();

	shift &= 0x1F;
	elem = (elem >> shift);
	uint32_t result;
	memcpy(&result, &elem, sizeof(uint32_t));

	frame->operandStack.push(result);
}

void i_lshr(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top();
  frame->operandStack.pop();

	int64_t elem = (((int64_t)elem1h) << 32) | elem1l;
	uint64_t shift = (uint64_t)frame->operandStack.top();
  frame->operandStack.pop();

	shift &= 0x1F;
	elem = (elem >> shift);
	uint64_t result;
	memcpy(&result, &elem, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_iushr(Frame* frame){
	uint32_t elem = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t shift = frame->operandStack.top();
  frame->operandStack.pop();

	shift &= 0x1F;
	elem = (elem >> shift);

	frame->operandStack.push(elem);
}

void i_lushr(Frame* frame){
	uint32_t elemh = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t eleml = frame->operandStack.top();
  frame->operandStack.pop();

	uint64_t elem = (((uint64_t)elemh) << 32) | eleml;
	uint32_t shift = frame->operandStack.top();
  frame->operandStack.pop();

	shift &= 0x1F;
	elem = (elem >> shift);

	uint32_t low = (uint32_t)(elem & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(elem >> 32);
	frame->operandStack.push(high);
}

void i_iand(Frame* frame){
	uint32_t elem1 = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t elem2 = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t result = (elem1 & elem2);
	frame->operandStack.push(result);
}

void i_land(Frame* frame){
	uint32_t elem1h = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t elem1l = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t elem2h = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t elem2l = frame->operandStack.top();
  frame->operandStack.pop();

	uint64_t elem1 = (((uint64_t)elem1h) << 32) | elem1l;
	uint64_t elem2 = (((uint64_t)elem2h) << 32) | elem2l;
	uint64_t result = (elem1 & elem2);

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_ior(Frame* frame){
	uint32_t elem1 = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t elem2 = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t result = (elem1 | elem2);
	frame->operandStack.push(result);
}

void i_lor(Frame* frame){
	uint32_t elem1h = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t elem1l = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t elem2h = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t elem2l = frame->operandStack.top();
  frame->operandStack.pop();

	uint64_t elem1 = (((uint64_t)elem1h) << 32) | elem1l;
	uint64_t elem2 = (((uint64_t)elem2h) << 32) | elem2l;
	uint64_t result = (elem1 | elem2);

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_ixor(Frame* frame){
	uint32_t elem1 = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t elem2 = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t result = (elem1 ^ elem2);

	frame->operandStack.push(result);
}

void i_lxor(Frame* frame){
	uint32_t elem1h = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t elem1l = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t elem2h = frame->operandStack.top();
  frame->operandStack.pop();

	uint32_t elem2l = frame->operandStack.top();
  frame->operandStack.pop();

	uint64_t elem1 = (((uint64_t)elem1h) << 32) | elem1l;
	uint64_t elem2 = (((uint64_t)elem2h) << 32) | elem2l;
	uint64_t result = (elem1 ^ elem2);

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);
}

void i_iinc(Frame* frame, uint8_t index, uint8_t inc){
	frame->localVariables.at(index) = frame->localVariables.at(index) + inc;
}

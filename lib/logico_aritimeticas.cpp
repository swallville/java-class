#include "logico_aritimeticas.hpp"

void i_iadd(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t sresult = elem1 + elem2;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_ladd(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem1 + elem2;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_fadd(Frame* frame){
	int32_t elem1 = frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2 = frame->operandStack.top().operand;
  frame->operandStack.pop();

	float f1, f2;

	f1 = decodeFloat(elem1);
	f2 = decodeFloat(elem2);
	//memcpy(&f1, &elem1, sizeof(int32_t));
	//memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = f1 + f2;
	//printf("f1 in fadd - %f\n", f1);
	//printf("f2 in fadd - %f\n", f2);
	//printf("fresult in fadd - %f\n", fresult);
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;
	data1->operand_float = fresult;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_dadd(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
	frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
	frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top().operand;
	frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top().operand;
	frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1 = decodeDouble(elem1h, elem1l);
	double d2 = decodeDouble(elem2h, elem2l);
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = d1 + d2;
	//printf("double d1 at dadd - %f\n", d1);
	//printf("double d2 at dadd - %f\n", d2);
	//printf("double result at dadd - %f\n", dresult);

	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;
	data1->operand_double = dresult;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;
	data2->operand_double = dresult;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_isub(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t sresult = elem2 - elem1;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_lsub(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem2 - elem1;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_fsub(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	float f1, f2;
	f1 = decodeFloat(elem1);
	f2 = decodeFloat(elem2);

	//memcpy(&f1, &elem1, sizeof(int32_t));
	//memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = f2 - f1;
	//printf("f1 in fsub - %f\n", f1);
	//printf("f2 in fsub - %f\n", f2);
	//printf("fresult in fsub - %f\n", fresult);
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_dsub(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = d2 - d1;
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_imul(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t sresult = elem1 * elem2;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_lmul(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	int64_t sresult = elem1 * elem2;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_fmul(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = f1 * f2;
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_dmul(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top().operand;
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

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_idiv(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t sresult = elem2 / elem1;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_ldiv(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;

	int64_t sresult = elem2 / elem1;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_fdiv(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = f2 / f1;
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_ddiv(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = d2 / d1;
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_irem(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t sresult = elem2 % elem1;
	uint32_t result;
	memcpy(&result, &sresult, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_lrem(Frame* frame){
	int32_t elem1h =(int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	long sresult = elem2 % elem1;
	uint64_t result;
	memcpy(&result, &sresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_frem(Frame* frame){
	int32_t elem1 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2 = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	float f1, f2;
	memcpy(&f1, &elem1, sizeof(int32_t));
	memcpy(&f2, &elem2, sizeof(int32_t));
	float fresult = fmodf(f1,f2);
	//printf("fresult frem - %f\n", fresult);
	uint32_t result;
	memcpy(&result, &fresult, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_drem(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem2l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int64_t elem1 = (((int64_t)elem1h) << 32) | elem1l;
	int64_t elem2 = (((int64_t)elem2h) << 32) | elem2l;
	double d1, d2;
	memcpy(&d1, &elem1, sizeof(int64_t));
	memcpy(&d2, &elem2, sizeof(int64_t));
	double dresult = fmod(d2,d1);
	uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_ineg(Frame* frame){
	int32_t elem = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t nelem = ((~elem) + 1);

	uint32_t result;
	memcpy(&result, &nelem, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_lneg(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int64_t elem = (((int64_t)elem1h) << 32) | elem1l;
	int64_t nelem = ((~elem) + 1);
	//printf("nelem at lneg - %lld\n", nelem);

	uint64_t result;
	memcpy(&result, &nelem, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_fneg(Frame* frame){
	int32_t elem = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	float f;
	memcpy(&f, &elem, sizeof(int32_t));
	float nelem = f*(-1);
	uint32_t result;
	memcpy(&result, &nelem, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_dneg(Frame* frame){
	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int64_t elem = (((int64_t)elem1h) << 32) | elem1l;
	double d;
	memcpy(&d, &elem, sizeof(int64_t));
	double nelem = d*(-1);
	uint64_t result;
	memcpy(&result, &nelem, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_ishl(Frame* frame){
	uint32_t shift = frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	shift &= 0x1F;
	elem = (elem << shift);
	uint32_t result;
	memcpy(&result, &elem, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_lshl(Frame* frame){
	uint64_t shift = (uint64_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int64_t elem = (((int64_t)elem1h) << 32) | elem1l;

	shift &= 0x3F;
	elem = (elem << shift);
	uint64_t result;
	memcpy(&result, &elem, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_ishr(Frame* frame){
	uint32_t shift = frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	shift &= 0x1F;
	//printf("elem in ishr - %d\n", elem);
	elem = (elem >> shift);
	//printf("elem in ishr after shift- %d\n", elem);
	uint32_t result;
	memcpy(&result, &elem, sizeof(uint32_t));

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_lshr(Frame* frame){
	uint64_t shift = (uint64_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1h = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int32_t elem1l = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

	int64_t elem = (((int64_t)elem1h) << 32) | elem1l;

	shift &= 0x3F;
	elem = (elem >> shift);
	uint64_t result;
	memcpy(&result, &elem, sizeof(uint64_t));

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_iushr(Frame* frame){
	uint32_t shift = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem = frame->operandStack.top().operand;
  frame->operandStack.pop();

	shift &= 0x1F;
	elem = (elem >> shift);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = elem;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_lushr(Frame* frame){
	uint32_t shift = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elemh = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t eleml = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint64_t elem = (((uint64_t)elemh) << 32) | eleml;

	shift &= 0x3F;
	elem = (elem >> shift);

	uint32_t low = (uint32_t)(elem & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(elem >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_iand(Frame* frame){
	uint32_t elem1 = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem2 = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t result = (elem1 & elem2);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_land(Frame* frame){
	uint32_t elem1h = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem1l = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem2h = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem2l = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint64_t elem1 = (((uint64_t)elem1h) << 32) | elem1l;
	uint64_t elem2 = (((uint64_t)elem2h) << 32) | elem2l;
	uint64_t result = (elem1 & elem2);

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_ior(Frame* frame){
	uint32_t elem1 = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem2 = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t result = (elem1 | elem2);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_lor(Frame* frame){
	uint32_t elem1h = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem1l = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem2h = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem2l = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint64_t elem1 = (((uint64_t)elem1h) << 32) | elem1l;
	uint64_t elem2 = (((uint64_t)elem2h) << 32) | elem2l;
	uint64_t result = (elem1 | elem2);

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_ixor(Frame* frame){
	uint32_t elem1 = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem2 = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t result = (elem1 ^ elem2);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = result;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	return;
}

void i_lxor(Frame* frame){
	uint32_t elem1h = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem1l = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem2h = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint32_t elem2l = frame->operandStack.top().operand;
  frame->operandStack.pop();

	uint64_t elem1 = (((uint64_t)elem1h) << 32) | elem1l;
	uint64_t elem2 = (((uint64_t)elem2h) << 32) | elem2l;
	uint64_t result = (elem1 ^ elem2);

	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = low;

	frame->operandStack.push((*data1));

	free(data1);
  data1 = NULL;

	uint32_t high = (uint32_t)(result >> 32);

	Data * data2 = (Data*) malloc(sizeof(Data));
	data2->operand = high;

	frame->operandStack.push((*data2));

	free(data2);
  data2 = NULL;

	return;
}

void i_iinc(Frame* frame, uint8_t index, int8_t inc){
	frame->localVariables.at(index).operand += inc;
	//printf("value at %d iinc - %d\n", index, frame->localVariables.at(index).operand);
	return;
}

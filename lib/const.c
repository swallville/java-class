#include "const.h"

void i_aconst_null(Frame* frame)
{
	uint32_t *value = (uint32_t*)malloc(sizeof(uint32_t));
	*value = 0;
	push(&(value),(frame->operandStack));
	
  return;
}

void i_iconst_m1(Frame* frame)
{
	int32_t f = -1;
	
	uint32_t value;
	memcpy(&value,&f,sizeof(uint32_t));
	push(&(value), &(frame->operandStack));
  return;
}

void i_iconst_0(Frame* frame)
{
	int32_t f = 0;
	
	uint32_t value;
	memcpy(&value,&f,sizeof(uint32_t));
	push(&(value), &(frame->operandStack));
  return;
}

void i_iconst_1(Frame* frame)
{
	int32_t f = 1;
	
	uint32_t value;
	memcpy(&value,&f,sizeof(uint32_t));
	push(&(value), &(frame->operandStack));
  return;
}

void i_iconst_2(Frame* frame)
{
	int32_t f = 2;
	
	uint32_t value;
	memcpy(&value,&f,sizeof(uint32_t));
	push(&(value), &(frame->operandStack));
  return;
}

void i_iconst_3(Frame* frame)
{
	
	int32_t f =3;
	
	uint32_t value;
	memcpy(&value,&f,sizeof(uint32_t));
	push(&(value), &(frame->operandStack));
  return;
}

void i_iconst_4(Frame* frame)
{
	int32_t f = 4;
	
	uint32_t value;
	memcpy(&value,&f,sizeof(uint32_t));
	push(&(value), &(frame->operandStack));
  return;
}

void i_iconst_5(Frame* frame)
{
	int32_t f = 5;
	
	uint32_t value;
	memcpy(&value,&f,sizeof(uint32_t));
	push(&(value), &(frame->operandStack));
  return;
}
void i_lconst_0(Frame* frame)
{
	uint64_t result = 0;
	
	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
	
  return;
}

void i_lconst_1(Frame* frame)
{
	uint64_t result = 1;
	
	uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
  return;
}

void i_fconst_0(Frame* frame)
{
	float value1 = 0.0;
	uint32_t value;
	 memcpy(&value,&value1,sizeof(uint32_t));
	 push(&(value), &(frame->operandStack));
  return;
}

void i_fconst_1(Frame* frame)
{
	float value1 = 1.0;
	uint32_t value;
	memcpy(&value,&value1,sizeof(uint32_t));
	push(&(value), &(frame->operandStack));
  return;
}

void i_fconst_2(Frame* frame)
{
	float value1 = 2.0;
	uint32_t value;
	memcpy(&value,&value1,sizeof(uint32_t));
	push(&(value), &(frame->operandStack));
  return;
}

void i_dconst_0(Frame* frame)
{
	double value1 = 0.0;
	uint64_t value;
	memcpy(&value,&value1,sizeof(uint64_t));
	
	uint32_t low = (uint32_t)(value & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(value >> 32);
	push(&(high), &(frame->operandStack));
  return;
}

void i_dconst_1(Frame* frame)
{
	double value1 = 1.0;
	uint64_t value;
	memcpy(&value,&value1,sizeof(uint64_t));
	
	uint32_t low = (uint32_t)(value & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(value >> 32);
	push(&(high), &(frame->operandStack));
  return;
}

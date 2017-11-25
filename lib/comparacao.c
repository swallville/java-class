#include "comparacao.h"

void i_lcmp(Frame* frame)
{
  uint64_t long1 = *((uint64_t*)pop(&(frame->operandStack))->value);
  uint64_t long2 = *((uint64_t*)pop(&(frame->operandStack))->value);
  uint32_t result = 0;

  if (long1 == long2){
  	push(&(result), &(frame->operandStack));
  } else if (long1 > long2){
  	result = 1;
  	push(&(result), &(frame->operandStack));
  } else {
  	result = -1;
  	push(&(result), &(frame->operandStack));
  }
  return;
}

void i_fcmpl(Frame* frame)
{

  uint32_t float1 = *((uint32_t*)pop(&(frame->operandStack))->value);
  uint32_t float2 = *((uint32_t*)pop(&(frame->operandStack))->value);
  uint32_t result = 0;
  float number1, number2;
  memcpy(&number1, &float1, sizeof(uint32_t));
  memcpy(&number2, &float2, sizeof(uint32_t));

  if (number1 == number2){
  	push(&(result), &(frame->operandStack));
  } else if (number1 > number2){
  	result = 1;
  	push(&(result), &(frame->operandStack));
  } else {
  	result = -1;
  	push(&(result), &(frame->operandStack));
  }
  return;
}

void i_fcmpg(Frame* frame)
{
	uint32_t float1 = *((uint32_t*)pop(&(frame->operandStack))->value);
  uint32_t float2 = *((uint32_t*)pop(&(frame->operandStack))->value);
  uint32_t result = 0;
  float number1, number2;
  memcpy(&number1, &float1, sizeof(uint32_t));
  memcpy(&number2, &float2, sizeof(uint32_t));

  if (number1 == number2){
  	push(&(result), &(frame->operandStack));
  } else if (number1 > number2){
  	result = 1;
  	push(&(result), &(frame->operandStack));
  } else {
  	result = -1;
  	push(&(result), &(frame->operandStack));
  }
  return;
}

void i_dcmpl(Frame* frame)
{
	uint64_t double1 = *((uint64_t*)pop(&(frame->operandStack))->value);
  uint64_t double2 = *((uint64_t*)pop(&(frame->operandStack))->value);
  uint32_t result = 0;
  float number1, number2;

  memcpy(&number1, &double1, sizeof(uint64_t));
  memcpy(&number2, &double2, sizeof(uint64_t));

  if (number1 == number2){
  	push(&(result), &(frame->operandStack));
  } else if (number1 > number2){
  	result = 1;
  	push(&(result), &(frame->operandStack));
  } else {
  	result = -1;
  	push(&(result), &(frame->operandStack));
  }
  return;
}

void i_dcmpg(Frame* frame)
{
	uint64_t double1 = *((uint64_t*)pop(&(frame->operandStack))->value);
  uint64_t double2 = *((uint64_t*)pop(&(frame->operandStack))->value);
  uint32_t result = 0;
  float number1, number2;
  memcpy(&number1, &double1, sizeof(uint64_t));
  memcpy(&number2, &double2, sizeof(uint64_t));

  if (number1 == number2){
  	push(&(result), &(frame->operandStack));
  } else if (number1 > number2){
  	result = 1;
  	push(&(result), &(frame->operandStack));
  } else {
  	result = -1;
  	push(&(result), &(frame->operandStack));
  }
  return;
}

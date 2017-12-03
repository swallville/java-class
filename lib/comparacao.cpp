#include "comparacao.hpp"

void i_lcmp(Frame* frame)
{
  uint32_t long1h = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t long1l = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t long2h = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t long2l = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t result = 0;

  uint64_t long1 = (((uint64_t)long1h) << 32) | long1l;
  uint64_t long2 = (((uint64_t)long2h) << 32) | long2l;

  Data * data1 = (Data*) malloc(sizeof(Data));

  if (long2 == long1){
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  } else if (long2 > long1){
  	result = 1;
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  } else {
  	result = -1;
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  }

  return;
}

void i_fcmpl(Frame* frame)
{
  uint32_t float1 = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t float2 = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t result = 0;
  float number1 = decodeFloat(float1);
  float number2 = decodeFloat(float2);
  //memcpy(&number1, &float1, sizeof(uint32_t));
  //memcpy(&number2, &float2, sizeof(uint32_t));

  //printf("Float 1 in fcmpl - %f\n", number1);
  //printf("Float 2 in fcmpl - %f\n", number2);

  Data * data1 = (Data*) malloc(sizeof(Data));

  if (number2 == number1){
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  } else if (number2 > number1){
  	result = 1;
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  } else {
  	result = -1;
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  }
  return;
}

void i_fcmpg(Frame* frame)
{
	uint32_t float1 = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t float2 = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t result = 0;
  float number1 = decodeFloat(float1);
  float number2 = decodeFloat(float2);
  //memcpy(&number1, &float1, sizeof(uint32_t));
  //memcpy(&number2, &float2, sizeof(uint32_t));

  Data * data1 = (Data*) malloc(sizeof(Data));

  if (number2 == number1){
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  } else if (number2 > number1){
  	result = 1;
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  } else {
  	result = -1;
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  }
  return;
}

void i_dcmpl(Frame* frame)
{
	uint32_t double1h = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t double1l = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t double2h = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t double2l = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t result = 0;

  uint64_t double1 = (((uint64_t)double1h) << 32) | double1l;
  uint64_t double2 = (((uint64_t)double2h) << 32) | double2l;
  //double number1, number2;

  //memcpy(&number1, &double1, sizeof(uint64_t));
  //memcpy(&number2, &double2, sizeof(uint64_t));

  //printf("dcmpl number1 - %llu\n", double1);
  //printf("dcmpl number2 - %llu\n", double2);

  Data * data1 = (Data*) malloc(sizeof(Data));

  if (double2 == double1){
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  } else if (double2 > double1){
  	result = 1;
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  } else {
  	result = -1;
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  }
  return;
}

void i_dcmpg(Frame* frame)
{
	uint32_t double1h = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t double1l = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t double2h = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t double2l = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t result = 0;

  uint64_t double1 = (((uint64_t)double1h) << 32) | double1l;
  uint64_t double2 = (((uint64_t)double2h) << 32) | double2l;

  //double number1, number2;

  //memcpy(&number1, &double1, sizeof(uint64_t));
  //memcpy(&number2, &double2, sizeof(uint64_t));

  Data * data1 = (Data*) malloc(sizeof(Data));

  if (double2 == double1){
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  } else if (double2 > double1){
  	result = 1;
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  } else {
  	result = -1;
    data1->operand = result;
  	frame->operandStack.push((*data1));
    free(data1);
    data1 = NULL;
  }
  return;
}

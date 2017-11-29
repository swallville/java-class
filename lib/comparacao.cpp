#include "comparacao.hpp"

void i_lcmp(Frame* frame)
{
  uint32_t long1h = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t long1l = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t long2h = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t long2l = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t result = 0;

  uint64_t long1 = (((uint64_t)long1h) << 32) | long1l;
  uint64_t long2 = (((uint64_t)long2h) << 32) | long2l;

<<<<<<< HEAD
  if (long2 == long1){
  	frame->operandStack.push(result);
  } else if (long2 > long1){
=======
  if (long1 == long2){
  	frame->operandStack.push(result);
  } else if (long1 > long2){
>>>>>>> 10ff1a779176f4f5c0055bd6de39ba66a18fc861
  	result = 1;
  	frame->operandStack.push(result);
  } else {
  	result = -1;
  	frame->operandStack.push(result);
  }

  return;
}

void i_fcmpl(Frame* frame)
{
  uint32_t float1 = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t float2 = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t result = 0;
  float number1, number2;
  memcpy(&number1, &float1, sizeof(uint32_t));
  memcpy(&number2, &float2, sizeof(uint32_t));

<<<<<<< HEAD
  if (number2 == number1){
  	frame->operandStack.push(result);
  } else if (number2 > number1){
=======
  if (number1 == number2){
  	frame->operandStack.push(result);
  } else if (number1 > number2){
>>>>>>> 10ff1a779176f4f5c0055bd6de39ba66a18fc861
  	result = 1;
  	frame->operandStack.push(result);
  } else {
  	result = -1;
  	frame->operandStack.push(result);
  }
  return;
}

void i_fcmpg(Frame* frame)
{
	uint32_t float1 = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t float2 = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t result = 0;
  float number1, number2;
  memcpy(&number1, &float1, sizeof(uint32_t));
  memcpy(&number2, &float2, sizeof(uint32_t));

<<<<<<< HEAD
  if (number2 == number1){
  	frame->operandStack.push(result);
  } else if (number2 > number1){
=======
  if (number1 == number2){
  	frame->operandStack.push(result);
  } else if (number1 > number2){
>>>>>>> 10ff1a779176f4f5c0055bd6de39ba66a18fc861
  	result = 1;
  	frame->operandStack.push(result);
  } else {
  	result = -1;
  	frame->operandStack.push(result);
  }
  return;
}

void i_dcmpl(Frame* frame)
{
	uint32_t double1h = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t double1l = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t double2h = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t double2l = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t result = 0;

  uint64_t double1 = (((uint64_t)double1h) << 32) | double1l;
  uint64_t double2 = (((uint64_t)double2h) << 32) | double2l;
<<<<<<< HEAD
  //double number1, number2;

  //memcpy(&number1, &double1, sizeof(uint64_t));
  //memcpy(&number2, &double2, sizeof(uint64_t));

  //printf("dcmpl number1 - %llu\n", double1);
  //printf("dcmpl number2 - %llu\n", double2);

  if (double2 == double1){
  	frame->operandStack.push(result);
  } else if (double2 > double1){
=======
  double number1, number2;

  memcpy(&number1, &double1, sizeof(uint64_t));
  memcpy(&number2, &double2, sizeof(uint64_t));

  if (number1 == number2){
  	frame->operandStack.push(result);
  } else if (number1 > number2){
>>>>>>> 10ff1a779176f4f5c0055bd6de39ba66a18fc861
  	result = 1;
  	frame->operandStack.push(result);
  } else {
  	result = -1;
  	frame->operandStack.push(result);
  }
  return;
}

void i_dcmpg(Frame* frame)
{
	uint32_t double1h = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t double1l = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t double2h = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t double2l = frame->operandStack.top();
  frame->operandStack.pop();

  uint32_t result = 0;

  uint64_t double1 = (((uint64_t)double1h) << 32) | double1l;
  uint64_t double2 = (((uint64_t)double2h) << 32) | double2l;
<<<<<<< HEAD
  //double number1, number2;

  //memcpy(&number1, &double1, sizeof(uint64_t));
  //memcpy(&number2, &double2, sizeof(uint64_t));

  if (double2 == double1){
  	frame->operandStack.push(result);
  } else if (double2 > double1){
=======
  double number1, number2;

  memcpy(&number1, &double1, sizeof(uint64_t));
  memcpy(&number2, &double2, sizeof(uint64_t));

  if (number1 == number2){
  	frame->operandStack.push(result);
  } else if (number1 > number2){
>>>>>>> 10ff1a779176f4f5c0055bd6de39ba66a18fc861
  	result = 1;
  	frame->operandStack.push(result);
  } else {
  	result = -1;
  	frame->operandStack.push(result);
  }
  return;
}

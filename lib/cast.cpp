#include "cast.hpp"

void i_i2l(Frame* frame)
{
  int64_t result = (int64_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

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

void i_i2f(Frame* frame)
{
  int32_t i = frame->operandStack.top().operand;
  frame->operandStack.pop();

  float f = (float) i;
  uint32_t result;
  memcpy(&result, &f, sizeof(uint32_t));

  Data * data1 = (Data*) malloc(sizeof(Data));
  data1->operand = result;

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_i2d(Frame* frame)
{
  int32_t temp = frame->operandStack.top().operand;
  frame->operandStack.pop();
  //printf("value into i2d - %d\n", temp);

  double dresult = (double)temp;
  //printf("dresult into i2d - %f\n", dresult);

  uint64_t result;
	memcpy(&result, &dresult, sizeof(uint64_t));
  //printf("result into i2d - %llu\n", result);

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

  //printf("double value at i2d - %f\n", decodeDouble(high, low));

  free(data2);
  data2 = NULL;

  return;
}

void i_l2i(Frame* frame)
{
  uint32_t high_bytes = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t low_bytes = frame->operandStack.top().operand;
  frame->operandStack.pop();

  int32_t result = (((int64_t)high_bytes) << 32) | low_bytes;

  Data * data1 = (Data*) malloc(sizeof(Data));
  data1->operand = result;

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_l2f(Frame* frame)
{
  uint32_t resulth = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t resultl = frame->operandStack.top().operand;
  frame->operandStack.pop();

  int64_t resultd = (((int64_t)resulth) << 32) | resultl;

  //printf("resultd at l2f - %lld\n", resultd);

  float f = (float) resultd;
  //printf("f at l2f - %f\n", f);

  int32_t result;
  memcpy(&result, &f, sizeof(uint32_t));
  //printf("result at l2f - %d\n", result);

  Data * data1 = (Data*) malloc(sizeof(Data));
  data1->operand = result;

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_l2d(Frame* frame)
{
  uint32_t resulth = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t resultl = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint64_t resultd = (((uint64_t)resulth) << 32) | resultl;
  double d = (double) resultd;
  uint64_t result2;
  memcpy(&result2,&d,sizeof(uint64_t));

  uint32_t low = (uint32_t)(result2 & 0x00000000FFFFFFFF);

  Data * data1 = (Data*) malloc(sizeof(Data));

  data1->operand = low;

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  uint32_t high = (uint32_t)(result2 >> 32);

  Data * data2 = (Data*) malloc(sizeof(Data));

  data2->operand = high;

  frame->operandStack.push((*data2));

  free(data2);
  data2 = NULL;

  return;
}

void i_f2i(Frame* frame)
{
  float f = frame->operandStack.top().operand_float;
  frame->operandStack.pop();

  int32_t i = (int32_t)f;
  //memcpy(&i, &f, sizeof(uint32_t));

  //uint32_t result = i;

  Data * data1 = (Data*) malloc(sizeof(Data));
  data1->operand = i;

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_f2l(Frame* frame)
{
  uint32_t temp = frame->operandStack.top().operand;
  frame->operandStack.pop();

  float temp2;
  memcpy(&temp2, &temp, sizeof(uint32_t));

  uint64_t result = temp2;

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

void i_f2d(Frame* frame)
{
  uint32_t temp = frame->operandStack.top().operand;
  frame->operandStack.pop();

  float temp2;

  memcpy(&temp2, &temp, sizeof(uint32_t));

  double temp3 = temp2;

  uint64_t result;
  memcpy(&result, &temp3, sizeof(uint64_t));

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

void i_d2i(Frame* frame)
{
  uint32_t resulth = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t resultl = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint64_t resultd = (((uint64_t)resulth) << 32) | resultl;

  double d;
  memcpy(&d, &resultd, sizeof(uint64_t));

  uint32_t result = d;

  Data * data1 = (Data*) malloc(sizeof(Data));
  data1->operand = result;

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_d2l(Frame* frame)
{
  uint32_t resulth = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t resultl = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint64_t resultd = (((uint64_t)resulth) << 32) | resultl;
  double d;
  memcpy(&d, &resultd, sizeof(uint64_t));
  uint64_t result2 = d;

  uint32_t low = (uint32_t)(result2 & 0x00000000FFFFFFFF);

  Data * data1 = (Data*) malloc(sizeof(Data));

  data1->operand = low;

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  uint32_t high = (uint32_t)(result2 >> 32);

  Data * data2 = (Data*) malloc(sizeof(Data));

  data2->operand = high;

  frame->operandStack.push((*data2));

  free(data2);
  data2 = NULL;

  return;
}

void i_d2f(Frame* frame)
{
  uint32_t resulth = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t resultl = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint64_t resultd = (((uint64_t)resulth) << 32) | resultl;

  double d;
  memcpy(&d, &resultd, sizeof(uint64_t));
  float f = d;
  uint32_t result;
  memcpy(&result, &f, sizeof(uint32_t));

  Data * data1 = (Data*) malloc(sizeof(Data));
  data1->operand = result;

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_i2b(Frame* frame)
{
  int32_t result = frame->operandStack.top().operand;
  frame->operandStack.pop();

  /*std::string str = std::to_string(result);

  char * cstr = new char [str.length() + 1];
  std::strcpy (cstr, str.c_str());

  int32_t value = atoi(cstr);*/

  char c = static_cast<char>(result);
  int32_t value = c;

  Data * data1 = (Data*) malloc(sizeof(Data));
  data1->operand = value;

  //printf("value at i2b - %d\n", value);

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  //delete[] cstr;

  return;
}

void i_i2c(Frame* frame)
{
  int32_t result = frame->operandStack.top().operand;
  frame->operandStack.pop();

  //printf("result at i2c - %d\n", result);

  wchar_t c = static_cast<wchar_t>(result);
  //unsigned char c = static_cast<char>(result);
  int32_t value = c;

  Data * data1 = (Data*) malloc(sizeof(Data));
  data1->operand = value;

  //printf("value at i2c - %c\n", value);

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  //delete[] cstr;

  return;
}

void i_i2s(Frame* frame)
{
  int32_t result = frame->operandStack.top().operand;
  frame->operandStack.pop();

  short temp = result;
  int32_t value = temp;

  Data * data1 = (Data*) malloc(sizeof(Data));
  data1->operand = value;

  frame->operandStack.push((*data1));

  //printf("value at i2s - %d\n", value);

  free(data1);
  data1 = NULL;

  return;
}

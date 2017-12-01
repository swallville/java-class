#include "cast.hpp"

void i_i2l(Frame* frame)
{
  uint64_t result = (uint64_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
  Data * data1 = (Data*) set_mem(sizeof(Data));
  data1->operand = low;

  frame->operandStack.push((*data1));

  uint32_t high = (uint32_t)(result >> 32);
  Data * data2 = (Data*) set_mem(sizeof(Data));
  data2->operand = high;

  frame->operandStack.push((*data2));

  return;
}

void i_i2f(Frame* frame)
{
  uint32_t i = frame->operandStack.top().operand;
  frame->operandStack.pop();

  float f = (float) i;
  uint32_t result;
  memcpy(&result, &f, sizeof(uint32_t));

  Data * data1 = (Data*) set_mem(sizeof(Data));
  data1->operand = result;

  frame->operandStack.push((*data1));

  return;
}

void i_i2d(Frame* frame)
{
  uint64_t result = (uint64_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
  double d = (double) low;
  uint32_t result2 = d;

  Data * data1 = (Data*) set_mem(sizeof(Data));
  data1->operand = result2;

  frame->operandStack.push((*data1));

  uint32_t high = (uint32_t)(result >> 32);
  double d2 = (double) high;
  uint32_t result3 = d2;

  Data * data2 = (Data*) set_mem(sizeof(Data));
  data2->operand = result3;

  frame->operandStack.push((*data2));

  return;
}

void i_l2i(Frame* frame)
{
  uint32_t high_bytes = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t low_bytes = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t result = (((uint64_t)high_bytes) << 32) | low_bytes;

  Data * data1 = (Data*) set_mem(sizeof(Data));
  data1->operand = result;

  frame->operandStack.push((*data1));

  return;
}

void i_l2f(Frame* frame)
{
  uint32_t resulth = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t resultl = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint64_t resultd = (((uint64_t)resulth) << 32) | resultl;

  double d;
  memcpy(&d, &resultd, sizeof(uint64_t));
  float f = (float) d;
  uint32_t result;
  memcpy(&result, &f, sizeof(uint32_t));

  Data * data1 = (Data*) set_mem(sizeof(Data));
  data1->operand = result;

  frame->operandStack.push((*data1));

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

  Data * data1 = (Data*) set_mem(sizeof(Data));

  data1->operand = low;

  frame->operandStack.push((*data1));

  uint32_t high = (uint32_t)(result2 >> 32);

  Data * data2 = (Data*) set_mem(sizeof(Data));

  data2->operand = high;

  frame->operandStack.push((*data2));

  return;
}

void i_f2i(Frame* frame)
{
  uint32_t f = frame->operandStack.top().operand;
  frame->operandStack.pop();

  int i = (int) f;
  uint32_t result;
  memcpy(&result, &i, sizeof(uint32_t));

  Data * data1 = (Data*) set_mem(sizeof(Data));
  data1->operand = result;

  frame->operandStack.push((*data1));

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

  Data * data1 = (Data*) set_mem(sizeof(Data));

  data1->operand = low;

  frame->operandStack.push((*data1));

  uint32_t high = (uint32_t)(result >> 32);

  Data * data2 = (Data*) set_mem(sizeof(Data));

  data2->operand = high;

  frame->operandStack.push((*data2));

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

  Data * data1 = (Data*) set_mem(sizeof(Data));

  data1->operand = low;

  frame->operandStack.push((*data1));

  uint32_t high = (uint32_t)(result >> 32);

  Data * data2 = (Data*) set_mem(sizeof(Data));

  data2->operand = high;

  frame->operandStack.push((*data2));

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

  Data * data1 = (Data*) set_mem(sizeof(Data));
  data1->operand = result;

  frame->operandStack.push((*data1));

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

  Data * data1 = (Data*) set_mem(sizeof(Data));

  data1->operand = low;

  frame->operandStack.push((*data1));

  uint32_t high = (uint32_t)(result2 >> 32);

  Data * data2 = (Data*) set_mem(sizeof(Data));

  data2->operand = high;

  frame->operandStack.push((*data2));

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

  Data * data1 = (Data*) set_mem(sizeof(Data));
  data1->operand = result;

  frame->operandStack.push((*data1));

  return;
}

void i_i2b(Frame* frame)
{
  uint32_t result = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint8_t lowlowb = (uint8_t)(result & 0x00000000000FFFF);
  uint32_t lowlow = lowlowb;

  Data * data1 = (Data*) set_mem(sizeof(Data));
  data1->operand = lowlow;

  frame->operandStack.push((*data1));

  result = (uint32_t)(result >> 8);
  uint8_t lowb = (uint8_t)(result & 0x00000000000FFFF);
  uint32_t low = lowb;

  Data * data2 = (Data*) set_mem(sizeof(Data));
  data2->operand = low;

  frame->operandStack.push((*data2));

  result = (uint32_t)(result >> 8);
  uint8_t highlowb = (uint8_t)(result & 0x00000000000FFFF);
  uint32_t highlow = highlowb;

  Data * data3 = (Data*) set_mem(sizeof(Data));
  data3->operand = highlow;

  frame->operandStack.push((*data3));

  result = (uint32_t)(result >> 8);
  uint8_t highb = (uint8_t)(result & 0x000000000000FFFF);
  uint32_t high = highb;

  Data * data4 = (Data*) set_mem(sizeof(Data));
  data4->operand = high;

  frame->operandStack.push((*data4));

  return;
}

void i_i2c(Frame* frame)
{
  uint32_t result = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint16_t lowc = (uint16_t)(result & 0x00000000FFFFFFFF);
  uint32_t low = lowc;

  Data * data1 = (Data*) set_mem(sizeof(Data));
  data1->operand = low;

  frame->operandStack.push((*data1));

  uint16_t highc = (uint16_t)(result >> 16);
  uint32_t high = highc;

  Data * data2 = (Data*) set_mem(sizeof(Data));
  data2->operand = high;

  frame->operandStack.push((*data2));

  return;
}

void i_i2s(Frame* frame)
{
  uint32_t result = frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint16_t lowc = (uint16_t)(result & 0x00000000FFFFFFFF);
  uint32_t low = lowc;

  Data * data1 = (Data*) set_mem(sizeof(Data));
  data1->operand = low;

  frame->operandStack.push((*data1));

  uint16_t highc = (uint16_t)(result >> 16);
  uint32_t high = highc;

  Data * data2 = (Data*) set_mem(sizeof(Data));
  data2->operand = high;

  frame->operandStack.push((*data2));

  return;
}

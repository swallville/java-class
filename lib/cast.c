#include "cast.h"


void i_i2l(Frame* frame)
{
  uint64_t result = *((uint32_t*)pop(&(frame->operandStack))->value);

  uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
  push(&(low), &(frame->operandStack));

  uint32_t high = (uint32_t)(result >> 32);
  push(&(high),&(frame->operandStack));
  return;
}

void i_i2f(Frame* frame)
{
  uint32_t i = *((uint32_t*)pop(&(frame->operandStack))->value);
  float f = (float) i;
  uint32_t result;
  memcpy(&result, &f, sizeof(uint32_t));
  push(&(result), &(frame->operandStack));
  return;
}

void i_i2d(Frame* frame)
{
  uint64_t result = *((uint32_t*)pop(&(frame->operandStack))->value);

  uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
  double d = (double) low;
  uint32_t result2 = d;
  push(&(result2), &(frame->operandStack));

  uint32_t high = (uint32_t)(result >> 32);
  double d2 = (double) high;
  uint32_t result3 = d2;
  push(&(result3), &(frame->operandStack));
  return;
}

void i_l2i(Frame* frame)
{
  uint64_t result = *((uint64_t*)pop(&(frame->operandStack))->value);

  uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
  push(&(low), &(frame->operandStack));

  uint32_t high = (uint32_t)(result >> 32);
  push(&(high), &(frame->operandStack));
  return;
}

void i_l2f(Frame* frame)
{
  uint64_t result = *((uint64_t*)pop(&(frame->operandStack))->value);

  uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
  float f = (float) low;
  uint32_t result2 = f;
  push(&(result2), &(frame->operandStack));

  uint32_t high = (uint32_t)(result >> 32);
  float f2 = (float) high;
  uint32_t result3 = f2;
  push(&(result3), &(frame->operandStack));
  return;
}

void i_l2d(Frame* frame)
{
  uint64_t result = *((uint64_t*)pop(&(frame->operandStack))->value);
  double d = (double) result;
  uint64_t result2;
  memcpy(&result2,&d,sizeof(uint64_t));

  uint32_t low = (uint32_t)(result2 & 0x00000000FFFFFFFF);
  push(&(low), &(frame->operandStack));

  uint32_t high = (uint32_t)(result2 >> 32);
  push(&(high), &(frame->operandStack));
  return;
}

void i_f2i(Frame* frame)
{
  uint32_t f = *((uint32_t*)pop(&(frame->operandStack))->value);
  int i = (int) f;
  uint32_t result;
  memcpy(&result, &i, sizeof(uint32_t));
  push(&(result), &(frame->operandStack));
  return;
}

void i_f2l(Frame* frame)
{
  uint32_t temp = *((uint32_t*)pop(&(frame->operandStack))->value);

  float temp2;
  memcpy(&temp2, &temp, sizeof(uint32_t));

  uint64_t result = temp2;

  uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
  push(&(low), &(frame->operandStack));

  uint32_t high = (uint32_t)(result >> 32);
  push(&(high), &(frame->operandStack));
  return;
}

void i_f2d(Frame* frame)
{
  uint32_t temp = *((uint32_t*)pop(&(frame->operandStack))->value);
  float temp2;

  memcpy(&temp2, &temp, sizeof(uint32_t));

  double temp3 = temp2;

  uint64_t result;
  memcpy(&result, &temp3, sizeof(uint64_t));

  uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
  push(&(low), &(frame->operandStack));

  uint32_t high = (uint32_t)(result >> 32);
  push(&(high), &(frame->operandStack));

  return;
}

void i_d2i(Frame* frame)
{
  uint64_t result = *((uint64_t*)pop(&(frame->operandStack))->value);

  uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
  push(&(low), &(frame->operandStack));

  uint32_t high = (uint32_t)(result >> 32);
  push(&(high), &(frame->operandStack));

  return;
}

void i_d2l(Frame* frame)
{
  uint64_t result = *((uint64_t*)pop(&(frame->operandStack))->value);
  long l = (long) result;
  uint64_t result2;
  memcpy(&result2,&l,sizeof(uint64_t));

  uint32_t low = (uint32_t)(result2 & 0x00000000FFFFFFFF);
  push(&(low), &(frame->operandStack));

  uint32_t high = (uint32_t)(result2 >> 32);
  push(&(high), &(frame->operandStack));

  return;
}

void i_d2f(Frame* frame)
{
  uint64_t result = *((uint64_t*)pop(&(frame->operandStack))->value);

  uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
  float f = (float) low;
  uint32_t result2 = f;
  push(&(result2), &(frame->operandStack));

  uint32_t high = (uint32_t)(result >> 32);
  float f2 = (float) high;
  uint32_t result3 = f2;
  push(&(result3), &(frame->operandStack));

  return;
}

void i_i2b(Frame* frame)
{
  uint32_t result = *((uint32_t*)pop(&(frame->operandStack))->value);

  uint8_t lowlowb = (uint8_t)(result & 0x00000000000FFFF);
  uint32_t lowlow = lowlowb;
  push(&(lowlow), &(frame->operandStack));

  result = (uint32_t)(result >> 8);
  uint8_t lowb = (uint8_t)(result & 0x00000000000FFFF);
  uint32_t low = lowb;
  push(&(low), &(frame->operandStack));

  result = (uint32_t)(result >> 8);
  uint8_t highlowb = (uint8_t)(result & 0x00000000000FFFF);
  uint32_t highlow = highlowb;
  push(&(highlow), &(frame->operandStack));

  result = (uint32_t)(result >> 8);
  uint8_t highb = (uint8_t)(result & 0x000000000000FFFF);
  uint32_t high = highb;
  push(&(high), &(frame->operandStack));
  return;
}


void i_i2c(Frame* frame)
{
  uint32_t result = *((uint32_t*)pop(&(frame->operandStack))->value);

  uint16_t lowc = (uint16_t)(result & 0x00000000FFFFFFFF);
  uint32_t low = lowc;
  push(&(low), &(frame->operandStack));

  uint16_t highc = (uint16_t)(result >> 16);
  uint32_t high = highc;
  push(&(high), &(frame->operandStack));
  return;
}


void i_i2s(Frame* frame)
{
  uint32_t result = *((uint32_t*)pop(&(frame->operandStack))->value);

  uint16_t lowc = (uint16_t)(result & 0x00000000FFFFFFFF);
  uint32_t low = lowc;
  push(&(low), &(frame->operandStack));

  uint16_t highc = (uint16_t)(result >> 16);
  uint32_t high = highc;
  push(&(high), &(frame->operandStack));
  return;
}

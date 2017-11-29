#include "ifs.hpp"

void i_ifeq(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t result = frame->operandStack.top();
  frame->operandStack.pop();

  if (result == 0) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t offset32 = offset16;
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

void i_ifne(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t result = frame->operandStack.top();
  frame->operandStack.pop();

  if (result != 0) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t offset32 = offset16;
    frame->codeIndexRef += (offset16 - 3);
  }
  return;

}

void i_iflt(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t result = frame->operandStack.top();
  frame->operandStack.pop();

  if (result < 0) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t offset32 = offset16;
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

void i_ifge(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t result = frame->operandStack.top();
  frame->operandStack.pop();

  if (result >= 0) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t offset32 = offset16;
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

void i_ifgt(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t result = frame->operandStack.top();
  frame->operandStack.pop();

  if (result > 0) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t offset32 = offset16;
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

void i_ifle(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t result = frame->operandStack.top();
  frame->operandStack.pop();

  if (result <= 0) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t offset32 = offset16;
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

void i_if_icmpeq(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t elem1 = frame->operandStack.top();
  frame->operandStack.pop();

  int32_t elem2 = frame->operandStack.top();
  frame->operandStack.pop();

  if (elem2 == elem1) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

void i_if_icmpne(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t elem1 = frame->operandStack.top();
  frame->operandStack.pop();

  int32_t elem2 = frame->operandStack.top();
  frame->operandStack.pop();

  if (elem2 != elem1) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

void i_if_icmplt(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t elem1 = frame->operandStack.top();
  frame->operandStack.pop();

  int32_t elem2 = frame->operandStack.top();
  frame->operandStack.pop();

  if (elem2 > elem1) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

void i_if_icmpge(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t elem1 = frame->operandStack.top();
  frame->operandStack.pop();

  int32_t elem2 = frame->operandStack.top();
  frame->operandStack.pop();

  if (elem2 <= elem1) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

void i_if_icmpgt(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t elem1 = frame->operandStack.top();
  frame->operandStack.pop();

  int32_t elem2 = frame->operandStack.top();
  frame->operandStack.pop();

  if (elem2 < elem1) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

void i_if_icmple(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t elem1 = frame->operandStack.top();
  frame->operandStack.pop();

  int32_t elem2 = frame->operandStack.top();
  frame->operandStack.pop();

  if (elem2 >= elem1) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

void i_if_acmpeq(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t elem1 = frame->operandStack.top();
  frame->operandStack.pop();

  int32_t elem2 = frame->operandStack.top();
  frame->operandStack.pop();

  if (elem2 == elem1) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

void i_if_acmpne(Frame* frame, uint8_t index1, uint8_t index2)
{
  int32_t elem1 = frame->operandStack.top();
  frame->operandStack.pop();

  int32_t elem2 = frame->operandStack.top();
  frame->operandStack.pop();

  if (elem2 != elem1) {
    int16_t offset16 = (((int16_t)index1) << 8) + index2;
    //int32_t
    frame->codeIndexRef += (offset16 - 3);
  }
  return;
}

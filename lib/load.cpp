#include "load.hpp"

void i_iload(Frame* frame, uint8_t index)
{
  frame->operandStack.push(frame->localVariables.at(index));

  return;
}

void i_lload(Frame* frame,  uint8_t index)
{
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index]);

    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	  frame->operandStack.push(low);

	  uint32_t high = (uint32_t)(result >> 32);
	  frame->operandStack.push(high);

  return;
}

void i_fload(Frame* frame, uint8_t index)
{
  frame->operandStack.push(frame->localVariables.at(index));

  return;
}

void i_dload(Frame* frame, uint8_t index)
{
  uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

  uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	frame->operandStack.push(low);

	uint32_t high = (uint32_t)(result >> 32);
	frame->operandStack.push(high);

  return;
}

void i_aload(Frame* frame, uint8_t index)
{
  frame->operandStack.push(frame->localVariables.at(index));

  return;
}

void i_iload_0(Frame* frame)
{
  frame->operandStack.push(frame->localVariables.at(0));

  //printf("value iload - %d\n", frame->operandStack.top());

  return;
}

void i_iload_1(Frame* frame)
{
  frame->operandStack.push(frame->localVariables.at(1));

  return;
}

void i_iload_2(Frame* frame)
{
  frame->operandStack.push(frame->localVariables.at(2));

  return;
}

void i_iload_3(Frame* frame)
{
  frame->operandStack.push(frame->localVariables.at(3));

  return;
}

void i_lload_0(Frame* frame)
{
    uint32_t index = 0;
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	  frame->operandStack.push(low);

	  uint32_t high = (uint32_t)(result >> 32);
	  frame->operandStack.push(high);

  return;
}

void i_lload_1(Frame* frame)
{
    uint32_t index = 1;
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	  frame->operandStack.push(low);

	  uint32_t high = (uint32_t)(result >> 32);
	  frame->operandStack.push(high);

  return;
}

void i_lload_2(Frame* frame)
{
    uint32_t index = 2;
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	  frame->operandStack.push(low);

	  uint32_t high = (uint32_t)(result >> 32);
	  frame->operandStack.push(high);

  return;
}

void i_lload_3(Frame* frame)
{
    uint32_t index = 3;
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	  frame->operandStack.push(low);

	  uint32_t high = (uint32_t)(result >> 32);
	  frame->operandStack.push(high);

  return;
}

void i_fload_0(Frame* frame)
{
  frame->operandStack.push(frame->localVariables.at(0));

  return;
}

void i_fload_1(Frame* frame)
{
  frame->operandStack.push(frame->localVariables.at(1));

  return;
}

void i_fload_2(Frame* frame)
{
  frame->operandStack.push(frame->localVariables.at(2));

  return;
}

void i_fload_3(Frame* frame)
{
  frame->operandStack.push(frame->localVariables.at(3));

  return;
}

void i_dload_0(Frame* frame)
{
   uint32_t index = 0;
   uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

   uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	 frame->operandStack.push(low);

	 uint32_t high = (uint32_t)(result >> 32);
	 frame->operandStack.push(high);

  return;
}

void i_dload_1(Frame* frame)
{
    uint32_t index = 1;
    uint32_t teste1 = frame->localVariables[index];
    uint32_t teste2 = frame->localVariables[index+1];
	  uint64_t result = ((uint64_t)teste1) <<32 | teste2;
	  double value;
	  memcpy(&value,&result,sizeof(uint64_t));

    //printf("double into dload_1 - %llu\n", result);

    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	  frame->operandStack.push(low);

	  uint32_t high = (uint32_t)(result >> 32);
	  frame->operandStack.push(high);

  return;
}

void i_dload_2(Frame* frame)
{
    uint32_t index = 2;
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	  frame->operandStack.push(low);

	  uint32_t high = (uint32_t)(result >> 32);
	  frame->operandStack.push(high);

  return;
}

void i_dload_3(Frame* frame)
{
    uint32_t index = 3;
    uint64_t result = (((uint64_t)frame->localVariables.at(index)) << 32) |(frame->localVariables.at(index + 1));

    //printf("double into dload_3 - %llu\n", result);

    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	  frame->operandStack.push(low);

	  uint32_t high = (uint32_t)(result >> 32);
	  frame->operandStack.push(high);

  return;
}


void i_aload_0(Frame* frame)
{
  frame->operandStack.push(frame->localVariables.at(0));

  return;
}

void i_aload_1(Frame* frame)
{
  frame->operandStack.push(frame->localVariables.at(1));

  return;
}

void i_aload_2(Frame* frame)
{
  frame->operandStack.push(frame->localVariables.at(2));

  return;
}

void i_aload_3(Frame* frame)
{
  frame->operandStack.push(frame->localVariables.at(3));

  return;
}

void i_iaload(Frame* frame)
{
   uint32_t index =  frame->operandStack.top();
   frame->operandStack.pop();

   uint32_t ref = frame->operandStack.top();
   frame->operandStack.pop();

   uint32_t* arrayRef = (uint32_t*)(uintptr_t) ref;

   frame->operandStack.push(arrayRef[index]);

  return;
}

void i_laload(Frame* frame)
{
    uint32_t index =  frame->operandStack.top();
    frame->operandStack.pop();

    uint32_t ref = frame->operandStack.top();
    frame->operandStack.pop();

    uint64_t* arrayRef = (uint64_t*)(uintptr_t) ref;

    uint32_t low = (uint32_t)(arrayRef[index] & 0x00000000FFFFFFFF);
    frame->operandStack.push(low);

    uint32_t high = (uint32_t)(arrayRef[index] >> 32);

    frame->operandStack.push(high);

  return;
}

void i_faload(Frame* frame)
{
    uint32_t index =  frame->operandStack.top();
    frame->operandStack.pop();

    uint32_t ref = frame->operandStack.top();
    frame->operandStack.pop();

    uint32_t* arrayRef = (uint32_t*)(uintptr_t) ref;

    frame->operandStack.push(arrayRef[index]);

  return;
}

void i_daload(Frame* frame)
{
    uint32_t index = frame->operandStack.top();
    frame->operandStack.pop();

    uint32_t ref = frame->operandStack.top();
    frame->operandStack.pop();

    uint64_t* arrayRef = (uint64_t*)(uintptr_t) ref;

    uint32_t low = (uint32_t)(arrayRef[index] & 0x00000000FFFFFFFF);
    frame->operandStack.push(low);

    uint32_t high = (uint32_t)(arrayRef[index] >> 32);

    frame->operandStack.push(high);

  return;
}

void i_aaload(Frame* frame)
{
    uint32_t index = frame->operandStack.top();
    frame->operandStack.pop();

    uint32_t ref = frame->operandStack.top();
    frame->operandStack.pop();

    uint32_t* arrayRef = (uint32_t*)(uintptr_t) ref;

    frame->operandStack.push(arrayRef[index]);

  return;
}

void i_baload(Frame* frame)
{
    uint32_t index =  frame->operandStack.top();
    frame->operandStack.pop();

    uint32_t ref = frame->operandStack.top();
    frame->operandStack.pop();

    uint8_t* arrayRef = (uint8_t*)(uintptr_t) ref;

    uint32_t result = (uint32_t)arrayRef[index];

    frame->operandStack.push(result);

  return;
}

void i_caload(Frame* frame)
{
    uint32_t index = frame->operandStack.top();
    frame->operandStack.pop();

    uint32_t ref = frame->operandStack.top();
    frame->operandStack.pop();

    uint16_t* arrayRef = (uint16_t*)(uintptr_t) ref;

    uint32_t result = (uint32_t)arrayRef[index];

    frame->operandStack.push(result);


  return;
}

void i_saload(Frame* frame)
{
    uint32_t index = frame->operandStack.top();
    frame->operandStack.pop();

    uint32_t ref = frame->operandStack.top();
    frame->operandStack.pop();

    uint16_t* arrayRef = (uint16_t*)(uintptr_t) ref;

    uint32_t result = (uint32_t)arrayRef[index];

    frame->operandStack.push(result);
  return;
}

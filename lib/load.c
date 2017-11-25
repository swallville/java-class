#include "load.h"

void i_iload(Frame* frame, uint8_t index)
{
    push(&(frame->localVariables[index]),&(frame->operandStack));

  return;
}

void i_lload(Frame* frame,  uint8_t index)
{
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index]);

    //empilha 64 bits
    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));


  return;
}

void i_fload(Frame* frame, uint8_t index)
{
     push(&(frame->localVariables[index]),&(frame->operandStack));

  return;
}

void i_dload(Frame* frame, uint8_t index)
{
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    //empilha 64 bits
    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));

  return;
}

void i_aload(Frame* frame, uint8_t index)
{
    push(&(frame->localVariables[index]),&(frame->operandStack));

  return;
}

void i_iload_0(Frame* frame)
{
    push(&(frame->localVariables[0]),&(frame->operandStack));
  return;
}

void i_iload_1(Frame* frame)
{
    push(&(frame->localVariables[1]),&(frame->operandStack));
  return;
}

void i_iload_2(Frame* frame)
{
    push(&(frame->localVariables[2]),&(frame->operandStack));
  return;
}

void i_iload_3(Frame* frame)
{
    push(&(frame->localVariables[3]),&(frame->operandStack));

  return;
}

void i_lload_0(Frame* frame)
{
    uint32_t index = 0;
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    //empilha 64 bits
    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
  return;
}

void i_lload_1(Frame* frame)
{
    uint32_t index = 1;
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    //empilha 64 bits
    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));

  return;
}

void i_lload_2(Frame* frame)
{
    uint32_t index = 2;
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    //empilha 64 bits
    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));

  return;
}

void i_lload_3(Frame* frame)
{
    uint32_t index = 3;
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    //empilha 64 bits
    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));

  return;
}

void i_fload_0(Frame* frame)
{
    push(&(frame->localVariables[0]),&(frame->operandStack));
  return;
}

void i_fload_1(Frame* frame)
{
    push(&(frame->localVariables[1]),&(frame->operandStack));

  return;
}

void i_fload_2(Frame* frame)
{
    push(&(frame->localVariables[2]),&(frame->operandStack));

  return;
}

void i_fload_3(Frame* frame)
{
    push(&(frame->localVariables[3]),&(frame->operandStack));

  return;
}

void i_dload_0(Frame* frame)
{
     uint32_t index = 0;
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    //empilha 64 bits
    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));
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

	//empilha 64 bits
    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));


  return;
}

void i_dload_2(Frame* frame)
{
     uint32_t index = 2;
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    //empilha 64 bits
    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));

  return;
}

void i_dload_3(Frame* frame)
{
     uint32_t index = 3;
    uint64_t result = (((uint64_t)frame->localVariables[index]) << 32) |(frame->localVariables[index+1]);

    //empilha 64 bits
    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
	push(&(low), &(frame->operandStack));

	uint32_t high = (uint32_t)(result >> 32);
	push(&(high), &(frame->operandStack));

  return;
}


void i_aload_0(Frame* frame)
{
     push(&(frame->localVariables[0]),&(frame->operandStack));
  return;
}

void i_aload_1(Frame* frame)
{
     push(&(frame->localVariables[1]),&(frame->operandStack));
  return;
}

void i_aload_2(Frame* frame)
{
     push(&(frame->localVariables[2]),&(frame->operandStack));

  return;
}

void i_aload_3(Frame* frame)
{
     push(&(frame->localVariables[3]),&(frame->operandStack));

  return;
}

void i_iaload(Frame* frame)
{
    uint32_t index =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t ref = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t* arrayRef = (uint32_t*)(uintptr_t) ref;
    push(&(arrayRef[index]),&(frame->operandStack));

  return;
}

void i_laload(Frame* frame)
{
    uint32_t index =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t ref = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t* arrayRef = (uint64_t*)(uintptr_t) ref;
    push(&(arrayRef[index]),&(frame->operandStack));

  return;
}

void i_faload(Frame* frame)
{
    uint32_t index =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t ref = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t* arrayRef = (uint32_t*)(uintptr_t) ref;
    push(&(arrayRef[index]),&(frame->operandStack));

  return;
}

void i_daload(Frame* frame)
{
    uint32_t index =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t ref = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t* arrayRef = (uint64_t*)(uintptr_t) ref;
    push(&(arrayRef[index]),&(frame->operandStack));

  return;
}

void i_aaload(Frame* frame)
{
    uint32_t index =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t ref = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t* arrayRef = (uint32_t*)(uintptr_t) ref;
    push(&(arrayRef[index]),&(frame->operandStack));

  return;
}

void i_baload(Frame* frame)
{
    uint32_t index =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t ref = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint8_t* arrayRef = (uint8_t*)(uintptr_t) ref;
    uint32_t result= arrayRef[index];

    push(&result,&(frame->operandStack));

  return;
}

void i_caload(Frame* frame)
{
    uint32_t index =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t ref = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint16_t* arrayRef = (uint16_t*)(uintptr_t) ref;
    uint32_t result= arrayRef[index];

    push(&result,&(frame->operandStack));

  return;
}

void i_saload(Frame* frame)
{
    uint32_t index =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t ref = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint16_t* arrayRef = (uint16_t*)(uintptr_t) ref;
    uint32_t result= arrayRef[index];

    push(&result,&(frame->operandStack));

  return;
}

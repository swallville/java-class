#include "load.hpp"

void i_iload(Frame* frame, uint8_t index)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));
	data1->operand = frame->localVariables.at(index).operand;

	frame->operandStack.push((*data1));

  return;
}

void i_lload(Frame* frame,  uint8_t index)
{
    uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index).operand);

    uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

    Data * data1 = (Data*) set_mem(sizeof(Data));
  	data1->operand = low;

  	frame->operandStack.push((*data1));

	  uint32_t high = (uint32_t)(result >> 32);

    Data * data2 = (Data*) set_mem(sizeof(Data));
  	data1->operand = high;

  	frame->operandStack.push((*data2));

  return;
}

void i_fload(Frame* frame, uint8_t index)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));
	data1->operand = frame->localVariables.at(index).operand;

	frame->operandStack.push((*data1));

  return;
}

void i_dload(Frame* frame, uint8_t index)
{
  uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

  uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

  Data * data1 = (Data*) set_mem(sizeof(Data));
  data1->operand = low;

  frame->operandStack.push((*data1));

	uint32_t high = (uint32_t)(result >> 32);

  Data * data2 = (Data*) set_mem(sizeof(Data));
  data1->operand = high;

  frame->operandStack.push((*data2));

  return;
}

void i_aload(Frame* frame, uint8_t index)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));

  if (frame->localVariables.at(index).tag == 0) {
    data1->reference = (Objeto*)frame->localVariables.at(index).reference;
    data1->tag = 0;
  } else {
    data1->reference = (tArray*)frame->localVariables.at(index).reference;
    data1->tag = 1;
  }

	frame->operandStack.push((*data1));

  return;
}

void i_iload_0(Frame* frame)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));
	data1->operand = frame->localVariables.at(0).operand;

	frame->operandStack.push((*data1));

  //printf("value iload - %d\n", frame->operandStack.top().operand);

  return;
}

void i_iload_1(Frame* frame)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));
	data1->operand = frame->localVariables.at(1).operand;

	frame->operandStack.push((*data1));

  return;
}

void i_iload_2(Frame* frame)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));
	data1->operand = frame->localVariables.at(2).operand;

	frame->operandStack.push((*data1));

  return;
}

void i_iload_3(Frame* frame)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));
	data1->operand = frame->localVariables.at(3).operand;

	frame->operandStack.push((*data1));

  return;
}

void i_lload_0(Frame* frame)
{
    uint32_t index = 0;
    uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

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

void i_lload_1(Frame* frame)
{
    uint32_t index = 1;
    uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

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

void i_lload_2(Frame* frame)
{
    uint32_t index = 2;
    uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

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

void i_lload_3(Frame* frame)
{
    uint32_t index = 3;
    uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

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

void i_fload_0(Frame* frame)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));
	data1->operand = frame->localVariables.at(0).operand;

	frame->operandStack.push((*data1));

  return;
}

void i_fload_1(Frame* frame)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));
	data1->operand = frame->localVariables.at(1).operand;

	frame->operandStack.push((*data1));

  return;
}

void i_fload_2(Frame* frame)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));
	data1->operand = frame->localVariables.at(2).operand;

	frame->operandStack.push((*data1));

  return;
}

void i_fload_3(Frame* frame)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));
	data1->operand = frame->localVariables.at(3).operand;

	frame->operandStack.push((*data1));

  return;
}

void i_dload_0(Frame* frame)
{
   uint32_t index = 0;
   uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

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

void i_dload_1(Frame* frame)
{
    uint32_t index = 1;
    uint32_t teste1 = frame->localVariables.at(index).operand;
    uint32_t teste2 = frame->localVariables.at(index + 1).operand;
	  uint64_t result = ((uint64_t)teste1) << 32 | teste2;
	  double value;
	  memcpy(&value,&result,sizeof(uint64_t));

    //printf("double into dload_1 - %llu\n", result);

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

void i_dload_2(Frame* frame)
{
    uint32_t index = 2;
    uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

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

void i_dload_3(Frame* frame)
{
    uint32_t index = 3;
    uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

    //printf("double into dload_3 - %llu\n", result);

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


void i_aload_0(Frame* frame)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));

  if (frame->localVariables.at(0).tag == 0) {
    data1->reference = (Objeto*)frame->localVariables.at(0).reference;
    data1->tag = 0;
  } else {
    data1->reference = (tArray*)frame->localVariables.at(0).reference;
    data1->tag = 1;
  }

	frame->operandStack.push((*data1));

  return;
}

void i_aload_1(Frame* frame)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));

  if (frame->localVariables.at(1).tag == 0) {
    data1->reference = (Objeto*)frame->localVariables.at(1).reference;
    data1->tag = 0;
  } else {
    data1->reference = (tArray*)frame->localVariables.at(1).reference;
    data1->tag = 1;
  }

	frame->operandStack.push((*data1));

  return;
}

void i_aload_2(Frame* frame)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));

  if (frame->localVariables.at(2).tag == 0) {
    data1->reference = (Objeto*)frame->localVariables.at(2).reference;
    data1->tag = 0;
  } else {
    data1->reference = (tArray*)frame->localVariables.at(2).reference;
    data1->tag = 1;
  }

	frame->operandStack.push((*data1));

  return;
}

void i_aload_3(Frame* frame)
{
  Data * data1 = (Data*) set_mem(sizeof(Data));

  if (frame->localVariables.at(3).tag == 0) {
    data1->reference = (Objeto*)frame->localVariables.at(3).reference;
    data1->tag = 0;
  } else {
    data1->reference = (tArray*)frame->localVariables.at(3).reference;
    data1->tag = 1;
  }

	frame->operandStack.push((*data1));

  return;
}

void i_iaload(Frame* frame)
{
   uint32_t index =  frame->operandStack.top().operand;
   frame->operandStack.pop();

   tArray* ref = (tArray*)frame->operandStack.top().reference;
   frame->operandStack.pop();

   uint32_t* arrayRef = ref->info.tipoInt;

   Data * data1 = (Data*) set_mem(sizeof(Data));
   data1->operand = arrayRef[index];

   frame->operandStack.push((*data1));

  return;
}

void i_laload(Frame* frame)
{
    uint32_t index =  frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    uint64_t* arrayRef = ref->info.tipoLong;

    uint32_t low = (uint32_t)(arrayRef[index] & 0x00000000FFFFFFFF);

    Data * data1 = (Data*) set_mem(sizeof(Data));
  	data1->operand = low;

  	frame->operandStack.push((*data1));

    uint32_t high = (uint32_t)(arrayRef[index] >> 32);

    Data * data2 = (Data*) set_mem(sizeof(Data));
  	data2->operand = high;

  	frame->operandStack.push((*data2));

  return;
}

void i_faload(Frame* frame)
{
    uint32_t index =  frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    uint32_t* arrayRef = ref->info.tipoFloat;

    Data * data1 = (Data*) set_mem(sizeof(Data));
    data1->operand = arrayRef[index];

    frame->operandStack.push((*data1));

  return;
}

void i_daload(Frame* frame)
{
    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    uint64_t* arrayRef = ref->info.tipoDouble;

    uint32_t low = (uint32_t)(arrayRef[index] & 0x00000000FFFFFFFF);

    Data * data1 = (Data*) set_mem(sizeof(Data));
  	data1->operand = low;

  	frame->operandStack.push((*data1));

    uint32_t high = (uint32_t)(arrayRef[index] >> 32);

    Data * data2 = (Data*) set_mem(sizeof(Data));
  	data2->operand = high;

    frame->operandStack.push((*data2));

  return;
}

void i_aaload(Frame* frame)
{
    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    uint32_t* arrayRef = ref->info.tipoReferencia;

    Data * data1 = (Data*) set_mem(sizeof(Data));
    data1->operand = arrayRef[index];

    frame->operandStack.push((*data1));

  return;
}

void i_baload(Frame* frame)
{
    uint32_t index =  frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    uint8_t* arrayRef;

    if (ref->tag == TipoByte) {
      arrayRef = ref->info.tipoByte;
    } else {
      arrayRef = ref->info.tipoBoolean;
    }

    Data * data1 = (Data*) set_mem(sizeof(Data));
    data1->operand = (uint32_t)arrayRef[index];

    frame->operandStack.push((*data1));

  return;
}

void i_caload(Frame* frame)
{
    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    uint16_t* arrayRef = ref->info.tipoChar;

    Data * data1 = (Data*) set_mem(sizeof(Data));
    data1->operand = (uint32_t)arrayRef[index];

    frame->operandStack.push((*data1));

  return;
}

void i_saload(Frame* frame)
{
    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    uint16_t* arrayRef = ref->info.tipoShort;

    Data * data1 = (Data*) set_mem(sizeof(Data));
    data1->operand = (uint32_t)arrayRef[index];

    frame->operandStack.push((*data1));

  return;
}

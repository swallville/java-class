#include "load.hpp"

void i_iload(Frame* frame, int8_t index)
{
  Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = frame->localVariables.at(index).operand;
  //printf("value of index at iload - %d\n", index);
  //printf("value at iload - %d\n", data1->operand);

	frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_lload(Frame* frame, int8_t index)
{
    //uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

    //uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);
    //printf("value at lload - %llu\n", result);
    Data * data1 = (Data*) malloc(sizeof(Data));
  	data1->operand = frame->localVariables.at(index + 1).operand;
  	frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

	  //uint32_t high = (uint32_t)(result >> 32);
    Data * data2 = (Data*) malloc(sizeof(Data));
  	data2->operand = frame->localVariables.at(index).operand;
  	frame->operandStack.push((*data2));

    free(data2);
    data2 = NULL;

  return;
}

void i_fload(Frame* frame, int8_t index)
{
  Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = frame->localVariables.at(index).operand;
  data1->operand_float = decodeFloat(frame->localVariables.at(index).operand);

	frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_dload(Frame* frame, int8_t index)
{
  //uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

  //uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

  Data * data1 = (Data*) malloc(sizeof(Data));
  data1->operand = frame->localVariables.at(index + 1).operand;

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

	//uint32_t high = (uint32_t)(result >> 32);

  Data * data2 = (Data*) malloc(sizeof(Data));
  data2->operand = frame->localVariables.at(index).operand;

  frame->operandStack.push((*data2));

  free(data2);
  data2 = NULL;

  return;
}

void i_aload(Frame* frame, int8_t index)
{
  frame->operandStack.push(frame->localVariables.at(index));

  return;
}

void i_iload_0(Frame* frame)
{
  Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = frame->localVariables.at(0).operand;

	frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  //printf("value iload - %d\n", frame->operandStack.top().operand);

  return;
}

void i_iload_1(Frame* frame)
{
  Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = frame->localVariables.at(1).operand;

	frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_iload_2(Frame* frame)
{
  Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = frame->localVariables.at(2).operand;
  //printf("value at iload_2 - %d\n", data1->operand);

	frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_iload_3(Frame* frame)
{
  Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = frame->localVariables.at(3).operand;

	frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_lload_0(Frame* frame)
{
  //uint32_t index = 0;
  //uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

  //uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

  Data * data1 = (Data*) malloc(sizeof(Data));
  data1->operand = frame->localVariables.at(1).operand;

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  //uint32_t high = (uint32_t)(result >> 32);

  Data * data2 = (Data*) malloc(sizeof(Data));
  data2->operand = frame->localVariables.at(0).operand;

  frame->operandStack.push((*data2));

  free(data2);
  data2 = NULL;

  //printf("Value at lload_0 - %ld\n", decodeLong(frame->localVariables.at(0).operand, frame->localVariables.at(1).operand));

 return;
}

void i_lload_1(Frame* frame)
{
    //uint32_t index = 1;
    //uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

    //uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

    Data * data1 = (Data*) malloc(sizeof(Data));
  	data1->operand = frame->localVariables.at(2).operand;

  	frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

	  //uint32_t high = (uint32_t)(result >> 32);

    Data * data2 = (Data*) malloc(sizeof(Data));
  	data2->operand = frame->localVariables.at(1).operand;

  	frame->operandStack.push((*data2));

    free(data2);
    data2 = NULL;

  return;
}

void i_lload_2(Frame* frame)
{
    //uint32_t index = 2;
    //uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

    //uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

    Data * data1 = (Data*) malloc(sizeof(Data));
  	data1->operand = frame->localVariables.at(3).operand;

  	frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

	  //uint32_t high = (uint32_t)(result >> 32);

    Data * data2 = (Data*) malloc(sizeof(Data));
  	data2->operand = frame->localVariables.at(2).operand;

  	frame->operandStack.push((*data2));

    free(data2);
    data2 = NULL;

  return;
}

void i_lload_3(Frame* frame)
{
    //uint32_t index = 3;
    //uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

    //uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

    Data * data1 = (Data*) malloc(sizeof(Data));
  	data1->operand = frame->localVariables.at(4).operand;

  	frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

	  //uint32_t high = (uint32_t)(result >> 32);

    Data * data2 = (Data*) malloc(sizeof(Data));
  	data2->operand = frame->localVariables.at(3).operand;

  	frame->operandStack.push((*data2));

    free(data2);
    data2 = NULL;

  return;
}

void i_fload_0(Frame* frame)
{
  Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = frame->localVariables.at(0).operand;
  data1->operand_float = decodeFloat(frame->localVariables.at(0).operand);

	frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_fload_1(Frame* frame)
{
  Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = frame->localVariables.at(1).operand;
  data1->operand_float = decodeFloat(frame->localVariables.at(1).operand);

	frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_fload_2(Frame* frame)
{
  Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = frame->localVariables.at(2).operand;
  data1->operand_float = decodeFloat(frame->localVariables.at(2).operand);

	frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_fload_3(Frame* frame)
{
  Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = frame->localVariables.at(3).operand;
  data1->operand_float = decodeFloat(frame->localVariables.at(3).operand);
  //printf("Float in fload_3 - %f\n", data1->operand_float);

	frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

  return;
}

void i_dload_0(Frame* frame)
{
   //int32_t index = 0;
   //uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

   //uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

   //printf("double at dload_0 - %f\n", decodeDouble(frame->localVariables.at(0).operand, frame->localVariables.at(1).operand));

   Data * data1 = (Data*) malloc(sizeof(Data));
   data1->operand = frame->localVariables.at(1).operand;

   frame->operandStack.push((*data1));

   free(data1);
   data1 = NULL;

	 //uint32_t high = (uint32_t)(result >> 32);

   Data * data2 = (Data*) malloc(sizeof(Data));
 	 data2->operand = frame->localVariables.at(0).operand;

 	 frame->operandStack.push((*data2));

   free(data2);
   data2 = NULL;

  return;
}

void i_dload_1(Frame* frame)
{
  //int32_t index = 1;
  //uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

  //uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

  Data * data1 = (Data*) malloc(sizeof(Data));
  data1->operand = frame->localVariables.at(2).operand;

  frame->operandStack.push((*data1));

  free(data1);
  data1 = NULL;

 //uint32_t high = (uint32_t)(result >> 32);

  Data * data2 = (Data*) malloc(sizeof(Data));
  data2->operand = frame->localVariables.at(1).operand;

  frame->operandStack.push((*data2));

  free(data2);
  data2 = NULL;

  return;
}

void i_dload_2(Frame* frame)
{
    //int32_t index = 2;
    //uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

    //uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

    //printf("double at dload_2- %f\n", decodeDouble(frame->localVariables.at(2).operand, frame->localVariables.at(3).operand));

    Data * data1 = (Data*) malloc(sizeof(Data));
    data1->operand = frame->localVariables.at(3).operand;

    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

	  //uint32_t high = (uint32_t)(result >> 32);

    Data * data2 = (Data*) malloc(sizeof(Data));
    data2->operand = frame->localVariables.at(2).operand;

    frame->operandStack.push((*data2));

    free(data2);
    data2 = NULL;

  return;
}

void i_dload_3(Frame* frame)
{
    //int32_t index = 3;
    //uint64_t result = (((uint64_t)frame->localVariables.at(index).operand) << 32) |(frame->localVariables.at(index + 1).operand);

    //printf("double into dload_3 - %llu\n", result);

    //uint32_t low = (uint32_t)(result & 0x00000000FFFFFFFF);

    Data * data1 = (Data*) malloc(sizeof(Data));
    data1->operand = frame->localVariables.at(4).operand;

    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

	  //uint32_t high = (uint32_t)(result >> 32);

    Data * data2 = (Data*) malloc(sizeof(Data));
    data2->operand = frame->localVariables.at(3).operand;

    frame->operandStack.push((*data2));

    free(data2);
    data2 = NULL;

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
   uint32_t index =  frame->operandStack.top().operand;
   frame->operandStack.pop();

   tArray* arrayRef = (tArray*)frame->operandStack.top().reference;
   frame->operandStack.pop();

   Data * data1 = (Data*) malloc(sizeof(Data));

   if (arrayRef->is_multarray == true) {
     data1->operand = *((uint32_t*)arrayRef->reference_helper);
   } else {
     data1->operand = arrayRef->info.tipoInt[index];
   }
   //printf("value at iaload - %d\n", *((uint32_t*)arrayRef->reference_helper));

   if (arrayRef->array_pos == arrayRef->base_array_pos) {
         arrayRef->reference_helper = (void*)(&arrayRef->info.tipoInt[arrayRef->base_array_pos]);
         arrayRef->array_pos = arrayRef->base_array_pos;
         arrayRef->base_array_pos += arrayRef->tamanho1;
   }

   data1->reference = (void*)arrayRef;

   frame->operandStack.push((*data1));

   free(data1);
   data1 = NULL;

  return;
}

void i_laload(Frame* frame)
{
    uint32_t index =  frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    int64_t* arrayRef = ref->info.tipoLong;

    uint32_t low = (uint32_t)(arrayRef[index] & 0x00000000FFFFFFFF);

    Data * data1 = (Data*) malloc(sizeof(Data));
  	data1->operand = low;

  	frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    uint32_t high = (uint32_t)(arrayRef[index] >> 32);

    Data * data2 = (Data*) malloc(sizeof(Data));
  	data2->operand = high;

  	frame->operandStack.push((*data2));

    free(data2);
    data2 = NULL;

  return;
}

void i_faload(Frame* frame)
{
    uint32_t index =  frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    int32_t* arrayRef = ref->info.tipoFloat;

    Data * data1 = (Data*) malloc(sizeof(Data));
    data1->operand = arrayRef[index];
    data1->reference = (void*)ref;

    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

  return;
}

void i_daload(Frame* frame)
{
    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    int64_t* arrayRef = ref->info.tipoDouble;

    uint32_t low = (uint32_t)(arrayRef[index] & 0x00000000FFFFFFFF);

    Data * data1 = (Data*) malloc(sizeof(Data));
  	data1->operand = low;

  	frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    uint32_t high = (uint32_t)(arrayRef[index] >> 32);

    Data * data2 = (Data*) malloc(sizeof(Data));
  	data2->operand = high;

    frame->operandStack.push((*data2));

    free(data2);
    data2 = NULL;

  return;
}

void i_aaload(Frame* frame)
{
    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    Data * data1 = (Data*) malloc(sizeof(Data));

    //printf("ref->tag - %d\n", ref->tag);
    //printf("index at aaload - %u\n", index);

    switch (ref->tag)
    {
      case TipoByte:
      {
        int8_t* arrayRef_byte = ref->info.tipoByte;

        data1->operand = arrayRef_byte[index];
        data1->reference = (void*)ref;

        frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;
        return;
      }
      case TipoChar:
      {
        uint16_t* arrayRef_char = ref->info.tipoChar;

        data1->operand = arrayRef_char[index];
        data1->reference = (void*)ref;

        frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;
        return;
      }
      case TipoDouble:
      {
        int64_t* arrayRef_double = ref->info.tipoDouble;

        data1->operand = arrayRef_double[index];
        data1->reference = (void*)ref;

        frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;
        return;
      }
      case TipoFloat:
      {
        int32_t* arrayRef_float = ref->info.tipoFloat;

        data1->operand = arrayRef_float[index];
        data1->reference = (void*)ref;

        frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;
        return;
      }
      case TipoInt:
      {
        int32_t* arrayRef_int = ref->info.tipoInt;

        data1->operand = arrayRef_int[ref->array_pos];

        //printf("data1->operand at aaload - %d\n", data1->operand);
        //printf("ref->array_pos at aaload - %d\n", ref->array_pos);

        ref->reference_helper = (void*)(&ref->info.tipoInt[ref->array_pos]);

        if (ref->array_pos < ref->base_array_pos) {
          ref->array_pos++;
        }

        data1->reference = (void*)ref;

        frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;
        return;
      }
      case TipoLong:
      {
        int64_t* arrayRef_long = ref->info.tipoLong;

        data1->operand = arrayRef_long[index];
        data1->reference = (void*)ref;

        frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;
        return;
      }
      case TipoReferencia:
      {
        int32_t* arrayRef_ref = ref->info.tipoReferencia;

        data1->operand = arrayRef_ref[index];
        data1->reference = (void*)ref;

        frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;
        return;
      }
      case TipoShort:
      {
        int16_t* arrayRef_short = ref->info.tipoShort;

        data1->operand = arrayRef_short[index];
        data1->reference = (void*)ref;

        frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;
        return;
      }
      case TipoBoolean:
      {
        int8_t* arrayRef_bool = ref->info.tipoBoolean;

        data1->operand = arrayRef_bool[index];
        data1->reference = (void*)ref;

        frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;
        return;
      }
      default:
      {
        int32_t* arrayRef_def = ref->info.tipoReferencia;

        data1->operand = arrayRef_def[index];
        data1->reference = (void*)ref;

        frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;
        return;
      }
    }
}

void i_baload(Frame* frame)
{
    uint32_t index =  frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    int8_t* arrayRef;

    if (ref->tag == TipoByte) {
      arrayRef = ref->info.tipoByte;
    } else {
      arrayRef = ref->info.tipoBoolean;
    }

    Data * data1 = (Data*) malloc(sizeof(Data));
    data1->operand = (int32_t)arrayRef[index];
    //printf("value at baload - %d\n", data1->operand);
    data1->reference = (void*)ref;

    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

  return;
}

void i_caload(Frame* frame)
{
    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    uint16_t* arrayRef = ref->info.tipoChar;

    Data * data1 = (Data*) malloc(sizeof(Data));
    data1->operand = (int32_t)arrayRef[index];
    data1->reference = (void*)ref;

    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

  return;
}

void i_saload(Frame* frame)
{
    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    int16_t* arrayRef = ref->info.tipoShort;

    Data * data1 = (Data*) malloc(sizeof(Data));
    data1->operand = (int32_t)arrayRef[index];
    //printf("value at saload - %d\n", data1->operand);
    data1->reference = (void*)ref;

    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

  return;
}

#include "others.hpp"

void i_nop()
{
    return;
};

void i_bipush(Frame* frame, int32_t* n){
    int32_t dado = *n;

    Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = dado;
    //printf("value into bipush - %d\n", data1->operand);

	frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    return;
}

void i_sipush(Frame* frame, int16_t* n)
{
    int32_t dado = *n;

    Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = dado;
    //printf("value into sipush - %d\n", data1->operand);

	frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    return;
}

void i_ldc(Frame* frame,uint8_t index, ConstPool* constantPool)
{
    uint8_t tag = constantPool[index - 1].tag;
    int32_t dado;
    //float f;

    switch (tag)
    {
      case INTEGER:
      {
        dado = constantPool[index - 1].integer_const.bytes;

        Data * data1 = (Data*) malloc(sizeof(Data));
      	data1->operand = dado;

      	frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;

        //delete data1;
        //data1 = NULL;
        break;
      }
      case FLOAT:
      {
        //dado = (constantPool[index - 1].float_const.bytes);
      	//f = decodeFloat(constantPool[index - 1].float_const.bytes);
        //dado = f;

        Data * data1 = (Data*) malloc(sizeof(Data));
    	data1->operand = (int32_t)constantPool[index - 1].float_const.bytes;

    	frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;

        //delete data1;
        //data1 = NULL;
        break;
      }
      case STRING:
      {
        dado = constantPool[index - 1].string_const.string_index;

        Data * data1 = (Data*) malloc(sizeof(Data));
    	data1->operand = dado;

    	frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;

        //delete data1;
        //data1 = NULL;
        break;
      }
    }
    return;
}

void i_ldc_w(Frame* frame, uint8_t index, uint8_t index2, ConstPool* constantPool)
{
    int32_t dado = 0;
    uint8_t tag = constantPool[index - 1].tag;
    //float f = 0;

    switch (tag)
    {
      case INTEGER:
      {
        dado = (constantPool[index - 1].integer_const.bytes);

        Data * data1 = (Data*) malloc(sizeof(Data));
    	data1->operand = dado;

    	frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;

        //delete data1;
        //data1 = NULL;
        break;
      }
      case FLOAT:
      {
        //dado = (constantPool[index - 1].float_const.bytes);
        //f = decodeFloat(constantPool[index - 1].float_const.bytes);
        //dado = f;
        //printf("Float here - %f\n", f);

        Data * data1 = (Data*) malloc(sizeof(Data));
    	data1->operand = (int32_t)constantPool[index - 1].float_const.bytes;

    	frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;

        //delete data1;
        //data1 = NULL;
        break;
      }
      case STRING:
      {
        dado = constantPool[index - 1].string_const.string_index;

        Data * data1 = (Data*) malloc(sizeof(Data));
    	data1->operand = dado;

    	frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;

        //delete data1;
        //data1 = NULL;
        break;
      }
    }
	return;
}

void i_ldc2_w(Frame* frame, uint8_t index, uint8_t index2, ConstPool* constantPool)
{
    uint16_t indexConcat = (index << 8) | index2;
    uint8_t tag = constantPool[indexConcat - 1].tag;
    //uint64_t dado;

    switch(tag)
    {
      case LONG:
      {
        //dado = ((uint64_t)constantPool[indexConcat - 1].long_const.bytes.highBytes << 32) | constantPool[indexConcat - 1].long_const.bytes.lowBytes;
        //printf("value at ldc2_w - %llu\n", dado);
        //empilhando 64 bits
        //uint32_t low = (uint32_t)(dado & 0x00000000FFFFFFFF);

        Data * data1 = (Data*) malloc(sizeof(Data));
    	data1->operand = (uint32_t)constantPool[indexConcat - 1].long_const.bytes.lowBytes;
    	frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;

        //delete data1;
        //data1 = NULL;

        //uint32_t high = (uint32_t)(dado >> 32);

        Data * data2 = (Data*) malloc(sizeof(Data));
    	data2->operand = (uint32_t)constantPool[indexConcat - 1].long_const.bytes.highBytes;

    	frame->operandStack.push((*data2));

        free(data2);
        data2 = NULL;

        //delete data2;
        //data2 = NULL;
        break;
      }
      case DOUBLE:
      {
        //dado = (uint64_t)decodeDouble(constantPool[indexConcat-1].long_const.bytes.highBytes, constantPool[indexConcat-1].long_const.bytes.lowBytes);

        //printf("indexConcat - %d\n", indexConcat);
        //printf("double - %llu\n", dado);

        //empilhando 64 bits
        //uint32_t low = (uint32_t)(dado & 0x00000000FFFFFFFF);

        Data * data1 = (Data*) malloc(sizeof(Data));
    	data1->operand = (uint32_t)constantPool[indexConcat-1].long_const.bytes.lowBytes;

    	frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;

        //delete data1;
        //data1 = NULL;

        //uint32_t high = (uint32_t)(dado >> 32);

        Data * data2 = (Data*) malloc(sizeof(Data));
    	data2->operand = (uint32_t)constantPool[indexConcat-1].long_const.bytes.highBytes;

    	frame->operandStack.push((*data2));

        free(data2);
        data2 = NULL;

        //delete data2;
        //data2 = NULL;
        break;
      }
    }
    return;
}

void i_goto(Frame* frame, uint8_t index1, uint8_t index2)
{
	int16_t offset16 = (((uint16_t)index1) << 8) + index2;
	frame->codeIndexRef += (offset16 - 3);

	return;
}

void i_jsr(Frame* frame, uint8_t index, uint8_t index2){
    Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = frame->codeIndexRef;

	frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    //delete data1;
    //data1 = NULL;

	int16_t offset16 = (((uint16_t)index) << 8) + index2;
	frame->codeIndexRef += (offset16 - 3);

	return;
}

void i_ret(Frame* frame, uint8_t index)
{
    frame->codeIndexRef = frame->localVariables.at(index).operand;
    return;
}

void i_tableswitch(Frame *frame, uint32_t enderecotable, int32_t high, int32_t low, int32_t defaultbyte, int32_t *tableswitch)
{
  uint32_t target;
  int32_t index = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

  if(index < low || index > high) {
    target = enderecotable + defaultbyte;
  } else {
    uint32_t offset = tableswitch[index - low];
    target = enderecotable + offset;
  }

  frame->codeIndexRef = target - 1;

  //printf("frame->codeIndexRef - %d\n", frame->codeIndexRef);

  return;
}

void i_lookupswitch(Frame * frame, int32_t npairs, uint32_t enderecolookup, int32_t defaultbyte, int32_t *match, int32_t *offset_table)
{
  int32_t key = (int32_t)frame->operandStack.top().operand;
  frame->operandStack.pop();

  uint32_t target;
  uint32_t i = 0;
	uint8_t found = 0;

	while((i < npairs) &&(!found)) {
		if(match[i] == key){
      found = 1;
    }
		i++;
	}
	i--;

	if(found) {
		target = offset_table[i] + enderecolookup;
	} else {
		target = defaultbyte + enderecolookup;
	}

	frame->codeIndexRef = target - 1;
  //printf("frame->codeIndexRef - %d\n", frame->codeIndexRef);

  return;
}

void i_ireturn(Frame *frame, std::stack<Frame*> &framesStack)
{
    Frame *frame1 = frame;
    int32_t valor = (int32_t)frame->operandStack.top().operand;
    frame->operandStack.pop();

    //printf("value i_ireturn - %d\n", valor);

    if (!framesStack.empty())
    {
        //printf("codeIndexRef frame1 - %d\n", frame1->codeIndexRef);

        frame = framesStack.top();
        framesStack.pop();


        //printf("codeIndexRef frame - %d\n", frame->codeIndexRef);

        //if (!framesStack.empty()){
            //printf("codeIndexRef frame at top ireturn - %d\n", framesStack.top()->codeIndexRef);
        //}

        Data * data1 = (Data*) malloc(sizeof(Data));
    	data1->operand = valor;

    	frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;

        //delete data1;
        //data1 = NULL;

        framesStack.push(frame);
    }

    frame1->codeIndexRef = frame->codeAttribute->codeLength;

    return;
}

void i_lreturn(Frame *frame, std::stack<Frame*> &framesStack)
{
    Frame *frame1 = frame;
    uint64_t valor = (uint64_t)frame->operandStack.top().operand;
    frame->operandStack.pop();

    if (!framesStack.empty())
    {
      frame = framesStack.top();
      framesStack.pop();

      //empilha 64 bits
      uint32_t low = (uint32_t)(valor & 0X00000000FFFFFFFF);

      Data * data1 = (Data*) malloc(sizeof(Data));
  	  data1->operand = low;

  	  frame->operandStack.push((*data1));

      free(data1);
      data1 = NULL;

      //delete data1;
      //data1 = NULL;

      uint32_t high = (uint32_t)(valor >> 32);

      Data * data2 = (Data*) malloc(sizeof(Data));
  	  data2->operand = high;

  	  frame->operandStack.push((*data2));

      free(data2);
      data2 = NULL;

      //delete data2;
      //data2 = NULL;

      framesStack.push(frame);

    }

    frame1->codeIndexRef = frame->codeAttribute->codeLength;

    return;
}

void i_freturn(Frame *frame, std::stack<Frame*> &framesStack)
{
    Frame *frame1 = frame;
    uint32_t valor = frame->operandStack.top().operand;
    frame->operandStack.pop();

    if (!framesStack.empty())
    {
      frame = framesStack.top();
      framesStack.pop();

      Data * data1 = (Data*) malloc(sizeof(Data));
  	  data1->operand = valor;

  	  frame->operandStack.push((*data1));

      free(data1);
      data1 = NULL;

      //delete data1;
      //data1 = NULL;

      framesStack.push(frame);
    }

    frame1->codeIndexRef = frame->codeAttribute->codeLength;

    return;
}

void i_dreturn(Frame* frame, std::stack<Frame*> &framesStack)
{
    Frame *frame1 = frame;
    uint64_t valor = (uint64_t)frame->operandStack.top().operand;
    frame->operandStack.pop();

    if (!framesStack.empty())
    {
      frame = framesStack.top();
      framesStack.pop();
      //empilha 64 bits
      uint32_t low = (uint32_t)(valor & 0X00000000FFFFFFFF);

      Data * data1 = (Data*) malloc(sizeof(Data));
  	  data1->operand = low;

  	  frame->operandStack.push((*data1));

      free(data1);
      data1 = NULL;

      //delete data1;
      //data1 = NULL;

      uint32_t high = (uint32_t)(valor >> 32);

      Data * data2 = (Data*) malloc(sizeof(Data));
  	  data2->operand = high;

  	  frame->operandStack.push((*data2));

      free(data2);
      data2 = NULL;

      //delete data2;
      //data2 = NULL;

      framesStack.push(frame);
    }

    frame1->codeIndexRef = frame->codeAttribute->codeLength;

    return;
}

void i_areturn(Frame* frame, std::stack<Frame*> &framesStack)
{
    Frame *frame1 = frame;
    uint32_t valor = frame->operandStack.top().operand;
    frame->operandStack.pop();

    if (!framesStack.empty())
    {
        frame = framesStack.top();
        framesStack.pop();

        Data * data1 = (Data*) malloc(sizeof(Data));
    	data1->operand = valor;

        frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;

        //delete data1;
        //data1 = NULL;

        framesStack.push(frame);
    }

    frame1->codeIndexRef = frame->codeAttribute->codeLength;

    return;
}

void i_return(Frame* frame)
{
    frame->codeIndexRef = frame->codeAttribute->codeLength;
    return;
}

void i_getstatic(Frame *frame, ListaStaticField *listaDeFields, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index = 0, tipoIndex = 0, nameIndex = 0, fieldIndex = 0, nomeClasseIndex = 0;
    int32_t valor = 0;
    char *tipo = NULL, *name = NULL, *nomeClasse = NULL, *nome = NULL;
    Class *classe = NULL;
    staticField *field = NULL;
    Data * data1 = (Data*) malloc(sizeof(Data));

    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;

    nomeClasseIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.class_index - 1;
    nomeClasseIndex = frame->runtimeConstantPool[nomeClasseIndex].class_const.name_index;
    tipoIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.nameAndType_index - 1;
    nameIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.name_index;
    tipoIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.descriptor_index;

    tipo = getUtf8FromConstantPool(tipoIndex, frame->runtimeConstantPool);
    name = getUtf8FromConstantPool(nameIndex, frame->runtimeConstantPool);
    nomeClasse = getUtf8FromConstantPool(nomeClasseIndex, frame->runtimeConstantPool);

    classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);

    //printf("tipo - %s\n", tipo);
    //printf("name - %s\n", name);
    //printf("nomeClasse - %s\n", nomeClasse);

    if(!classe)
    {
        if(!strcmp(nomeClasse, "java/lang/System"))
        {
            //printf("value getstatic - %d\n", valor);
        	data1->operand = valor;
            data1->reference = NULL;
            //Data temp = (*data1);
            //printf("value data1->operand - %d\n", data1->operand);
            /*printf("Stack size before - %lu\n", frame->operandStack.size());
            if (frame->operandStack.empty()) {
                printf("Empty\n");
                printf("Stack size - %lu\n", frame->operandStack.size());
                frame->operandStack.push((*data1));

                free(data1);
                data1 = NULL;
            } else{
                std::stack<Data> bug;
                bug.push((*data1));
                swap(frame->operandStack, bug);
                printf("Not Empty\n");
                printf("Stack size - %lu\n", frame->operandStack.size());
                printf("value top stack now - %d\n", frame->operandStack.top().operand);
                printf("pop made\n");
            }*/
        	frame->operandStack.push((*data1));

            free(data1);
            data1 = NULL;
            //delete data1;
            //data1 = NULL;
            //printf("Stack size now - %lu\n", frame->operandStack.size());

            free_mem((void **) &tipo);
            free_mem((void **) &name);
            free_mem((void **) &nomeClasse);

            return;
        }
        else{
            exit(-1);
        }
    }

    field = recupera_field(nomeClasse, &listaDeFields);

    if(!field)
    {
        //printf("value getstatic - %u\n", valor);
        data1->operand = valor;
        data1->reference = NULL;
        frame->operandStack.push((*data1));

        free(data1);
        data1 = NULL;

        //delete data1;
        //data1 = NULL;
        //printf("value top stack - %d\n", frame->operandStack.top());

        free_mem((void **) &tipo);
        free_mem((void **) &name);
        free_mem((void **) &nomeClasse);

        return;
    }

    for (fieldIndex = 0; fieldIndex < classe->fields_count; fieldIndex++)
    {
        uint16_t nomeIndex = classe->fields[fieldIndex].name_index - 1;

        nome = getUtf8FromConstantPool(nomeIndex, classe->constant_pool);

        if (!strcmp(name, nome)){
            free_mem((void **) &nome);
            break;
        }
        free_mem((void **) &nome);
    }

    valor = field->valor[fieldIndex];
    data1->operand = valor;
    data1->reference = NULL;
    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    //delete data1;
    //data1 = NULL;

    //printf("value getstatic - %u\n", valor);
    //printf("value top stack - %d\n", frame->operandStack.top());

    free_mem((void **) &tipo);
    free_mem((void **) &name);
    free_mem((void **) &nomeClasse);

    return;
}

void i_putstatic(Frame *frame, ListaStaticField *listaDeFields, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, tipoIndex, nameIndex, fieldIndex, nomeClasseIndex;
    uint32_t valor;
    char *tipo, *name, *nomeClasse, *nome;
    Class *classe;
    staticField *field;

    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;

    nomeClasseIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.class_index - 1;
    nomeClasseIndex = frame->runtimeConstantPool[nomeClasseIndex].class_const.name_index;
    tipoIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.nameAndType_index - 1;
    nameIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.name_index;
    tipoIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.descriptor_index;

    tipo = getUtf8FromConstantPool(tipoIndex, frame->runtimeConstantPool);
    name = getUtf8FromConstantPool(nameIndex, frame->runtimeConstantPool);
    nomeClasse = getUtf8FromConstantPool(nomeClasseIndex, frame->runtimeConstantPool);

    classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);

    valor = frame->operandStack.top().operand;
    frame->operandStack.pop();

    for (fieldIndex = 0; fieldIndex < classe->fields_count; fieldIndex++)
    {
        uint16_t nomeIndex = classe->fields[fieldIndex].name_index - 1;

        nome = getUtf8FromConstantPool(nomeIndex, classe->constant_pool);

        if (!strcmp(name, nome)){
            free_mem((void **) &nome);
            break;
        }
        free_mem((void **) &nome);
    }

    field = recupera_field(nomeClasse, &listaDeFields);

    if (field == NULL)
    {
        field = (staticField *) set_mem(sizeof(staticField));
        field->NomeClasse = (char *) set_mem(sizeof(char) * (strlen(nomeClasse) + 1));
        strcpy(field->NomeClasse, nomeClasse);
        field->fieldCount = classe->fields_count;
        field->valor = (uint64_t *) set_mem(sizeof(uint64_t) * field->fieldCount);
        field->valor[fieldIndex] = valor;
        InsereListaDeFields(&listaDeFields, field);
    }

    field->valor[fieldIndex] = valor;

    free_mem((void **) &tipo);
    free_mem((void **) &name);
    free_mem((void **) &nomeClasse);

    return;
}

void i_getfield(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, tipoIndex, nameIndex, fieldIndex;
    char *tipo, *name, *nome;

    Objeto* obj = (Objeto*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;

    tipoIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.nameAndType_index - 1;
    nameIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.name_index - 1;
    tipoIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.descriptor_index - 1;

    tipo = getUtf8FromConstantPool(tipoIndex, frame->runtimeConstantPool);
    name = getUtf8FromConstantPool(nameIndex, frame->runtimeConstantPool);

    for (fieldIndex = 0; fieldIndex < obj->tamanhotipoField; fieldIndex++)
    {
        uint16_t nomeIndex = obj->classe->fields[fieldIndex].name_index - 1;

        nome = getUtf8FromConstantPool(nomeIndex, obj->classe->constant_pool);

        if (!strcmp(name, nome)){
            free_mem((void **) &nome);
            break;
        }
        free_mem((void **) &nome);
    }

    Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = obj->tipofield[fieldIndex];

	frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    free_mem((void **) &tipo);
    free_mem((void **) &name);

    return;
}

void i_putfield(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, tipoIndex, nameIndex, fieldIndex;
    uint32_t valor;
    char *tipo, *name, *nome;

    Objeto* obj = (Objeto*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;

    tipoIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.nameAndType_index - 1;
    nameIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.name_index;
    tipoIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.descriptor_index;

    tipo = getUtf8FromConstantPool(tipoIndex, frame->runtimeConstantPool);
    name = getUtf8FromConstantPool(nameIndex, frame->runtimeConstantPool);

    valor = frame->operandStack.top().operand;
    frame->operandStack.pop();

    for (fieldIndex = 0; fieldIndex < obj->classe->fields_count; fieldIndex++)
    {
        uint16_t nomeIndex = obj->classe->fields[fieldIndex].name_index - 1;

        nome = getUtf8FromConstantPool(nomeIndex, obj->classe->constant_pool);

        if (!strcmp(name, nome)){
            free_mem((void **) &nome);
            break;
        }
        free_mem((void **) &nome);
    }

    obj->tipofield[fieldIndex] = valor;

    free_mem((void **) &tipo);
    free_mem((void **) &name);

    return;
}

void i_invokevirtual(Frame *frame, std::stack<Frame*> &pilhaDeFrames, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, Heap *heap)
{
    uint16_t index = 0, classIndex = 0, descriptorIndex = 0, metodoIndex = 0;
    uint32_t valor = 0, *argumentos = NULL;
    char *nomeClasse = NULL, *nomeMetodo = NULL, *metodoDesc = NULL, *nome = NULL, *nomeDesc = NULL;
    float valorF = 0;
    int i = 0;
    Class *classe = NULL;

    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;
    classIndex = frame->runtimeConstantPool[index - 1].methodRef_const.class_index - 1;
    classIndex = frame->runtimeConstantPool[classIndex].class_const.name_index;
    nomeClasse = getUtf8FromConstantPool(classIndex, frame->runtimeConstantPool);

    //printf("nomeClasse - %s\n", nomeClasse);

    descriptorIndex = frame->runtimeConstantPool[index - 1].methodRef_const.nameAndType_index - 1;
    metodoIndex = frame->runtimeConstantPool[descriptorIndex].nameAndType_const.name_index;
    descriptorIndex = frame->runtimeConstantPool[descriptorIndex].nameAndType_const.descriptor_index;
    nomeMetodo = getUtf8FromConstantPool(metodoIndex, frame->runtimeConstantPool);
    metodoDesc = getUtf8FromConstantPool(descriptorIndex, frame->runtimeConstantPool);

    //printf("metodoDesc - %s\n", metodoDesc);
    //printf("bytes - %s\n", bytes);
    //printf("length - %d\n", length);

    if (!strcmp(nomeClasse, "java/io/PrintStream") && (!strcmp(nomeMetodo, "print") || !strcmp(nomeMetodo, "println")))
    {
        //Long
        if (strstr(metodoDesc, "J") != NULL)
        {
            uint32_t valorh = frame->operandStack.top().operand;
            frame->operandStack.pop();

            uint32_t valorl = frame->operandStack.top().operand;
            frame->operandStack.pop();

            uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
            //printf("LONG\n");
            printf("%lld", (long long) valor);
        }
        //Double
        else if (strstr(metodoDesc, "D") != NULL)
        {
            uint32_t valorh = frame->operandStack.top().operand;
            frame->operandStack.pop();

            uint32_t valorl = frame->operandStack.top().operand;
            frame->operandStack.pop();

            double d = decodeDouble(valorh, valorl);
            //uint64_t ud = d;
            //printf("Double\n");
            printf("%f", d);

        }
        //Boolean
        else if (strstr(metodoDesc, "Z") != NULL)
        {
            if (frame->operandStack.top().operand)
            {
              frame->operandStack.pop();
              printf("true");
            }
            else
            {
              frame->operandStack.pop();
              printf("false");
            }
        }
        //Char
        else if (strstr(metodoDesc, "C") != NULL)
        {
            //Array
            if (strstr(metodoDesc, "[C") != NULL)
            {
                tArray* array1 = (tArray*)frame->operandStack.top().reference;
                frame->operandStack.pop();
                //printf("Array of char\n");
                // std::locale()   is the "global" locale
                // std::locale("") is the locale configured through the locale system
                // At startup, the global locale is set to std::locale("C"), so we need
                // to change that if we want locale-aware functions to use the configured
                // locale.
                // This sets the global" locale to the default locale.
                std::locale::global(std::locale(""));

                // The various standard io streams were initialized before main started,
                // so they are all configured with the default global locale, std::locale("C").
                // If we want them to behave in a locale-aware manner, including using the
                // hopefully correct encoding for output, we need to "imbue" each iostream
                // with the default locale.
                // We don't have to do all of these in this simple example,
                // but it's probably a good idea.
                std::cin.imbue(std::locale());
                std::cout.imbue(std::locale());
                std::cerr.imbue(std::locale());
                std::wcin.imbue(std::locale());
                std::wcout.imbue(std::locale());
                std::wcerr.imbue(std::locale());

                std::wcout << wchar_t(frame->operandStack.top().operand);
                for (i = 0; i < array1->tamanho1; i++) {
                    std::wcout << wchar_t(array1->info.tipoChar[i]);
                    //printf("%c", array1->info.tipoChar[i]);
                }
            }
            //Char
            else{
                // std::locale()   is the "global" locale
                // std::locale("") is the locale configured through the locale system
                // At startup, the global locale is set to std::locale("C"), so we need
                // to change that if we want locale-aware functions to use the configured
                // locale.
                // This sets the global" locale to the default locale.
                std::locale::global(std::locale(""));

                // The various standard io streams were initialized before main started,
                // so they are all configured with the default global locale, std::locale("C").
                // If we want them to behave in a locale-aware manner, including using the
                // hopefully correct encoding for output, we need to "imbue" each iostream
                // with the default locale.
                // We don't have to do all of these in this simple example,
                // but it's probably a good idea.
                std::cin.imbue(std::locale());
                std::cout.imbue(std::locale());
                std::cerr.imbue(std::locale());
                std::wcin.imbue(std::locale());
                std::wcout.imbue(std::locale());
                std::wcerr.imbue(std::locale());

                std::wcout << wchar_t(frame->operandStack.top().operand);
                //printf("%c", frame->operandStack.top().operand);
                //printf("char\n");
                frame->operandStack.pop();
            }
        }
        //Inteiro
        else if (strstr(metodoDesc, "I") != NULL){
            //printf("Int\n");
            printf("%d", frame->operandStack.top().operand);
            frame->operandStack.pop();
        }
        //Float
        else if (strstr(metodoDesc, "F") != NULL)
        {
            valor = frame->operandStack.top().operand;
            frame->operandStack.pop();
            valorF = decodeFloat(valor);

            //memcpy(&valorF, &valor, sizeof(uint32_t));
            //printf("Float\n");
            printf("%f", valorF);
        }
        //String
        else if (strstr(metodoDesc, "Ljava/lang/String") != NULL)
        {
            valor = frame->operandStack.top().operand;
            frame->operandStack.pop();

            //printf("valor - %d\n", valor);

            if (valor != 0)
            {
                char *cPointer = getUtf8FromConstantPool(valor, frame->runtimeConstantPool);
                //printf("String\n");
                printf("%s", cPointer);
                free_mem((void **) &cPointer);
            }
            else {
                //printf("String\n");
                printf("%s", (char *) (long) valor);
            }
        }
        //Object
        else if (strstr(metodoDesc, "Ljava/lang/Object") != NULL)
        {
            void *pPointer = frame->operandStack.top().reference;
            frame->operandStack.pop();
            //printf("Pointer\n");
            printf("%p",pPointer);
        }

        if (strstr(nomeMetodo, "println") != NULL) {
            printf("\n");
        }
    }
    else
    {
        uint32_t numparam = 0;

        classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);

        if (classe == NULL)
        {
            char path[] = "./etc/";
            char *nomeArquivo;

            classe = (Class *) set_mem(sizeof(Class));
            nomeArquivo = (char *) set_mem(sizeof(char) * (strlen(nomeClasse) + 13));

            strcpy(nomeArquivo, path);
            strcat(nomeArquivo, nomeClasse);
            strcat(nomeArquivo, ".class");

            //printf("Name of file %s\n", nomeArquivo);

            FILE* fp = openFile((char*)nomeArquivo, (char*)"rb");

            classe = getClassfile(fp);
            listaDeClasses = InsereListaDeClasses(&listaDeClasses, classe);
            frame->heap->listaDeClasses = listaDeClasses;

            free_mem((void **) &nomeArquivo);
            closeFile(&fp);
        }

        uint8_t *bytes = frame->runtimeConstantPool[descriptorIndex].utf8_const.bytes;
        uint16_t length = frame->runtimeConstantPool[descriptorIndex].utf8_const.length;

        for (i = 0; i < length && bytes[i] != ')'; i++)
        {
            if(bytes[i] == 'L')
            {
                while(bytes[i] != ';') {
                    i++;
                }

                numparam++;
            }
            else if((bytes[i] == 'B') || (bytes[i] == 'C') || (bytes[i] == 'F') || (bytes[i] == 'I') || (bytes[i] == 'S') || (bytes[i] == 'Z'))
            {
                numparam++;
            }
            else if((bytes[i] == 'D')||(bytes[i] == 'J'))
            {
                numparam += 2;
            }
        }

        argumentos = (uint32_t *) set_mem(sizeof(uint32_t) * (numparam + 1));

        for (i = numparam; i >= 0; i--) {
            argumentos[i] = frame->operandStack.top().operand;
            frame->operandStack.pop();
        }

        nomeMetodo = getUtf8FromConstantPool(metodoIndex, frame->runtimeConstantPool);

        for(i = 0; i < classe->methods_count; i++)
        {
            index = classe->methods[i].name_index - 1;
            nome = getUtf8FromConstantPool(index, classe->constant_pool);

            uint32_t index1 = classe->methods[i].descriptor_index - 1;

            nomeDesc = getUtf8FromConstantPool(index1, classe->constant_pool);

            if(!strcmp(nomeMetodo, nome) && !strcmp(metodoDesc, nomeDesc)){
                break;
            }
        }
        free_mem((void **) &nomeMetodo);
        free_mem((void **) &metodoDesc);
        free_mem((void **) &nome);
        free_mem((void **) &nomeDesc);
        free_mem((void **) &nomeClasse);

        if (i != classe->methods_count)
        {
            if (classe->methods[i].access_flags & ACC_NATIVE)
            {
                uint64_t zero64 = 0;
                uint32_t zero32 = 0;

                bytes = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.bytes;
                length = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.length;

                if(bytes[length - 1] == 'D' || bytes[length - 1] == 'J') {
                    uint32_t low = (uint32_t)(zero64 & 0x00000000FFFFFFFF);

                    Data * data1 = (Data*) malloc(sizeof(Data));
                	data1->operand = low;

                	frame->operandStack.push((*data1));

                    free(data1);
                    data1 = NULL;

            	    uint32_t high = (uint32_t)(zero64 >> 32);

                    Data * data2 = (Data*) malloc(sizeof(Data));
                	data2->operand = high;

                	frame->operandStack.push((*data2));

                    free(data2);
                    data2 = NULL;
                } else if(bytes[length - 1] != 'V') {
                    Data * data1 = (Data*) malloc(sizeof(Data));
                	data1->operand = zero32;

                	frame->operandStack.push((*data1));

                    free(data1);
                    data1 = NULL;
                }
            }
            else
            {
                prepareMethod(&classe->methods[i], classe, pilhaDeFrames, &heap);

                Frame *frame1 = pilhaDeFrames.top();
                Frame *current = frame;
                pilhaDeFrames.pop();

                for (int j = numparam; j >= 0; j--)
                {
                    Data * data1 = (Data*) malloc(sizeof(Data));
                	data1->operand = argumentos[j];

                	frame1->localVariables.push_back((*data1));

                    free(data1);
                    data1 = NULL;
                }
                free_mem((void **) &argumentos);
                pilhaDeFrames.push(current);
                pilhaDeFrames.push(frame1);

                executeMethod(&classe->methods[i], *(classe), pilhaDeFrames);
            }
        }
        else
            printf("metodo não encontrado");
    }

    //free_mem((void **) &nomeClasse);
    //free_mem((void **) &nomeMetodo);
    //free_mem((void **) &metodoDesc);
    //free_mem((void **) &nome);
    //free_mem((void **) &nomeDesc);
    //free_mem((void **) &argumentos);

    return;
}

void i_invokespecial(Frame *frame, std::stack<Frame*> &pilhaDeFrames, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, Heap *heap)
{
    uint8_t *bytes = NULL;
    uint16_t index = 0, classIndex = 0, descriptorIndex = 0, metodoIndex = 0, length = 0;
    uint32_t numParam = 0, *argumentos = NULL;
    char *nomeClasse = NULL, *nomeMetodo = NULL, *nome, *nomeDesc, *metodoDesc;
    int i = 0;
    Class *classe = NULL;

    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;
    classIndex = frame->runtimeConstantPool[index - 1].methodRef_const.class_index - 1;
    classIndex = frame->runtimeConstantPool[classIndex].class_const.name_index ;
    nomeClasse = getUtf8FromConstantPool(classIndex, frame->runtimeConstantPool);
    classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);

    if (classe == NULL)
    {
        char path[] = "./etc/";
        char *nomeArquivo;

        classe = (Class *) set_mem(sizeof(Class));
        nomeArquivo = (char *) set_mem(sizeof(char) * (strlen(nomeClasse) + 13));

        strcpy(nomeArquivo, path);
        strcat(nomeArquivo, nomeClasse);
        strcat(nomeArquivo, ".class");

        printf("nomeArquivo - %s\n", nomeArquivo);

        FILE* fp = openFile((char*)nomeArquivo, (char*)"rb");

        classe = getClassfile(fp);
        listaDeClasses = InsereListaDeClasses(&listaDeClasses, classe);
        frame->heap->listaDeClasses = listaDeClasses;

        free_mem((void **) &nomeArquivo);
        closeFile(&fp);
    }

    //printf("index - %d\n", index);

    descriptorIndex = frame->runtimeConstantPool[index - 1].methodRef_const.nameAndType_index - 1;

    //printf("descriptorIndex before - %d\n", descriptorIndex);

    metodoIndex = frame->runtimeConstantPool[descriptorIndex].nameAndType_const.name_index;

    //printf("metodoIndex - %d\n", metodoIndex);

    descriptorIndex = frame->runtimeConstantPool[descriptorIndex].nameAndType_const.descriptor_index;

    //printf("descriptorIndex - %d\n", descriptorIndex);

    nomeMetodo = getUtf8FromConstantPool(metodoIndex, frame->runtimeConstantPool);
    metodoDesc = getUtf8FromConstantPool(descriptorIndex, frame->runtimeConstantPool);

    //printf("Nome do metodo - %s\n", nomeMetodo);
    //printf("Nome do metodoDesc - %s\n", metodoDesc);

    bytes = frame->runtimeConstantPool[descriptorIndex - 1].utf8_const.bytes;
    length = frame->runtimeConstantPool[descriptorIndex - 1].utf8_const.length;

    free_mem((void **) &nomeClasse);

    //printf("bytes - %s\n", bytes);
    //printf("length - %d\n", length);

    for (i = 0; i < length && bytes[i] != ')'; i++)
    {
        if(bytes[i] == 'L')
        {
            while(bytes[i] != ';')
                i++;

            numParam++;
        }
        else if((bytes[i] == 'B') || (bytes[i] == 'C') || (bytes[i] == 'F') || (bytes[i] == 'I') || (bytes[i] == 'S') || (bytes[i] == 'Z'))
            numParam++;
        else if((bytes[i] == 'D') || (bytes[i] == 'J'))
            numParam += 2;
    }

    argumentos = (uint32_t *) set_mem(sizeof(uint32_t) * (numParam + 1));

    for (i = numParam; i >= 0; i--){
        argumentos[i] = frame->operandStack.top().operand;
        frame->operandStack.pop();
    }

    for(i = 0; i < classe->methods_count; i++)
    {
        index = classe->methods[i].name_index - 1;
        nome = getUtf8FromConstantPool(index, classe->constant_pool);

        uint16_t index1 = classe->methods[i].descriptor_index - 1;

        nomeDesc = getUtf8FromConstantPool(index1, classe->constant_pool);

        if(!strcmp(nomeMetodo, nome) && !strcmp(metodoDesc, nomeDesc)){
            break;
        }
    }
    free_mem((void **) &nomeMetodo);
    free_mem((void **) &metodoDesc);
    free_mem((void **) &nome);
    free_mem((void **) &nomeDesc);

    if (classe->methods[i].access_flags & ACC_NATIVE)
    {
        uint32_t zero32 = 0;
        uint64_t zero64 = 0;

        bytes = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.bytes;
        length = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.length;

        if(bytes[length - 1] == 'D' || bytes[length - 1] == 'J') {
            uint32_t low = (uint32_t)(zero64 & 0x00000000FFFFFFFF);

            Data * data1 = (Data*) malloc(sizeof(Data));
        	data1->operand = low;

        	frame->operandStack.push((*data1));

            free(data1);
            data1 = NULL;

            uint32_t high = (uint32_t)(zero64 >> 32);

            Data * data2 = (Data*) malloc(sizeof(Data));
        	data2->operand = high;

        	frame->operandStack.push((*data2));

            free(data2);
            data2 = NULL;
        } else if(bytes[length - 1] != 'V') {
            Data * data1 = (Data*) malloc(sizeof(Data));
        	data1->operand = zero32;

        	frame->operandStack.push((*data1));

            free(data1);
            data1 = NULL;
        }
    }
    else
    {
        prepareMethod(&classe->methods[i], classe, pilhaDeFrames, &heap);
        Frame* current = frame;
        Frame *frame1 = pilhaDeFrames.top();
        pilhaDeFrames.pop();

        for (int j = numParam; j >= 0; j--) {
            Data * data1 = (Data*) malloc(sizeof(Data));
            data1->operand = argumentos[j];

            frame1->localVariables.push_back((*data1));

            free(data1);
            data1 = NULL;
        }
        free_mem((void **) &argumentos);
        pilhaDeFrames.push(current);
        pilhaDeFrames.push(frame1);

        executeMethod(&classe->methods[i], *(classe), pilhaDeFrames);
    }

    //free_mem((void **) &nomeClasse);
    //free_mem((void **) &nomeMetodo);
    //free_mem((void **) &metodoDesc);
    //free_mem((void **) &nome);
    //free_mem((void **) &nomeDesc);
    //free_mem((void **) &argumentos);

    return;
}

void i_invokestatic(Frame *frame, std::stack<Frame*> &pilhaDeFrames, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, Heap *heap)
{
    uint8_t *bytes = NULL;
    uint16_t index = 0, classIndex = 0, descriptorIndex = 0, metodoIndex = 0, length = 0;
    int32_t numParam = 0, *argumentos = NULL;
    char *nomeClasse = NULL, *nomeMetodo = NULL, *metodoDesc = NULL, *nome = NULL, *nomeDesc = NULL;
    int i = 0;
    Class *classe = NULL;

    index = (uint32_t) indexByte1 << 8 | (uint32_t) indexByte2;
    classIndex = frame->runtimeConstantPool[index - 1].methodRef_const.class_index - 1;
    classIndex = frame->runtimeConstantPool[classIndex].class_const.name_index;
    nomeClasse = getUtf8FromConstantPool(classIndex, frame->runtimeConstantPool);


    classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);

    descriptorIndex = frame->runtimeConstantPool[index - 1].methodRef_const.nameAndType_index - 1;
    metodoIndex = frame->runtimeConstantPool[descriptorIndex].nameAndType_const.name_index;
    descriptorIndex = frame->runtimeConstantPool[descriptorIndex].nameAndType_const.descriptor_index;
    metodoDesc = getUtf8FromConstantPool(descriptorIndex, frame->runtimeConstantPool);

    bytes = frame->runtimeConstantPool[descriptorIndex - 1].utf8_const.bytes;
    length = frame->runtimeConstantPool[descriptorIndex - 1].utf8_const.length;

    free_mem((void **) &nomeClasse);

    //printf("nomeClasse - %s\n", nomeClasse);

    //printf("metodoDesc - %s\n", metodoDesc);
    //printf("bytes - %s\n", bytes);
    //printf("length - %d\n", length);

    for (i = 0; i < length && bytes[i] != ')'; i++)
    {
        if(bytes[i] == 'L')
        {
            while(bytes[i] != ';')
                i++;

            numParam++;
        }
        else if((bytes[i] == 'B') || (bytes[i] == 'C') || (bytes[i] == 'F') || (bytes[i] == 'I') || (bytes[i] == 'S') || (bytes[i] == 'Z'))
            numParam++;
        else if((bytes[i] == 'D') || (bytes[i] == 'J'))
            numParam += 2;
    }

    //printf("numParam - %d\n", numParam);

    argumentos = (int32_t *) set_mem(sizeof(int32_t) * numParam);

    for (i = (numParam - 1); i >= 0; i--) {
        argumentos[i] = frame->operandStack.top().operand;
        frame->operandStack.pop();
    }

    nomeMetodo = getUtf8FromConstantPool(metodoIndex, frame->runtimeConstantPool);

    //printf("classe->methods_count - %d\n", classe->methods_count);

    for(i = 0; i < classe->methods_count; i++)
    {
        index = classe->methods[i].name_index;
        nome = getUtf8FromConstantPool(index, classe->constant_pool);

        uint16_t index1 = classe->methods[i].descriptor_index;

        nomeDesc = getUtf8FromConstantPool(index1, classe->constant_pool);

        if(!strcmp(nomeMetodo, nome) && !strcmp(metodoDesc, nomeDesc)){
            break;
        }
    }
    free_mem((void **) &nomeMetodo);
    free_mem((void **) &metodoDesc);
    free_mem((void **) &nome);
    free_mem((void **) &nomeDesc);

    //printf("nomeMetodo - %s\n", nomeMetodo);
    //printf("nomeDesc - %s\n", nomeDesc);
    //printf("i - %d\n", i);

    if (i != classe->methods_count)
    {
        if (classe->methods[i].access_flags & ACC_NATIVE)
        {
            uint32_t zero32 = 0;
            uint64_t zero64 = 0;

            bytes = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.bytes;
            length = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.length;

            if(bytes[length - 1] == 'D' || bytes[length - 1] == 'J') {
                uint32_t low = (uint32_t)(zero64 & 0x00000000FFFFFFFF);

                Data * data1 = (Data*) malloc(sizeof(Data));
            	data1->operand = low;

            	frame->operandStack.push((*data1));

                free(data1);
                data1 = NULL;
                //delete data1;
                //data1 = NULL;

                uint32_t high = (uint32_t)(zero64 >> 32);

                Data * data2 = (Data*) malloc(sizeof(Data));
            	data2->operand = high;
                //delete data2;
                //data2 = NULL;

            	frame->operandStack.push((*data2));

                free(data2);
                data2 = NULL;
            } else if(bytes[length - 1] != 'V') {
                Data * data1 = (Data*) malloc(sizeof(Data));
            	data1->operand = zero32;

                //delete data1;
                //data1 = NULL;

            	frame->operandStack.push((*data1));

                free(data1);
                data1 = NULL;
            }
        }
        else
        {
            prepareMethod(&classe->methods[i], classe, pilhaDeFrames, &heap);
            Frame* current = frame;
            Frame *frame1 = pilhaDeFrames.top();
            pilhaDeFrames.pop();

            for (int j = (numParam - 1); j >= 0; j--){
                //printf("argumentos[%d] - %d\n", j, argumentos[j]);
                Data * data1 = (Data*) malloc(sizeof(Data));
                data1->operand = argumentos[j];

                //delete data1;
                //data1 = NULL;

                frame1->localVariables.push_back((*data1));

                free(data1);
                data1 = NULL;
            }
            free_mem((void **) &argumentos);
            pilhaDeFrames.push(current);
            pilhaDeFrames.push(frame1);

            //printf("method executed - %d\n", classe->methods[i].name_index);
            //printf("TOP OF FRAME CODEINDEXREF - %d\n", pilhaDeFrames.top()->codeIndexRef);
            executeMethod(&classe->methods[i], *(classe), pilhaDeFrames);
        }
    }
    else
        printf("metodo não encontrado");

    //free_mem((void **) &nomeClasse);
    //free_mem((void **) &nomeMetodo);
    //free_mem((void **) &metodoDesc);
    //free_mem((void **) &nome);
    //free_mem((void **) &nomeDesc);
    //free_mem((void **) &argumentos);

    return;
}

void i_invokeinterface(Frame *frame, std::stack<Frame*> &pilhaDeFrames, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, uint8_t contagem, uint8_t zero, Heap *heap)
{
    uint32_t *argumentos;
    uint16_t index = 0, classeIndex = 0, descriptorIndex = 0;
    char *nome = NULL, *nomeMetodo = NULL, *nomeClasse = NULL, *nomeDesc = NULL, *metodoDesc = NULL;
    int i = 0;
    Class *classe;
    Objeto *obj = (Objeto *) set_mem(sizeof(Objeto));

    argumentos = (uint32_t *) set_mem(sizeof(uint32_t) * (contagem + 1));

    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;
    classeIndex = index;
    nomeClasse = getUtf8FromConstantPool(classeIndex, frame->runtimeConstantPool);
    obj->classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);

    for (i = contagem; i >= 0; i--)
    {
        argumentos[i] = frame->operandStack.top().operand;
        frame->operandStack.pop();
    }

    index = frame->runtimeConstantPool[index - 1].interfaceMethodRef_const.nameAndType_index - 1;
    descriptorIndex = frame->runtimeConstantPool[index].nameAndType_const.descriptor_index;
    index = frame->runtimeConstantPool[index].nameAndType_const.name_index;
    classeIndex = frame->runtimeConstantPool[classeIndex - 1].interfaceMethodRef_const.class_index - 1;
    classeIndex = frame->runtimeConstantPool[classeIndex].class_const.name_index;

    nomeClasse = getUtf8FromConstantPool(classeIndex, frame->runtimeConstantPool);
    metodoDesc = getUtf8FromConstantPool(descriptorIndex, frame->runtimeConstantPool);
    nomeMetodo = getUtf8FromConstantPool(index, frame->runtimeConstantPool);

    classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);

    for(i = 0; i < classe->methods_count; i++)
    {
        uint16_t index1 = classe->methods[i].descriptor_index - 1;

        nomeDesc = getUtf8FromConstantPool(index1, classe->constant_pool);

        index = classe->methods[i].name_index - 1;
        nome = getUtf8FromConstantPool(index, classe->constant_pool);

        if(!strcmp(nomeMetodo, nome) && !strcmp(metodoDesc, nomeDesc))
            break;
    }
    free_mem((void **) &nome);
    free_mem((void **) &nomeMetodo);
    free_mem((void **) &nomeDesc);
    free_mem((void **) &nomeClasse);
    free_mem((void **) &metodoDesc);

    if (i != obj->classe->methods_count)
    {
        prepareMethod(&obj->classe->methods[i], obj->classe, pilhaDeFrames, &heap);

        Frame *frame1 = pilhaDeFrames.top();
        Frame *current = frame;
        pilhaDeFrames.pop();

        for (int j = contagem; j >= 0; j--){
            //printf("argumentos[%d] - %d\n", j, argumentos[j]);
            Data * data1 = (Data*) malloc(sizeof(Data));
            data1->operand = argumentos[j];

            frame1->localVariables.push_back((*data1));

            free(data1);
            data1 = NULL;
        }
        free_mem((void **) &argumentos);
        pilhaDeFrames.push(current);
        pilhaDeFrames.push(frame1);

        executeMethod(&obj->classe->methods[i], *(obj->classe), pilhaDeFrames);
    }
    else
        printf("Metodo não encontrado");

    //free_mem((void **) &nome);
    //free_mem((void **) &nomeMetodo);
    //free_mem((void **) &nomeDesc);
    //free_mem((void **) &nomeClasse);
    //free_mem((void **) &metodoDesc);
    //free_mem((void **) &argumentos);

    return;
}

void i_invokedynamic(Frame *frame, std::stack<Frame*> &pilhaDeFrames, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, uint8_t zero_1, uint8_t zero_2, Heap *heap)
{
    return;
}

void i_new(Frame *frame, uint8_t indexByte1, uint8_t indexByte2, ListaClasses *listaDeClasses)
{
    uint16_t index;
    char *nomeClasse;
    Objeto *obj;

    index = (uint16_t) (indexByte1 << 8) | (uint16_t) (indexByte2);
    index = frame->runtimeConstantPool[index - 1].class_const.name_index;

    nomeClasse = getUtf8FromConstantPool(index, frame->runtimeConstantPool);

    obj = (Objeto *) set_mem(sizeof(Objeto));
    obj->classe = RecuperaClassePorNome(nomeClasse,&listaDeClasses);

    if (obj->classe == NULL)
    {
        char path[] = "./etc/";
        char *nomeArquivo;

        nomeArquivo = (char *) set_mem(sizeof(char) * (strlen(nomeClasse) + 13));

        strcpy(nomeArquivo, path);
        strcat(nomeArquivo, nomeClasse);
        strcat(nomeArquivo, ".class");

        printf("nomeArquivo - %s\n", nomeArquivo);

        FILE* fp = openFile((char*)nomeArquivo, (char*)"rb");

        obj->classe = getClassfile(fp);
        listaDeClasses = InsereListaDeClasses(&listaDeClasses, obj->classe);
        frame->heap->listaDeClasses = listaDeClasses;

        free_mem((void **) &nomeArquivo);
        closeFile(&fp);
    }

    obj->tamanhotipoField = obj->classe->fields_count;
    obj->tipofield = (uint32_t *) set_mem(sizeof(uint32_t) * obj->tamanhotipoField);

    Data * data1 = (Data*) malloc(sizeof(Data));
	data1->reference = (void*)obj;
    data1->tag = 0;

    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    //delete data1;
    //data1 = NULL;

    free_mem((void **) &nomeClasse);

    return;
}

void i_newarray(Frame *frame, uint8_t aType)
{
    tArray* array;
    uint32_t valor;

    array = (tArray*) set_mem(sizeof(tArray));
    valor = frame->operandStack.top().operand;
    frame->operandStack.pop();

    //printf("aType - %d\n", aType);
    //printf("valor - %d\n", valor);

    switch (aType)
    {
    case TipoByte:
        array->tag = TipoByte;
        array->info.tipoByte = (uint8_t *) set_mem(sizeof(uint8_t) * valor);
        break;
    case TipoChar:
        array->tag = TipoChar;
        array->info.tipoChar = (uint16_t *) set_mem(sizeof(uint16_t) * valor);
        break;
    case TipoDouble:
        array->tag = TipoDouble;
        array->info.tipoDouble = (uint64_t *) set_mem(sizeof(uint64_t) * valor);
        break;
    case TipoFloat:
        array->tag = TipoFloat;
        array->info.tipoFloat = (uint32_t *) set_mem(sizeof(uint32_t) * valor);
        break;
    case TipoInt:
        array->tag = TipoInt;
        array->info.tipoInt = (uint32_t *) set_mem(sizeof(uint32_t) * valor);
        break;
    case TipoLong:
        array->tag = TipoLong;
        array->info.tipoLong = (uint64_t *) set_mem(sizeof(uint64_t) * valor);
        break;
    case TipoReferencia:
        array->tag = TipoReferencia;
        array->info.tipoReferencia = (uint32_t *) set_mem(sizeof(uint32_t) * valor);
        break;
    case TipoShort:
        array->tag = TipoShort;
        array->info.tipoShort = (uint16_t *) set_mem(sizeof(uint16_t) * valor);
        break;
    case TipoBoolean:
        array->tag = TipoBoolean;
        array->info.tipoBoolean = (uint8_t *) set_mem(sizeof(uint8_t) * valor);
        break;
    default:
        array->tag = TipoReferencia;
        array->info.tipoReferencia = (uint32_t *) set_mem(sizeof(uint32_t) * valor);
        break;
    }
    array->array_pos = 0;
    array->base_array_pos = array->tamanho1;
    array->reference_helper = NULL;
    array->is_multarray = false;
	Data * data1 = (Data*) malloc(sizeof(Data));
	data1->reference = (void*)array;
    data1->tag = 1;

    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    //delete data1;
    //data1 = NULL;

    //free_mem((void **) &array);

    return;
}

void i_anewarray(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    tArray *array;
    uint16_t index;
    uint32_t i = 0, valor;
    char *tipo;

    array = (tArray*) set_mem(sizeof(tArray));

    index = (uint16_t) (indexByte1 << 8) | (uint16_t) (indexByte2);
    index = frame->runtimeConstantPool[index - 1].class_const.name_index - 1;
    tipo = getUtf8FromConstantPool(index, frame->runtimeConstantPool);

    valor = frame->operandStack.top().operand;
    frame->operandStack.pop();

    while (tipo[i] == '[')
        i++;

    switch (tipo[i])
    {
    case 'B':
        array->tag = TipoByte;
        array->info.tipoByte = (uint8_t *) set_mem(sizeof(uint8_t) * valor);
        break;
    case 'C':
        array->tag = TipoChar;
        array->info.tipoChar = (uint16_t *) set_mem(sizeof(uint16_t) * valor);
        break;
    case 'D':
        array->tag = TipoDouble;
        array->info.tipoDouble = (uint64_t *) set_mem(sizeof(uint64_t) * valor);
        break;
    case 'F':
        array->tag = TipoFloat;
        array->info.tipoFloat = (uint32_t *) set_mem(sizeof(uint32_t) * valor);
        break;
    case 'I':
        array->tag = TipoInt;
        array->info.tipoInt = (uint32_t *) set_mem(sizeof(uint32_t) * valor);
        break;
    case 'J':
        array->tag = TipoLong;
        array->info.tipoLong = (uint64_t *) set_mem(sizeof(uint64_t) * valor);
        break;
    case 'L':
        array->tag = TipoReferencia;
        array->info.tipoReferencia = (uint32_t *) set_mem(sizeof(uint32_t) * valor);
        break;
    case 'S':
        array->tag = TipoShort;
        array->info.tipoShort = (uint16_t *) set_mem(sizeof(uint16_t) * valor);
        break;
    case 'Z':
        array->tag = TipoBoolean;
        array->info.tipoBoolean = (uint8_t *) set_mem(sizeof(uint8_t) * valor);
        break;
    default:
        array->tag = TipoReferencia;
        array->info.tipoReferencia = (uint32_t *) set_mem(sizeof(uint32_t) * valor);
        break;
    }
    array->array_pos = 0;
    array->base_array_pos = array->tamanho1;
    array->reference_helper = NULL;
    array->is_multarray = false;
    Data * data1 = (Data*) malloc(sizeof(Data));
	data1->reference = (void*)array;
    data1->tag = 1;

    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    //delete data1;
    //data1 = NULL;

    //free_mem((void **) &array);
    free_mem((void **) &tipo);

    return;
}

void i_arraylength(Frame *frame)
{
    tArray* array = (tArray*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = array->tamanho1;

    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    //delete data1;
    //data1 = NULL;

    return;
}
// To be implemented
void i_athrow(Frame *frame)
{
    return;
}

void i_checkcast(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, indexObjeto;
    char *nomeClasse = NULL, *nomeClasseObjeto = NULL;

    Objeto* obj = (Objeto*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    index = (uint16_t) (indexByte1 << 8) | (uint16_t) (indexByte2);

    if(obj != NULL)
    {
        index = frame->runtimeConstantPool[index - 1].class_const.name_index - 1;
        indexObjeto = obj->classe->constant_pool[obj->classe->thisClass - 1].class_const.name_index - 1;

        nomeClasse = getUtf8FromConstantPool(index, frame->runtimeConstantPool);
        nomeClasseObjeto = getUtf8FromConstantPool(indexObjeto, obj->classe->constant_pool);

        if(!strcmp(nomeClasse, nomeClasseObjeto))
            printf("Erro: Objeto do tipo errado\n");

        free_mem((void **) &nomeClasse);
        free_mem((void **) &nomeClasseObjeto);
    }
    else
        printf("Erro: Referencia nula\n");

    Data * data1 = (Data*) malloc(sizeof(Data));
	data1->reference = (void*)obj;
    data1->tag = 0;

    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    return;
}

void i_instanceof(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, indexObjeto;
    uint32_t valor = 0;
    char *nomeClasse, *nomeClasseObjeto;

    Objeto* obj = (Objeto*)frame->operandStack.top().reference;
    frame->operandStack.pop();

    index = (uint16_t) (indexByte1 << 8) | (uint16_t) (indexByte2);

    if(obj != NULL)
    {
        index = frame->runtimeConstantPool[index - 1].class_const.name_index - 1;
        indexObjeto = obj->classe->constant_pool[obj->classe->thisClass - 1].class_const.name_index - 1;

        nomeClasse = getUtf8FromConstantPool(index, frame->runtimeConstantPool);
        nomeClasseObjeto = getUtf8FromConstantPool(indexObjeto, obj->classe->constant_pool);

        if(!strcmp(nomeClasse, nomeClasseObjeto)){
            valor = 1;
        }

        free_mem((void **) &nomeClasse);
        free_mem((void **) &nomeClasseObjeto);
    }

    Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = valor;

	frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    return;
}

void i_monitorenter(Frame *frame)
{
    return;
}

void i_monitorexit(Frame *frame)
{
    return;
}

void i_wide(Frame *frame, uint8_t opcode, uint8_t index1, uint8_t index2, uint8_t constByte1, uint8_t constByte2)
{
    int16_t valor;
    uint16_t indexConcat = 0;

    indexConcat = (uint16_t) (index1 << 8) | (uint16_t) (index2);

    switch (opcode)
    {
        case 0x15:
            frame->operandStack.push(frame->localVariables.at(indexConcat));
            break;
        case 0x16:
            frame->operandStack.push(frame->localVariables.at(indexConcat + 1));
            frame->operandStack.push(frame->localVariables.at(indexConcat));
            break;
        case 0x17:
            frame->operandStack.push(frame->localVariables.at(indexConcat));
            break;
        case 0x18:
            frame->operandStack.push(frame->localVariables.at(indexConcat + 1));
            frame->operandStack.push(frame->localVariables.at(indexConcat));
            break;
        case 0x19:
            frame->operandStack.push(frame->localVariables.at(indexConcat));
            break;
        case 0x36:
            frame->localVariables.at(indexConcat) = frame->operandStack.top();
            frame->operandStack.pop();
            break;
        case 0x37:
            frame->localVariables.at(indexConcat) = frame->operandStack.top();
            frame->operandStack.pop();

            frame->localVariables.at(indexConcat + 1) = frame->operandStack.top();
            frame->operandStack.pop();
            break;
        case 0x38:
            frame->localVariables.at(indexConcat) = frame->operandStack.top();
            frame->operandStack.pop();
            break;
        case 0x39:
            frame->localVariables.at(indexConcat) = frame->operandStack.top();
            frame->operandStack.pop();

            frame->localVariables.at(indexConcat + 1) = frame->operandStack.top();
            frame->operandStack.pop();
            break;
        case 0x3a:
            frame->localVariables.at(indexConcat + 1) = frame->operandStack.top();
            frame->operandStack.pop();
            break;
        case 0x84:
            valor = (int16_t) (constByte1 << 8) | (int16_t) (constByte2);

            frame->localVariables.at(indexConcat).operand = frame->localVariables.at(indexConcat).operand + valor;
            break;
    }

    return;
}

void i_multianewarray(Frame *frame, uint8_t indexByte1, uint8_t indexByte2, uint8_t dimensions)
{
    tArray *array;
    uint16_t index;
    uint32_t valor;
    int i;
    char *tipo;

    array = (tArray *) set_mem(sizeof(tArray));

    index = (uint16_t) (indexByte1 << 8 | indexByte2);
    index = frame->runtimeConstantPool[index - 1].class_const.name_index;
    tipo = getUtf8FromConstantPool(index, frame->runtimeConstantPool);

    valor = frame->operandStack.top().operand;
    frame->operandStack.pop();

    array->tamanho1 = valor;
    //printf("dimensions at multianewarray - %d\n", dimensions);

    for (i = 1; i < dimensions; i++) {
        valor *= frame->operandStack.top().operand;
        frame->operandStack.pop();
    }

    i = 0;

    while (tipo[i] == '[')
    {
        i++;
    }

    array->tamanho = valor;

    //printf("valor at multianewarray - %d\n", array->tamanho);

    //printf("tipo[i] - %c\n", tipo[i]);

    switch (tipo[i])
    {
    case 'B':
        array->tag = TipoByte;
        array->info.tipoByte = (uint8_t *) set_mem(sizeof(uint8_t) * valor);
        break;
    case 'C':
        array->tag = TipoChar;
        array->info.tipoChar = (uint16_t *) set_mem(sizeof(uint16_t) * valor);
        break;
    case 'D':
        array->tag = TipoDouble;
        array->info.tipoDouble = (uint64_t *) set_mem(sizeof(uint64_t) * valor);
        break;
    case 'F':
        array->tag = TipoFloat;
        array->info.tipoFloat = (uint32_t *) set_mem(sizeof(uint32_t) * valor);
        break;
    case 'I':
        array->tag = TipoInt;
        //printf("INT - TAG = %d\n", array->tag);
        array->info.tipoInt = (uint32_t *) set_mem(sizeof(uint32_t) * valor);
        break;
    case 'J':
        array->tag = TipoLong;
        array->info.tipoLong = (uint64_t *) set_mem(sizeof(uint64_t) * valor);
        break;
    case 'L':
        array->tag = TipoReferencia;
        array->info.tipoReferencia = (uint32_t *) set_mem(sizeof(uint32_t) * valor);
        break;
    case 'S':
        array->tag = TipoShort;
        array->info.tipoShort = (uint16_t *) set_mem(sizeof(uint16_t) * valor);
        break;
    case 'Z':
        array->tag = TipoBoolean;
        array->info.tipoBoolean = (uint8_t *) set_mem(sizeof(uint8_t) * valor);
        break;
    default:
        array->tag = TipoReferencia;
        array->info.tipoReferencia = (uint32_t *) set_mem(sizeof(uint32_t) * valor);
        break;
    }
    array->array_pos = 0;
    array->base_array_pos = array->tamanho1;
    array->reference_helper = NULL;
    array->is_multarray = true;
    Data * data1 = (Data*) malloc(sizeof(Data));
    data1->reference = (void*)array;
    data1->tag = 1;

    frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;

    //free_mem((void **) &array);
    free_mem((void **) &tipo);

    return;
}

void i_ifnull(Frame *frame, uint8_t branchByte1, uint8_t branchByte2)
{
    void* objRef;

    objRef = frame->operandStack.top().reference;
    frame->operandStack.pop();

    if (objRef == NULL)
    {
        int16_t offset = (((uint16_t) branchByte1) << 8) + branchByte2;

        frame->codeIndexRef += offset;
    }

    return;
}

void i_ifnonnull(Frame *frame, uint8_t branchByte1, uint8_t branchByte2)
{
    void* objRef;

    objRef = frame->operandStack.top().reference;
    frame->operandStack.pop();

    if (objRef != NULL)
    {
        int16_t offset = (((uint16_t) branchByte1) << 8) + branchByte2;

        frame->codeIndexRef += offset;
    }

    return;
}

void i_goto_w(Frame *frame, uint8_t branchByte1, uint8_t branchByte2, uint8_t branchByte3, uint8_t branchByte4)
{
    uint32_t branchOffset;

    branchOffset = ((uint32_t) branchByte1 << 24) | ((uint32_t) branchByte2 << 16) | ((uint32_t) branchByte3 << 8) | ((uint32_t) branchByte4);
    frame->codeIndexRef += branchOffset - 3;

    return;
}

void i_jsr_w(Frame *frame, uint8_t branchByte1, uint8_t branchByte2, uint8_t branchByte3, uint8_t branchByte4)
{
    uint32_t branchOffset, pc;

    branchOffset = ((uint32_t) branchByte1 << 24) | ((uint32_t) branchByte2 << 16) | ((uint32_t) branchByte3 << 8) | ((uint32_t) branchByte4);
    pc = frame->codeIndexRef + 5;

    Data * data1 = (Data*) malloc(sizeof(Data));
	data1->operand = pc;

	frame->operandStack.push((*data1));

    free(data1);
    data1 = NULL;


    frame->codeIndexRef += branchOffset - 3;

    return;
}

staticField *recupera_field(char *nome, ListaStaticField **listadefields)
{
    ListaStaticField *lsf1;
    lsf1 = *listadefields;
    while (lsf1 != NULL)
    {
        if (!strcmp(nome, lsf1->dado->NomeClasse))
            return lsf1->dado;
        lsf1 = lsf1->prox;
    }
    return NULL;
}

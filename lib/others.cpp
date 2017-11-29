#include "others.hpp"

void i_nop()
{
    return;
};

void i_bipush(Frame* frame, uint32_t* n){
    uint32_t dado = *n;
    frame->operandStack.push(dado);

    return;
}

void i_sipush(Frame* frame,uint16_t* n)
{
    uint32_t dado = *n;
    frame->operandStack.push(dado);

    return;
}

void i_ldc(Frame* frame,uint8_t index, ConstPool* constantPool)
{
    uint8_t tag = constantPool[index-1].tag;
    uint32_t dado;
    float f;

    switch (tag)
    {
      case INTEGER:
      {
        frame->operandStack.push(constantPool[index-1].integer_const.bytes);
        break;
      }
      case FLOAT:
      {
        dado = constantPool[index-1].float_const.bytes;
      	memcpy(&f, &dado, sizeof(uint32_t));
  		frame->operandStack.push(dado);
        break;
      }
      case STRING:
      {
        dado = constantPool[index-1].string_const.string_index;
    	frame->operandStack.push(dado);
        break;
      }
    }
    return;
}

void i_ldc_w(Frame* frame, uint8_t index, uint8_t index2, ConstPool* constantPool)
{
    uint32_t dado=0;
    uint8_t tag = constantPool[index-1].tag;
    float f=0;

    switch (tag)
    {
      case INTEGER:
      {
        frame->operandStack.push(constantPool[index-1].integer_const.bytes);
        break;
      }
      case FLOAT:
      {
        dado = (constantPool[index-1].float_const.bytes);
        memcpy(&f, &dado, sizeof(uint32_t));
        frame->operandStack.push(constantPool[index-1].float_const.bytes);
        break;
      }
      case STRING:
      {
        dado = constantPool[index-1].string_const.string_index;
        frame->operandStack.push(dado);
        break;
      }
    }
	return;
}

void i_ldc2_w(Frame* frame, uint8_t index, uint8_t index2, ConstPool* constantPool)
{
    uint16_t indexConcat = (index<<8) | index2;
    uint8_t tag = constantPool[indexConcat-1].tag;
    uint64_t dado;

    switch(tag)
    {
      case LONG:
      {
        dado = ((uint64_t)constantPool[indexConcat-1].long_const.bytes.highBytes <<32) | constantPool[indexConcat-1].long_const.bytes.lowBytes;

        //empilhando 64 bits
        uint32_t low = (uint32_t)(dado & 0x00000000FFFFFFFF);
        frame->operandStack.push(low);

        uint32_t high = (uint32_t)(dado >> 32);
        frame->operandStack.push(high);
        break;
      }
      case DOUBLE:
      {
        dado = (uint64_t)decodeDouble(constantPool[indexConcat-1].long_const.bytes.highBytes, constantPool[indexConcat-1].long_const.bytes.lowBytes);

        //printf("indexConcat - %d\n", indexConcat);
        //printf("double - %llu\n", dado);

        //empilhando 64 bits
        uint32_t low = (uint32_t)(dado & 0x00000000FFFFFFFF);
        frame->operandStack.push(low);

        uint32_t high = (uint32_t)(dado >> 32);
        frame->operandStack.push(high);

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
    frame->operandStack.push(frame->codeIndexRef);

	int16_t offset16 = (((uint16_t)index) << 8) + index2;
	frame->codeIndexRef += (offset16 - 3);

	return;
}

void i_ret(Frame* frame, uint8_t index)
{
    frame->codeIndexRef = frame->localVariables.at(index);
    return;
}

void i_tableswitch(Frame *frame, uint32_t enderecotable, int32_t high, int32_t low, int32_t defaultbyte, int32_t *tableswitch)
{
  uint32_t target;
  int32_t index = (int32_t)frame->operandStack.top();
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
  int32_t key = (int32_t)frame->operandStack.top();
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
    int32_t valor = (int32_t)frame->operandStack.top();
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

        frame->operandStack.push(valor);
        framesStack.push(frame);
    }

    frame1->codeIndexRef = frame->codeAttribute->codeLength;

    return;
}

void i_lreturn(Frame *frame, std::stack<Frame*> &framesStack)
{
    Frame *frame1 = frame;
    uint64_t valor = (uint64_t)frame->operandStack.top();
    frame->operandStack.pop();

    if (!framesStack.empty())
    {
      frame = framesStack.top();
      framesStack.pop();

      //empilha 64 bits
      uint32_t low = (uint32_t)(valor & 0X00000000FFFFFFFF);
      frame->operandStack.push(low);

      uint32_t high = (uint32_t)(valor >> 32);
      frame->operandStack.push(high);

      framesStack.push(frame);

    }

    frame1->codeIndexRef = frame->codeAttribute->codeLength;

    return;
}

void i_freturn(Frame *frame, std::stack<Frame*> &framesStack)
{
    Frame *frame1 = frame;
    uint32_t valor = frame->operandStack.top();
    frame->operandStack.pop();

    if (!framesStack.empty())
    {
      frame = framesStack.top();
      framesStack.pop();

      frame->operandStack.push(valor);
      framesStack.push(frame);

    }

    frame1->codeIndexRef = frame->codeAttribute->codeLength;

    return;
}

void i_dreturn(Frame* frame, std::stack<Frame*> &framesStack)
{
    Frame *frame1 = frame;
    uint64_t valor = (uint64_t)frame->operandStack.top();
    frame->operandStack.pop();

    if (!framesStack.empty())
    {
      frame = framesStack.top();
      framesStack.pop();
      //empilha 64 bits
      uint32_t low = (uint32_t)(valor & 0X00000000FFFFFFFF);
      frame->operandStack.push(low);
      uint32_t high = (uint32_t)(valor >> 32);
      frame->operandStack.push(high);

      framesStack.push(frame);
    }

    frame1->codeIndexRef = frame->codeAttribute->codeLength;

    return;
}

void i_areturn(Frame* frame, std::stack<Frame*> &framesStack)
{
    Frame *frame1 = frame;
    uint32_t valor = frame->operandStack.top();
    frame->operandStack.pop();

    if (!framesStack.empty())
    {
        frame = framesStack.top();
        framesStack.pop();

        frame->operandStack.push(valor);

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
    uint32_t valor = 0;
    char *tipo = NULL, *name = NULL, *nomeClasse = NULL, *nome = NULL;
    Class *classe = NULL;
    staticField *field = NULL;

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
    //printf("nome - %s\n", name);
    //printf("nomeClasse - %s\n", nomeClasse);

    if(!classe)
    {
        if(!strcmp(nomeClasse, "java/lang/System"))
        {
            //printf("value getstatic - %u\n", valor);
            frame->operandStack.push(valor);
            //printf("value top stack - %d\n", frame->operandStack.top());

            free_mem((void **) &tipo);
            free_mem((void **) &name);
            free_mem((void **) &nomeClasse);

            return;
        }
        else
            exit(-1);
    }

    field = recupera_field(nomeClasse, &listaDeFields);

    if(!field)
    {
        //printf("value getstatic - %u\n", valor);
        frame->operandStack.push(valor);
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

        if (!strcmp(name, nome))
            break;
    }

    valor = field->valor[fieldIndex];
    frame->operandStack.push(valor);

    //printf("value getstatic - %u\n", valor);
    //printf("value top stack - %d\n", frame->operandStack.top());

    free_mem((void **) &tipo);
    free_mem((void **) &name);
    free_mem((void **) &nome);
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

    valor = frame->operandStack.top();
    frame->operandStack.pop();

    for (fieldIndex = 0; fieldIndex < classe->fields_count; fieldIndex++)
    {
        uint16_t nomeIndex = classe->fields[fieldIndex].name_index - 1;

        nome = getUtf8FromConstantPool(nomeIndex, classe->constant_pool);

        if (!strcmp(name, nome))
            break;
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
    free_mem((void **) &nome);
    free_mem((void **) &nomeClasse);

    return;
}

void i_getfield(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, tipoIndex, nameIndex, fieldIndex;
    char *tipo, *name, *nome;

    Objeto *obj = frame->objectStack.top();
    frame->objectStack.pop();

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

        if (!strcmp(name, nome))
            break;
    }

    frame->operandStack.push(obj->tipofield[fieldIndex]);

    free_mem((void **) &tipo);
    free_mem((void **) &name);
    free_mem((void **) &nome);

    return;
}

void i_putfield(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, tipoIndex, nameIndex, fieldIndex;
    uint32_t valor;
    char *tipo, *name, *nome;

    Objeto *obj = frame->objectStack.top();
    frame->objectStack.pop();

    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;

    tipoIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.nameAndType_index - 1;
    nameIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.name_index - 1;
    tipoIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.descriptor_index - 1;

    tipo = getUtf8FromConstantPool(tipoIndex, frame->runtimeConstantPool);
    name = getUtf8FromConstantPool(nameIndex, frame->runtimeConstantPool);

    valor = frame->operandStack.top();
    frame->operandStack.pop();

    for (fieldIndex = 0; fieldIndex < obj->classe->fields_count; fieldIndex++)
    {
        uint16_t nomeIndex = obj->classe->fields[fieldIndex].name_index - 1;

        nome = getUtf8FromConstantPool(nomeIndex, obj->classe->constant_pool);

        if (!strcmp(name, nome))
            break;
    }

    obj->tipofield[fieldIndex] = valor;

    free_mem((void **) &tipo);
    free_mem((void **) &name);
    free_mem((void **) &nome);

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
            uint32_t valorh = frame->operandStack.top();
            frame->operandStack.pop();

            uint32_t valorl = frame->operandStack.top();
            frame->operandStack.pop();

            uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
            //printf("LONG\n");
            printf("%.1lld", (long long) valor);
        }
        //Double
        else if (strstr(metodoDesc, "D") != NULL)
        {
            uint32_t valorh = frame->operandStack.top();
            frame->operandStack.pop();

            uint32_t valorl = frame->operandStack.top();
            frame->operandStack.pop();

            uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
            double d = (double) valor;
            //uint64_t ud = d;
            //printf("Double\n");
            printf("%.1f", d);

        }
        //Boolean
        else if (strstr(metodoDesc, "Z") != NULL)
        {
            if (frame->operandStack.top())
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
                tArray* array1 = (tArray*)(long)frame->operandStack.top();
                frame->operandStack.pop();
                //printf("Array of char\n");
                for (i = 0; i < array1->tamanho1; i++) {
                    printf("%c", array1->info.tipoChar[i]);
                }
            }
            //Char
            else{
                printf("%c", frame->operandStack.top());
                //printf("char\n");
                frame->operandStack.pop();
            }
        }
        //Inteiro
        else if (strstr(metodoDesc, "I") != NULL){
            //printf("Int\n");
            printf("%d", frame->operandStack.top());
            frame->operandStack.pop();
        }
        //Float
        else if (strstr(metodoDesc, "F") != NULL)
        {
            valor = frame->operandStack.top();
            frame->operandStack.pop();

            memcpy(&valorF, &valor, sizeof(uint32_t));
            //printf("Float\n");
            printf("%f", valorF);
        }
        //String
        else if (strstr(metodoDesc, "Ljava/lang/String") != NULL)
        {
            valor = frame->operandStack.top();
            frame->operandStack.pop();

            //printf("valor - %d\n", valor);

            if (valor != 0)
            {
                char *cPointer = getUtf8FromConstantPool(valor, frame->runtimeConstantPool);
                //printf("String\n");
                printf("%s", cPointer);
            }
            else {
                //printf("String\n");
                printf("%s", (char *) (long) valor);
            }
        }
        //Object
        else if (strstr(metodoDesc, "Ljava/lang/Object") != NULL)
        {
            valor = frame->operandStack.top();
            frame->operandStack.pop();

            void *pPointer = (void*) (long) valor;
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
            argumentos[i] = frame->operandStack.top();
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
            	    frame->operandStack.push(low);

            	    uint32_t high = (uint32_t)(zero64 >> 32);
            	    frame->operandStack.push(high);
                } else if(bytes[length-1] != 'V') {
                    frame->operandStack.push(zero32);
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
                    frame1->localVariables.push_back(argumentos[j]);
                }

                pilhaDeFrames.push(current);
                pilhaDeFrames.push(frame1);

                executeMethod(&classe->methods[i], *(classe), pilhaDeFrames);
            }
        }
        else
            printf("metodo não encontrado");
    }

    free_mem((void **) &nomeClasse);
    free_mem((void **) &nomeMetodo);
    free_mem((void **) &metodoDesc);
    free_mem((void **) &nome);
    free_mem((void **) &nomeDesc);
    free_mem((void **) &argumentos);

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
        argumentos[i] = frame->operandStack.top();
        frame->operandStack.pop();
    }

    for(i = 0; i < classe->methods_count; i++)
    {
        index = classe->methods[i].name_index - 1;
        nome = getUtf8FromConstantPool(index, classe->constant_pool);

        uint16_t index1 = classe->methods[i].descriptor_index - 1;

        nomeDesc = getUtf8FromConstantPool(index1, classe->constant_pool);

        if(!strcmp(nomeMetodo, nome) && !strcmp(metodoDesc, nomeDesc))
            break;
    }

    if (classe->methods[i].access_flags & ACC_NATIVE)
    {
        uint32_t zero32 = 0;
        uint64_t zero64 = 0;

        bytes = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.bytes;
        length = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.length;

        if(bytes[length - 1] == 'D' || bytes[length - 1] == 'J') {
            uint32_t low = (uint32_t)(zero64 & 0x00000000FFFFFFFF);
            frame->operandStack.push(low);

            uint32_t high = (uint32_t)(zero64 >> 32);
            frame->operandStack.push(high);
        } else if(bytes[length-1] != 'V') {
            frame->operandStack.push(zero32);
        }
    }
    else
    {
        prepareMethod(&classe->methods[i], classe, pilhaDeFrames, &heap);
        Frame* current = frame;
        Frame *frame1 = pilhaDeFrames.top();
        pilhaDeFrames.pop();

        for (int j = numParam; j >= 0; j--) {
            frame1->localVariables.push_back(argumentos[j]);
        }

        pilhaDeFrames.push(current);
        pilhaDeFrames.push(frame1);

        executeMethod(&classe->methods[i], *(classe), pilhaDeFrames);
    }

    free_mem((void **) &nomeClasse);
    free_mem((void **) &nomeMetodo);
    free_mem((void **) &metodoDesc);
    free_mem((void **) &nome);
    free_mem((void **) &nomeDesc);
    free_mem((void **) &argumentos);

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
        argumentos[i] = frame->operandStack.top();
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

        if(!strcmp(nomeMetodo, nome) && !strcmp(metodoDesc, nomeDesc))
            break;
    }

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
                frame->operandStack.push(low);

                uint32_t high = (uint32_t)(zero64 >> 32);
                frame->operandStack.push(high);
            } else if(bytes[length-1] != 'V') {
                frame->operandStack.push(zero32);
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
                frame1->localVariables.push_back(argumentos[j]);
            }
            pilhaDeFrames.push(current);
            pilhaDeFrames.push(frame1);

            //printf("method executed - %d\n", classe->methods[i].name_index);
            //printf("TOP OF FRAME CODEINDEXREF - %d\n", pilhaDeFrames.top()->codeIndexRef);
            executeMethod(&classe->methods[i], *(classe), pilhaDeFrames);
        }
    }
    else
        printf("metodo não encontrado");

    free_mem((void **) &nomeClasse);
    free_mem((void **) &nomeMetodo);
    free_mem((void **) &metodoDesc);
    free_mem((void **) &nome);
    free_mem((void **) &nomeDesc);
    free_mem((void **) &argumentos);

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
        argumentos[i] = frame->operandStack.top();
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

    if (i != obj->classe->methods_count)
    {
        prepareMethod(&obj->classe->methods[i], obj->classe, pilhaDeFrames, &heap);

        Frame *frame1 = pilhaDeFrames.top();
        Frame *current = frame;
        pilhaDeFrames.pop();

        for (int j = contagem; j >= 0; j--){
            //printf("argumentos[%d] - %d\n", j, argumentos[j]);
            frame1->localVariables.push_back(argumentos[j]);
        }
        pilhaDeFrames.push(current);
        pilhaDeFrames.push(frame1);

        executeMethod(&obj->classe->methods[i], *(obj->classe), pilhaDeFrames);
    }
    else
        printf("Metodo não encontrado");

    free_mem((void **) &nome);
    free_mem((void **) &nomeMetodo);
    free_mem((void **) &nomeDesc);
    free_mem((void **) &nomeClasse);
    free_mem((void **) &metodoDesc);
    free_mem((void **) &argumentos);

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
    index = frame->runtimeConstantPool[index - 1].class_const.name_index - 1;

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

        FILE* fp = openFile((char*)nomeArquivo, (char*)"rb");

        obj->classe = getClassfile(fp);
        listaDeClasses = InsereListaDeClasses(&listaDeClasses, obj->classe);
        frame->heap->listaDeClasses = listaDeClasses;

        free_mem((void **) &nomeArquivo);
        closeFile(&fp);
    }

    obj->tamanhotipoField = obj->classe->fields_count;
    obj->tipofield = (uint32_t *) set_mem(sizeof(uint32_t) * obj->tamanhotipoField);

    frame->objectStack.push(obj);

    free_mem((void **) &nomeClasse);

    return;
}

void i_newarray(Frame *frame, uint8_t aType)
{
    tArray* array;
    uint32_t valor, referencia;

    array = (tArray *) set_mem(sizeof(tArray));
    valor = frame->operandStack.top();
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

    referencia = (long)array;

    frame->operandStack.push(referencia);

    free_mem((void **) &array);

    return;
}

void i_anewarray(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    tArray *array;
    uint16_t index;
    uint32_t i = 0, valor, referencia;
    char *tipo;

    array = (tArray *) set_mem(sizeof(tArray));

    index = (uint16_t) (indexByte1 << 8) | (uint16_t) (indexByte2);
    index = frame->runtimeConstantPool[index - 1].class_const.name_index - 1;
    tipo = getUtf8FromConstantPool(index, frame->runtimeConstantPool);

    valor = frame->operandStack.top();
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
    referencia = (int)(long)array;

    frame->operandStack.push(referencia);

    free_mem((void **) &array);
    free_mem((void **) &tipo);

    return;
}

void i_arraylength(Frame *frame)
{
    tArray* array = (tArray*)(long)frame->operandStack.top();
    frame->operandStack.pop();

    frame->operandStack.push(array->tamanho1);

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

    Objeto *obj = frame->objectStack.top();
    frame->objectStack.pop();

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

    frame->objectStack.push(obj);

    return;
}

void i_instanceof(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, indexObjeto;
    uint32_t valor = 0;
    char *nomeClasse, *nomeClasseObjeto;

    Objeto *obj = frame->objectStack.top();
    frame->objectStack.pop();

    index = (uint16_t) (indexByte1 << 8) | (uint16_t) (indexByte2);

    if(obj != NULL)
    {
        index = frame->runtimeConstantPool[index - 1].class_const.name_index - 1;
        indexObjeto = obj->classe->constant_pool[obj->classe->thisClass - 1].class_const.name_index - 1;

        nomeClasse = getUtf8FromConstantPool(index, frame->runtimeConstantPool);
        nomeClasseObjeto = getUtf8FromConstantPool(indexObjeto, obj->classe->constant_pool);

        if(!strcmp(nomeClasse, nomeClasseObjeto))
            valor = 1;

        free_mem((void **) &nomeClasse);
        free_mem((void **) &nomeClasseObjeto);
    }

    frame->operandStack.push(valor);

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
    uint32_t value = 0;

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
            value = frame->operandStack.top();
            frame->operandStack.pop();

            frame->localVariables.at(indexConcat) = value;
            break;
        case 0x37:
            value = frame->operandStack.top();
            frame->operandStack.pop();

            frame->localVariables.at(indexConcat) = value;

            value = frame->operandStack.top();
            frame->operandStack.pop();

            frame->localVariables.at(indexConcat + 1) = value;
            break;
        case 0x38:
            value = frame->operandStack.top();
            frame->operandStack.pop();

            frame->localVariables.at(indexConcat) = value;
            break;
        case 0x39:
            value = frame->operandStack.top();
            frame->operandStack.pop();

            frame->localVariables.at(indexConcat) = value;
            value = frame->operandStack.top();
            frame->operandStack.pop();

            frame->localVariables.at(indexConcat + 1) = value;
            break;
        case 0x3a:
            value = frame->operandStack.top();
            frame->operandStack.pop();

            frame->localVariables.at(indexConcat + 1) = value;
            break;
        case 0x84:
            valor = (int16_t) (constByte1 << 8) | (int16_t) (constByte2);

            frame->localVariables.at(indexConcat) = frame->localVariables.at(indexConcat) + valor;
            break;
    }

    return;
}

void i_multianewarray(Frame *frame, uint8_t indexByte1, uint8_t indexByte2, uint8_t dimensions)
{
    tArray *array;
    uint16_t index;
    uint32_t valor, referencia;
    int i;
    char *tipo;

    array = (tArray *) set_mem(sizeof(tArray));

    index = (uint16_t) (indexByte1 << 8 | indexByte2);
    index = ((frame->runtimeConstantPool[index - 1].class_const.name_index) - 1);
    tipo = getUtf8FromConstantPool(index, frame->runtimeConstantPool);

    valor = frame->operandStack.top();
    frame->operandStack.pop();

    array->tamanho1 = valor;

    for (i = 1; i < dimensions; i++) {
        valor *= frame->operandStack.top();
        frame->operandStack.pop();
    }

    i = 0;

    while (tipo[i] == '[')
    {
        i++;
    }

    array->tamanho = valor;

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

    referencia = (int)(long)array;

    frame->operandStack.push(referencia);

    free_mem((void **) &array);
    free_mem((void **) &tipo);

    return;
}

void i_ifnull(Frame *frame, uint8_t branchByte1, uint8_t branchByte2)
{
    uint32_t objRef = 0;

    objRef = frame->operandStack.top();
    frame->operandStack.pop();

    if (objRef == 0x0)
    {
        int16_t offset = (((uint16_t) branchByte1) << 8) + branchByte2;

        frame->codeIndexRef += offset;
    }

    return;
}

void i_ifnonnull(Frame *frame, uint8_t branchByte1, uint8_t branchByte2)
{
    uint32_t objRef;

    objRef = frame->operandStack.top();
    frame->operandStack.pop();

    if (objRef != 0x0)
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

    frame->operandStack.push(pc);

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

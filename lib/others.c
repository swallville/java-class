#include "others.h"

void i_nop()
{
    return;
};

void i_bipush(Frame* frame,uint32_t* n){
    push(n,&(frame->operandStack));
    return;
}

void i_sipush(Frame* frame,uint16_t* n)
{
    uint32_t dado = *n;
    push(&dado,&(frame->operandStack));
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
        push(&constantPool[index-1].integer_const.bytes,&(frame->operandStack));
        break;
    case FLOAT:
    	dado =  constantPool[index-1].float_const.bytes;
    	memcpy(&f, &dado, sizeof(uint32_t));
		push(&dado,&(frame->operandStack));
        break;
    case STRING:
		dado =  constantPool[index-1].string_const.string_index;
		push(&dado,&(frame->operandStack));
        break;
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
        push(&constantPool[index-1].integer_const.bytes,&(frame->operandStack));
        break;
    case FLOAT:
        	dado = (constantPool[index-1].float_const.bytes);
        	memcpy(&f, &dado, sizeof(uint32_t));
        push(&(constantPool[index-1].float_const.bytes),&(frame->operandStack));
        break;
    case STRING:
		dado = constantPool[index-1].string_const.string_index;
		push(&dado,&(frame->operandStack));
        break;
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

		dado = ((uint64_t)constantPool[indexConcat-1].long_const.bytes.highBytes <<32) | constantPool[indexConcat-1].long_const.bytes.lowBytes;
		push(&dado,&(frame->operandStack));
        break;
    case DOUBLE:
        dado = ((uint64_t)constantPool[indexConcat-1].long_const.bytes.highBytes <<32) | constantPool[indexConcat-1].long_const.bytes.lowBytes;

        //empilhando 64 bits
        uint32_t low = (uint32_t)(dado & 0x00000000FFFFFFFF);
        push(&(low), &(frame->operandStack));

        uint32_t high = (uint32_t)(dado >> 32);
        push(&(high), &(frame->operandStack));


        break;
    }
    return;
}

void i_goto(Frame* frame, uint8_t index1, uint8_t index2)
{
	int16_t offset16 = (((uint16_t)index1)<<8)+index2;
	frame->codeIndexRef += (offset16 - 3);

	return;
}

void i_jsr(Frame* frame, uint8_t index, uint8_t index2){
	push(&(frame->codeIndexRef),&(frame->operandStack));
	int16_t offset16 = (((uint16_t)index)<<8)+index2;
		frame->codeIndexRef += (offset16 - 3);

	return;
}

void i_ret(Frame* frame, uint8_t index)
{
    (*frame->codeIndexRef) = frame->localVariables[index];
    return;
}

void i_tableswitch(Frame *frame)
{
  return;
}

void i_lookupswitch(Frame * frame)
{
  
  return;
}

void i_ireturn(Frame *frame)
{
    Frame *frame1;
    uint32_t valor;
    valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame1 = frame;

    if (frame->framesStack != NULL)
    {
        frame = (Frame*)(pop(&(frame->framesStack))->value);
        push(&(valor),&(frame->operandStack));
        push(&(frame),&(frame->framesStack));
        free_mem((void**)&frame1);
    }
    else
    {
        (*frame->codeIndexRef) = frame->codeAttribute->codeLength;
    }
    return;
}

void i_lreturn(Frame *frame)
{
    Frame *frame1;
    uint64_t valor;
    valor = *((uint64_t*)pop(&(frame->operandStack))->value);
    frame1 = frame;
    if (frame->framesStack != NULL)
    {
        frame = (Frame*)(pop(&(frame->framesStack))->value);

            //empilha 64 bits
            uint32_t low = (uint32_t)(valor & 0X00000000FFFFFFFF);
            push(&(low), &(frame->operandStack));
            uint32_t high = (uint32_t)(valor >> 32);
            push(&(high), &(frame->operandStack));

        push((&frame),&(frame->framesStack));
        free_mem((void**)&frame1);

    }
    else
    {
        (*frame->codeIndexRef) = frame->codeAttribute->codeLength;
    }

    return;
}

void i_freturn(Frame *frame)
{
    Frame *frame1;
    uint32_t valor;
    valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame1 = frame;


    if (frame->framesStack != NULL)
    {
        frame = (Frame*)(pop(&(frame->framesStack))->value);
        push(&valor,&(frame->operandStack));
        push((&frame),&(frame->framesStack));
        free_mem((void**)&frame1);

    }
    else
    {
        (*frame->codeIndexRef) = frame->codeAttribute->codeLength;
    }

    return;
}

void i_dreturn(Frame* frame)
{
    Frame *frame1;
    uint64_t valor;
    valor = *((uint64_t*)pop(&(frame->operandStack))->value);
    frame1 = frame;

    if (frame->framesStack != NULL)
    {
        frame = (Frame*)(pop(&(frame->framesStack))->value);

        //empilha 64 bits
            uint32_t low = (uint32_t)(valor & 0X00000000FFFFFFFF);
            push(&(low), &(frame->operandStack));
            uint32_t high = (uint32_t)(valor >> 32);
            push(&(high), &(frame->operandStack));

        push(&frame,&frame->framesStack);
        free_mem((void**)&frame1);
    }
    else
    {
         (*frame->codeIndexRef) = frame->codeAttribute->codeLength;
    }
    return;
}

void i_areturn(Frame* frame)
{
    Frame *frame1;
    uint32_t valor;
    valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame1 = frame;

    if (frame->framesStack != NULL)
    {
        frame = (Frame*)(pop(&(frame->framesStack))->value);
        push(&(valor),&(frame->operandStack));
        push(&(frame),&(frame->framesStack));
        free_mem((void**)&frame1);
    }
    else
    {
        (*frame->codeIndexRef) = frame->codeAttribute->codeLength;
    }
    return;
}

void i_return(Frame* frame)
{
    (*frame->codeIndexRef) = frame->codeAttribute->codeLength;
    return;
}

void i_getstatic(Frame *frame, ListaStaticField *listaDeFields, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index = 0, tipoIndex = 0, nameIndex = 0, fieldIndex = 0, nomeClasseIndex = 0;
    uint64_t valor = 0;
    char *tipo = NULL, *name = NULL, *nomeClasse = NULL, *nome = NULL;
    Class *classe = NULL;
    staticField *field = NULL;
    
    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;
    
    nomeClasseIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.class_index - 1;
    nomeClasseIndex = frame->runtimeConstantPool[nomeClasseIndex].class_const.name_index - 1;
    tipoIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.nameAndType_index - 1;
    nameIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.name_index - 1;
    tipoIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.descriptor_index - 1;

    tipo = getUtf8FromConstantPool(tipoIndex, frame->runtimeConstantPool);
    name = getUtf8FromConstantPool(nameIndex, frame->runtimeConstantPool);
    nomeClasse = getUtf8FromConstantPool(nomeClasseIndex, frame->runtimeConstantPool);
    
    classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);
    
    if(!classe)
    {
        if(!strcmp(nomeClasse, "java/lang/System"))
        {
            push(&valor, &(frame->operandStack));

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
        push(&valor, &(frame->operandStack));

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
    push(&valor, &(frame->operandStack));
        
    free_mem((void **) &tipo);
    free_mem((void **) &name);
    free_mem((void **) &nome);
    free_mem((void **) &nomeClasse);
    
    return;
}

void i_putstatic(Frame *frame, ListaStaticField *listaDeFields, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, tipoIndex, nameIndex, fieldIndex, nomeClasseIndex;
    uint64_t valor;
    char *tipo, *name, *nomeClasse, *nome;
    Class *classe;
    staticField *field;
    
    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;

    nomeClasseIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.class_index - 1;
    nomeClasseIndex = frame->runtimeConstantPool[nomeClasseIndex].class_const.name_index - 1;
    tipoIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.nameAndType_index - 1;
    nameIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.name_index - 1;
    tipoIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.descriptor_index - 1;

    tipo = getUtf8FromConstantPool(tipoIndex, frame->runtimeConstantPool);
    name = getUtf8FromConstantPool(nameIndex, frame->runtimeConstantPool);
    nomeClasse = getUtf8FromConstantPool(nomeClasseIndex, frame->runtimeConstantPool);
    
    classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);
    
    valor = (uint64_t) pop(&(frame->operandStack));

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
    Objeto *obj;

    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;

    tipoIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.nameAndType_index - 1;
    nameIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.name_index - 1;
    tipoIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.descriptor_index - 1;
    
    tipo = getUtf8FromConstantPool(tipoIndex, frame->runtimeConstantPool);
    name = getUtf8FromConstantPool(nameIndex, frame->runtimeConstantPool);

    obj = (void *) (long) pop(&(frame->operandStack));

    for (fieldIndex = 0; fieldIndex < obj->tamanhotipoField; fieldIndex++)
    {
        uint16_t nomeIndex = obj->classe->fields[fieldIndex].name_index - 1;

        nome = getUtf8FromConstantPool(nomeIndex, obj->classe->constant_pool);

        if (!strcmp(name, nome))
            break;
    }

    push((void *) obj->tipofield[fieldIndex], &(frame->operandStack));
    
    free_mem((void **) &tipo);
    free_mem((void **) &name);
    free_mem((void **) &nome);

    return;
}

void i_putfield(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, tipoIndex, nameIndex, fieldIndex;
    uint64_t valor;
    char *tipo, *name, *nome;
    Objeto *obj;

    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;
    
    tipoIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.nameAndType_index - 1;
    nameIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.name_index - 1;
    tipoIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.descriptor_index - 1;
    
    tipo = getUtf8FromConstantPool(tipoIndex, frame->runtimeConstantPool);
    name = getUtf8FromConstantPool(nameIndex, frame->runtimeConstantPool);

    valor = (uint64_t) pop(&(frame->operandStack));
    obj = (void *) (long) pop(&(frame->operandStack));
    
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

void i_invokevirtual(Frame *frame, Stack *pilhaDeFrames, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, Heap *heap)
{
    uint16_t index = 0, classIndex = 0, descriptorIndex = 0, metodoIndex = 0;
    uint32_t valor32 = 0, *argumentos = NULL;
    uint64_t valor64 = 0;
    char *nomeClasse = NULL, *nomeMetodo = NULL, *metodoDesc = NULL, *nome = NULL, *nomeDesc = NULL;
    float valorF = 0;
    int i = 0;
    Class *classe = NULL;
    
    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;
    classIndex = frame->runtimeConstantPool[index - 1].methodRef_const.class_index - 1;
    classIndex = frame->runtimeConstantPool[classIndex].class_const.name_index - 1;
    nomeClasse = getUtf8FromConstantPool(classIndex, frame->runtimeConstantPool);
    descriptorIndex = frame->runtimeConstantPool[index - 1].methodRef_const.nameAndType_index - 1;
    metodoIndex = frame->runtimeConstantPool[descriptorIndex].nameAndType_const.name_index - 1;
    descriptorIndex = frame->runtimeConstantPool[descriptorIndex].nameAndType_const.descriptor_index - 1;
    nomeMetodo = getUtf8FromConstantPool(metodoIndex, frame->runtimeConstantPool);
    metodoDesc = getUtf8FromConstantPool(descriptorIndex, frame->runtimeConstantPool);

    if (!strcmp(nomeClasse, "java/io/PrintStream") && (!strcmp(nomeMetodo, "print") || !strcmp(nomeMetodo, "println")))
    {
        //Long
        if (strstr(metodoDesc, "J") != NULL)
        {
            valor64 = (uint64_t) pop(&(frame->operandStack));
            
            int64_t value = valor64;
            
            printf("%ld", value);
        }
        //Double
        else if (strstr(metodoDesc, "D") != NULL)
        {
            valor64 = (uint64_t) pop(&(frame->operandStack));
            
            double value;
            
            memcpy(&value, &valor64, sizeof(uint64_t));
            printf("%f", value);

        }
        //Boolean
        else if (strstr(metodoDesc, "Z") != NULL)
        {
            if (pop(&(frame->operandStack)))
                printf("TRUE");
            else
                printf("FALSE");
        }
        //Char
        else if (strstr(metodoDesc, "C") != NULL)
        {
            //Array
            if (strstr(metodoDesc, "[C") != NULL)
            {
                tArray *array1 = (void*) (long) pop(&(frame->operandStack));
                
                for (i = 0; i < array1->tamanho1; i++)
                    printf("%c", array1->info.tipoChar[i]);
            }
            //Char
            else
                printf("%c", (int) (long) pop(&(frame->operandStack)));
        }
        //Inteiro
        else if (strstr(metodoDesc, "I") != NULL)
            printf("%d", (int32_t) (long) pop(&(frame->operandStack)));
        //Float
        else if (strstr(metodoDesc, "F") != NULL)
        {
            valor32 = (uint32_t) (long) pop(&(frame->operandStack));
            memcpy(&valorF, &valor32, sizeof(uint32_t));
            printf("%f", valorF);

        }
        //String
        else if (strstr(metodoDesc, "Ljava/lang/String") != NULL)
        {
            valor32 = (uint32_t) (long) pop(&(frame->operandStack));
            
            if (valor32 != 0)
            {
                char *cPointer = getUtf8FromConstantPool((uint16_t) valor32 - 1, frame->currentClass->constant_pool);
                printf("%s", cPointer);
            }
            else
                printf("%s", (char *) (long) valor32);
        }
        //Object
        else if (strstr(metodoDesc, "Ljava/lang/Object") != NULL)
        {
            valor32 = (uint32_t) (long) pop(&(frame->operandStack));
            
            void *pPointer = (void*) (long) valor32;
            printf("%p",pPointer);
        }

        if (strstr(nomeMetodo, "println") != NULL)
            printf("\n");
    }
    else
    {
        uint32_t numparam = 0;
        
        classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);
        
        if (classe == NULL)
        {
            char *nomeArquivo;
            
            classe = (Class *) set_mem(sizeof(Class));
            nomeArquivo = (char *) set_mem(sizeof(char) * (strlen(nomeClasse) + 7));
            strcpy(nomeArquivo, nomeClasse);
            strcat(nomeArquivo, ".class");
            classe = getClassfile((FILE *) (long) openFile(nomeArquivo, "rb"));
            listaDeClasses = InsereListaDeClasses(&listaDeClasses, classe);
            frame->heap->listaDeClasses = listaDeClasses;

            free_mem((void **) &nomeArquivo);
        }

        uint8_t *bytes = frame->runtimeConstantPool[descriptorIndex].utf8_const.bytes;
        uint16_t length = frame->runtimeConstantPool[descriptorIndex].utf8_const.length;

        for (i = 0; i < length && bytes[i] != ')'; i++)
        {
            if(bytes[i] == 'L')
            {
                while(bytes[i] != ';')
                    i++;
                
                numparam++;
            }
            else if((bytes[i] == 'B') || (bytes[i] == 'C') || (bytes[i] == 'F') || (bytes[i] == 'I') || (bytes[i] == 'S') || (bytes[i] == 'Z'))
                numparam++;
            else if((bytes[i] == 'D')||(bytes[i] == 'J'))
                numparam += 2;
        }

        argumentos = (uint32_t *) set_mem(sizeof(uint32_t) * (numparam + 1));

        for (i = numparam; i >= 0; i--)
            argumentos[i] = (uint32_t) (long) pop(&(frame->operandStack));

        nomeMetodo = getUtf8FromConstantPool(metodoIndex, frame->runtimeConstantPool);

        for(i = 0; i < classe->methods_count; i++)
        {
            index = classe->methods[i].name_index - 1;
            nome = getUtf8FromConstantPool(index, classe->constant_pool);
            
            uint32_t index1 = classe->methods[i].descriptor_index - 1;
            
            nomeDesc = getUtf8FromConstantPool(index1, classe->constant_pool);
            
            if(!strcmp(nomeMetodo, nome) && !strcmp(metodoDesc, nomeDesc))
                break;
        }

        if (i != classe->methods_count)
        {
            if (classe->methods[i].access_flags & ACC_NATIVE)
            {
                uint64_t zero = 0;

                bytes = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.bytes;
                length = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.length;
                
                push(&zero, &frame->operandStack);
            }
            else
            {
                Frame *frame1 = (Frame *) pop(&pilhaDeFrames);
                
                for (int j = numparam; j >= 0; j--)
                    frame1->localVariables[j] = argumentos[j];

                push(frame1, &pilhaDeFrames);
                executeMethod(&classe->methods[i], *(classe));
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

void i_invokespecial(Frame *frame, Stack *pilhaDeFrames, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, Heap *heap)
{
    uint8_t *bytes = NULL;
    uint16_t index = 0, classIndex = 0, descriptorIndex = 0, metodoIndex = 0, length = 0;
    uint32_t numParam = 0, *argumentos = NULL;
    char *nomeClasse = NULL, *nomeMetodo = NULL, *nome, *nomeDesc, *metodoDesc;
    int i = 0;
    Class *classe = NULL;
    
    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;
    classIndex = frame->runtimeConstantPool[index - 1].methodRef_const.class_index - 1;
    classIndex = frame->runtimeConstantPool[classIndex].class_const.name_index - 1;
    nomeClasse = getUtf8FromConstantPool(classIndex, frame->runtimeConstantPool);
    classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);
    
    if (classe == NULL)
    {
        char *nomeArquivo;
        
        classe = (Class *) set_mem(sizeof(Class));
        nomeArquivo = (char *) set_mem(sizeof(char) * (strlen(nomeClasse) + 7));
        strcpy(nomeArquivo, nomeClasse);
        strcat(nomeArquivo, ".class");
        classe = getClassfile((FILE *) (long) openFile(nomeArquivo, "rb"));
        listaDeClasses = InsereListaDeClasses(&listaDeClasses, classe);
        frame->heap->listaDeClasses = listaDeClasses;

        free_mem((void **) &nomeArquivo);
    }

    descriptorIndex = frame->runtimeConstantPool[index - 1].methodRef_const.nameAndType_index - 1;
    metodoIndex = frame->runtimeConstantPool[descriptorIndex].nameAndType_const.name_index - 1;
    descriptorIndex = frame->runtimeConstantPool[descriptorIndex].nameAndType_const.descriptor_index - 1;
    nomeMetodo = getUtf8FromConstantPool(metodoIndex, frame->runtimeConstantPool);
    metodoDesc = getUtf8FromConstantPool(descriptorIndex, frame->runtimeConstantPool);
    
    bytes = frame->runtimeConstantPool[descriptorIndex].utf8_const.bytes;
    length = frame->runtimeConstantPool[descriptorIndex].utf8_const.length;

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

    for (i = numParam; i >= 0; i--)
        argumentos[i] = (uint32_t) (long) pop(&(frame->operandStack));

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
        uint64_t zero = 0;
        
        bytes = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.bytes;
        length = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.length;
        
        push(&zero, &frame->operandStack);
    }
    else
    {        
        Frame *frame1 = (Frame *) pop(&pilhaDeFrames);
        
        for (int j = numParam; j >= 0; j--)
            frame1->localVariables[j] = argumentos[j];
        
        push(frame1, &pilhaDeFrames);
        executeMethod(&classe->methods[i], *(classe));
    }
    
    free_mem((void **) &nomeClasse);
    free_mem((void **) &nomeMetodo);
    free_mem((void **) &metodoDesc);
    free_mem((void **) &nome);
    free_mem((void **) &nomeDesc);
    free_mem((void **) &argumentos);
    
    return;
}

void i_invokestatic(Frame *frame, Stack *pilhaDeFrames, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, Heap *heap)
{
    uint8_t *bytes = NULL;
    uint16_t index = 0, classIndex = 0, descriptorIndex = 0, metodoIndex = 0, length = 0;
    uint32_t numParam = 0, *argumentos = NULL;
    char *nomeClasse = NULL, *nomeMetodo = NULL, *metodoDesc = NULL, *nome = NULL, *nomeDesc = NULL;
    int i = 0;
    Class *classe = NULL;
    
    index = (uint32_t) indexByte1 << 8 | (uint32_t) indexByte2;
    classIndex = frame->runtimeConstantPool[index - 1].methodRef_const.class_index - 1;
    classIndex = frame->runtimeConstantPool[classIndex].class_const.name_index - 1;
    nomeClasse = getUtf8FromConstantPool(classIndex, frame->runtimeConstantPool);
    classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);
    
    descriptorIndex = frame->runtimeConstantPool[index - 1].methodRef_const.nameAndType_index - 1;
    metodoIndex = frame->runtimeConstantPool[descriptorIndex].nameAndType_const.name_index - 1;
    descriptorIndex = frame->runtimeConstantPool[descriptorIndex].nameAndType_const.descriptor_index - 1;
    metodoDesc = getUtf8FromConstantPool(descriptorIndex, frame->runtimeConstantPool);
    
    bytes = frame->runtimeConstantPool[descriptorIndex].utf8_const.bytes;
    length = frame->runtimeConstantPool[descriptorIndex].utf8_const.length;

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

    argumentos = (uint32_t *) set_mem(sizeof(uint32_t) * numParam);

    for (i = (numParam - 1); i >= 0; i--)
        argumentos[i] = (uint32_t) (long) pop(&(frame->operandStack));

    nomeMetodo = getUtf8FromConstantPool(metodoIndex, frame->runtimeConstantPool);

    for(i = 0; i < classe->methods_count; i++)
    {
        index = classe->methods[i].name_index - 1;
        nome = getUtf8FromConstantPool(index, classe->constant_pool);
        
        uint16_t index1 = classe->methods[i].descriptor_index - 1;
        
        nomeDesc = getUtf8FromConstantPool(index1, classe->constant_pool);
        
        if(!strcmp(nomeMetodo, nome) && !strcmp(metodoDesc, nomeDesc))
            break;
    }

    if (i != classe->methods_count)
    {
        if (classe->methods[i].access_flags & ACC_NATIVE)
        {
            uint64_t zero = 0;
            
            bytes = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.bytes;
            length = classe->constant_pool[classe->methods[i].descriptor_index - 1].utf8_const.length;
            
            push(&zero, &frame->operandStack);
        }
        else
        {
            Frame *frame1 = (Frame *) pop(&pilhaDeFrames);
            
            for (int j = (numParam - 1); j >= 0; j--)
                frame1->localVariables[j] = argumentos[j];
            
            push(frame1, &pilhaDeFrames);
            executeMethod(&classe->methods[i], *(classe));
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

void i_invokeinterface(Frame *frame, Stack *pilhaDeFrames, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, uint8_t contagem, uint8_t zero, Heap *heap)
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
        argumentos[i] = (uint32_t) (long) pop(&frame->operandStack);
    
    index = frame->runtimeConstantPool[index - 1].interfaceMethodRef_const.nameAndType_index - 1;
    descriptorIndex = frame->runtimeConstantPool[index].nameAndType_const.descriptor_index - 1;
    index = frame->runtimeConstantPool[index].nameAndType_const.name_index - 1;
    classeIndex = frame->runtimeConstantPool[classeIndex - 1].interfaceMethodRef_const.class_index - 1;
    classeIndex = frame->runtimeConstantPool[classeIndex].class_const.name_index - 1;
    
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
        Frame *frame1 = (void *) (long) pop(&pilhaDeFrames);
        
        for (int j = contagem; j >= 0; j--)
            frame1->localVariables[j] = argumentos[j];
        
        push(frame1, &pilhaDeFrames);
        executeMethod(&obj->classe->methods[i], *(obj->classe));
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

void i_invokedynamic(Frame *frame, Stack *pilhadeframes, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, uint8_t zero_1, uint8_t zero_2, Heap *heap)
{
    return;
}

void i_new(Frame *frame, uint8_t indexByte1, uint8_t indexByte2, ListaClasses *listaDeClasses)
{
    uint16_t index;
    uint32_t valor;
    char *nomeClasse;
    Objeto *obj;
    
    index = (uint16_t) (indexByte1 << 8) | (uint16_t) (indexByte2);
    index = frame->runtimeConstantPool[index - 1].class_const.name_index - 1;
    
    nomeClasse = getUtf8FromConstantPool(index, frame->runtimeConstantPool);
    
    obj = (Objeto *) set_mem(sizeof(Objeto));
    obj->classe = RecuperaClassePorNome(nomeClasse,&listaDeClasses);
    
    if (obj->classe == NULL)
    {
        char *nomeArquivo;
        
        nomeArquivo = (char *) set_mem(sizeof(char) * (strlen(nomeClasse) + 7));
        strcpy(nomeArquivo, nomeClasse);
        strcat(nomeArquivo, ".class");
        obj->classe = getClassfile((FILE *) (long) openFile(nomeArquivo, "rb"));
        listaDeClasses = InsereListaDeClasses(&listaDeClasses, obj->classe);
        frame->heap->listaDeClasses = listaDeClasses;

        free_mem((void **) &nomeArquivo);
    }
    
    obj->tamanhotipoField = obj->classe->fields_count;    
    obj->tipofield = (uint64_t *) set_mem(sizeof(uint64_t) * obj->tamanhotipoField);
    
    valor = (uint32_t) (long) obj;
    push(&valor, &(frame->operandStack));

    free_mem((void **) &nomeClasse);

    return;
}

void i_newarray(Frame *frame, uint8_t aType)
{
    tArray *array;
    uint32_t valor, referencia;
    
    array = (tArray *) set_mem(sizeof(tArray));
    valor = (uint32_t) (long) pop(&(frame->operandStack));
    
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

    referencia = (int) (long) array;
    push(&referencia, &(frame->operandStack));

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
    
    valor = (uint32_t) (long) pop(&(frame->operandStack));
    
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

    referencia = (int) (long) array;
    push(&referencia, &(frame->operandStack));
    
    free_mem((void **) &array);
    free_mem((void **) &tipo);
    
    return;
}

void i_arraylength(Frame *frame)
{
    tArray *array;
    
    array = (void *) (long) pop(&(frame->operandStack));
    push(&(array->tamanho1), &(frame->operandStack));

    return;
}

void i_athrow(Frame *frame)
{
    return;
}

void i_checkcast(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, indexObjeto;
    char *nomeClasse = NULL, *nomeClasseObjeto = NULL;
    Objeto *obj;
    
    index = (uint16_t) (indexByte1 << 8) | (uint16_t) (indexByte2);
    obj = (void *) (long) pop(&(frame->operandStack));
    
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
    
    push(obj, &(frame->operandStack));

    return;
}

void i_instanceof(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, indexObjeto;
    uint32_t valor = 0;
    char *nomeClasse, *nomeClasseObjeto;
    Objeto *obj;
    
    index = (uint16_t) (indexByte1 << 8) | (uint16_t) (indexByte2);
    obj = (void *) (long) pop(&(frame->operandStack));

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
    
    push(&valor, &(frame->operandStack));

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
            push(&(frame->localVariables[indexConcat]), &(frame->operandStack));
            break;
        case 0x16:
            push(&(frame->localVariables[indexConcat + 1]), &(frame->operandStack));
            push(&(frame->localVariables[indexConcat]), &(frame->operandStack));
            break;
        case 0x17:
            push(&(frame->localVariables[indexConcat]), &(frame->operandStack));
            break;
        case 0x18:
            push(&(frame->localVariables[indexConcat + 1]), &(frame->operandStack));
            push(&(frame->localVariables[indexConcat]), &(frame->operandStack));
            break;
        case 0x19:
            push(&(frame->localVariables[indexConcat]), &(frame->operandStack));
            break;
        case 0x36:
            value = (uint32_t) (long) pop(&(frame->operandStack));
            frame->localVariables[indexConcat] = value;
            break;
        case 0x37:
            value = (uint32_t) (long) pop(&(frame->operandStack));
            frame->localVariables[indexConcat] = value;
            value = (uint32_t) (long) pop(&(frame->operandStack));
            frame->localVariables[indexConcat + 1] = value;
            break;
        case 0x38:
            value = (uint32_t) (long) pop(&(frame->operandStack));
            frame->localVariables[indexConcat] = value;
            break;
        case 0x39:
            value = (uint32_t) (long) pop(&(frame->operandStack));
            frame->localVariables[indexConcat] = value;
            value = (uint32_t) (long) pop(&(frame->operandStack));
            frame->localVariables[indexConcat + 1] = value;
            break;
        case 0x3a:
            value = (uint32_t) (long) pop(&(frame->operandStack));
            frame->localVariables[indexConcat] = value;
            break;
        case 0x84:
            valor = (int16_t) (constByte1 << 8) | (int16_t) (constByte2);
            frame->localVariables[indexConcat] += valor;
            break;
    }
    
    return;
}

void i_multianewarray(Frame *frame, uint8_t indexByte1, uint8_t indexByte2, uint8_t dimensions)
{
    tArray *array;
    uint16_t index;
    uint32_t valor,referencia;
    int i;
    char *tipo;
    
    array = (tArray *) set_mem(sizeof(tArray));
    
    index = (uint16_t) (indexByte1 << 8 | indexByte2);
    index = ((frame->runtimeConstantPool[index - 1].class_const.name_index) - 1);
    tipo = getUtf8FromConstantPool(index, frame->runtimeConstantPool);
    
    valor = (uint32_t) (long) pop(&(frame->operandStack));
    array->tamanho1 = valor;
    
    for (i = 1; i < dimensions; i++)
        valor *= (uint32_t) (long) pop(&(frame->operandStack));
    
    i = 0;

    while (tipo[i] == '[')
        i++;

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

    referencia = (int) (long) array;
    push(&referencia, &(frame->operandStack));
    
    free_mem((void **) &array);
    free_mem((void **) &tipo);
    
    return;
}

void i_ifnull(Frame *frame, uint8_t branchByte1, uint8_t branchByte2)
{
    uint32_t objRef = 0;
    
    objRef = (uint32_t) (long) pop(&(frame->operandStack));
    
    if (objRef == 0x0)
    {
        int16_t offset = (((uint16_t) branchByte1) << 8) + branchByte2;
        
        *(frame->codeIndexRef) += offset;
    }

    return;
}

void i_ifnonnull(Frame *frame, uint8_t branchByte1, uint8_t branchByte2)
{
    uint32_t objRef;

    objRef = (uint32_t) (long) pop(&(frame->operandStack));
    
    if (objRef != 0x0)
    {
        int16_t offset = (((uint16_t) branchByte1) << 8) + branchByte2;
        
        *(frame->codeIndexRef) += offset;
    }

    return;
}

void i_goto_w(Frame *frame, uint8_t branchByte1, uint8_t branchByte2, uint8_t branchByte3, uint8_t branchByte4)
{
    uint32_t branchOffset;
    
    branchOffset = ((uint32_t) branchByte1 << 24) | ((uint32_t) branchByte2 << 16) | ((uint32_t) branchByte3 << 8) | ((uint32_t) branchByte4);
    *(frame->codeIndexRef) += branchOffset - 3;

    return;
}

void i_jsr_w(Frame *frame, uint8_t branchByte1, uint8_t branchByte2, uint8_t branchByte3, uint8_t branchByte4)
{
    uint32_t branchOffset, pc;

    branchOffset = ((uint32_t) branchByte1 << 24) | ((uint32_t) branchByte2 << 16) | ((uint32_t) branchByte3 << 8) | ((uint32_t) branchByte4);
    pc = *(frame->codeIndexRef) + 5;
    push(&pc, &(frame->operandStack));
    *(frame->codeIndexRef) += branchOffset - 3;
    
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

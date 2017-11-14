
#include "others.h"

void i_nop()
{
    return;
};

void i_bipush(Frame* frame,uint32_t* n){
    push(&(frame->operandStack),n);
    return;
}

void i_sipush(Frame* frame,uint16_t* n)
{
	uint32_t dado = *n;
    push(&(frame->operandStack),&dado);
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
        push(&(frame->operandStack),&constantPool[index-1].integer_const.bytes);
        break;
    case FLOAT:
    	dado =  constantPool[index-1].float_const.bytes;
    	memcpy(&f, &dado, sizeof(uint32_t));
		push(&(frame->operandStack),&dado);
        break;
    case STRING:
		dado =  constantPool[index-1].string_const.string_index;
		push(&(frame->operandStack),&dado);
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
        push(&(frame->operandStack),&constantPool[index-1].integer_const.bytes);
        break;
    case FLOAT:
        	dado = (constantPool[index-1].float_const.bytes);
        	memcpy(&f, &dado, sizeof(uint32_t));
        push(&(frame->operandStack),&(constantPool[index-1].float_const.bytes));
        break;
    case STRING:
		dado = constantPool[index-1].string_const.string_index;
		push(&(frame->operandStack),&dado);
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
		dado = ((uint64_t)constantPool[indexConcat-1].long_const.highBytes <<32) | constantPool[indexConcat-1].long_const.lowBytes;
		push(&(frame->operand),&dado);
        break;
    case DOUBLE:
        dado = ((uint64_t)constantPool[indexConcat-1].long_const.highBytes <<32) | constantPool[indexConcat-1].long_const.lowBytes;

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
	push(&(frame->operandStack), &(frame->codeIndexRef));
	int16_t offset16 = (((uint16_t)index)<<8)+index2;
		frame->codeIndexRef += (offset16 - 3);

	return;
}

void i_ret(Frame* frame, uint8_t index)
{
    frame->codeIndexRef = frame->localVariables[index];
    return;
}

void i_tableswitch(Frame *frame)
{

    return;
}

void i_lookupswitch(Frame *frame)
{
    return;
}

void i_ireturn(Frame *frame)
{
    return;
}

void i_lreturn(Frame *frame)
{
    return;
}

void i_freturn(Frame *frame)
{
    return;
}

void i_dreturn(Frame* frame)
{
    return;
}

void i_areturn(Frame* frame)
{
    return;
}

void i_return(Frame* frame)
{
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
    
    nomeclasseindex = frame->runtimeConstantPool[index - 1].fieldRef_const.class_index - 1;
    nomeclasseindex = frame->runtimeConstantPool[nomeclasseindex].class_const.name_index - 1;
    tipoIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.name_and_type_index - 1;
    nameIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.name_index - 1;
    tipoIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.descriptor_index - 1;

    tipo = utf8ToString(frame->runtimeConstantPool[tipoIndex].utf8_const.bytes, frame->runtimeConstantPool[tipoIndex].utf8_const.length);
    name = utf8ToString(frame->runtimeConstantPool[nameIndex].utf8_const.bytes, frame->runtimeConstantPool[nameIndex].utf8_const.length);
    nomeClasse = utf8ToString(frame->runtimeConstantPool[nomeClasseIndex].utf8_const.bytes, frame->runtimeConstantPool[nomeClasseIndex].utf8_const.length);
    
    classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);
    
    if(!classe)
    {
        if(!strcmp(nomeClasse, "java/lang/System"))
        {
            push(&valor, &(frame->operandStack));

            free(tipo);
            free(name);
            free(nomeClasse);

            return;
        }
        else
            exit(-1);
    }

    field = recupera_field(nomeClasse, &listaDeFields);
    
    if(!field)
    {
        push(&valor, &(frame->operandStack));

        free(tipo);
        free(name);
        free(nomeClasse);

        return;
    }
    
    for (fieldIndex = 0; fieldIndex < classe->fields_count; fieldIndex++)
    {
        uint16_t nomeindex = classe->fields[fieldIndex].name_index - 1;

        nome = utf8ToString(classe->constant_pool[nomeIndex].utf8_const.bytes, classe->constant_pool[nomeIndex].utf8_const.length);
        
        if (!strcmp(name, nome))
            break;
    }

    valor = field->valor[fieldIndex];
    push(&valor, &(frame->operandStack));
        
    free(tipo);
    free(name);
    free(nome);
    free(nomeClasse);
    
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

    tipo = utf8ToString(frame->runtimeConstantPool[tipoIndex].utf8_const.bytes, frame->runtimeConstantPool[tipoIndex].utf8_const.length);
    name = utf8ToString(frame->runtimeConstantPool[nameIndex].utf8_const.bytes, frame->runtimeConstantPool[nameIndex].utf8_const.length);
    nomeClasse = utf8ToString(frame->runtimeConstantPool[nomeClasseIndex].utf8_const.bytes, frame->runtimeConstantPool[nomeClasseIndex].utf8_const.length);
    
    classe = RecuperaClassePorNome(nomeClasse, &listaDeClasses);
    
    valor = pop(&(frame->operandStack));

    for (fieldIndex = 0; fieldIndex < classe->fields_count; fieldIndex++)
    {
        uint16_t nomeindex = classe->fields[fieldIndex].name_index - 1;

        nome = utf8ToString(classe->constant_pool[nomeIndex].utf8_const.bytes, classe->constant_pool[nomeIndex].utf8_const.length);
        
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
        field->valor = (uint64_t *) set_mem(sizeof(u8) * field->fieldCount);
        field->valor[fieldIndex] = valor;
        InsereListaDeFields(&listaDeFields, field);
    }

    field->valor[fieldIndex] = valor;
    
    free(tipo);
    free(name);
    free(nome);
    free(nomeClasse);

    return;
}

void i_getfield(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, tipoIndex, nameIndex, fieldIndex;
    uint64_t valor;
    char *tipo, *name, *nome;
    Objeto *obj;

    index = (uint16_t) indexByte1 << 8 | (uint16_t) indexByte2;

    tipoIndex = frame->runtimeConstantPool[index - 1].fieldRef_const.nameAndType_index - 1;
    nameIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.name_index - 1;
    tipoIndex = frame->runtimeConstantPool[tipoIndex].nameAndType_const.descriptor_index - 1;
    
    tipo = utf8ToString(frame->runtimeConstantPool[tipoIndex].utf8_const.bytes, frame->runtimeConstantPool[tipoIndex].utf8_const.length);
    name = utf8ToString(frame->runtimeConstantPool[nameIndex].utf8_const.bytes, frame->runtimeConstantPool[nameIndex].utf8_const.length);

    obj = pop(&(frame->operandStack));

    for (fieldIndex = 0; fieldIndex < obj->tamanhotipoField; fieldIndex++)
    {
        uint16_t nomeindex = obj->classe->fields[fieldIndex].name_index - 1;

        nome = utf8ToString(obj->classe->constant_pool[nomeIndex].utf8_const.bytes, obj->classe->constant_pool[nomeIndex].utf8_const.length);

        if (!strcmp(name, nome))
            break;
    }

    push(obj->tipofield[fieldIndex], &(frame->operandStack));
    
    free(tipo);
    free(name);
    free(nome);

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
    
    tipo = utf8ToString(frame->runtimeConstantPool[tipoIndex].utf8_const.bytes, frame->runtimeConstantPool[tipoIndex].utf8_const.length);
    name = utf8ToString(frame->runtimeConstantPool[nameIndex].utf8_const.bytes, frame->runtimeConstantPool[nameIndex].utf8_const.length);

    valor = pop(&(frame->operandStack));
    obj = pop(&(frame->operandStack));
    
    for (fieldIndex = 0; fieldIndex < obj->classe->fields_count; fieldIndex++)
    {
        uint16_t nomeIndex = obj->classe->fields[fieldIndex].name_index - 1;

        nome = utf8ToString(obj->classe->constant_pool[nomeIndex].utf8_const.bytes, obj->classe->constant_pool[nomeIndex].utf8_const.length);
        
        if (!strcmp(name, nome))
            break;
    }

    obj->tipofield[fieldIndex] = valor;
    
    free(tipo);
    free(name);
    free(nome);

    return;
}

void i_invokevirtual(Frame *frame, Stack *pilhadeframes, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, Heap *heap)
{
    return;
}

void i_invokespecial(Frame *frame, Stack *pilhadeframes, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, Heap *heap)
{
    return;
}

void i_invokestatic(Frame *frame, Stack *pilhadeframes, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, Heap *heap)
{
    return;
}

void i_invokeinterface(Frame *frame, Stack *pilhadeframes, ListaClasses *listaDeClasses, uint8_t indexByte1, uint8_t indexByte2, uint8_t contagem, uint8_t zero, Heap *heap)
{
    uint32_t *argumentos;
    uint16_t index = 0, classeindex = 0, descriptorindex = 0;
    int i = 0;
    char *nome = NULL, *nomemetodo = NULL, *nomeclasse = NULL, *nomedesc = NULL, *metododesc = NULL;
    Class *classe;
    Objeto *obj = (Objeto *) set_mem(sizeof(Objeto));
    
    argumentos = (uint32_t *) set_mem(sizeof(uint32_t) * (contagem + 1));
    
    index = (uint16_t) indexbyte1 << 8 | (uint16_t) indexbyte2;
    classeindex = index;
    nomeClasse = utf8ToString(frame->runtimeConstantPool[classeindex].utf8_const.bytes, frame->runtimeConstantPool[classeindex].utf8_const.length);
    obj->classe = RecuperaClassePorNome(nomeclasse, &listadeclasses);
    
    for (i = contagem; i >= 0; i--)
        argumentos[i] = pop(&frame->operandStack);
    
    index = frame->runtimeConstantPool[index - 1].interfaceMethodRef_const.name_and_type_index - 1;
    descriptorindex = frame->runtimeConstantPool[index].nameAndType_const.descriptor_index - 1;
    index = frame->runtimeConstantPool[index].nameAndType_const.name_index - 1;
    classeindex = frame->runtimeConstantPool[classeindex - 1].interfaceMethodRef_const.class_index - 1;
    classeindex = frame->runtimeConstantPool[classeindex].class_const.name_index - 1;
    
    nomeClasse = utf8ToString(frame->runtimeConstantPool[classeindex].utf8_const.bytes, frame->runtimeConstantPool[classeindex].utf8_const.length);
    metododesc = utf8ToString(frame->runtimeConstantPool[descriptorindex].utf8_const.bytes, frame->runtimeConstantPool[descriptorindex].utf8_const.length);
    nomemetodo = utf8ToString(frame->runtimeConstantPool[index].utf8_const.bytes, frame->runtimeConstantPool[index].utf8_const.length);
    
    classe = RecuperaClassePorNome(nomeclasse, &listadeclasses);
    
    for(i = 0; i < classe->methods_count; i++)
    {
        uint16_t index1 = classe->methods[i].descriptor_index - 1;
        
        nomedesc = utf8ToString(classe->constant_pool[index1].utf8_const.bytes, classe->constant_pool[index1].utf8_const.length);
        
        index = classe->methods[i].name_index - 1;
        nome = utf8ToString(classe->constant_pool[index].utf8_const.bytes, classe->constant_pool[index].utf8_const.length);

        if(!strcmp(nomemetodo, nome) && !strcmp(metododesc, nomedesc))
            break;
    }
    
    if (i != obj->classe->methods_count)
    {
        // ATENCAO
        prepara_metodo(&obj->classe->methods[i], obj->classe, &pilhadeframes, &heap);
        
        Frame *frame1 = pop(&pilhadeframes);
        
        for (int j = contagem; j >= 0; j--)
            frame1->localVariables[j] = argumentos[j];
        
        pilhadeframes = push(frame1, &pilhadeframes);
        // ATENCAO
        executa_metodo(&obj->classe->methods[i], obj->classe, pilhadeframes);
    }
    else
        printf("Metodo não encontrado");

    free(nome);
    free(nomemetodo);
    free(nomedesc);
    free(nomeClasse);
    free(metododesc);
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
    
    nomeClasse = dereferencia_instrucao(index, frame->runtimeConstantPool);
    
    obj = (Objeto *) set_mem(sizeof(Objeto));
    obj->classe = RecuperaClassePorNome(nomeClasse,&listaDeClasses);
    
    if (obj->classe == NULL)
    {
        Class *classe;
        char *nomeArquivo;
        
        classe = (Class *) set_mem(sizeof(Class));
        nomeArquivo = (char *) set_mem(sizeof(char) * (strlen(nomeClasse) + 7));
        
        strcpy(nomeArquivo, nomeClasse);
        strcat(nomeArquivo, ".class");
        
        // ATENCAO
        carrega_classe(nomeArquivo, classe);
        obj->classe = getClassfile();
        
        listaDeClasses = InsereListaDeClasses(&listaDeClasses, classe);
        frame->heap->listaDeClasses = listaDeClasses;
    }
    
    obj->tamanhotipoField = obj->classe->fields_count;    
    obj->tipofield = (uint64_t *) set_mem(sizeof(uint64_t) * obj->tamanhotipoField);
    
    valor = (uint32_t) (long) obj;
    push(&valor, &(frame->operandStack));

    return;
}

void i_newarray(Frame *frame, uint8_t atype)
{
    return;
}

void i_anewarray(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    return;
}

void i_arraylength(Frame *frame)
{
    tArray *array;
    
    array = pop(&(frame->operandStack));
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
    obj = pop(&(frame->operandStack));
    
    if(obj != NULL)
    {
        index = frame->runtimeConstantPool[index - 1].class_const.name_index - 1;
        indexObjeto = obj->classe->constant_pool[obj->classe->thisClass - 1].class_const.name_index - 1;

        nomeClasse = utf8ToString(frame->runtimeConstantPool[index].utf8_const.bytes, frame->runtimeConstantPool[index].utf8_const.length);
        nomeClasseObjeto = utf8ToString(obj->classe->constant_pool[indexObjeto].utf8_const.bytes, obj->classe->constant_pool[indexObjeto].utf8_const.length);
        
        if(!strcmp(nomeClasse, nomeClasseObjeto))
            printf("Erro: Objeto do tipo errado\n");
    }
    else
        printf("Erro: Referencia nula\n");
    
    push((uint32_t *) obj, &(frame->operandStack));
    
    free(nomeClasse);
    free(nomeClasseObjeto);

    return;
}

void i_instanceof(Frame *frame, uint8_t indexByte1, uint8_t indexByte2)
{
    uint16_t index, indexObjeto;
    uint32_t valor = 0;
    char *nomeClasse, *nomeClasseObjeto;
    Objeto *obj;
    
    index = (uint16_t) (indexByte1 << 8) | (uint16_t) (indexByte2);
    obj = pop(&(frame->operandStack));

    if(obj != NULL)
    {
        index = frame->constant_pool[index - 1].info.Class.name_index - 1;
        indexObjeto = obj->classe->constant_pool[obj->classe->thisClass - 1].class_const.name_index - 1;
        
        nomeClasse = utf8ToString(frame->runtimeConstantPool[index].utf8_const.bytes, frame->runtimeConstantPool[index].utf8_const.length);
        nomeClasseObjeto = utf8ToString(obj->classe->constant_pool[indexObjeto].utf8_const.bytes, obj->classe->constant_pool[indexObjeto].utf8_const.length);
        
        if(!strcmp(nomeClasse, nomeClasseObjeto))
            valor = 1;
    }
    
    push(&valor, &(frame->operandStack));

    free(nomeClasse);
    free(nomeClasseObjeto);

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

void i_wide(Frame *frame, uint8_t opcode, uint8_t index, uint8_t index2, uint8_t constbyte1, uint8_t constbyte2)
{
    return;
}

void i_multianewarray(Frame *frame, uint8_t indexByte1, uint8_t indexByte2, uint8_t dimensions)
{
    return;
}

void i_ifnull(Frame *frame, uint8_t branchByte1, uint8_t branchByte2)
{
    uint32_t objRef = 0;
    
    objRef = pop(&(frame->operandStack));
    
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

    objRef = pop(&(frame->operandStack));
    
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
    frame->codeIndexRef = frame->codeIndexRef + branchOffset - 3;

    return;
}

void i_jsr_w(Frame *frame, uint8_t branchByte1, uint8_t branchByte2, uint8_t branchByte3, uint8_t branchByte4)
{
    uint32_t branchOffset, pc;

    branchOffset = ((uint32_t) branchByte1 << 24) | ((uint32_t) branchByte2 << 16) | ((uint32_t) branchByte3 << 8) | ((uint32_t) branchByte4);
    pc = frame->codeIndexRef + 5;
    push(&pc, &(frame->pilhaDeOperandos));
    frame->codeIndexRef = frame->codeIndexRef + branchOffset - 3;
    
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

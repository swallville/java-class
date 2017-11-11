#include "others.h"

void i_nop()
{
    return;
}

void i_bipush(Frame* frame, uint32_t* n)
{
    return;
}

void i_sipush(Frame* frame, uint16_t* n)
{
    return;
}

void i_ldc(Frame* frame,uint8_t index, ConstPool* constantPool)
{
    return;
}

void i_ldc_w(Frame* frame, uint8_t index, uint8_t index2, ConstPool* constantPool)
{
	return;
}

void i_ldc2_w(Frame* frame, uint8_t index, uint8_t index2, ConstPool* constantPool)
{
    return;
}

void i_goto(Frame* frame, uint8_t index1, uint8_t index2)
{
	return;
}

void i_jsr(Frame* frame, uint8_t index, uint8_t index2){
	return;
}

void i_ret(Frame* frame, uint8_t index)
{
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

void i_getstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2)
{
    return;
}

void i_putstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2)
{
    return;
}

void i_getfield(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
{
    return;
}

void i_putfield(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
{
    return;
}

void i_invokevirtual(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, Heap *heap)
{
    return;
}

void i_invokespecial(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, Heap *heap)
{
    return;
}

void i_invokestatic(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, Heap *heap)
{
    return;
}

void i_invokeinterface(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, uint8_t contagem, uint8_t zero, Heap *heap)
{
    return;
}

void i_invokedynamic(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, uint8_t zero_1, uint8_t zero_2, Heap *heap)
{
    return;
}

void i_new(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2, ListaClasses *listadeclasses)
{
    return;
}

void i_newarray(Frame *frame, uint8_t atype)
{
    return;
}

void i_anewarray(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
{
    return;
}

void i_arraylength(Frame *frame)
{
    return;
}

void i_athrow(Frame *frame)
{
    return;
}
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
        push(&(frame->operandStack),&constantPool[index-1].info.integer_const.bytes);
        break;
    case FLOAT:
    	dado =  constantPool[index-1].info.float_const.bytes;
    	memcpy(&f, &dado, sizeof(uint32_t));
		push(&(frame->operandStack),&dado);
        break;
    case STRING:
		dado =  constantPool[index-1].info.string_const.string_index;
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
        push(&(frame->operandStack),&constantPool[index-1].info.integer_const.bytes);
        break;
    case FLOAT:
        	dado = (constantPool[index-1].info.float_const.bytes);
        	memcpy(&f, &dado, sizeof(uint32_t));
        push(&(frame->operandStack),&(constantPool[index-1].info.float_const.bytes));
        break;
    case STRING:
		dado = constantPool[index-1].info.string_const.string_index;
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
		dado = ((uint64_t)constantPool[indexConcat-1].info.long_const.highBytes <<32) | constantPool[indexConcat-1].info.long_const.lowBytes;
		push(&(frame->operand),&dado);
        break;
    case DOUBLE:
        dado = ((uint64_t)constantPool[indexConcat-1].info.long_const.highBytes <<32) | constantPool[indexConcat-1].info.long_const.lowBytes;

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

void i_getstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2)
{
    return;
}

void i_putstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2)
{
    return;
}

void i_getfield(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
{
    return;
}

void i_putfield(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
{
    return;
}

void i_invokevirtual(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, Heap *heap)
{
    return;
}

void i_invokespecial(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, Heap *heap)
{
    return;
}

void i_invokestatic(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, Heap *heap)
{
    return;
}

void i_invokeinterface(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, uint8_t contagem, uint8_t zero, Heap *heap)
{
    return;
}

void i_invokedynamic(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, uint8_t zero_1, uint8_t zero_2, Heap *heap)
{
    return;
}

void i_new(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2, ListaClasses *listadeclasses)
{
    return;
}

void i_newarray(Frame *frame, uint8_t atype)
{
    return;
}

void i_anewarray(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
{
    return;
}

void i_arraylength(Frame *frame)
{
    return;
}

void i_athrow(Frame *frame)
{
    return;
}

void i_checkcast(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
{
    return;
}

void i_instanceof(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
{
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

void i_multianewarray(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2, uint8_t dimensions)
{
    return;
}

void i_ifnull(Frame *frame, uint8_t branchbyte1, uint8_t branchbyte2)
{
    return;
}

void i_ifnonnull(Frame *frame, uint8_t branchbyte1, uint8_t branchbyte2)
{
    return;
}

void i_goto_w(Frame *frame, uint8_t branchbyte1, uint8_t branchbyte2, uint8_t branchbyte3, uint8_t branchbyte4)
{
    return;
}

void i_jsr_w(Frame *frame, uint8_t branchbyte1, uint8_t branchbyte2, uint8_t branchbyte3, uint8_t branchbyte4)
{
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

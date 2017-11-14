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

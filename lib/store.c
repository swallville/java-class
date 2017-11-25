#include "store.h"

void i_istore(Frame* frame, uint8_t index)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame->localVariables[index] = valor;
}

void i_lstore(Frame* frame, uint8_t index)
{
    uint32_t valorh = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valorl = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    frame->localVariables[index] = (valor) >> 32;
    frame->localVariables[index + 1] = (valor) & 0x00000000FFFFFFFF;
}

void i_fstore(Frame* frame, uint8_t index)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    float f = (float) valor;
    uint32_t uf = f;
    frame->localVariables[index] = uf;
}

void i_dstore(Frame* frame, uint8_t index)
{
    uint32_t valorh = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valorl = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    double d = (double) valor;
    uint64_t ud = d;
    frame->localVariables[index] = (ud) >> 32;
    frame->localVariables[index + 1] = (ud) & 0x00000000FFFFFFFF;
}

void i_astore(Frame* frame, uint8_t index)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame->localVariables[index] = valor;
}

void i_istore_0(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame->localVariables[0] = valor;
}

void i_istore_1(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame->localVariables[1] = valor;
}

void i_istore_2(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame->localVariables[2] = valor;
}

void i_istore_3(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame->localVariables[3] = valor;
}

void i_lstore_0(Frame* frame)
{
    uint32_t valorh = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valorl = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    frame->localVariables[0] = (valor) >> 32;
    frame->localVariables[1] = (valor) & 0x00000000FFFFFFFF;
}

void i_lstore_1(Frame* frame)
{
    uint32_t valorh = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valorl = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    frame->localVariables[1] = (valor) >> 32;
    frame->localVariables[2] = (valor) & 0x00000000FFFFFFFF;
}

void i_lstore_2(Frame* frame)
{
    uint32_t valorh = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valorl = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    frame->localVariables[2] = (valor) >> 32;
    frame->localVariables[3] = (valor) & 0x00000000FFFFFFFF;
}

void i_lstore_3(Frame* frame)
{
    uint32_t valorh = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valorl = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    frame->localVariables[3] = (valor) >> 32;
    frame->localVariables[4] = (valor) & 0x00000000FFFFFFFF;
}

void i_fstore_0(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    float f = (float) valor;
    uint32_t uf = f;
    frame->localVariables[0] = uf;
}

void i_fstore_1(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    float f = (float) valor;
    uint32_t uf = f;
    frame->localVariables[1] = uf;
}

void i_fstore_2(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    float f = (float) valor;
    uint32_t uf = f;
    frame->localVariables[2] = uf;
}

void i_fstore_3(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    float f = (float) valor;
    uint32_t uf = f;
    frame->localVariables[3] = uf;
}

void i_dstore_0(Frame* frame)
{
    uint32_t valorh = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valorl = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    double d = (double) valor;
    uint64_t ud = d;
    frame->localVariables[0] = (ud) >> 32;
    frame->localVariables[1] = (ud) & 0x00000000FFFFFFFF;
}

void i_dstore_1(Frame* frame)
{
    uint32_t valorh = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valorl = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    double d = (double) valor;
    uint64_t ud = d;
    frame->localVariables[1] = (ud) >> 32;
    frame->localVariables[2] = (ud) & 0x00000000FFFFFFFF;
}

void i_dstore_2(Frame* frame)
{
    uint32_t valorh = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valorl = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    double d = (double) valor;
    uint64_t ud = d;
    frame->localVariables[2] = (ud) >> 32;
    frame->localVariables[3] = (ud) & 0x00000000FFFFFFFF;
}

void i_dstore_3(Frame* frame)
{
    uint32_t valorh = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valorl = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    double d = (double) valor;
    uint64_t ud = d;
    frame->localVariables[3] = (ud) >> 32;
    frame->localVariables[4] = (ud) & 0x00000000FFFFFFFF;
}

void i_astore_0(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame->localVariables[0] = valor;
}

void i_astore_1(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame->localVariables[1] = valor;
}

void i_astore_2(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame->localVariables[2] = valor;
}

void i_astore_3(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    frame->localVariables[3] = valor;
}

void i_iastore(Frame* frame)
{
    uint32_t index = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t* array = (void*)((long)pop(&(frame->operandStack))->value);
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    array[index] = valor;
}

void i_lastore(Frame* frame)
{
    uint32_t index = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t* array = (void*)((long)pop(&(frame->operandStack))->value);
    uint32_t valorh = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valorl = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    array[index] = valor;
}

void i_fastore(Frame* frame)
{
    uint32_t index = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t* array = (void*)((long)pop(&(frame->operandStack))->value);
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    float f = (float) valor;
    uint32_t uf = f;
    array[index] = uf;
}

void i_dastore(Frame* frame)
{
    uint32_t index = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t* array = (void*)((long)pop(&(frame->operandStack))->value);
    uint32_t valorh = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valorl = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    double d = (double) valor;
    uint64_t ud = d;
    array[index] = ud;
}

void i_aastore(Frame* frame)
{
    uint32_t index = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t* array = (void*)((long)pop(&(frame->operandStack))->value);
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    array[index] = valor;
}

void i_bastore(Frame* frame)
{
    uint32_t index = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint8_t* array = (void*)((long)pop(&(frame->operandStack))->value);
    uint8_t valor = *((uint8_t*)pop(&(frame->operandStack))->value);
    array[index] = valor;
}

void i_castore(Frame* frame)
{
    uint32_t index = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint16_t* array = (void*)((long)pop(&(frame->operandStack))->value);
    uint16_t valor = *((uint16_t*)pop(&(frame->operandStack))->value);
    array[index] = valor;
}

void i_sastore(Frame* frame)
{
    uint32_t index = *((uint32_t*)pop(&(frame->operandStack))->value);
    uint16_t* array = (void*)((long)pop(&(frame->operandStack))->value);
    uint16_t valor = *((uint16_t*)pop(&(frame->operandStack))->value);
    array[index] = valor;
}

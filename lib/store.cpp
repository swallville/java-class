#include "store.hpp"

void i_istore(Frame* frame, uint8_t index)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    if (frame->localVariables.size() < (index + 1)) {
        frame->localVariables.resize(index + 1);
    }

    frame->localVariables.at(index) = valor;

    return;
}

void i_lstore(Frame* frame, uint8_t index)
{
    Data valorh = frame->operandStack.top();
    frame->operandStack.pop();

    Data valorl = frame->operandStack.top();
    frame->operandStack.pop();

    //uint64_t valor = (((uint64_t)valorh) << 32) | valorl;

    if (frame->localVariables.size() < (index + 2)) {
        frame->localVariables.resize(index + 2);
    }

    frame->localVariables.at(index) = valorh;
    frame->localVariables.at(index + 1) = valorl;

    return;
}

void i_fstore(Frame* frame, uint8_t index)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    float f = (float) valor.operand;
    valor.operand = f;

    if (frame->localVariables.size() < (index + 1)) {
        frame->localVariables.resize(index + 1);
    }

    frame->localVariables.at(index) = valor;

    return;
}

void i_dstore(Frame* frame, uint8_t index)
{
    Data valorh = frame->operandStack.top();
    frame->operandStack.pop();

    Data valorl = frame->operandStack.top();
    frame->operandStack.pop();

    uint64_t valor = (((uint64_t)valorh.operand) << 32) | valorl.operand;
    double d = (double) valor;
    uint64_t ud = d;

    if (frame->localVariables.size() < (index + 2)) {
        frame->localVariables.resize(index + 2);
    }

    valorh.operand = (ud) >> 32;
    frame->localVariables.at(index) = valorh;

    valorl.operand = (ud) & 0x00000000FFFFFFFF;
    frame->localVariables.at(index + 1) = valorl;

    return;
}

void i_astore(Frame* frame, uint8_t index)
{
    void* valor = frame->operandStack.top().reference;
    int tag = frame->operandStack.top().tag;
    frame->operandStack.pop();

    if (frame->localVariables.size() < (index + 1)) {
        frame->localVariables.resize(index + 1);
    }


    Data * data1 = (Data*) set_mem(sizeof(Data));
    data1->reference = valor;
    data1->tag = tag;

    frame->localVariables.at(index) = (*data1);

    return;
}

void i_istore_0(Frame* frame)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    if (frame->localVariables.size() < 1) {
        frame->localVariables.resize(1);
    }

    frame->localVariables.at(0) = valor;

    return;
}

void i_istore_1(Frame* frame)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    if (frame->localVariables.size() < 2) {
        frame->localVariables.resize(2);
    }

    frame->localVariables.at(1) = valor;

    return;
}

void i_istore_2(Frame* frame)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    if (frame->localVariables.size() < 3) {
        frame->localVariables.resize(3);
    }

    frame->localVariables.at(2) = valor;

    return;
}

void i_istore_3(Frame* frame)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    if (frame->localVariables.size() < 4) {
        frame->localVariables.resize(4);
    }

    frame->localVariables.at(3) = valor;

    return;
}

void i_lstore_0(Frame* frame)
{
    Data valorh = frame->operandStack.top();
    frame->operandStack.pop();

    Data valorl = frame->operandStack.top();
    frame->operandStack.pop();

    //uint64_t valor = (((uint64_t)valorh) << 32) | valorl;

    if (frame->localVariables.size() < 2) {
        frame->localVariables.resize(2);
    }

    frame->localVariables.at(0) = valorh;
    frame->localVariables.at(1) = valorl;

    return;
}

void i_lstore_1(Frame* frame)
{
    Data valorh = frame->operandStack.top();
    frame->operandStack.pop();

    Data valorl = frame->operandStack.top();
    frame->operandStack.pop();

    //uint64_t valor = (((uint64_t)valorh) << 32) | valorl;

    if (frame->localVariables.size() < 3) {
        frame->localVariables.resize(3);
    }

    frame->localVariables.at(1) = valorh;
    frame->localVariables.at(2) = valorl;

    return;
}

void i_lstore_2(Frame* frame)
{
    Data valorh = frame->operandStack.top();
    frame->operandStack.pop();

    Data valorl = frame->operandStack.top();
    frame->operandStack.pop();

    if (frame->localVariables.size() < 4) {
        frame->localVariables.resize(4);
    }

    //uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    frame->localVariables.at(2) = valorh;
    frame->localVariables.at(3) = valorl;

    return;
}

void i_lstore_3(Frame* frame)
{
    Data valorh = frame->operandStack.top();
    frame->operandStack.pop();

    Data valorl = frame->operandStack.top();
    frame->operandStack.pop();

    //uint64_t valor = (((uint64_t)valorh) << 32) | valorl;

    if (frame->localVariables.size() < 5) {
        frame->localVariables.resize(5);
    }

    frame->localVariables.at(3) = valorh;
    frame->localVariables.at(4) = valorl;

    return;
}

void i_fstore_0(Frame* frame)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    float f = (float) valor.operand;
    valor.operand = f;

    if (frame->localVariables.size() < 1) {
        frame->localVariables.resize(1);
    }

    frame->localVariables.at(0) = valor;

    return;
}

void i_fstore_1(Frame* frame)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    float f = (float) valor.operand;
    valor.operand = f;

    if (frame->localVariables.size() < 2) {
        frame->localVariables.resize(2);
    }

    frame->localVariables.at(1) = valor;

    return;
}

void i_fstore_2(Frame* frame)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    float f = (float) valor.operand;
    valor.operand = f;

    if (frame->localVariables.size() < 3) {
        frame->localVariables.resize(3);
    }

    frame->localVariables.at(2) = valor;

    return;
}

void i_fstore_3(Frame* frame)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    float f = (float) valor.operand;
    valor.operand = f;

    if (frame->localVariables.size() < 4) {
        frame->localVariables.resize(4);
    }

    frame->localVariables.at(3) = valor;

    return;
}

void i_dstore_0(Frame* frame)
{
    Data valorh = frame->operandStack.top();
    frame->operandStack.pop();

    Data valorl = frame->operandStack.top();
    frame->operandStack.pop();

    uint64_t valor = (uint64_t)decodeDouble(valorh.operand, valorl.operand);
    double d = (double) valor;
    uint64_t ud = d;

    if (frame->localVariables.size() < 2) {
        frame->localVariables.resize(2);
    }

    valorh.operand =  (ud) >> 32;
    frame->localVariables.at(0) = valorh;

    valorl.operand = (ud) & 0x00000000FFFFFFFF;

    frame->localVariables.at(1) = valorl;

    return;
}

void i_dstore_1(Frame* frame)
{
    Data valorh = frame->operandStack.top();
    frame->operandStack.pop();

    Data valorl = frame->operandStack.top();
    frame->operandStack.pop();

    uint64_t valor = (uint64_t)decodeDouble(valorh.operand, valorl.operand);
    double d = (double) valor;
    uint64_t ud = d;

    //printf("double into dstore_1 - %llu\n", ud);

    if (frame->localVariables.size() < 3) {
        frame->localVariables.resize(3);
    }

    valorh.operand =  (ud) >> 32;
    frame->localVariables.at(1) = valorh;

    valorl.operand = (ud) & 0x00000000FFFFFFFF;

    frame->localVariables.at(2) = valorl;

    return;
}

void i_dstore_2(Frame* frame)
{
    Data valorh = frame->operandStack.top();
    frame->operandStack.pop();

    Data valorl = frame->operandStack.top();
    frame->operandStack.pop();

    uint64_t valor = (uint64_t)decodeDouble(valorh.operand, valorl.operand);
    double d = (double) valor;
    uint64_t ud = d;

    if (frame->localVariables.size() < 4) {
        frame->localVariables.resize(4);
    }

    valorh.operand =  (ud) >> 32;
    frame->localVariables.at(2) = valorh;

    valorl.operand = (ud) & 0x00000000FFFFFFFF;

    frame->localVariables.at(3) = valorl;

    return;
}

void i_dstore_3(Frame* frame)
{
    Data valorh = frame->operandStack.top();
    frame->operandStack.pop();

    Data valorl = frame->operandStack.top();
    frame->operandStack.pop();

    uint64_t valor = ((uint64_t)valorh.operand) << 32 | valorl.operand;
    double d = (double) valor;
    uint64_t ud = d;

    //printf("valor em dstore_3 - %llu\n", ud);

    if (frame->localVariables.size() < 5) {
        frame->localVariables.resize(5);
    }

    valorh.operand =  (ud) >> 32;
    frame->localVariables.at(3) = valorh;

    valorl.operand = (ud) & 0x00000000FFFFFFFF;

    frame->localVariables.at(4) = valorl;

    return;
}

void i_astore_0(Frame* frame)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    if (frame->localVariables.size() < 1) {
        frame->localVariables.resize(1);
    }

    frame->localVariables.at(0) = valor;

    return;
}

void i_astore_1(Frame* frame)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    if (frame->localVariables.size() < 2) {
        frame->localVariables.resize(2);
    }

    frame->localVariables.at(1) = valor;

    return;
}

void i_astore_2(Frame* frame)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    if (frame->localVariables.size() < 3) {
        frame->localVariables.resize(3);
    }

    frame->localVariables.at(2) = valor;

    return;
}

void i_astore_3(Frame* frame)
{
    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    if (frame->localVariables.size() < 4) {
        frame->localVariables.resize(4);
    }

    frame->localVariables.at(3) = valor;

    return;
}

void i_iastore(Frame* frame)
{
    uint32_t valor = frame->operandStack.top().operand;
    frame->operandStack.pop();

    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* arrayRef = (tArray*)(frame->operandStack.top().reference);
    frame->operandStack.pop();

    //printf("Hello\n");

    arrayRef->info.tipoInt[index] = valor;

    return;
}

void i_lastore(Frame* frame)
{
    uint32_t valorh = frame->operandStack.top().operand;
    frame->operandStack.pop();

    uint32_t valorl = frame->operandStack.top().operand;
    frame->operandStack.pop();

    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;

    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* arrayRef = (tArray*)(frame->operandStack.top().reference);
    frame->operandStack.pop();

    arrayRef->info.tipoLong[index] = valor;

    return;
}

void i_fastore(Frame* frame)
{
    uint32_t valor = frame->operandStack.top().operand;
    frame->operandStack.pop();
    float f = (float) valor;
    uint32_t uf = f;

    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* arrayRef = (tArray*)(frame->operandStack.top().reference);
    frame->operandStack.pop();

    arrayRef->info.tipoFloat[index] = uf;

    return;
}

void i_dastore(Frame* frame)
{
    uint32_t valorh = frame->operandStack.top().operand;
    frame->operandStack.pop();

    uint32_t valorl = frame->operandStack.top().operand;
    frame->operandStack.pop();

    uint64_t valor = (((uint64_t)valorh) << 32) | valorl;
    double d = (double) valor;
    uint64_t ud = d;

    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* arrayRef = (tArray*)(frame->operandStack.top().reference);
    frame->operandStack.pop();

    arrayRef->info.tipoDouble[index] = ud;

    return;
}

void i_aastore(Frame* frame)
{
    uint32_t valor = frame->operandStack.top().operand;
    frame->operandStack.pop();

    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* arrayRef = (tArray*)(frame->operandStack.top().reference);
    frame->operandStack.pop();

    arrayRef->info.tipoReferencia[index] = valor;

    return;
}

void i_bastore(Frame* frame)
{
    uint8_t valor = (uint8_t)frame->operandStack.top().operand;
    frame->operandStack.pop();

    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* ref = (tArray*)(frame->operandStack.top().reference);
    frame->operandStack.pop();

    if (ref->tag == TipoByte) {
      ref->info.tipoByte[index] = valor;
    } else {
      ref->info.tipoBoolean[index] = valor;
    }

    return;
}

void i_castore(Frame* frame)
{
    uint16_t valor = (uint16_t)frame->operandStack.top().operand;
    frame->operandStack.pop();

    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* arrayRef = (tArray*)(frame->operandStack.top().reference);
    frame->operandStack.pop();

    arrayRef->info.tipoChar[index] = valor;

    return;
}

void i_sastore(Frame* frame)
{
    uint16_t valor = frame->operandStack.top().operand;
    frame->operandStack.pop();

    uint32_t index = frame->operandStack.top().operand;
    frame->operandStack.pop();

    tArray* arrayRef = (tArray*)(frame->operandStack.top().reference);
    frame->operandStack.pop();

    arrayRef->info.tipoShort[index] = valor;

    return;
}

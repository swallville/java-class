/**
* @file others.h
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções que não se classificaram em nenhum dos outros arquivos.s
*/

#ifndef OTHERS_H
#define OTHERS_H

#include <math.h>
#include <string.h>
#include "instruction.h"
#include "execute.h"
#include "utils.h"

#define TipoReferencia  0
#define TipoBoolean     4
#define TipoChar        5
#define TipoFloat       6
#define TipoDouble      7
#define TipoByte        8
#define TipoShort       9
#define TipoInt         10
#define TipoLong        11

/**
*   @fn void i_nop()
*   @brief Não faz operação alguma.
*   @return
*/
void i_nop();

/**
*   @fn void i_bipush(Frame* frame, uint32_t* n)
*   @brief Empilha um byte, como inteiro.
*	@param n Byte a ser empilhado.
*   @return
*/
void i_bipush(Frame* frame, uint32_t* n);

/**
*   @fn void i_sipush(Frame* frame, uint16_t* n)
*   @brief Empilha um short.
*	@param n Short a ser empilhado.
*   @return
*/
void i_sipush(Frame* frame, uint16_t* n);

/**
*   @fn void i_ldc(Frame* frame, uint8_t index)
*   @brief Empilha uma única palavra constante.
*	@param index Empilha um indice a partir do Constant Pool(String, int or float).
*   @return
*/
void i_ldc(Frame* frame, uint8_t index, ConstPool* constantPool);

/**
*   @fn void i_ldc(Frame* frame, uint8_t index)
*   @brief Empilha uma única palavra constante, porém tem o indice formado por 16bits.
*	@param index1 Primeira parte de indice para acesso a constante.
*	@param index2 Última parte de indice para acesso a constante.
*   @return
*/
void i_ldc_w(Frame* frame, uint8_t index, uint8_t index2, ConstPool* constantPool);

/**
*   @fn void i_ldc2_w(Frame* frame, uint8_t index, uint8_t index2)
*   @brief Empilha uma palavra dupla constante, tendo o indice formado por 16bits.
*	@param index1 Primeira parte de indice para acesso a constante.
*	@param index2 Última parte de indice para acesso a constante.
*   @return
*/
void i_ldc2_w(Frame* frame, uint8_t index, uint8_t index2, ConstPool* constantPool);

/**
*   @fn void i_goto(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Pula para outra instrução, tendo seu offset construído pelos 16bits de index.
*	@param index1 Primeira parte de indice para acesso a constante.
*	@param index2 Última parte de indice para acesso a constante.
*   @return
*/
void i_goto(Frame* frame, uint8_t index1, uint8_t index2);


/**
*   @fn void i_goto(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Pula para a subrotina indicada pelo branchoffset construdos pelo index. E empilha o endereço de retorno na pilha.
*	@param index1 Primeira parte de indice para acesso a constante.
*	@param index2 Última parte de indice para acesso a constante.
*   @return
*/
void i_jsr(Frame* frame, uint8_t index, uint8_t index2);

/**
*   @fn void i_ret(Frame* frame, uint8_t index1)
*   @brief Continua a execução a partir do endereço pego na variável local indicada pelo index.
*	@param index1 Primeira parte de indice para acesso a constante.
*	@param index2 Última parte de indice para acesso a constante.
*   @return
*/
void i_ret(Frame* frame, uint8_t index);

/**
*   @fn void i_ireturn(Stack *pilhadeframes)
*   @brief Retorna um inteiro a partir de um método.
*	@param pilhadeframes
*   @return
*/
void i_ireturn(Frame *frame);

/**
*   @fn void i_lreturn(Stack *pilhadeframes)
*   @brief Retorna um long a partir de um método.
*	@param pilhadeframes
*   @return
*/
void i_lreturn(Frame *frame);

/**
*   @fn void i_freturn(Stack *pilhadeframes)
*   @brief Retorna um float a partir de um método.
*	@param pilhadeframes
*   @return
*/
void i_freturn(Frame *frame);

/**
*   @fn void i_dreturn(Stack *pilhadeframes)
*   @brief Retorna um double a partir de um método.
*	@param pilhadeframes
*   @return
*/
void i_dreturn(Frame *frame);

/**
*   @fn void i_areturn(Stack *pilhadeframes)
*   @brief Retorna uma referência a partir de um método.
*	@param pilhadeframes
*   @return
*/
void i_areturn(Frame *frame);

/**
*   @fn void i_return(Stack *pilhadeframes)
*   @brief Retorna void a partir de um método.
*	@param pilhadeframes
*   @return
*/
void i_return(Frame *frame);

/**
*   @fn void i_getstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2)
*   @brief identifica um field e coloca na pilha de operandos
*	@param frame
*   @param listadefields
*   @param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_getstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2);

/**
*   @fn void i_putstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2)
*   @brief pega um field da pilha de operandos e coloca na lista de fields
*	@param frame
*   @param listadefields
*   @param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_putstatic(Frame *frame, ListaStaticField *listadefields, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2);

/**
*   @fn void i_getfield(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
*   @brief identifica um field de um objeto e coloca na pilha de operandos
*	@param frame
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_getfield(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2);

/**
*   @fn void i_getfield(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
*   @brief pega um valor e um objeto da pilha e coloca o valor no field correto do objeto
*	@param frame
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_putfield(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2);

/**
*   @fn void i_invokevirtual(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, Heap *heap)
*   @brief invoca um metodo ,que esta em um objeto na pilha de operandos junto com seus argumentos, e coloca o resultado na pilha de operandos o nome do metodo eh identificado por (indexbyte1<<8 + indexbyte2) no constant_pool do frame corrente
*	@param frame
*	@param pilhadeframes
*	@param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_invokevirtual(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, Heap *heap);

/**
*   @fn void i_invokespecial(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, Heap *heap)
*   @brief invoca um metodo ,que esta em um objeto na pilha de operandos junto com seus argumentos, e coloca o resultado na pilha de operandos o nome do metodo eh identificado por (indexbyte1<<8 + indexbyte2) no constant_pool do frame corrente
*	@param frame
*	@param pilhadeframes
*	@param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_invokespecial(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, Heap *heap);

/**
*   @fn void i_invokestatic(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, Heap *heap)
*   @brief invoca um metodo ,que tem seus argumentos na pilha de operandos, e coloca o resultado na pilha de operandos o nome do metodo eh identificado por (indexbyte1<<8 + indexbyte2) no constant_pool do frame corrente
*	@param frame
*	@param pilhadeframes
*	@param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_invokestatic(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, Heap *heap);

/**
*   @fn void i_invokeinterface(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, uint8_t contagem, uint8_t zero, Heap *heap)
*   @brief invoca um metodo ,que esta em um objeto na pilha de operandos junto com seus argumentos, e coloca o resultado na pilha de operandos o nome do metodo eh identificado por (indexbyte1<<8 + indexbyte2) no constant_pool do frame corrente
*	@param frame
*	@param pilhadeframes
*	@param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @param contagem
*   @param zero
*   @return
*/
void i_invokeinterface(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, uint8_t contagem, uint8_t zero, Heap *heap);

/**
*   @fn void i_invokedynamic(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, uint8_t zero_1, uint8_t zero_2, Heap *heap)
*   @brief invoca um metodo ,que esta em um objeto na pilha de operandos junto com seus argumentos, e coloca o resultado na pilha de operandos o nome do metodo eh identificado por (indexbyte1<<8 + indexbyte2) no constant_pool do frame corrente
*	@param frame
*	@param pilhadeframes
*	@param listadeclasses
*   @param indexbyte1
*   @param indexbyte2
*   @param zero_1
*   @param zero_2
*   @return
*/
void i_invokedynamic(Frame *frame, Stack *pilhadeframes, ListaClasses *listadeclasses, uint8_t indexbyte1, uint8_t indexbyte2, uint8_t zero_1, uint8_t zero_2, Heap *heap);

/**
*   @fn void i_new(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2, ListaClasses *listadeclasses)
*   @brief cria um objeto do tipo da classe identificado por (indexbyte1<<8 + indexbyte2) indice do constant_pool do frame corrente, ecoloca o resultado na pilha.
*	@param frame
*   @param indexbyte1
*   @param indexbyte2
*	@param listadeclasses
*   @return
*/
void i_new(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2, ListaClasses *listadeclasses);

/**
*   @fn void i_newarray(Frame *frame, uint8_t atype)
*   @brief cria um novo array do tipo identificado por atype e tamanho pego da pilha e coloca o resultado na pilha
*	@param frame
*   @param atype
*   @return
*/
void i_newarray(Frame *frame, uint8_t atype);

/**
*   @fn void i_anewarray(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
*   @brief cria um novo array do tipo identificado por (indexbyte1<<8 + indexbyte2) indice do constant_pool do frame corrente, e tamanho pego da pilha e coloca o resultado na pilha
*	@param frame
*   @param indexbyte1
*   @param indexbyte2
*   @return
*/
void i_anewarray(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2);

/**
*   @fn void i_arraylength(Frame *frame)
*   @brief pega a referencia de um array da pilha e empilha o seu tamanho
*	@param frame
*   @return
*/
void i_arraylength(Frame *frame);

/**
*   @fn void i_athrow(Frame *frame)
*   @brief lança um erro ou exceção (aviso de que o restante da pilha é cancelado, deixando apenas uma referência para o Throwable)
*	@param frame
*   @return
*/
void i_athrow(Frame *frame);

/**
*   @fn void i_checkcast(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
*   @brief verifica o tipo de um objeto, nome da classe identificado por (indexbyte1<<8 + indexbyte2) indice do constant pool corrente
*	@param frame
*	@param indexbyte1
*	@param indexbyte2
*   @return
*/
void i_checkcast(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2);

/**
*   @fn void i_instanceof(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2)
*   @brief identifica o tipo do objeto e poe na pilha o resultado
*	@param frame
*	@param indexbyte1
*	@param indexbyte2
*   @return
*/
void i_instanceof(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2);
void i_monitorenter(Frame *frame);
void i_monitorexit(Frame *frame);

/**
*   @fn void i_wide(Frame *frame, uint8_t opcode, uint8_t index, uint8_t index2, uint8_t constbyte1, uint8_t constbyte2)
*   @brief a função pega uma função identificada por opcode e extende ela pra receber 16_bits com (constbyte1<<8 + constbyte2)
*	@param frame
*	@param opcode
*	@param index
*	@param index2
*	@param constbyte1
*	@param constbyte2
*   @return
*/
void i_wide(Frame *frame, uint8_t opcode, uint8_t index, uint8_t index2, uint8_t constbyte1, uint8_t constbyte2);

/**
*   @fn void i_multianewarray(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2, uint8_t dimensions)
*   @brief cria um array multidimensional de dimensão "dimensions" do tipo identificado por (indexbyte1<<8 + indexbyte2) indice do constant pool
*	@param frame
*	@param indexbyte1
*	@param indexbyte2
*	@param dimensions
*   @return
*/
void i_multianewarray(Frame *frame, uint8_t indexbyte1, uint8_t indexbyte2, uint8_t dimensions);

/**
*   @fn void i_ifnull(Frame *frame, uint8_t branchbyte1, uint8_t branchbyte2)
*   @brief se valor pego na pilha for NULL pula para indice (branchbyte1<<8 + branchbyte2)
*	@param frame
*	@param branchbyte1
*	@param branchbyte2
*   @return
*/
void i_ifnull(Frame *frame, uint8_t branchbyte1, uint8_t branchbyte2);

/**
*   @fn void i_ifnannull(Frame *frame, uint8_t branchbyte1, uint8_t branchbyte2)
*   @brief se valor pego na pilha não for NULL pula para indice (branchbyte1<<8 + branchbyte2)
*	@param frame
*	@param branchbyte1
*	@param branchbyte2
*   @return
*/
void i_ifnonnull(Frame *frame, uint8_t branchbyte1, uint8_t branchbyte2);

/**
*   @fn void i_goto_w(Frame *frame, uint8_t branchbyte1, uint8_t branchbyte2, uint8_t branchbyte3, uint8_t branchbyte4)
*   @brief pula para indice (branchbyte1<<24 + branchbyte2<<16 + branchbyte3<<8 + branchbyte4)
*	@param frame
*	@param branchbyte1
*	@param branchbyte2
*	@param branchbyte3
*	@param branchbyte4
*   @return
*/
void i_goto_w(Frame *frame, uint8_t branchbyte1, uint8_t branchbyte2, uint8_t branchbyte3, uint8_t branchbyte4);

/**
*   @fn void i_jsr_w(Frame *frame, uint8_t branchbyte1, uint8_t branchbyte2, uint8_t branchbyte3, uint8_t branchbyte4)
*   @brief pula para indice (branchbyte1<<24 + branchbyte2<<16 + branchbyte3<<8 + branchbyte4) e coloca na pilha o endereço da proxima instrução apos jsr_w
*	@param frame
*	@param branchbyte1
*	@param branchbyte2
*	@param branchbyte3
*	@param branchbyte4
*   @return
*/
void i_jsr_w(Frame *frame, uint8_t branchbyte1, uint8_t branchbyte2, uint8_t branchbyte3, uint8_t branchbyte4);

/**
*   @fn void i_tableswitch(Frame *frame)
*   @brief
*	@param frame
*/
void i_tableswitch(Frame *frame, uint32_t enderecotable, int32_t high, int32_t low, int32_t defaultbyte, int32_t *tableswitch);

/**
*   @fn void i_lookupswitch(Frame *frame)
*   @brief
*	@param frame
*/
void i_lookupswitch(Frame *frame, int32_t npairs, uint32_t enderecolookup, int32_t defaultbyte, int32_t *match, int32_t *offset_table);

/**
*   @fn staticField *recupera_field(char *nome, ListaStaticField **listadefields)
*   @brief retorna um staticField identificado por nome da listadefields
*	@param nome
*	@param listadefields
*   @return
*/
staticField *recupera_field(char *nome, ListaStaticField **listadefields);

#endif //OTHERS_H

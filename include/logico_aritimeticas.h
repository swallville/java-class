/**
* @file logico_aritimeticas.h
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções logico-aritiméticas.
*/

#ifndef LOGICO_ARITIMETICAS_H
#define LOGICO_ARITIMETICAS_H

#include "instruction.h"
#include "stack.h"
#include "class.h"
#include <math.h>

/**
*   @fn void i_iadd(Frame* frame)
*   @brief Desempilha dois números do tipo inteiros, realiza a soma e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_iadd(Frame* frame);

/**
*   @fn void i_ladd(Frame* frame)
*   @brief Desempilha dois números do tipo long, realiza a soma e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_ladd(Frame* frame);

/**
*   @fn void i_fadd(Frame* frame)
*   @brief Desempilha dois números do tipo float, realiza a soma e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_fadd(Frame* frame);

/**
*   @fn void i_dadd(Frame* frame)
*   @brief Desempilha dois números do tipo double, realiza a soma e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_dadd(Frame* frame);

/**
*   @fn void i_isub(Frame* frame)
*   @brief Desempilha dois números do tipo inteiro, realiza a subtração e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_isub(Frame* frame);

/**
*   @fn void i_lsub(Frame* frame)
*   @brief Desempilha dois números do tipo long, realiza a subtração e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_lsub(Frame* frame);

/**
*   @fn void i_fsub(Frame* frame)
*   @brief Desempilha dois números do tipo float, realiza a subtração e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_fsub(Frame* frame);

/**
*   @fn void i_dsub(Frame* frame)
*   @brief Desempilha dois números do tipo double, realiza a subtração e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_dsub(Frame* frame);

/**
*   @fn void i_imul(Frame* frame)
*   @brief Desempilha dois números do tipo inteiro, realiza a multiplicação e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_imul(Frame* frame);

/**
*   @fn void i_lmul(Frame* frame)
*   @brief Desempilha dois números do tipo long, realiza a multiplicação e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_lmul(Frame* frame);

/**
*   @fn void i_fmul(Frame* frame)
*   @brief Desempilha dois números do tipo float, realiza a multiplicação e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_fmul(Frame* frame);

/**
*   @fn void i_imul(Frame* frame)
*   @brief Desempilha dois números do tipo double, realiza a multiplicação e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_dmul(Frame* frame);

/**
*   @fn void i_idiv(Frame* frame)
*   @brief Desempilha dois números do tipo inteiro, realiza a divisão e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_idiv(Frame* frame);

/**
*   @fn void i_ldiv(Frame* frame)
*   @brief Desempilha dois números do tipo long, realiza a divisão e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_ldiv(Frame* frame);

/**
*   @fn void i_fdiv(Frame* frame)
*   @brief Desempilha dois números do tipo float, realiza a divisão e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_fdiv(Frame* frame);

/**
*   @fn void i_ddiv(Frame* frame)
*   @brief Desempilha dois números do tipo double, realiza a divisão e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_ddiv(Frame* frame);

/**
*   @fn void i_irem(Frame* frame)
*   @brief Desempilha dois números do tipo inteiro, realiza a divisão e empilha o resto da divisão.
*   @param frame Frame corrente.
*   @return
*/
void i_irem(Frame* frame);

/**
*   @fn void i_lrem(Frame* frame)
*   @brief Desempilha dois números do tipo long, realiza a divisão e empilha o resto da divisão.
*   @param frame Frame corrente.
*   @return
*/
void i_lrem(Frame* frame);

/**
*   @fn void i_frem(Frame* frame)
*   @brief Desempilha dois números do tipo float, realiza a divisão e empilha o resto da divisão.
*   @param frame Frame corrente.
*   @return
*/
void i_frem(Frame* frame);

/**
*   @fn void i_drem(Frame* frame)
*   @brief Desempilha dois números do tipo double, realiza a divisão e empilha o resto da divisão.
*   @param frame Frame corrente.
*   @return
*/
void i_drem(Frame* frame);

/**
*   @fn void i_ineg(Frame* frame)
*   @brief Desempilha um inteiro, realiza a negação do valor e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_ineg(Frame* frame);

/**
*   @fn void i_lneg(Frame* frame)
*   @brief Desempilha um long, realiza a negação do valor e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_lneg(Frame* frame);

/**
*   @fn void i_fneg(Frame* frame)
*   @brief Desempilha um float, realiza a negação do valor e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_fneg(Frame* frame);

/**
*   @fn void i_dneg(Frame* frame)
*   @brief Desempilha um double, realiza a negação do valor e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_dneg(Frame* frame);

/**
*   @fn void i_ishl(Frame* frame)
*   @brief Desempilha dois valores inteiros da pilha, realiza o shift para a esquerda de n bits,indicados pelos 5 bits menos significativos do inteiro1, no inteiro 2. O sinal é preservado.
*   @param frame Frame corrente.
*   @return
*/
void i_ishl(Frame* frame);

/**
*   @fn void i_lshl(Frame* frame)
*   @brief Desempilha um valor inteiro e um valor long da pilha, realiza o shift para a esquerda de n bits,indicados pelos 5 bits menos significativos do inteiro1, no valor long. O sinal é preservado.
*   @param frame Frame corrente.
*   @return
*/
void i_lshl(Frame* frame);

/**
*   @fn void i_ishr(Frame* frame)
*   @brief Desempilha dois valores inteiros da pilha, realiza o shift para a direita de n bits,indicados pelos 5 bits menos significativos do inteiro1, no inteiro 2. O sinal é preservado.
*   @param frame Frame corrente.
*   @return
*/
void i_ishr(Frame* frame);

/**
*   @fn void i_lshr(Frame* frame)
*   @brief Desempilha um valor inteiro e um valor long da pilha, realiza o shift para a direit de n bits,indicados pelos 5 bits menos significativos do inteiro1, no valor long. O sinal é preservado.
*   @param frame Frame corrente.
*   @return
*/
void i_lshr(Frame* frame);

/**
*   @fn void i_iushr(Frame* frame)
*   @brief Desempilha dois valores inteiros da pilha, realiza o shift para a direita de n bits,indicados pelos 5 bits menos significativos do inteiro1, no inteiro 2. O sinal não é preservado.
*   @param frame Frame corrente.
*   @return
*/
void i_iushr(Frame* frame);

/**
*   @fn void i_lushr(Frame* frame)
*   @brief Desempilha um valor inteiro e um valor long da pilha, realiza o shift para a direita de n bits,indicados pelos 5 bits menos significativos do inteiro1, no valor long. O sinal não é preservado.
*   @param frame Frame corrente.
*   @return
*/
void i_lushr(Frame* frame);

/**
*   @fn void i_iand(Frame* frame)
*   @brief Desempilha dois valores inteiros da pilha, realiza a operação lógica de AND bit a bit.
*   @param frame Frame corrente.
*   @return
*/
void i_iand(Frame* frame);

/**
*   @fn void i_land(Frame* frame)
*   @brief Desempilha dois valores long da pilha, realiza a operação lógica de AND bit a bit.
*   @param frame Frame corrente.
*   @return
*/
void i_land(Frame* frame);

/**
*   @fn void i_ior(Frame* frame)
*   @brief Desempilha dois valores inteiros da pilha, realiza a operação lógica de OR bit a bit.
*   @param frame Frame corrente.
*   @return
*/
void i_ior(Frame* frame);

/**
*   @fn void i_lor(Frame* frame)
*   @brief Desempilha dois valores long da pilha, realiza a operação lógica de OR bit a bit.
*   @param frame Frame corrente.
*   @return
*/
void i_lor(Frame* frame);

/**
*   @fn void i_ixor(Frame* frame)
*   @brief Desempilha dois valores inteiros da pilha, realiza a operação lógica de XOR bit a bit.
*   @param frame Frame corrente.
*   @return
*/
void i_ixor(Frame* frame);

/**
*   @fn void i_lxor(Frame* frame)
*   @brief Desempilha dois valores long da pilha, realiza a operação lógica de XOR bit a bit.
*   @param frame Frame corrente.
*   @return
*/
void i_lxor(Frame* frame);

/**
*   @fn void i_iinc(Frame* frame, uint8_t index, uint8_t inc)
*   @brief Incrementa a variável local com o valor da variável inc.
*   @param frame Frame corrente.
*   @param index Indice do elemento a ser incrementado no vetor de variáveis locais.
*   @param inc Incremento que será dado a variável local.
*   @return
*/
void i_iinc(Frame* frame, uint8_t index, uint8_t inc);

#endif // LOGICO_ARITIMETICAS_H

/**
* @file logico_aritimeticas.hpp
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções logico-aritiméticas.
*/

#ifndef LOGICO_ARITIMETICAS_H
#define LOGICO_ARITIMETICAS_H

#include "instruction.hpp"
#include "class.hpp"
#include <math.h>

/**
*   @fn void i_iadd(Frame*)
*   @brief Desempilha dois números do tipo inteiros, realiza a soma e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_iadd(Frame*);

/**
*   @fn void i_ladd(Frame*)
*   @brief Desempilha dois números do tipo long, realiza a soma e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_ladd(Frame*);

/**
*   @fn void i_fadd(Frame*)
*   @brief Desempilha dois números do tipo float, realiza a soma e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_fadd(Frame*);

/**
*   @fn void i_dadd(Frame*)
*   @brief Desempilha dois números do tipo double, realiza a soma e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_dadd(Frame*);

/**
*   @fn void i_isub(Frame*)
*   @brief Desempilha dois números do tipo inteiro, realiza a subtração e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_isub(Frame*);

/**
*   @fn void i_lsub(Frame*)
*   @brief Desempilha dois números do tipo long, realiza a subtração e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_lsub(Frame*);

/**
*   @fn void i_fsub(Frame*)
*   @brief Desempilha dois números do tipo float, realiza a subtração e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_fsub(Frame*);

/**
*   @fn void i_dsub(Frame*)
*   @brief Desempilha dois números do tipo double, realiza a subtração e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_dsub(Frame*);

/**
*   @fn void i_imul(Frame*)
*   @brief Desempilha dois números do tipo inteiro, realiza a multiplicação e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_imul(Frame*);

/**
*   @fn void i_lmul(Frame*)
*   @brief Desempilha dois números do tipo long, realiza a multiplicação e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_lmul(Frame*);

/**
*   @fn void i_fmul(Frame*)
*   @brief Desempilha dois números do tipo float, realiza a multiplicação e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_fmul(Frame*);

/**
*   @fn void i_imul(Frame*)
*   @brief Desempilha dois números do tipo double, realiza a multiplicação e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_dmul(Frame*);

/**
*   @fn void i_idiv(Frame*)
*   @brief Desempilha dois números do tipo inteiro, realiza a divisão e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_idiv(Frame*);

/**
*   @fn void i_ldiv(Frame*)
*   @brief Desempilha dois números do tipo long, realiza a divisão e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_ldiv(Frame*);

/**
*   @fn void i_fdiv(Frame*)
*   @brief Desempilha dois números do tipo float, realiza a divisão e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_fdiv(Frame*);

/**
*   @fn void i_ddiv(Frame*)
*   @brief Desempilha dois números do tipo double, realiza a divisão e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_ddiv(Frame*);

/**
*   @fn void i_irem(Frame*)
*   @brief Desempilha dois números do tipo inteiro, realiza a divisão e empilha o resto da divisão.
*   @param frame Frame corrente.
*   @return
*/
void i_irem(Frame*);

/**
*   @fn void i_lrem(Frame*)
*   @brief Desempilha dois números do tipo long, realiza a divisão e empilha o resto da divisão.
*   @param frame Frame corrente.
*   @return
*/
void i_lrem(Frame*);

/**
*   @fn void i_frem(Frame*)
*   @brief Desempilha dois números do tipo float, realiza a divisão e empilha o resto da divisão.
*   @param frame Frame corrente.
*   @return
*/
void i_frem(Frame*);

/**
*   @fn void i_drem(Frame*)
*   @brief Desempilha dois números do tipo double, realiza a divisão e empilha o resto da divisão.
*   @param frame Frame corrente.
*   @return
*/
void i_drem(Frame*);

/**
*   @fn void i_ineg(Frame*)
*   @brief Desempilha um inteiro, realiza a negação do valor e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_ineg(Frame*);

/**
*   @fn void i_lneg(Frame*)
*   @brief Desempilha um long, realiza a negação do valor e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_lneg(Frame*);

/**
*   @fn void i_fneg(Frame*)
*   @brief Desempilha um float, realiza a negação do valor e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_fneg(Frame*);

/**
*   @fn void i_dneg(Frame*)
*   @brief Desempilha um double, realiza a negação do valor e empilha o resultado.
*   @param frame Frame corrente.
*   @return
*/
void i_dneg(Frame*);

/**
*   @fn void i_ishl(Frame*)
*   @brief Desempilha dois valores inteiros da pilha, realiza o shift para a esquerda de n bits,indicados pelos 5 bits menos significativos do inteiro1, no inteiro 2. O sinal é preservado.
*   @param frame Frame corrente.
*   @return
*/
void i_ishl(Frame*);

/**
*   @fn void i_lshl(Frame*)
*   @brief Desempilha um valor inteiro e um valor long da pilha, realiza o shift para a esquerda de n bits,indicados pelos 5 bits menos significativos do inteiro1, no valor long. O sinal é preservado.
*   @param frame Frame corrente.
*   @return
*/
void i_lshl(Frame*);

/**
*   @fn void i_ishr(Frame*)
*   @brief Desempilha dois valores inteiros da pilha, realiza o shift para a direita de n bits,indicados pelos 5 bits menos significativos do inteiro1, no inteiro 2. O sinal é preservado.
*   @param frame Frame corrente.
*   @return
*/
void i_ishr(Frame*);

/**
*   @fn void i_lshr(Frame*)
*   @brief Desempilha um valor inteiro e um valor long da pilha, realiza o shift para a direit de n bits,indicados pelos 5 bits menos significativos do inteiro1, no valor long. O sinal é preservado.
*   @param frame Frame corrente.
*   @return
*/
void i_lshr(Frame*);

/**
*   @fn void i_iushr(Frame*)
*   @brief Desempilha dois valores inteiros da pilha, realiza o shift para a direita de n bits,indicados pelos 5 bits menos significativos do inteiro1, no inteiro 2. O sinal não é preservado.
*   @param frame Frame corrente.
*   @return
*/
void i_iushr(Frame*);

/**
*   @fn void i_lushr(Frame*)
*   @brief Desempilha um valor inteiro e um valor long da pilha, realiza o shift para a direita de n bits,indicados pelos 5 bits menos significativos do inteiro1, no valor long. O sinal não é preservado.
*   @param frame Frame corrente.
*   @return
*/
void i_lushr(Frame*);

/**
*   @fn void i_iand(Frame*)
*   @brief Desempilha dois valores inteiros da pilha, realiza a operação lógica de AND bit a bit.
*   @param frame Frame corrente.
*   @return
*/
void i_iand(Frame*);

/**
*   @fn void i_land(Frame*)
*   @brief Desempilha dois valores long da pilha, realiza a operação lógica de AND bit a bit.
*   @param frame Frame corrente.
*   @return
*/
void i_land(Frame*);

/**
*   @fn void i_ior(Frame*)
*   @brief Desempilha dois valores inteiros da pilha, realiza a operação lógica de OR bit a bit.
*   @param frame Frame corrente.
*   @return
*/
void i_ior(Frame*);

/**
*   @fn void i_lor(Frame*)
*   @brief Desempilha dois valores long da pilha, realiza a operação lógica de OR bit a bit.
*   @param frame Frame corrente.
*   @return
*/
void i_lor(Frame*);

/**
*   @fn void i_ixor(Frame*)
*   @brief Desempilha dois valores inteiros da pilha, realiza a operação lógica de XOR bit a bit.
*   @param frame Frame corrente.
*   @return
*/
void i_ixor(Frame*);

/**
*   @fn void i_lxor(Frame*)
*   @brief Desempilha dois valores long da pilha, realiza a operação lógica de XOR bit a bit.
*   @param frame Frame corrente.
*   @return
*/
void i_lxor(Frame*);

/**
*   @fn void i_iinc(Frame*, uint8_t, uint8_t)
*   @brief Incrementa a variável local com o valor da variável inc.
*   @param frame Frame corrente.
*   @param index Indice do elemento a ser incrementado no vetor de variáveis locais.
*   @param inc Incremento que será dado a variável local.
*   @return
*/
void i_iinc(Frame*, uint8_t, uint8_t);

#endif // LOGICO_ARITIMETICAS_H

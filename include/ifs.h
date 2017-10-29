/**
* @file ifs.h
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de jumps condicionais.
*/

#ifndef IFS_H
#define IFS_H

#include "instruction.h"
#include "stack.h"
#include "class.h"
#include <math.h>

/**
*   @fn void i_ifeq(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha um valor, se igual a zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifeq(Frame* frame, uint8_t index1, uint8_t index2);

/**
*   @fn void i_ifne(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha um valor, se diferente de zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifne(Frame* frame,uint8_t index1,uint8_t index2);

/**
*   @fn void i_iflt(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha um valor, se menor que zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_iflt(Frame* frame, uint8_t index1, uint8_t index2);

/**
*   @fn void i_ifge(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha um valor, se maior ou igual a zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifge(Frame* frame, uint8_t index1, uint8_t index2);

/**
*   @fn void i_ifgt(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha um valor, se maior que zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifgt(Frame* frame, uint8_t index1, uint8_t index2);

/**
*   @fn void i_ifle(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha um valor, se menor ou igual a zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifle(Frame* frame, uint8_t index1, uint8_t index2);

/**
*   @fn void i_if_icmpeq(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha dois inteiros, se forem iguais, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmpeq(Frame* frame, uint8_t index1, uint8_t index2);

/**
*   @fn void i_if_icmpne(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha dois inteiros, se não forem iguais, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmpne(Frame* frame, uint8_t index1, uint8_t index2);

/**
*   @fn void i_if_icmplt(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha dois inteiros, se o valor 1 for menor que o valor2, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmplt(Frame* frame, uint8_t index1, uint8_t index2);

/**
*   @fn void i_if_icmpge(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha dois inteiros, se o valor 1 for maior ou igual ao valor2, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmpge(Frame* frame, uint8_t index1, uint8_t index2);

/**
*   @fn void i_if_icmpgt(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha dois inteiros, se o valor 1 for maior que valor2, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmpgt(Frame* frame, uint8_t index1, uint8_t index2);

/**
*   @fn void i_if_icmple(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha dois inteiros, se o valor 1 for menor ou igual ao valor2, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmple(Frame* frame, uint8_t index1, uint8_t index2);

/**
*   @fn void i_if_acmpeq(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha duas referencias para objetos, se as referências forem iguais, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_acmpeq(Frame* frame, uint8_t index1, uint8_t index2);

/**
*   @fn void i_if_acmpne(Frame* frame, uint8_t index1, uint8_t index2)
*   @brief Função que desempilha duas referencias para objetos, se as referências não forem iguais, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_acmpne(Frame* frame, uint8_t index1, uint8_t index2);

#endif

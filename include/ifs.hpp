/**
* @file ifs.hpp
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de jumps condicionais.
*/

#ifndef IFS_H
#define IFS_H

#include "instruction.hpp"
#include "class.hpp"
#include <memory>
#include <math.h>

/**
*   @fn void i_ifeq(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha um valor, se igual a zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifeq(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_ifne(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha um valor, se diferente de zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifne(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_iflt(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha um valor, se menor que zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_iflt(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_ifge(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha um valor, se maior ou igual a zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifge(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_ifgt(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha um valor, se maior que zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifgt(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_ifle(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha um valor, se menor ou igual a zero, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_ifle(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_if_icmpeq(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha dois inteiros, se forem iguais, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmpeq(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_if_icmpne(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha dois inteiros, se não forem iguais, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmpne(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_if_icmplt(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha dois inteiros, se o valor 1 for menor que o valor2, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmplt(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_if_icmpge(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha dois inteiros, se o valor 1 for maior ou igual ao valor2, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmpge(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_if_icmpgt(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha dois inteiros, se o valor 1 for maior que valor2, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmpgt(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_if_icmple(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha dois inteiros, se o valor 1 for menor ou igual ao valor2, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_icmple(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_if_acmpeq(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha duas referencias para objetos, se as referências forem iguais, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_acmpeq(Frame*, uint8_t, uint8_t);

/**
*   @fn void i_if_acmpne(Frame*, uint8_t, uint8_t)
*   @brief Função que desempilha duas referencias para objetos, se as referências não forem iguais, desvia para a instrução no branchoffset(que é um short com sinal construido a partir dos bytes sem sinal: index1 << 8 + index2)
*   @param frame Frame corrente.
*   @param index1 Primeiros 8bits do branchoffset.
*   @param index2 Últimos 8bits do branchoffset.
*   @return
*/
void i_if_acmpne(Frame*, uint8_t, uint8_t);

#endif

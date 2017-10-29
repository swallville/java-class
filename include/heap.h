/**
 * @file heap.h
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * @todo Description
 */

#ifndef _HEAP_H
#define _HEAP_H

#include <string.h>
#include "heap.h"
#include "class.h"
#include "mem-manager.h"

typedef struct tipoarray
{
    uint8_t tag;
    uint32_t tamanho;
    uint32_t tamanho1;
    union
    {
        uint8_t *tipoBoolean;
        uint8_t *tipoByte;
        uint16_t *tipoChar;
        uint16_t *tipoShort;
        uint32_t *tipoReferencia;
        uint32_t *tipoInt;
        uint32_t *tipoFloat;
        uint64_t *tipoLong;
        uint64_t *tipoDouble;
    } info;
} tArray;

typedef struct listadearrays
{
    tArray                  *dado;
    struct listadearrays    *prox;
} ListaArrays;

typedef struct tipoobjeto
{
    Class    *classe;
    uint16_t tamanhotipoField;
    uint64_t *tipofield;
} Objeto;

typedef struct
{
	char     *NomeClasse;
	uint16_t  fieldCount;
	uint64_t  *valor;
} staticField;

typedef struct listastaticfield
{
	staticField             *dado;
	struct listastaticfield *prox;
} ListaStaticField;

typedef struct listadeobjetos
{
    Objeto                  *dado;
    struct listadeobjetos   *prox;
} ListaObjetos;

typedef struct listadeclasses
{
    Class                   *dado;
    struct listadeclasses   *prox;
} ListaClasses;

typedef struct heap
{
    struct listadearrays    *listaDeArrays;
    struct listastaticfield *listaStaticField;
    struct listadeobjetos   *listaDeObjetos;
    struct listadeclasses   *listaDeClasses;
    struct pilhadeframes    *pilhaDeFrames;
} Heap;

/**
*   @fn void InsereListaDeClasses(ListaClasses **listadeclasses, Class *dado)
*   @brief Funcao que insere um elemento na lista de classes.
*   @param listadeclasses Lista que recebera o elemento.
*   @param dado Dado a ser inserido.
*/
ListaClasses* InsereListaDeClasses(ListaClasses **listadeclasses, Class *dado);

/**
*   @fn void desalocaListaDeClasses(ListaClasses *listadeclasses)
*   @brief Funcao que desaloca completamente uma lista de classes.
*   @param listadeclasses Lista a ser destruida.
*/
void desalocaListaDeClasses(ListaClasses *listadeclasses);

/**
*   @fn void InsereListaDeFields(ListaStaticField **listadefields, staticField *dado)
*   @brief Funcao que insere um elemento na lista de fields.
*   @param listadefields Lista que recebera o elemento.
*   @param dado Dado a ser inserido.
*/
void InsereListaDeFields(ListaStaticField **listadefields, staticField *dado);

/**
*   @fn void desalocaListaDeFields(ListaStaticField *listadefields)
*   @brief Funcao que desaloca completamente uma lista de fields.
*   @param listadefields Lista a ser destruida.
*/
void desalocaListaDeFields(ListaStaticField *listadefields);

/**
*   @fn Class *RecuperaIesimaClasse(int index, ListaClasses **listadeclasses)
*   @brief Funcao que recebe um indice e procura na lista de classes a classe correspondente a esse indice.
*   @param index Indice da lista a ser recuperado.
*   @param listadeclasses Lista que contem as classes carregadas.
*   @return I-esima classe da lista.
*/
Class *RecuperaIesimaClasse(int index, ListaClasses **listadeclasses);

/**
*   @fn Class *RecuperaClassePorNome(char *nome, ListaClasses **listadeclasses)
*   @brief Funcao que recebe um indice e procura na lista de classes a classe correspondente a esse indice.
*   @param nome Nome da classe a ser recuperada.
*   @param listadeclasses Lista que contem as classes carregadas.
*   @return Classe com o nome correspondente.
*/
Class *RecuperaClassePorNome(char *nome, ListaClasses **listadeclasses);

/**
*   @fn Heap* InicializaHeap()
*   @brief Funcao que inicializa a Heap do programa.
*   @return Heap alocada.
*/
Heap* InicializaHeap();

/**
*   @fn void desalocaHeap(Heap *heap)
*   @brief Funcao que inicializa a Heap do programa.
*   @param Heap a ser desalocada.
*/
void desalocaHeap(Heap *heap);

#endif /* _HEAP_H */

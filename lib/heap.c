#include "heap.h"

ListaClasses* InsereListaDeClasses(ListaClasses **listadeclasses, Class *dado)
{
    ListaClasses *lc1;
    lc1 = (ListaClasses*) set_mem(sizeof(ListaClasses));
    lc1->dado = dado;
    if((*listadeclasses) == NULL)
		lc1->prox = NULL;
	else
		lc1->prox = *listadeclasses;
    return lc1;
}

void desalocaListaDeClasses(ListaClasses *listadeclasses)
{
    free_mem( (void**) &listadeclasses);
}

void InsereListaDeFields(ListaStaticField **listadefields, staticField *dado)
{
    ListaStaticField *lsf1;
    lsf1 = (ListaStaticField*) set_mem(sizeof(ListaStaticField));
    lsf1->dado = dado;
    if((*listadefields)==NULL)
		lsf1->prox = NULL;
	else
		lsf1->prox = *listadefields;

    *listadefields = lsf1;
    return;
}

void desalocaListaDeFields(ListaStaticField *listadefields)
{
    free_mem( (void**) &listadefields);
}

Class *RecuperaIesimaClasse(int index, ListaClasses **listadeclasses)
{
    ListaClasses *lc1;

    lc1 = *listadeclasses;
    for(int i = 0; i < index + 1; i++)
    {
        if(i == index)
        {
            return lc1->dado;
        }
        lc1 = lc1->prox;
    }
    return NULL;
}

Class *RecuperaClassePorNome(char *nome, ListaClasses **listadeclasses)
{
    ListaClasses *lc1;
    lc1 = *listadeclasses;
    while (lc1 != NULL)
    {

        char* thisClass = getUtf8FromConstantPool(lc1->dado->constant_pool[lc1->dado->thisClass - 1].class_const.name_index, lc1->dado->constant_pool);

        if (!strcmp(nome, thisClass)) {
            return lc1->dado;
        }

        lc1 = lc1->prox;
        free_mem( (void**) &thisClass );
    }
    return NULL;
}


Heap* InicializaHeap() {
    Heap* heap = (Heap *) set_mem(sizeof(Heap));

    heap->listaDeArrays = NULL;
    heap->listaStaticField = NULL;
    heap->listaDeClasses = NULL;
    heap->listaDeObjetos = NULL;
    
    return heap;
}

void desalocaHeap(Heap *heap) {
    desalocaListaDeClasses(heap->listaDeClasses);
    desalocaListaDeFields(heap->listaStaticField);
    free_mem( (void**) &heap );
}

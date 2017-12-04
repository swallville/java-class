#include "heap.hpp"

Heap* InicializaHeap() {
    Heap* heap = (Heap *) set_mem(sizeof(Heap));

    return heap;
}

void desalocaHeap(Heap *heap) {
    free_mem( (void**) &heap );
}

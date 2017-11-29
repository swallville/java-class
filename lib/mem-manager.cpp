/**
 * @file mem-manager.c
 * @brief Memory management operations library source.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the mem-manager.h file.
 */
#include "mem-manager.hpp"

/**
 * @brief global variable for the Memory Manager.
 *
 * The variable that store the main Memory Manager
 */
MemManager* memList = NULL;

void* set_mem(size_t memorySpace) {
    void *pointer = malloc(memorySpace);
    
    if (pointer == NULL) {
        return NULL;
    }

    if (memList == NULL) {
        memList = memInit(pointer);
    } else {
        memAdd(&memList, pointer);
    }

    return pointer;
}

void free_mem(void** pointer) {
    if (memList != NULL && (*pointer) != NULL) {
        MemManager* deletedNode = memDelete(&memList, (*pointer));
        if (deletedNode != NULL) {
            deletedNode->elemRef = NULL;
            deletedNode->next = NULL;
            free(deletedNode);
            deletedNode = NULL;
        }
    }
    if ((*pointer) != NULL) {
        free((*pointer));
    }
    (*pointer) = NULL;
}

void freeMemManager() {
    if (memList != NULL) {
        MemManager *previous = memList;
        for (;memList != NULL; previous = memList) {
            memList = memList->next;
            if (previous->elemRef != NULL) {
                free(previous->elemRef);
            }
            previous->elemRef = NULL;
            previous->next = NULL;
            free(previous);
            previous = NULL;
        }
    }
}

MemManager* memInit(void* elemRef) {
    MemManager *manager = (MemManager*) malloc(sizeof(MemManager));
    manager->elemRef = elemRef;
    manager->next = NULL;

    return manager;
}

void memAdd(MemManager** managerRef, void* elemRef) {
    MemManager* newRef = (MemManager*) malloc(sizeof(MemManager));
    newRef->elemRef = elemRef;
    newRef->next = (*managerRef);
    (*managerRef) = newRef;
}

MemManager* memDelete(MemManager** managerRef, void* elemRef) {
    MemManager* current = NULL;
    MemManager* previous = NULL;
    for (current = (*managerRef); current != NULL; current = current->next) {
        if (current->elemRef == elemRef) {
            if (previous == NULL) {
                (*managerRef) = current->next;
            } else {
                previous->next = current->next;
            }
            return current;
        }
        previous = current;
    }
    return NULL;
}

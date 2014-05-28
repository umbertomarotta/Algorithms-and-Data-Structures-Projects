#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "list.h"

lista lista_interi(){
    /*
    lista brum = (lista)malloc(sizeof(struct slista));
    if(!brum) return NULL;
    list_new(&brum->lis, sizeof(int), NULL);
    return brum;*/
    lista brum = (lista)malloc(sizeof(list));
    list_new(brum, sizeof(int), NULL);
    return brum;
}

void lista_cancella(lista* brum){
    if(!brum) return;
    #define ord (*brum)
    list_destroy(ord);
    free(ord);
    ord = NULL;
    #undef ord
}


bool _lista_StampaInteri(void *data) {
  printf("%d >> ", *(int*)data);
  return TRUE;
}

void lista_StampaInteri(lista lis){
        assert(lis->elementSize == sizeof(int));
        if(!lis) return;
        list_for_each(lis, (listIterator)_lista_StampaInteri);
        /*
        int num;
        while(list_size(lis)){
            list_head(lis, &num, TRUE);
            if (list_size(lis)) printf("%d >> ", num);
            else  printf("%d ", num);
        }*/
}

void lista_catsx(lista list, lista l2){
    assert( list->elementSize == l2->elementSize && list->freeFn == l2->freeFn);
    if(!list->head) list->head = l2->head;
    if(list->tail) list->tail->next = l2->head;
    list->tail = l2->tail;
    list->logicalLength += l2->logicalLength;
}

void list_new(list *list, int elementSize, freeFunction freeFn)
{
  assert(elementSize > 0);
  list->logicalLength = 0;
  list->elementSize = elementSize;
  list->head = list->tail = NULL;
  list->freeFn = freeFn;
}

void list_destroy(list *list)
{
    listNode *current;
    while(list->head != NULL) {
        current = list->head;
        list->head = current->next;

        if(list->freeFn) {
            list->freeFn(current->data);
        }

        free(current->data);
        free(current);
    }
    list->head = list->tail = NULL;
    list->logicalLength = 0;
    }

void list_prepend(list *list, void *element)
{
  listNode *node = malloc(sizeof(listNode));
  node->data = malloc(list->elementSize);
  memcpy(node->data, element, list->elementSize);

  node->next = list->head;
  list->head = node;

  // first node?
  if(!list->tail) {
    list->tail = list->head;
  }

  list->logicalLength++;
}

void list_append(list *list, void *element)
{
  listNode *node = malloc(sizeof(listNode));
  node->data = malloc(list->elementSize);
  node->next = NULL;

  memcpy(node->data, element, list->elementSize);

  if(list->logicalLength == 0) {
    list->head = list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }

  list->logicalLength++;
}

void list_for_each(list *list, listIterator iterator)
{
  assert(iterator != NULL);

  listNode *node = list->head;
  bool result = TRUE;
  while(node != NULL && result) {
    result = iterator(node->data);
    node = node->next;
  }
}

void list_head(list *list, void *element, bool removeFromList)
{
    assert(list->head != NULL);

    listNode *node = list->head;
    memcpy(element, node->data, list->elementSize);

    if(removeFromList) {
        list->head = node->next;
        list->logicalLength--;

        free(node->data);
        free(node);
    }
}

/*
void list_tail(list *list, void *element)
{
  assert(list->tail != NULL);
  listNode *node = list->tail;
  memcpy(element, node->data, list->elementSize);
}*/

void list_tail(list *list, void *element, bool removeFromList)
{
    assert(list->tail != NULL);
    listNode *node = list->tail;
    memcpy(element, node->data, list->elementSize);

    if(removeFromList) {
        assert(list->head != NULL);
        listNode *current = list->head;
        if (current != list->tail)
            while(current->next != list->tail)
                current = current->next;
        current->next = NULL;
        list->tail = current;
        list->logicalLength--;

        free(node->data);
        free(node);
    }
}

int list_size(list *list)
{
  return list->logicalLength;
}

/*
void list_print_int(list *list)
{
    listNode *node = list->head;
    while(node != NULL) {
        result = iterator(node->data);
        node = node->next;
    }
}*/

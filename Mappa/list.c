#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "list.h"
#include "grafo.h"

lista lista_interi(){
    lista brum = (lista)malloc(sizeof(list));
    list_new(brum, sizeof(int), NULL);
    return brum;
}

lista lista_double(){
    lista brum = (lista)malloc(sizeof(list));
    list_new(brum, sizeof(double), NULL);
    return brum;
}

lista lista_stringhe(){
    lista brum = (lista)malloc(sizeof(list));
    list_new(brum, sizeof(char)*50, NULL);
    return brum;
}

lista lista_grafi(){
    lista brum = (lista)malloc(sizeof(list));
    list_new(brum, sizeof(grafo), NULL);
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
        printf("N");
}

bool _lista_StampaStringhe(void *data) {
    printf("%s >> ", (char*)data);
    return TRUE;
}

void lista_StampaStringhe(lista lis){
        //assert(lis->elementSize == sizeof(char*));
        if(!lis) return;
        list_for_each(lis, (listIterator)_lista_StampaStringhe);
        printf("N");
}

void lista_catsx(lista list, lista l2){
    assert( list->elementSize == l2->elementSize && list->freeFn == l2->freeFn);
    if(!list->head) list->head = l2->head;
    if(list->tail) list->tail->next = l2->head;
    list->tail = l2->tail;
    list->logicalLength += l2->logicalLength;
}

nodo _nodo_insert_prior(nodo hed, nodo nu){
    if(!hed) return nu;
    if(hed->prior >= nu->prior){
        nu->next = hed;
        return nu;
    }
    else hed->next = _nodo_insert_prior(hed->next, nu);
    return hed;
}

nodo _nodo_destroy(nodo hed, void *element, lista list){
    if(!hed || !list) return hed;
    if(*((int*)hed->data) == *(int*)element){
    //if(*(hed->data) == *element){
        nodo ret = hed->next;
        if(list->freeFn) {
            list->freeFn(hed->data);
        }

        free(hed->data);
        free(hed);
        list->logicalLength--;
        return ret;
    }
    else hed->next = _nodo_destroy(hed->next, element, list);
    return hed;
}

void list_insert_prior(list *list, void *element, double prior){
    listNode *node = malloc(sizeof(listNode));
    node->data = malloc(list->elementSize);
    node->next = NULL;
    node->prior = prior;

    memcpy(node->data, element, list->elementSize);

    if(list->logicalLength == 0) {
        list->head = list->tail = node;
    } else {
        list->head = _nodo_insert_prior(list->head, node);
        //list->tail->next = node;
        if(!node->next) list->tail = node;
    }

    list->logicalLength++;
}

void list_update_prior(list *list, void *element, double prior){
    if(!list) return;
    int old = list->logicalLength;
    list->head = _nodo_destroy(list->head, element, list);
    int neu = list->logicalLength;
    if(old != neu) list_insert_prior(list, element, prior);
}

void lista_RimuoviNodo(lista lis, void *element){

}

void list_updateall_prior(list *list, void *element, double prior){
    if(!list) return;
    int num=0, old=0, neu=1;
    while(old != neu){
        old = list->logicalLength;
        list->head = _nodo_destroy(list->head, element, list);
        neu = list->logicalLength;
        if(old != neu) num++;
    }
    while(num){
        list_insert_prior(list, element, prior);
        num--;
    }
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
  node->prior = 0;
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
  node->prior = 0;

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

void list_head_prior(list *list, void *element, int* prior, bool removeFromList)
{
    assert(list->head != NULL);

    listNode *node = list->head;
    memcpy(element, node->data, list->elementSize);
    memcpy(prior, &node->prior, sizeof(int));

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

#ifndef __LIST_H
#define __LIST_H

typedef void (*freeFunction)(void *);

typedef enum { FALSE, TRUE } bool;

typedef bool (*listIterator)(void *);

typedef struct _listNode {
  void *data;
  double prior;
  struct _listNode *next;
} listNode;

typedef struct {
  int logicalLength;
  int elementSize;
  listNode *head;
  listNode *tail;
  freeFunction freeFn;
} list;

typedef list* lista;
typedef listNode* nodo;

lista lista_interi();
lista lista_double();
lista lista_stringhe();
lista lista_grafi();
void lista_cancella(lista* brum);
void lista_catsx(lista list, lista l2);

bool _lista_StampaInteri(void *data);
void lista_StampaInteri(lista lis);

bool _lista_StampaStringhe(void *data);
void lista_StampaStringhe(lista lis);

nodo _nodo_insert_prior(nodo hed, nodo nu);
nodo _nodo_destroy(nodo hed, void *element, lista list);
void list_insert_prior(list* list, void *element, double prior);
void list_update_prior(list* list, void *element, double prior);

void list_new(list *list, int elementSize, freeFunction freeFn);
void list_destroy(list *list);

void list_prepend(list *list, void *element);
void list_append(list *list, void *element);
int list_size(list *list);

void list_for_each(list *list, listIterator iterator);
void list_head(list *list, void *element, bool removeFromList);
void list_tail(list *list, void *element, bool removeFromList);
void list_head_prior(list *list, void *element, int* prior, bool removeFromList);
//void list_tail(list *list, void *element);

#endif

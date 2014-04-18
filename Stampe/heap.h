#include "pc.h"
#define max 128

typedef struct s_heap* Heap;

Heap initHeap(Heap);
int left(int);
int right(int);
int parent(int);
void swap(Heap,int,int);
void insert_heap(Heap, pc);
void Heapify(Heap, int);
void deleteNode(Heap, int);

<<<<<<< HEAD
=======
#include "pc.h"
>>>>>>> 7cbdc228d3de5c716c6f6928d51215cd2cc37968

typedef struct s_heap* Heap;

Heap initHeap();
int left(int);
int right(int);
int parent(int);
void swap(Heap,int,int);
void insert_heap(Heap, pc);
void Heapify(Heap, int);
void deleteNode(Heap, int);
int get_heapsize(Heap);
pc get_pc(Heap,int);
pc get_top_priority_pc(Heap);
void set_heapsize(Heap, int);

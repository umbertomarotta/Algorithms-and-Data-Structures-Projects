
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

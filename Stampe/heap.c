#include <string.h>
#include <stdlib.h>
#include "pc.h"
#include "heap.h"
#define max 128

struct s_heap {
        pc pc[max];
        int heapsize;
};


Heap initHeap(Heap coda){
    coda=(Heap)malloc(sizeof(struct s_heap));
    coda->heapsize=-1;
    memset(coda->pc,0,max);
    return coda;
}


int left(int curr)
{
        return 2*curr+1;
}

int right(int curr)
{
        return 2*curr+2;
}

int parent(int curr)
{
        return (curr-1)/2;
}

void swap(Heap coda, int i, int j)
{
        pc tmp = coda->pc[i];
        coda->pc[i] = coda->pc[j];
        coda->pc[j] = tmp;
}

void insert_heap(Heap coda, pc new_pc)
{
        int curr,father;
        if(coda->heapsize<max)
        {
                coda->pc[++coda->heapsize] = new_pc;
                curr=coda->heapsize;
                father=parent(curr);
                while(get_priority_pc(coda->pc[curr]) < get_priority_pc(coda->pc[father]))
                {
                        swap(coda, curr, father);
                        curr=father;
                        father=parent(curr);
                }
        }
}

void Heapify(Heap coda, int i)
{
        int l,r,largest;
        l = left(i);
        r = right(i);
        if (l < coda->heapsize && get_priority_pc(coda->pc[l]) > get_priority_pc(coda->pc[i]))
                largest = l;
        else largest = i;
        if (r < coda->heapsize && get_priority_pc(coda->pc[r]) > get_priority_pc(coda->pc[largest]))
                largest = r;

        if (largest != i) {
                swap(coda, i, largest);
                Heapify(coda, largest);
        }
}


void deleteNode(Heap coda, int node)
{
        int father, curr;
        if(node<coda->heapsize)
        {
                swap(coda, node, coda->heapsize);
                coda->heapsize--;
                if(get_priority_pc(coda->pc[node]) < get_priority_pc(coda->pc[parent(node)]))
                {
                    curr=node;
                    father=parent(node);
                    while(get_priority_pc(coda->pc[curr]) < get_priority_pc(coda->pc[father]))
                    {
                        swap(coda, curr, father);
                        curr=father;
                        father=parent(curr);
                    }
                }
                else
                    Heapify(coda,node);

        }

}


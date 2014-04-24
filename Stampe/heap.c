#include <string.h>
#include <stdlib.h>
#include "job.h"
#include "stampe.h"
#include "pc.h"
#include "heap.h"
#define max 32

struct s_heap {
        pc pc[max];
        int heapsize;
};

Heap initHeap(){
    int i;
    Heap coda = (Heap)malloc(sizeof(struct s_heap));
    coda->heapsize = -1;
    for (i=0; i<max; i++) coda->pc[i] = NULL;
    return coda;
}

int left(int curr){
        return 2*curr+1;
}

int right(int curr){
        return 2*curr+2;
}

int parent(int curr){
        return (curr-1)/2;
}

void swap(Heap coda, int i, int j){
        pc tmp = coda->pc[i];
        coda->pc[i] = coda->pc[j];
        coda->pc[j] = tmp;
}

void insert_heap(Heap coda, pc new_pc){
    int curr,father;
    if(coda->heapsize < max)
    {
        coda->pc[++coda->heapsize] = new_pc;
        curr = coda->heapsize;
        father = parent(curr);
        while(1 && get_priority_pc(coda->pc[curr]) < get_priority_pc(coda->pc[father]))
        {
            swap(coda, curr, father);
            curr = father;
            father = parent(curr);
        }
    }
}

void Heapify(Heap coda, int i){
        int l,r,lesser;
        l = left(i);
        r = right(i);
        if (l <= coda->heapsize && get_priority_pc(coda->pc[l]) < get_priority_pc(coda->pc[i]))
                lesser = l;
        else lesser = i;
        if (r <= coda->heapsize && get_priority_pc(coda->pc[r]) < get_priority_pc(coda->pc[lesser]))
                lesser = r;

        if (lesser != i) {
                swap(coda, i, lesser);
                Heapify(coda, lesser);
        }
}

void deleteNode(Heap coda, int node){
        int father, curr;
        if(node<=coda->heapsize)
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
                else Heapify(coda,node);


        }

}

int get_heapsize(Heap coda){
    return coda->heapsize;
}

pc get_top_priority_pc(Heap coda){
    pc top = coda->pc[0];
    deleteNode(coda, 0);
    return top;
}

void set_heapsize(Heap coda, int n){
    if(coda!=NULL && n < max)
        coda->heapsize = n;
}

pc get_pc(Heap coda, int n){
    if(n <= coda->heapsize)
        return coda->pc[n];
    else return NULL;
}

void update_priority(Heap coda, pc brum, int new_priority)
{
    int curr=0,padre;
    if(set_priority_job(brum,new_priority))
    {
        while(coda->pc[curr]!=brum && curr <=get_heapsize(coda))
            curr++;
        if(get_priority_pc(coda->pc[curr]) < get_priority_pc(coda->pc[parent(curr)]))
        {
            padre=parent(curr);
            while(get_priority_pc(coda->pc[curr])<get_priority_pc(coda->pc[padre]))
            {
                swap(coda,curr,padre);
                curr=padre;
                padre=parent(curr);
            }
        }
        else Heapify(coda,curr);
    }
}

pc get_pc_by_id(Heap coda,int id){
    int i;
    if(coda->heapsize>=0)
        for(i=0;i<=get_heapsize(coda);i++)
            if(get_id_pc(coda->pc[i])==id)
                return coda->pc[i];
    return NULL;
}

void deallocaHeap(Heap coda)
{
    int i=0;
    while(cancella_pc(coda->pc[i])&&i<max){
        i++;
        coda->pc[i]=NULL;
    }
    free(coda);
    coda=NULL;
}

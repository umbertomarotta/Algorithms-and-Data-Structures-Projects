#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"
#include "infrastruttura.h"
#include "pc.h"
#include "stampe.h"
#define max 32

struct sinfrastruttura{
    long n_job;
    int n_pc;
    Heap coda;
};


void simulate(infrastruttura system){
    while(get_heapsize(system->coda)>0)
    {
        stampa_pc(get_top_priority_pc(system->coda));

    }

}

infrastruttura initSystem()
{
    infrastruttura system = (infrastruttura)malloc(sizeof(struct sinfrastruttura));
    return system;
}

infrastruttura get_random_system()
{
    pc r_pc=NULL;
    long n_job;
    int n_pc,seq_id=0;
    srand(time(NULL));
    infrastruttura system = initSystem();
    n_pc=rand() % max;
    system->n_pc = n_pc;
    n_job = pow(2,n_pc);
    system->n_job = n_job;
    system->coda = initHeap();
    set_heapsize(system->coda, system->n_pc);
    while(n_pc>0)
    {
        insert_heap(system->coda, nuovo_pc(seq_id,seq_id,NULL));
        seq_id++;
        n_pc--;
    }
    while(n_job>0)
    {
        if((r_pc=get_pc(system->coda,rand()%system->n_pc))!=NULL)
        {
            set_coda_pc(r_pc,nuova_stampa_random(get_coda(r_pc), 1, n_job));
            n_job--;
        }
    }
    return system;

}

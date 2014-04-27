#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include "job.h"
#include "stampe.h"
#include "pc.h"
#include "heap.h"
#include "infrastruttura.h"
#include "utils.h"
#define MAX 22
#define MIN 21
#define MUTE 0

struct sinfrastruttura{
    long n_job;
    int n_pc;
    Heap coda;
};

void simulate(infrastruttura system)
{
    /* DEBUG */
    printf("PROCESSING...\n\n");
    /* ------ */
    stampa story = NULL;
    if(system->coda!=NULL)
    {
        while(get_heapsize(system->coda) >= 0){
            story = stampa_pc_ex(get_top_priority_pc(system->coda), story, MUTE);
        }
        /* DEBUG */
        printf("LAVORI STAMPATI: %d\n", get_num_stampe(story));
        /* ------ */
        deallocaHeap(system->coda);
        system->coda=NULL;
    }
    else printf("Niente da simulare!\n");
}

infrastruttura initSystem(){
    infrastruttura system = (infrastruttura)malloc(sizeof(struct sinfrastruttura));
    system->coda = initHeap();
    return system;
}
//
infrastruttura get_random_system()
{
    pc r_pc = NULL;
    int n_job;
    int n_pc, seq_id = 1;
    srand(time(NULL));
    infrastruttura system = initSystem();
    n_pc = rand()%(MAX - MIN) + MIN;
    system->n_pc = n_pc;
    //n_job = n_pc*10;
    n_job = pow(2, n_pc);
    system->n_job = n_job;
    while(n_pc)
    {
        insert_heap(system->coda, nuovo_pc(seq_id, seq_id, NULL));
        seq_id++;
        n_pc--;
    }

    /* DEBUG */
    long long debug = 0, debug2 = n_job, secondi, debug3 = 0, debug4 = 1;
    time_t tim = time(NULL), tim1 = time(NULL);
    printf("CARICAMENTO: ../%"PRId64"\n", debug2);
    /* ------ */
    while(n_job)
    {
        /* DEBUG */
        secondi = difftime(time(NULL),tim);
        if (difftime(time(NULL),tim1) >= 1) {
            clear_screen();
            printf("CARICAMENTO: %"PRId64"/%"PRId64" (%"PRId64"%%)\nSECONDI: %"PRId64"\nJOB AL SECONDO: %"PRId64"\nMINUTI RIMANENTI: %"PRId64"\n",
                debug,
                debug2,
                (debug*100)/debug2,
                secondi,
                debug4,
                (((debug2-debug)/debug4)/60)
            );
            debug4 = debug3;
            debug3 = 0;
            tim1 = time(NULL);
        }
        /* ------ */

        r_pc = get_pc(system->coda, rand()%(system->n_pc));
        if(r_pc)
        {
            accoda_stampa_pc(r_pc, n_job);
            n_job--;

            /* DEBUG */
            debug++;
            debug3++;
            /* ------ */
        }
    }

    /* DEBUG */
    clear_screen();
    printf("CARICAMENTO: %"PRId64"/%"PRId64"\n", debug, debug2);
    /* ------ */

    return system;

}

void stampa_coda(infrastruttura system)
{
    int i;
    if(system->coda!=NULL && get_heapsize(system->coda)>=0)
    {
        for(i=0;i<=get_heapsize(system->coda);i++)
            stampa_pc(get_pc(system->coda,i));
    }
    else printf("coda vuota!\n");
}


void update_priority_I(infrastruttura system){
    int id, npriority;
    pc brum=NULL;
    clear_screen();
    printf("Immetti l'ID del pc che vuoi modificare\n");
    scanf("%d",&id);
    brum = get_pc_by_id(system->coda, id);
    if(brum)
    {
        printf("quale priorità vuoi assegnargli?");
        scanf("%d",&npriority);
        update_priority(system->coda,brum,npriority);
    }
    else printf("pc selezionato inesistente\n");
}

int dealloca_infr(infrastruttura system){
    if (system == NULL) {
        return 0;
    }
    deallocaHeap(system->coda);
    system->coda = NULL;
    return 1;
}


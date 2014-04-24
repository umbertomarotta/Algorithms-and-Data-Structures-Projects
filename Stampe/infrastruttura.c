#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "job.h"
#include "stampe.h"
#include "pc.h"
#include "heap.h"
#include "infrastruttura.h"
#include "utils.h"
#define MAX 21
#define MIN 20
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
    while(get_heapsize(system->coda) >= 0){
        story = stampa_pc_ex(get_top_priority_pc(system->coda), story, MUTE);
    }
    /* DEBUG */
    printf("LAVORI STAMPATI: %d\n", get_num_stampe(story));
    /* ------ */
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
    long n_job;
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
    int debug = 0, debug2 = n_job, secondi, debug3 = 0, debug4 = 0;
    time_t tim = time(NULL), tim1 = time(NULL);
    printf("CARICAMENTO: ../%d\n", debug2);
    /* ------ */
    while(n_job)
    {
        /* DEBUG */
//        secondi = difftime(time(NULL),tim);
//        printf("CARICAMENTO: %d/%d\nSECONDI: %d\nJOB AL SECONDO: %d\n", debug, debug2, secondi, debug4);
//        if (difftime(time(NULL),tim1) >= 1) {
//            debug4 = debug3;
//            debug3 = 0;
//            tim1 = time(NULL);
//        }
//        clear_screen();
        /* ------ */
        r_pc = get_pc(system->coda, rand()%(system->n_pc));
        if(r_pc)
        {
            //set_coda_pc(r_pc, nuova_stampa_random(get_coda(r_pc), 1, (system->n_job)));
            //set_coda_pc(r_pc, inserisci_stampa(get_coda(r_pc), nuova_stampa(nuovo_job(n_job))));
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
    printf("CARICAMENTO: %d/%d\n", debug, debug2);
    /* ------ */

    return system;

}

void stampa_coda(infrastruttura system)
{
    int i;
    if(get_heapsize(system->coda)>=0)
    {
        for(i=0;i<=get_heapsize(system->coda);i++)
            stampa_pc(get_pc(system->coda,i));
    }
    else printf("coda vuota!\n");
}


void update_priority_I(infrastruttura system){
    int id, npriority;
    pc brum;
    clear_screen();
    printf("Immetti l'ID del pc che vuoi modificare\n");
    scanf("%d",&id);
    if(brum=get_pc_by_id(system->coda, id))
    {
        printf("quale priorità vuoi assegnargli?");
        scanf("%d",&npriority);
        update_priority(system->coda,brum,npriority);
    }
    else printf("pc selezionato inesistente\n");
}


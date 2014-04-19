#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "job.h"
#include "stampe.h"
#include "pc.h"

struct spc{
    int id;
    int priority;
    stampa coda;
};

pc nuovo_pc(int id, int priority, stampa coda){
    pc brum = (pc)malloc(sizeof(struct spc));
    brum->id = id;
    brum->priority = priority;
    brum->coda = coda;
    return brum;
}

int get_id_pc(pc car){
    if (car) return car->id;
    else return -1;
}

int get_priority_pc(pc car){
    if (car) return car->priority;
    return INT_MAX;
}

int set_id_pc(pc car, int id){
    if (!car) return 0;
    car->id = id;
    return 1;
}

int set_priority_job(pc car, int priority){
    if (!car) return 0;
    car->priority = priority;
    return 1;
}

int cancella_pc(pc car){
    if (car == NULL) return 0;
    cancella_stampa(car->coda);
    free(car);
    return 1;
}

int stampa_pc(pc brum){
    if (brum != NULL) {
        printf("ID PC: %02d\nPRIORITA': %02d\nCODA STAMPA: ", (brum->id)%100, (brum->priority)%100);
        stampa_stampe(brum->coda);
        printf("\n\n");
        return 1;
    }
    else
        return printf("NO PC\n\n");
}

<<<<<<< HEAD
stampa stampa_pc_ex(pc brum, stampa story, int mute){
    if (brum != NULL) {
        if (!mute) printf("ID PC: %02d\nPRIORITA': %02d\nCODA STAMPA: ", (brum->id)%100, (brum->priority)%100);
        story = stampa_stampe_ex(brum->coda, story, mute);
        if (!mute) printf("\n\n");
        return story;
    }
    printf("NO PC\n\n");
    return story;
}

void set_coda_pc(pc curr, stampa abr){
    if(curr!=NULL)
        curr->coda = abr;
}

stampa get_coda(pc curr){
    if(curr)
        return curr->coda;
    return NULL;
=======
void set_coda_pc(pc curr,stampa abr){
    if(curr!=NULL)
        curr->coda=abr;
}

stampa get_coda(pc curr){
    if(curr!=NULL)
        return curr->coda;
>>>>>>> 7cbdc228d3de5c716c6f6928d51215cd2cc37968
}

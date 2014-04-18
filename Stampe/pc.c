#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "stampe.h"
#include "job.h"
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

pc get_priority_pc(pc car){
    if (car) return car->priority;
    return NULL;
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
    else {
        return printf("NO PC\n\n");
}
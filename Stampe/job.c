#include <stdio.h>
#include <stdlib.h>
#include "job.h"

struct sjob{
    //pc sender;
    //char[20] utente;
    int id;
};

job nuovo_job(int id){
    job brum = (job)malloc(sizeof(struct sjob));
    //brum->sender = sender;
    brum->id = id;
    return brum;
}

int get_id_job(job car){
    if (car) return car->id;
    else return -1;
}

/*pc get_sender_job(job car){
    //if (car) return car->sender;
    return NULL;
}*/

int set_id_job(job car, int id){
    if (!car) return 0;
    car->id = id;
    return 1;
}

int set_sender_job(job car){
    if (!car) return 0;
    //car->sender = dest;
    return 1;
}

int cancella_job(job car){
    if (car == NULL) return 0;
    //cancella_pc(car->sender);
    free(car);
    return 1;
}

int stampa_job(job brum){
    //if (brum != NULL && brum->sender != NULL) return printf("[%02d]%d", (brum->id)%100, get_id_pc((brum->sender))%10);
    if (brum != NULL) return printf("[%02d]", (brum->id)%100);
    else return printf("    ");
}

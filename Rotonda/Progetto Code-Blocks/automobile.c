#include <stdio.h>
#include <stdlib.h>
#include "automobile.h"

struct sautomobile{
    int destinazione;
    int id;
};


int set_id_auto(automobile car, int id){
    if (!car) return 0;
    car->id = id;
    return 1;
}

int set_dest_auto(automobile car, int dest){
    if (!car) return 0;
    car->destinazione = dest;
    return 1;
}

int get_id_auto(automobile car){
    if (car) return car->id;
    else return -1;
}

int get_dest_auto(automobile car){
    if (car) return car->destinazione;
    else return -1;
}

automobile nuova_auto(int dest, int id){
    automobile brum = (automobile)malloc(sizeof(struct sautomobile));
    if (dest<0) dest = 0;
    brum->destinazione = dest;
    brum->id = id;
    return brum;
}

int cancella_auto(automobile car){
    if (car == NULL) return 0;
    free(car);
    return 1;
}

void stampa_auto(automobile brum){
    if (brum != NULL)printf("[%02d]%d", (brum->id+1)%100, (brum->destinazione+1)%10);
    else printf("     ");
}



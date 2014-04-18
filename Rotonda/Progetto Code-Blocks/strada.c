#include <stdio.h>
#include <stdlib.h>
#include "automobile.h"
#include "coda.h"
#include "strada.h"

struct sstrada{
    coda inizio;
    coda fine;
    char nome;
};

int set_nome_strada(strada brum, char nom){
    if(!brum) return 0;
    brum->nome = nom;
    return 1;
}

char get_nome_strada(strada brum){
    if(brum) return brum->nome;
    else return '0';
}

coda get_inizio_strada(strada brum){
    if(brum) return brum->inizio;
    else return NULL;
}

strada nuova_strada(char nom, coda que){
    strada brum = (strada)malloc(sizeof(struct sstrada));
    brum->inizio = que;
    brum->fine = fine_coda(que);
    brum->nome = nom;
    return brum;
}

int accoda_auto_strada(strada brum, automobile car){
    if ( brum == NULL || car == NULL) return 0;
    if (brum->inizio && brum->fine){
        brum->fine = accoda_auto_coda(brum->fine, car);
        brum->fine = fine_coda(brum->fine);
    }
    else{
        brum->inizio = nuova_coda(car);
        brum->fine = brum->inizio;
    }
    return 1;
}

automobile decoda_auto_strada(strada brum){
    if (brum != NULL){
        //automobile car = coda_pop_auto(&(brum->inizio));
        if (brum->inizio == NULL) return NULL;
        coda canc = brum->inizio;
        automobile car = get_auto_coda(canc);
        brum->inizio = get_next_coda(canc);
        free(canc);
        if (brum->inizio == NULL) brum->fine = NULL;
        return car;
    }
    else return NULL;
}

int cancella_strada(strada brum){
    if (brum == NULL) return 0;
    int ncar = cancella_coda(brum->inizio);
    free(brum);
    return ncar;
}

int cancella_auto_strada(strada road, int ID){
    if(!road) return 0;
    if(get_id_auto(get_auto_coda(road->inizio)) ==ID){
        cancella_auto(decoda_auto_strada(road));
        return 1;
    }
    int res = cancella_auto_coda(road->inizio, get_next_coda(road->inizio),ID);
    if (!res) return 0;
    if (res == 2) road->fine = get_prev_coda(road->inizio, NULL);
    return 1;
}

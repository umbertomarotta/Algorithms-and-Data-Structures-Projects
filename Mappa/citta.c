#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>
#include <math.h>

#include "citta.h"
//#include "mappa.h"
//#include "grafo.h"

//Distanza massima in chilometri
#define WORLD_DIST 20038

//Circonferenza della terra in chilometri
#define WORLD_SIZE 40076

#define CITY_MAXLIV 7
/*
0 - Paesino
1 - Comune
2 - Provincia
3 - Capoluogo
4 - Capitale
5 - Scalo Internazionale
6 - Megalopoli
*/

struct scitta{
    int posX;
    int posY;
    char* nome;
    int livello;
    int fazione;
};

citta citta_Random(){
    citta city = (citta)malloc(sizeof(struct scitta));
    city->nome = "prova";
    city->livello = rand()%CITY_MAXLIV;
    city->posX = rand()%WORLD_SIZE;
    city->posY = rand()%WORLD_SIZE;
    //printf("x: %d\n", city->posX);
    city->fazione = 0;
    return city;
}

int citta_Cancella(citta* city){
    #define tip (*city)
    if(!tip) return 1;
    free(tip->nome);
    free(tip);
    tip = NULL;
    return 0;
    #undef tip
}

int citta_Distanza(citta c1, citta c2){
    if(!c1 || !c2) return -1;
    int dist = sqrt(pow(c2->posX-c1->posX,2)+pow(c2->posY-c1->posY,2));
    //if (dist > WORLD_DIST) dist = WORLD_SIZE - dist;
    assert(dist >= 0);
    return dist;
}

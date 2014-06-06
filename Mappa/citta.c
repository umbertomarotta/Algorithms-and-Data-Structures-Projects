#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

#include "citta.h"
//#include "mappa.h"
//#include "grafo.h"

/*
0 - Paesino
1 - Comune
2 - Provincia
3 - Capoluogo
4 - Capitale
5 - Scalo Internazionale
6 - Megalopoli
*/

citta citta_Nuova(char* nome, int posx, int posy, int liv){
    citta city = (citta)malloc(sizeof(struct scitta));
    //city->nome = "prova";
    if(nome){
        city->nome=(char*)malloc(strlen(nome)*sizeof(char));
        strcpy(city->nome,nome);
    }
    else city->nome = "NoName City";
    city->posX = posx%WORLD_SIZE;
    city->posY = posy%WORLD_SIZE;
    //printf("x: %d\n", city->posX);
    city->fazione = 0;
    city->isola = 0;
    city->livello = liv;
    //city->livello = rand()%CITY_MAXLIV;
    return city;
}

char* citta_toString(citta c1){
    if(!c1) return NULL;
    char* res = calloc( strlen(c1->nome) + 60, sizeof(char));
    sprintf(res, "%s# %d %d %d", c1->nome, c1->posX, c1->posY, c1->livello);
    return res;
}

citta citta_fromString(char* s){
    char* nome;
    int posx, posy, liv;
    //sscanf(s, "%[^#]# %d %d %d",nome, &posx, &posy, &liv);
    char *str;
    nome=strtok(s,"#");
    strcat(nome,"\0");
    int i=strlen(nome);
    posx=atoi(strtok(NULL," "));
    posy=atoi(strtok(NULL," "));
    liv=atoi(strtok(NULL,"\n"));
    return citta_Nuova(nome, posx, posy, liv);
}

citta citta_Random(){
    char* caso[54] = { "Tetherow",
        "Loachapoka",
        "Novinger",
        "Panorama Park",
        "West Mayfield",
        "Holly",
        "Quebradillas",
        "Weaubleau",
        "Flemington",
        "Wylie",
        "Jewell Junction",
        "St Rosa",
        "Tropic",
        "Curlew Lake",
        "Shady Point",
        "Las Cruces",
        "Roslyn Estates",
        "Glenmora",
        "Millbrook",
        "Currie",
        "Shiloh",
        "Webster City",
        "Belcher",
        "Las Animas",
        "Potomac Mills",
        "Short",
        "Talco",
        "Talty",
        "Maplewood",
        "Lenkerville",
        "Yeagertown",
        "Santa_Claus",
        "Arctic Village",
        "Bethany Beach",
        "Upper Fruitland",
        "Tinton Falls",
        "Marblehead",
        "La Mesilla",
        "Cabana Colony",
        "Roseau",
        "Lake Benton",
        "Dunlap",
        "Zillah",
        "Morland",
        "Ridgely",
        "Cotton Plant",
        "South Lyon",
        "Pattonsburg",
        "Russiaville",
        "Sabula",
        "Umberto City",
        "Muranos Reign",
        "Francescolandia",
        "NonNapoli",
        };
    citta city = (citta)malloc(sizeof(struct scitta));
    //city->nome = "prova";
    city->nome = caso[rand()%54];
    city->posX = rand()%WORLD_SIZE;
    city->posY = rand()%WORLD_SIZE;
    //printf("x: %d\n", city->posX);
    city->fazione = 0;
    city->isola = 0;
    int liv = rand()%100;
    if(liv > 75) city->livello = 0;
    else if(liv > 25) city->livello = 1;
    else if(liv > 14) city->livello = 2;
    else if(liv > 7) city->livello = 3;
    else if(liv > 4) city->livello = 3;
    else if(liv > 2) city->livello = 4;
    else if(liv > 1) city->livello = 5;
    else city->livello = 6;
    //city->livello = rand()%CITY_MAXLIV;
    return city;
}

int citta_Cancella(citta city){
    //#define tip (*city)
    if(!city) return 1;
    //free(city->nome);
    free(city);
    //tip = NULL;
    return 0;
    //#undef tip
}

int citta_Distanza(citta c1, citta c2){
    if(!c1 || !c2) return -1;
    int dist = sqrt(pow(c2->posX-c1->posX,2)+pow(c2->posY-c1->posY,2));
    //if (dist > WORLD_DIST) dist = WORLD_SIZE - dist;
    assert(dist >= 0);
    return dist;
}

int citta_livello(citta c1){
    if(!c1) return -1;
    else return c1->livello;
}

int citta_stampa(citta c1){
    if(!c1) return 1;
    char tipo[50];
    switch ( c1->livello ) {
    case 1:
        strcpy(tipo, "Comune");
        break;
    case 2:
        strcpy(tipo, "Provincia");
        break;
    case 3:
        strcpy(tipo, "Capoluogo");
        break;
    case 4:
        strcpy(tipo, "Capitale");
        break;
    case 5:
        strcpy(tipo, "Metropoli");
        break;
    case 6:
        strcpy(tipo, "Megalopoli");
        break;
    default:
        strcpy(tipo, "Paesino");
        break;
    }
    printf("%12s: %16s (%04d,%04d)", tipo, c1->nome, c1->posX, c1->posY);
    return 0;
}


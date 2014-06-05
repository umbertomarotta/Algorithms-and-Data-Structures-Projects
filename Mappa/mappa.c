#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>

#include "mappa.h"
#include "citta.h"
#include "grafo.h"
#include "utils.h"

#define DIM 1000
#define FAST 0

grafo grafo_getVoli(mappa map){
    return map->Voli;
}

grafo grafo_getFerrovie(mappa map){
    return map->Ferrovie;
}

grafo grafo_getAutostrade(mappa map){
    return map->Autostrade;
}

grafo grafo_getStrade(mappa map){
    return map->Strade;
}

mappa mappa_nuova_hardcode(int numcitta){
    mappa map = (mappa)malloc(sizeof(struct smappa));
    map->Costo_Aereo = 0.20F; //Basato su costo al chilometro di un volo alitalia
    map->Costo_Treno = 0.08F; //Basto sul costo di un treno italo
    map->Costo_Pedaggio = 0.06F; //http://www.autostrade.it/documents/10279/25719/tariffa.gif
    map->Costo_Benzina = 0.09F; //Basato sul consumo di una fiat panda
    map->Vel_Aereo = 850; //Velocità massima di un aribus A320
    map->Vel_Treno = 300; //Velocità frecciarossa
    map->Vel_Autostrade = 120; //Autostrade italiane
    map->Vel_Strade = 50; //strade italiane
    map->NumCitta = numcitta;
    map->cities = calloc(numcitta, sizeof(citta));
    citta* city = map->cities;
    int i, j, li, lj;
    int numpesi = 2;
    for (i=0; i<numcitta; i++) city[i] = citta_Random();
    map->Voli = grafo_Nuovo(numcitta, numpesi);
    map->Ferrovie = grafo_Nuovo(numcitta, numpesi);
    map->Autostrade = grafo_Nuovo(numcitta, numpesi);
    map->Strade = grafo_Nuovo(numcitta, numpesi);
    grafo_Rinomina(map->Voli, "Voli");
    grafo_Rinomina(map->Ferrovie, "Ferrovie");
    grafo_Rinomina(map->Autostrade, "Autostrade");
    grafo_Rinomina(map->Strade, "Strade");
    double tempo, costo, dist;
    int str=0, aut=0, tre=0, vol=0;

    /* DEBUG */
    int work = numcitta*numcitta, done = 0;
    time_t tim = time(NULL);

    for (i=0; i<numcitta; i++){
        for (j=0; j<numcitta; j++){

            /* DEBUG */
            done++;
            if (difftime(time(NULL),tim) >= 1) {
                clear_screen();
                printf("CARICAMENTO: %d/%d (%1.2f%%)\n", done, work, (float)(done*100)/work);
                tim = time(NULL);
            }
            //printf("azz\n");
            if (i==j) continue;
            dist = (double)citta_Distanza(city[i], city[j]);
            li = citta_livello(city[i]);
            lj = citta_livello(city[j]);
            //printf("dist %d %d = %.2f\n", i, j, dist);
            tempo = (dist/map->Vel_Aereo);
            if( FAST || tempo*2 < grafo_raggiunge(map->Voli, i, j))
            if(i > j && ((dist > 1000 && li > 3 && lj > 3) || (dist > 180 && dist < 1000 && li > 2 && lj > 2))){
                //printf("Vol\n");
                costo = (dist*map->Costo_Aereo);
                grafo_AggiungiArco(map->Voli, i, j, 2, tempo, costo);
                grafo_AggiungiArco(map->Voli, j, i, 2, tempo, costo);
                vol++;
            }
            dist = (dist*1.5); //impedimenti Geografici
            tempo = (dist/map->Vel_Treno);
            if( FAST || tempo*2 < grafo_raggiunge(map->Ferrovie, i, j))
            if(i > j && dist > 100 && dist < 500  && li > 1 && lj > 1){
                //printf("Fer\n");
                costo = (dist*map->Costo_Treno);
                grafo_AggiungiArco(map->Ferrovie, i, j, 2, tempo, costo);
                grafo_AggiungiArco(map->Ferrovie, j, i, 2, tempo, costo);
                tre++;
            }
            tempo = (dist/map->Vel_Autostrade);
            if( FAST || tempo*2 < grafo_raggiunge(map->Autostrade, i, j))
            if(i > j && dist > 50 && dist < 300  && li > 0 && lj > 0 ){
                //printf("Auto\n");
                costo = (dist*(map->Costo_Pedaggio + map->Costo_Benzina));
                grafo_AggiungiArco(map->Autostrade, i, j, 2, tempo, costo );
                grafo_AggiungiArco(map->Autostrade, j, i, 2, tempo, costo );
                aut++;
            }
            tempo = dist/map->Vel_Strade;
            if( FAST || tempo*2 < grafo_raggiunge(map->Strade, i, j))
            if(i > j && dist < 50){
                //printf("Str\n");
                costo = dist*map->Costo_Pedaggio;
                grafo_AggiungiArco(map->Strade, i, j, 2, tempo, costo);
                grafo_AggiungiArco(map->Strade, j, i, 2, tempo, costo);
                str++;
                //grafo_AggiungiArco(map->Strade, i, j, 2, 666, 666);
            }
        }
    }

    /* DEBUG */
    clear_screen();
    printf("Numero Citta: %d\n", numcitta);
    printf("Strade Interurbane: %d\n", str);
    printf("Tratte Autostradali: %d\n", aut);
    printf("Tratte Ferroviarie: %d\n", tre);
    printf("Voli: %d\n", vol);
    printf("\n");
    return map;
}

int mappa_stampa(mappa map){
    if(!map) return 1;
    grafo_Stampa(map->Voli);
    printf("\n\n");
    grafo_Stampa(map->Ferrovie);
    printf("\n\n");
    grafo_Stampa(map->Autostrade);
    printf("\n\n");
    grafo_Stampa(map->Strade);
    printf("\n\n");
    return 0;
}

int mappa_getCostoMezzo(int vel_media, int tempo, int costo_mezzo){
    return (vel_media*tempo)*costo_mezzo;
}

int mappa_StampaCitta(mappa map){
    if(!map) return 1;
    int res = 10;
    int i, j, x, y;
    int matr[res][res];
//    grafo_Stampa(map->Voli);
//    grafo_Stampa(map->Ferrovie);
//    grafo_Stampa(map->Strade);
//    grafo_Stampa(map->Autostrade);
    for(i=0; i<res; i++) for(j=0; j<res; j++) matr[i][j] = -1;
    for(i=0; i<map->NumCitta; i++){
        printf("ID: %04d ", i);
        x = ((map->cities[i]->posX)*res)/WORLD_SIZE;
        y = ((map->cities[i]->posY)*res)/WORLD_SIZE;
        matr[res-1-y][x] = i;
        citta_stampa(map->cities[i]);
        printf("\n");
    }
    printf("\nMappa: %d Km^2\n_", WORLD_SIZE*WORLD_SIZE);
    for(i=0; i<res; i++) printf("_____");
    printf("_\n|");
    for(i=0; i<res; i++){
        for(j=0; j<res; j++){
            if (matr[i][j] != -1) printf("%4d ", matr[i][j]);
            else printf("     ");
        }
        printf("|\n|");
    }
    for(i=0; i<res; i++) printf("_____");
    printf("|\n");
    return 0;
}



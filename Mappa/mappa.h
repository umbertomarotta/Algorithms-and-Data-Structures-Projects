#ifndef __MAP_H
#define __MAP_H

#include "grafo.h"
#include "citta.h"

struct smappa{
    float Costo_Aereo;
    float Costo_Treno;
    float Costo_Pedaggio;
    float Costo_Benzina;
    int Vel_Aereo;
    int Vel_Treno;
    int Vel_Autostrade;
    int Vel_Strade;
    grafo Voli;
    grafo Ferrovie;
    grafo Autostrade;
    grafo Strade;
    int NumCitta;
    citta* cities;
};

typedef struct smappa* mappa;

char* mappa_getNomeCitta(mappa map, int i);

void mappa_stampaListaCitta(mappa map, lista city, lista mezzi);

int mappa_CancellaCitta(mappa map, int i);

mappa mappa_nuova_hardcode(int numcitta);

mappa mappa_nuova_hardcore(int numcitta);

int mappa_stampa(mappa map);

int mappa_getCostoMezzo(int vel_media, int tempo, int costo_mezzo);

grafo mappa_CoperturaMin(citta* cities, int numc, float cost, int vel, int distmin, int distmax, int lmin);

int mappa_StampaCitta(mappa map);

grafo grafo_getStrade(mappa map);

grafo grafo_getVoli(mappa map);

grafo grafo_getFerrovie(mappa map);

grafo grafo_getAutostrade(mappa map);

#endif

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

mappa mappa_nuova_hardcode(int numcitta);
mappa mappa_nuova_hardcore(int numcitta);

char* mappa_getNomeCitta(mappa map, int i);

int mappa_stampa(mappa map);
int mappa_StampaCitta(mappa map);
int mappa_stampaPercorso(mappa map, lista city, lista mezzi);
int mappa_getCostoMezzo(int vel_media, int tempo, int costo_mezzo);
int mappa_CancellaCitta(mappa map, int id);

grafo mappa_CoperturaMin(citta* cities, int numc, float cost, int vel, int distmin, int distmax, int lmin);
grafo grafo_getStrade(mappa map);
grafo grafo_getVoli(mappa map);
grafo grafo_getFerrovie(mappa map);
grafo grafo_getAutostrade(mappa map);

int mappa_mapToFile(mappa map, char* nomeF);
mappa mappa_mapFromFile(char* nomeF);

int mappa_cancella(mappa map);

#endif

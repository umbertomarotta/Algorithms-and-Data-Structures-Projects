#include "grafo.h"

typedef struct smappa* mappa;

mappa mappa_nuova_hardcode(int numcitta);

int mappa_stampa(mappa map);

int mappa_getCostoMezzo(int vel_media, int tempo, int costo_mezzo);

int mappa_StampaCitta(mappa map);

grafo grafo_getStrade(mappa map);

grafo grafo_getVoli(mappa map);

grafo grafo_getFerrovie(mappa map);

grafo grafo_getAutostrade(mappa map);


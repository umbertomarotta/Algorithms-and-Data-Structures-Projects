#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "grafo.h"
#include "mappa.h"
#include "citta.h"
#include "utils.h"

int main(){
    srand(time(NULL));
    mappa map = mappa_nuova_hardcode(21);
    mappa_StampaCitta(map);
    //mappa_stampa(map);
/*
//    grafo gra = grafo_Nuovo(10, 0);
//    grafo_AggiungiArcoEx(gra, 1, 9, 0);
//    grafo_AggiungiArcoEx(gra, 1, 8, 0);
//    grafo_Stampa(gra);

//    citta c1 = citta_Random();
//    citta c2 = citta_Random();
//    printf("distanza: %d", citta_Distanza(c1,c2));
//    printf("\n\n");

    grafo gra = grafo_Random(11, 1, 10, 10);
    grafo_Rinomina(gra, "gra");
    grafo gra1 = grafo_Random(11, 1, 10, 10);
    grafo_Rinomina(gra1, "gra1");
    grafo gra2 = grafo_Random(11, 1, 10, 10);
    grafo_Rinomina(gra2, "gra2");
    //grafo gra3 = grafo_Random(11, 1, 10, 10);
    grafo gra3 = grafo_fromString(grafo_toString(gra2));
    grafo_Rinomina(gra3, "gra2 copia");

//    ord = grafo_getPath(gra2, 9, 1);
//    lista_StampaInteri(ord);
//    printf("\n\n");
//    lista_cancella(&ord);
//    ord = grafo_getPath(gra1, 9, 1);
//    lista_StampaInteri(ord);
//    printf("\n\n");
//    lista_cancella(&ord);
//    ord = grafo_getPath(gra, 9, 1);
//    lista_StampaInteri(ord);
//    printf("\n\n");
//    lista_cancella(&ord);

    lista grafi = lista_grafi();
    list_append(grafi, &gra3);
    list_append(grafi, &gra2);
    list_append(grafi, &gra1);
    list_append(grafi, &gra);

    grafo_Stampa(gra3);
    printf("\n\n");
    grafo_Stampa(gra2);
    printf("\n\n");
    grafo_Stampa(gra1);
    printf("\n\n");
    grafo_Stampa(gra);
    printf("\n\n");

    lista ord = lista_interi();
    lista mez = lista_stringhe();
    //grafo_getPath(gra, 9, 1, &ord);
    grafo_getPathM(grafi, 9, 1, 0, &ord, &mez);
    printf("Path: %d\n\n", list_size(ord));
    lista_StampaInteri(ord);
    printf("\n\n");
    lista_StampaStringhe(mez);
    printf("\n\n");
*/
    return 0;
}

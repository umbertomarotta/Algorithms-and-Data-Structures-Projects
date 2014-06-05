#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "list.h"
#include "grafo.h"
#include "citta.h"
#include "mappa.h"
#include "utils.h"


int main(){
    srand(time(NULL));

    int num_city, source, dest;
    mappa map = NULL;
    grafo voli=NULL, ferrovie=NULL, autostrade=NULL, strade=NULL;
    int scelta = -1;
    while(scelta != 0){
        clear_screen();
        printf("\n [1] Genera Mappa Random\n");
        printf("\n [2] Stampa Mappa\n");
        printf("\n [3] Trova percorso ottimo in base al tempo\n");
        printf("\n [4] Trova percorso ottimo in base al costo\n");
        printf("\n [5] Inserisci job in un pc\n");
        printf("\n [6] Cancella job da un pc\n");
        printf("\n [0] Esci\n\n");
        printf("Scegli: ");
        scanf("%d",&scelta);
        press_enter();
        switch (scelta) {
            case 1:
                printf("\nInserisci numero di citta' \n");
                scanf("%d",&num_city);
                map = mappa_nuova_hardcode(num_city);
            break;
        case 2:
            if(map!=NULL){
                mappa_StampaCitta(map);
                printf("\n\nLINKS\n\n");
//                printf("\n\n");
//                grafo_Stampa(grafo_getVoli(map));
//                printf("\n\n");
//                grafo_Stampa(grafo_getFerrovie(map));
//                printf("\n\n");
//                grafo_Stampa(grafo_getAutostrade(map));
//                printf("\n\n");
//                grafo_Stampa(grafo_getStrade(map));
//                printf("\n\n");

            }
            else printf("devi prima avere una mappa!\n");
            press_enter();
            break;
        case 3:
            if(map!=NULL){
                lista grafi = lista_grafi();
                voli=grafo_getVoli(map);
                ferrovie=grafo_getFerrovie(map);
                autostrade=grafo_getAutostrade(map);
                strade=grafo_getStrade(map);
                list_append(grafi, &(voli));
                list_append(grafi, &(ferrovie));
                list_append(grafi, &(autostrade));
                list_append(grafi, &(strade));
                lista ord = lista_interi();
                lista mez = lista_stringhe();
                //grafo_getPath(gra, 9, 1, &ord);
                printf("Inserire Sorgente e Destinazione:\n");
                scanf("%d %d",&source,&dest);
                grafo_getPathM(grafi, source, dest, 0, &ord, &mez);
                printf("Path: %d\n\n", list_size(ord));
                lista_StampaInteri(ord);
                printf("\n\n");
                lista_StampaStringhe(mez);
                printf("\n\n");
                press_enter();
            }
            else printf("devi prima avere uno scenario iniziale!\n");
            press_enter();
            break;
        case 4:
            if(map!=NULL){
                lista grafi = lista_grafi();
                voli=grafo_getVoli(map);
                ferrovie=grafo_getFerrovie(map);
                autostrade=grafo_getAutostrade(map);
                strade=grafo_getStrade(map);
                list_append(grafi, &(voli));
                list_append(grafi, &(ferrovie));
                list_append(grafi, &(autostrade));
                list_append(grafi, &(strade));
                lista ord = lista_interi();
                lista mez = lista_stringhe();
                //grafo_getPath(gra, 9, 1, &ord);
                printf("Inserire Sorgente e Destinazione:\n");
                scanf("%d %d",&source,&dest);
                grafo_getPathM(grafi, source, dest, 1, &ord, &mez);
                printf("Path: %d\n\n", list_size(ord));
                lista_StampaInteri(ord);
                printf("\n\n");
                lista_StampaStringhe(mez);
                printf("\n\n");
                press_enter();
            }
            else printf("devi prima avere uno scenario iniziale!\n");
            press_enter();
            break;

        /*case 5:
            if(system!=NULL)
                insert_job_pc_I(system);
            break;
        case 6:
            if(system!=NULL)
                delete_job_I(system);
            break;*/
        case 0:
            clear_screen();
            printf("\n[0] Esci\n\n");
            printf("Arrivederci!\n");
            press_enter();
            break;
        default:
            clear_screen();
            feature_segreta();
            press_enter();
            break;
        }
    }
    //mappa_stampa(map);



    return 0;
}

int main1(){
    srand(time(NULL));

    grafo g1 = grafo_Random(11, 1, 5, 10);
    //grafo g1 = grafo_Nuovo(10, 3);
    grafo_Stampa(g1);
    printf("\n\n");
    grafo_RimuoviNodo(g1, 5);
    grafo_Stampa(g1);

    //grafo_AggiungiArco(g1, 9, 1, 2, 6., 66.);
    //grafo_Stampa(g1);
    //grafo_RimuoviArco(g1, 9, 1);
    //grafo_Stampa(g1);
}

int main2(){

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

}

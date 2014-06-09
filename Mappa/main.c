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

    int num_city, source, dest, scelta = -1, id=0, i;
    char yes, nomeF[50];
    double tempo=0, costo=0, dist=0;
    mappa map = NULL;
    grafo graph = NULL, voli = NULL, ferrovie = NULL, autostrade = NULL, strade = NULL;
    while(scelta != 0){
        clear_screen();
        printf("\n [1] Genera Mappa Random\n");
        printf("\n [2] Stampa Mappa\n");
        printf("\n [3] Trova percorso ottimo in base al tempo\n");
        printf("\n [4] Trova percorso ottimo in base al costo\n");
        printf("\n [5] Rimuovi Collegamento\n");
        printf("\n [6] Rimuovi citta' dalla mappa\n");
        printf("\n [7] Esporta mappa su file\n");
        printf("\n [8] Importa mappa da file\n");
        printf("\n [9] Aggiungi Collegamento\n");
        printf("\n [10] Aggiungi citta' alla mappa\n");
        printf("\n [11] Stampa Grafo\n");
        printf("\n [0] Esci\n\n");
        printf("Scegli: ");
        scanf("%d",&scelta);
        press_enter();
        switch (scelta) {
            case 1:
                printf("\nInserisci numero di citta' \n");
                scanf("%d",&num_city);
                mappa_cancella(map);
                map = mappa_nuova_hardcode(num_city);
            break;
        case 2:
            if(map){
                mappa_StampaCitta(map);
                printf("\n\n");
            }
            else printf("devi prima avere una mappa!\n");
            press_enter();
            break;
        case 3:
            if(map){
                mappa_StampaCitta(map);
                printf("\n\n");
                lista grafi = lista_grafi();
                voli = grafo_getVoli(map);
                ferrovie = grafo_getFerrovie(map);
                autostrade = grafo_getAutostrade(map);
                strade = grafo_getStrade(map);

                printf("Puoi prendere l'aereo? (s/n): ");
                scanf("%c", &yes);
                press_enter();
                if (yes == 's' || yes == 'S'){
                    printf("Per tutte le citta'?(s/n): ");
                    scanf("%c", &yes);
                    press_enter();
                    if (yes != 's' && yes != 'S'){
                        printf("Quante citta' vuoi ingorare?: ");
                        scanf("%d", &dest);
                        press_enter();
                        if (dest) printf("Inserisci le %d citta: ", dest);
                        for(i=0; i<dest; i++){
                            scanf("%d", &id);
                            if(id >= 0 && id < voli->nv) voli->ignore[id] = 1;
                        }
                        press_enter();

                    }
                    list_append(grafi, &(voli));
                }
                printf("Puoi prendere il treno? (s/n): ");
                scanf("%c", &yes);
                press_enter();
                if (yes == 's' || yes == 'S'){
                    printf("Per tutte le citta'?(s/n): ");
                    scanf("%c", &yes);
                    press_enter();
                    if (yes != 's' && yes != 'S'){
                        printf("Quante citta' vuoi ingorare?: ");
                        scanf("%d", &dest);
                        press_enter();
                        if (dest) printf("Inserisci le %d citta: ", dest);
                        for(i=0; i<dest; i++){
                            scanf("%d", &id);
                            if(id >= 0 && id < ferrovie->nv) ferrovie->ignore[id] = 1;
                        }
                        press_enter();

                    }
                    list_append(grafi, &(ferrovie));
                }
                printf("Puoi prendere strade a pedaggio? (s/n): ");
                scanf("%c", &yes);
                press_enter();
                if (yes == 's' || yes == 'S'){
                    printf("Per tutte le citta'?(s/n): ");
                    scanf("%c", &yes);
                    press_enter();
                    if (yes != 's' && yes != 'S'){
                        printf("Quante citta' vuoi ingorare?: ");
                        scanf("%d", &dest);
                        press_enter();
                        if (dest) printf("Inserisci le %d citta: ", dest);
                        for(i=0; i<dest; i++){
                            scanf("%d", &id);
                            if(id >= 0 && id < autostrade->nv) autostrade->ignore[id] = 1;
                        }
                        press_enter();

                    }
                    list_append(grafi, &(autostrade));
                }
                list_append(grafi, &(strade));

                printf("Da dove parti? (ID): ");
                scanf("%d",&source);
                press_enter();
                printf("Da dove vorresti arrivare? (ID): ");
                scanf("%d",&dest);
                press_enter();
                printf("Da %s a %s\n\n", mappa_getNomeCitta(map, source), mappa_getNomeCitta(map,dest));

                lista ord = lista_interi();
                lista mez = lista_stringhe();
                if(!grafo_getPathM(grafi, source, dest, 0, &ord, &mez)){
                    list_head(grafi, &graph, FALSE);
                    printf("Ti ci vorranno %.1f Ore\n", graph->dist[dest][0]);
                    printf("Ma dovrai spendere %.1f Euro\n", graph->dist[dest][1]);
                }
		        mappa_stampaPercorso(map, ord, mez);

                for(i=0; i< strade->nv; i++){
                    strade->ignore[id] = 0;
                    autostrade->ignore[id] = 0;
                    ferrovie->ignore[id] = 0;
                    voli->ignore[id] = 0;
                }
		        lista_cancella(&ord);
		        lista_cancella(&mez);
		        lista_cancella(&grafi);
            }
            else printf("devi prima avere uno scenario iniziale!\n");
            press_enter();
            break;
        case 4:
            if(map){
                mappa_StampaCitta(map);
                printf("\n\n");
                lista grafi = lista_grafi();
                voli = grafo_getVoli(map);
                ferrovie = grafo_getFerrovie(map);
                autostrade = grafo_getAutostrade(map);
                strade = grafo_getStrade(map);

                printf("Puoi prendere l'aereo? (s/n): ");
                scanf("%c", &yes);
                press_enter();
                if (yes == 's' || yes == 'S'){
                    printf("Per tutte le citta'?(s/n): ");
                    scanf("%c", &yes);
                    press_enter();
                    if (yes != 's' && yes != 'S'){
                        printf("Quante citta' vuoi ingorare?: ");
                        scanf("%d", &dest);
                        press_enter();
                        if (dest) printf("Inserisci le %d citta: ", dest);
                        for(i=0; i<dest; i++){
                            scanf("%d", &id);
                            if(id >= 0 && id < voli->nv) voli->ignore[id] = 1;
                        }
                        press_enter();

                    }
                    list_append(grafi, &(voli));
                }
                printf("Puoi prendere il treno? (s/n): ");
                scanf("%c", &yes);
                press_enter();
                if (yes == 's' || yes == 'S'){
                    printf("Per tutte le citta'?(s/n): ");
                    scanf("%c", &yes);
                    press_enter();
                    if (yes != 's' && yes != 'S'){
                        printf("Quante citta' vuoi ingorare?: ");
                        scanf("%d", &dest);
                        press_enter();
                        if (dest) printf("Inserisci le %d citta: ", dest);
                        for(i=0; i<dest; i++){
                            scanf("%d", &id);
                            if(id >= 0 && id < ferrovie->nv) ferrovie->ignore[id] = 1;
                        }
                        press_enter();

                    }
                    list_append(grafi, &(ferrovie));
                }
                printf("Puoi prendere strade a pedaggio? (s/n): ");
                scanf("%c", &yes);
                press_enter();
                if (yes == 's' || yes == 'S'){
                    printf("Per tutte le citta'?(s/n): ");
                    scanf("%c", &yes);
                    press_enter();
                    if (yes != 's' && yes != 'S'){
                        printf("Quante citta' vuoi ingorare?: ");
                        scanf("%d", &dest);
                        press_enter();
                        if (dest) printf("Inserisci le %d citta: ", dest);
                        for(i=0; i<dest; i++){
                            scanf("%d", &id);
                            if(id >= 0 && id < autostrade->nv) autostrade->ignore[id] = 1;
                        }
                        press_enter();

                    }
                    list_append(grafi, &(autostrade));
                }
                list_append(grafi, &(strade));

                printf("Da dove parti? (ID): ");
                scanf("%d",&source);
                press_enter();
                printf("Da dove vorresti arrivare? (ID): ");
                scanf("%d",&dest);
                press_enter();
                printf("Da %s a %s\n\n", mappa_getNomeCitta(map, source), mappa_getNomeCitta(map,dest));

                lista ord = lista_interi();
                lista mez = lista_stringhe();
                if(!grafo_getPathM(grafi, source, dest, 1, &ord, &mez)){
                    list_head(grafi, &graph, FALSE);
                    printf("Dovrai spendere %.1f Euro\n", graph->dist[dest][1]);
                    printf("Ma ci vorranno %.1f Ore\n", graph->dist[dest][0]);
                }
		        mappa_stampaPercorso(map, ord, mez);

                for(i=0; i< strade->nv; i++){
                    strade->ignore[id] = 0;
                    autostrade->ignore[id] = 0;
                    ferrovie->ignore[id] = 0;
                    voli->ignore[id] = 0;
                }
		        lista_cancella(&ord);
		        lista_cancella(&mez);
		        lista_cancella(&grafi);
            }
            else printf("devi prima avere uno scenario iniziale!\n");
            press_enter();
            break;
        case 5:
            if(map)
            {
                printf("\nSelezionare il tipo di collegamento\n");
                printf("\n[1] Aereo\n");
                printf("\n[2] Ferroviario\n");
                printf("\n[3] Autostradale\n");
                printf("\n[4] Stradale\n");
                scanf("%d",&scelta);
                graph=NULL;
                switch (scelta)
                {
                    case 1:
                        graph=grafo_getVoli(map);
                        break;
                    case 2:
                        graph=grafo_getFerrovie(map);
                        break;
                    case 3:
                        graph=grafo_getAutostrade(map);
                        break;
                    case 4:
                        graph=grafo_getStrade(map);
                        break;
                }
                if(graph!=NULL)
                {
                    printf("Inserire Sorgente e Destinazione\n");
                    scanf("%d %d", &source, &dest);
                    grafo_RimuoviArco(graph, source, dest);
                }
            }
            else printf("devi prima avere una mappa!\n");
            press_enter();
            break;
        case 6:
            if(map)
            {
                clear_screen();
                mappa_StampaCitta(map);
                printf("Inserire ID della città da eliminare %p\n", map->Voli);
                scanf("%d", &id);
                mappa_CancellaCitta(map, id);
                clear_screen();
                mappa_StampaCitta(map);
                printf("Fatto\n");
                press_enter();
            }
            else printf("devi prima avere una mappa!\n");
            press_enter();
            break;
        case 7:
            if(map)
            {
                printf("Inserire il nome del file\n");
                scanf("%s",nomeF);
                if( mappa_mapToFile(map, nomeF))
                    printf("Scrittura avvenuta con successo.\n");
                else printf("Scrittura fallita.\n");
            }
            else printf("devi prima avere una mappa!\n");
            press_enter();
            break;
        case 8:
            printf("Inserire il nome del file\n");
            scanf("%s",nomeF);
            mappa_cancella(map);
            map = mappa_mapFromFile(nomeF);
            if(map)
                printf("Import avvenuto con successo.\n");
            else printf("Import fallito\n");
            break;
        case 9:
            if(map)
            {
                do{
                    printf("Inserire Sorgente e Destinazione\n");
                    scanf("%d %d", &source, &dest);
                } while(source < 0 || dest < 0 || source >= map->NumCitta || dest >= map->NumCitta);
                press_enter();
                printf("\nSelezionare il tipo di collegamento\n");
                printf("\n[1] Aereo\n");
                printf("\n[2] Ferroviario\n");
                printf("\n[3] Autostradale\n");
                printf("\n[4] Stradale\n");
                scanf("%d",&scelta);
                graph = NULL;
                dist = (double)citta_Distanza(map->cities[source], map->cities[dest]);
                switch (scelta)
                {
                    case 1:
                        graph = grafo_getVoli(map);
                        tempo = (dist/map->Vel_Aereo);
                        costo = (dist*map->Costo_Aereo);
                        break;
                    case 2:
                        graph = grafo_getFerrovie(map);
                        tempo = (dist/map->Vel_Treno);
                        costo = (dist*map->Costo_Treno);
                        break;
                    case 3:
                        graph = grafo_getAutostrade(map);
                        tempo = (dist/map->Vel_Autostrade);
                        costo = (dist*(map->Costo_Pedaggio + map->Costo_Benzina));
                        break;
                    case 4:
                        graph = grafo_getStrade(map);
                        tempo = dist/map->Vel_Strade;
                        costo = dist*map->Costo_Pedaggio;
                        break;
                }
                if(graph!=NULL)
                {
                    grafo_AggiungiArco(graph, source, dest, 2, tempo, costo);
                    grafo_AggiungiArco(graph, dest, source, 2, tempo, costo);
                }
            }
            else printf("devi prima avere una mappa!\n");
            press_enter();
            break;
        case 10:
            if(map)
            {
                clear_screen();
                mappa_StampaCitta(map);
                printf("\n\nInserire il nome della città da aggiungere: ");
                scanf("%s",nomeF);
                printf("Inserire la coppia di coordinate: ");
                scanf("%d %d", &source, &dest);
                source = source%WORLD_SIZE;
                dest = dest%WORLD_SIZE;
                printf("Inserire il livello: ");
                scanf("%d", &id);
                mappa_AggiungiCitta(map, nomeF, source, dest, id);
                clear_screen();
                mappa_StampaCitta(map);
                printf("Fatto\n");
                press_enter();
            }
            else printf("devi prima avere una mappa!\n");
            press_enter();
            break;
         case 11:
            if(map){
                printf("\nSelezionare il grafo\n");
                printf("\n[1] Aereo\n");
                printf("\n[2] Ferroviario\n");
                printf("\n[3] Autostradale\n");
                printf("\n[4] Stradale\n");
                scanf("%d",&scelta);
                graph = NULL;
                switch (scelta)
                {
                    case 1:
                        graph = grafo_getVoli(map);
                        break;
                    case 2:
                        graph = grafo_getFerrovie(map);
                        break;
                    case 3:
                        graph = grafo_getAutostrade(map);
                        break;
                    default:
                        graph = grafo_getStrade(map);
                        break;
                }
                printf("\n\n");
                grafo_Stampa(graph);
                printf("\n\n");
                press_enter();
            }
            else printf("devi prima avere una mappa!\n");
            press_enter();
            break;
        case 0:
            clear_screen();
            printf("[0] Esci\n\n");
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
    return 0;
}

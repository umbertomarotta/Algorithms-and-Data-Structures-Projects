#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "automobile.h"
#include "coda.h"
#include "strada.h"
#include "rotonda.h"
#include "utils.h"
#include "menu.h"

int main(){
    //Inizializzazione
    srand(time(NULL));
    rotonda rot = NULL;

    //Menu
    int scelta = -1;
    while(scelta != 0){
        clear_screen();
        printf("\n [1] Nuova Rotonda Vuota\n");
        printf("\n [2] Nuova Rotonda Random\n");
        printf("\n [3] Stampa Rotonda\n");
        printf("\n [4] Simula 10 step\n");
        printf("\n [5] Simula N Step\n");
        printf("\n [6] Carica Rotonda (su file)\n");
        printf("\n [7] Salva Rotonda (su file)\n");
        printf("\n [8] Inserisci Strade\n");
        printf("\n [9] Inserisci Strade Random\n");
        printf("\n [10] Cancella Strada\n");
        printf("\n [11] Inserisci Auto\n");
        printf("\n [12] Inserisci Auto Random\n");
        printf("\n [13] Modifica Auto\n");
        printf("\n [14] Cancella Auto\n");
        printf("\n [0] Esci\n\n");
        printf("Scegli: ");
        scanf("%d",&scelta);
        press_enter();
        switch (scelta) {
        case 1:
            rot = menu_nuova_rotonda_vuota(rot);
            break;
        case 2:
            rot = menu_nuova_rotonda_random(rot);
            break;
        case 3:
            menu_stampa_rotonda(rot);
            break;
        case 4:
            menu_simula_10_step(rot);
            break;
        case 5:
            menu_simula_N_step(rot);
            break;
        case 6:
            rot = menu_carica_rotonda(rot);
            break;
        case 7:
            menu_salva_rotonda(rot);
            break;
        case 8:
            menu_inserisci_strade(rot);
            break;
        case 9:
            menu_inserisci_strade_random(rot);
            break;
        case 10:
            menu_cancella_strada(rot);
            break;
        case 11:
            menu_inserisci_auto(rot);
            break;
        case 12:
            menu_inserisci_auto_random(rot);
            break;
        case 13:
            menu_modifica_auto(rot);
            break;
        case 14:
            menu_cancella_auto(rot);
            break;
        case 0:
            clear_screen();
            printf("\n[0] Esci\n\n");
            printf("Arrivederci!\n");
            break;
        default:
            clear_screen();
            menu_feature_segreta();
            press_enter();
            break;
        }
    }
    if(rot) cancella_rotonda(rot);
    return 0;
}

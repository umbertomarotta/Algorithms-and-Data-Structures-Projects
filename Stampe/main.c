#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "job.h"
//#include "stampe.h"
//#include "pc.h"
//#include "heap.h"
#include "infrastruttura.h"
#include "utils.h"

int main(){
    srand(time(NULL));
    infrastruttura system = NULL;
    int scelta = -1;
    while(scelta != 0){
        clear_screen();
        printf("\n [1] Genera scenario random (n pc, 2^n jobs)\n");
        printf("\n [2] Simula\n");
        printf("\n [3] Stampa scenario corrente\n");
        printf("\n [4] Modifica priorità di un pc\n");
        printf("\n [5] Inserisci job in un pc\n");
        printf("\n [6] Cancella job da un pc\n");
        printf("\n [0] Esci\n\n");
        printf("Scegli: ");
        scanf("%d",&scelta);
        press_enter();
        switch (scelta) {
        case 1:
            dealloca_infr(system);
            system = get_random_system();
            break;
        case 2:
            if(system!=NULL){
                simulate_fast(system);
            }
            else printf("devi prima avere uno scenario iniziale!\n");
            press_enter();
            break;
        case 3:
            if(system!=NULL){
                stampa_coda(system);
            }
            else printf("devi prima avere uno scenario iniziale!\n");
            press_enter();
            break;
        case 4:
            if(system!=NULL)
                update_priority_I(system);
            break;
        case 5:
            if(system!=NULL)
                insert_job_pc_I(system);
            break;
        case 6:
            if(system!=NULL)
                delete_job_I(system);
            break;
        /*case 7:
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
            break;*/
        case 0:
            clear_screen();
            printf("\n[0] Esci\n\n");
            printf("Arrivederci!\n");
            break;
      /*  default:
            clear_screen();
            menu_feature_segreta();
            press_enter();
            break;*/
        }
    }
    if(system!=NULL) dealloca_infr(system);
    return 0;
}

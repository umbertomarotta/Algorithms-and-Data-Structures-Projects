#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "automobile.h"
#include "coda.h"
#include "strada.h"
#include "rotonda.h"
#include "utils.h"
#include "menu.h"

#if defined POSIX
  #define CLEARSCR system ( "clear" )
#elif defined MSDOS || defined WIN32
  #define CLEARSCR system ( "cls" )
#else
  #define CLEARSCR system ( "clear" )
#endif

rotonda menu_nuova_rotonda_vuota(rotonda rot){
    CLEARSCR;
    printf("\n[1] Nuova Rotonda Vuota\n\n");
    if (rot != NULL) cancella_rotonda(rot);
    rot = nuova_rotonda();
    printf("La rotonda e' stata creata\n");
    press_enter();
    return rot;
}

rotonda menu_nuova_rotonda_random(rotonda rot){
    CLEARSCR;
    int brum, strade;
    printf("\n[2] Nuova Rotonda Random\n\n");
    if (rot != NULL) cancella_rotonda(rot);
    printf("Numero automobili coinvolte: ");
    scanf("%d",&brum);
    printf("Numero uscite della rotonda: ");
    scanf("%d",&strade);
    rot = random_rotonda(brum, strade);
    return rot;
}

rotonda menu_carica_rotonda(rotonda rot){
    char nomeF[DIM];
    rotonda tmp;
    CLEARSCR;
    printf("\n[6] Carica Rotonda (da file)\n\n");
    printf("\nInserisci il nome del file: ");
    scanf("%s", nomeF);
    press_enter();
    tmp = fleggi_rotatoria(nomeF);
    if (!tmp){
        CLEARSCR;
        printf("\n[6] Carica Rotonda (da file)\n\n");
        printf("\nFile non trovato\n");
        press_enter();
        return rot;
    }
    if (rot != NULL) cancella_rotonda(rot);
    return tmp;
}

void menu_salva_rotonda(rotonda rot){
    char nomeF[DIM];
    CLEARSCR;
    printf("\n[7]Salva Rotonda su file\n\n");
    if (rot == NULL){
        printf("Devi prima averla una Rotonda\n");
        press_enter();
        return;
    }
    printf("\nInserisci il nome del file: ");
    scanf("%s",nomeF);
    fout_rotatoria(rot,nomeF);
}

void menu_stampa_rotonda(rotonda rot){
    CLEARSCR;
    printf("\n[3] Stampa Rotonda\n\n");
    if (rot != NULL){
        stampa_rotonda(rot);
        press_enter();
    }
    else{
        printf("Devi prima averla una Rotonda\n");
        press_enter();
    }
}

void menu_simula_10_step(rotonda rot){
    CLEARSCR;
    printf("\n[4] Simula 10 step\n\n");
    if (rot != NULL){
        int i;
        for(i=0; i<10; i++){
            CLEARSCR;
            printf("\n[4] Simula 10 step\n\n");
            printf("Numero Step: %d\n", i+1);
            stampa_rotonda(rot);
            step_rotonda(rot, 2);
        }
        press_enter();
    }
    else{
        printf("Devi prima averla una Rotonda\n");
        press_enter();
    }
}

void menu_simula_N_step(rotonda rot){
    CLEARSCR;
    printf("\n[5] Simula N step\n\n");
    int step, secondi, i;
    if (rot != NULL){
        printf("Numero step (0 = svuotamento): ");
        scanf("%d",&step);
        press_enter();
        printf("Secondi per step (0 = manuale): ");
        scanf("%d",&secondi);
        press_enter();
        for(i=0; i<step; i++){
            CLEARSCR;
            printf("\n[5] Simula N step\n\n");
            printf("Numero Step: %d\n", i+1);
            stampa_rotonda(rot);
            step_rotonda(rot, secondi);
            if (!secondi) press_enter();
        }
        if (!step){
            i=0;
            while(!rotonda_vuota(rot)){
                CLEARSCR;
                printf("\n[5] Simula N step\n\n");
                printf("Numero Step: %d\n", i+1);
                stampa_rotonda(rot);
                step_rotonda(rot, secondi);
                if (!secondi) press_enter();
                i++;
            }
        }
        CLEARSCR;
        printf("\n[5] Simula N step\n\n");
        printf("Finito!\n");
        stampa_rotonda(rot);
        press_enter();
    }
    else{
        printf("Devi prima averla una Rotonda\n");
        press_enter();
    }
}

void menu_inserisci_strade(rotonda rot){
    CLEARSCR;
    printf("\n[8] Inserisci Strade\n\n");
    int strade, brum;
    if (rot == NULL){
        printf("Devi prima averla una Rotonda\n");
        press_enter();
        return;
    }
    stampa_rotonda(rot);
    printf("\nNumero strade da inserire: ");
    scanf("%d",&strade);
    press_enter();
    strade = strade%(DIM - get_numero_strade(rot));
    int i;
    for(i=0; i < strade; i++){
        CLEARSCR;
        printf("\n[8] Inserisci Strade\n\n");
        stampa_rotonda(rot);
        printf("\nPosizione: ");
        scanf("%d",&brum);
        press_enter();
        if(!inserisci_strada(rot, brum)){
            printf("C'e' gia' una strada li'");
            press_enter();
            i--;
        }
    }
    CLEARSCR;
    printf("\n[8] Inserisci Strade\n\n");
    stampa_rotonda(rot);
    printf("\nFatto");
    press_enter();
}

void menu_inserisci_strade_random(rotonda rot){
    CLEARSCR;
    printf("\n[8] Inserisci Strade\n\n");
    int strade;
    if (rot == NULL){
        printf("Devi prima averla una Rotonda\n");
        press_enter();
        return;
    }
    stampa_rotonda(rot);
    printf("\nNumero strade da inserire: ");
    scanf("%d",&strade);
    press_enter();
    strade = strade%(DIM - get_numero_strade(rot));
    while(strade) if (inserisci_strada(rot, rand()%DIM)) strade--;
    CLEARSCR;
    printf("\n[8] Inserisci Strade\n\n");
    stampa_rotonda(rot);
    printf("\nFatto");
    press_enter();
}

void menu_inserisci_auto(rotonda rot){
    CLEARSCR;
    printf("\n[11] Inserisci Auto\n\n");
    if (rot == NULL || !get_numero_strade(rot)){
        printf("Devi prima una Rotonda con delle strade\n");
        press_enter();
        return;
    }
    stampa_rotonda(rot);
    char lett; int i, num, id, dest;

    printf("\nNumero auto da inserire: ");
    scanf("%d",&num);
    press_enter();
    for(i=0; i<num; i++){
        CLEARSCR;
        printf("\n[11] Inserisci Auto\n\n");
        stampa_rotonda(rot);
        id = rotonda_nextval(rot);
        printf("\nDestinazione Auto Numero %d: ", id+1);
        scanf("%d",&dest);
        press_enter();
        automobile car = nuova_auto(dest-1, id);
        do{
            printf("\nLettera Strada (Maiuscolo): ");
            scanf("%c",&lett);
            press_enter();
        } while (!inserisci_auto_strada(rot,car, lett));
    }
    CLEARSCR;
    printf("\n[11] Inserisci Auto\n\n");
    stampa_rotonda(rot);
    printf("\nFatto!\n");
    press_enter();
}

void menu_inserisci_auto_random(rotonda rot){
    CLEARSCR;
    printf("\n[12] Inserisci Auto Random\n\n");
    if (rot == NULL){
        printf("Devi prima averla una Rotonda\n");
        press_enter();
        return;
    }
    stampa_rotonda(rot);
    /*------------------------------------------*/
    int num;
    printf("\nNumero auto da inserire: ");
    scanf("%d",&num);
    press_enter();
    int ok = accoda_auto_rotonda_random(rot, num);
    CLEARSCR;
    printf("\n[10] Cancella Strada\n\n");
    stampa_rotonda(rot);
    if (!ok) printf("\nNessuna strada non trovata\n");
    else printf("\nFatto!\n");
    press_enter();
}

void menu_modifica_auto(rotonda rot){
    CLEARSCR;
    printf("\n[13] Modifica Auto\n\n");
    if (rot == NULL){
        printf("Devi prima averla una Rotonda\n");
        press_enter();
        return;
    }
    stampa_rotonda(rot);
    /*------------------------------------------*/
    int id, dest;
    printf("\nAuto Numero: ");
    scanf("%d",&id);
    press_enter();
    automobile car = cerca_auto(rot, id-1);
    if(car){
        printf("\nNuovo Numero Auto (ID): ");
        scanf("%d",&id);
        press_enter();
        printf("\nNuova Destinazione Auto (Numero uscita): ");
        scanf("%d",&dest);
        press_enter();
        set_id_auto(car, id-1);
        set_dest_auto(car,dest-1);
        CLEARSCR;
        printf("\n[13] Modifica Auto\n\n");
        stampa_rotonda(rot);
        printf("\nFatto!\n");
        press_enter();
    }
    else{
        printf("\nAuto non trovata\n");
        press_enter();
    }
}

void menu_cancella_auto(rotonda rot){
    clear_screen();
    printf("\n[14] Cancella Auto\n");
    if(rot==NULL){
        printf("Devi prima averla una Rotonda\n");
        press_enter();
        return;
    }
    stampa_rotonda(rot);
    int ID;
    printf("\nID auto da cancellare: ");
    scanf("%d",&ID);
    press_enter();
    if(cancella_auto_rotonda(rot,ID-1))
    {
        clear_screen();
        printf("\n[14] Cancella Auto\n");
        stampa_rotonda(rot);
        printf("\nAuto cancellata!");
        press_enter();
        clear_screen();
    }
    else
    {
        printf("\nAuto non cancellata");
        press_enter();
    }

}

void menu_cancella_strada(rotonda rot){
    CLEARSCR;
    printf("\n[10] Cancella Strada\n\n");
    if (rot == NULL){
        printf("Devi prima averla una Rotonda\n");
        press_enter();
        return;
    }
    stampa_rotonda(rot);
    char brum; int ok;
    printf("\nLettera Strada (Maiuscolo): ");
    scanf("%c",&brum);
    press_enter();
    ok = cancella_strada_rotonda(rot, brum);
    CLEARSCR;
    printf("\n[10] Cancella Strada\n\n");
    stampa_rotonda(rot);
    if (!ok) printf("\nStrada non trovata\n");
    else printf("\nFatto!\n");
    press_enter();

}

void menu_feature_segreta(){
    printf("\nKING IL CAVALIERE IMPEDISCE\nOGNI INPUT ILLEGALE\n\n");
    printf("                  {}\n");
    printf("  ,   A           {}\n");
    printf(" / \\, | ,        .--.\n");
    printf("|  =|= >        /.--.\\\n");
    printf(" \\ /` | `       |====|\n");
    printf("  `   |         |`::`|\n");
    printf("      |     .-;`\\..../`;_.-^-._\n");
    printf("     /\\\\/  /  |...::..|`   :   `|\n");
    printf("     |:'\\ |   /'''::''|   .:.   |\n");
    printf("      \\ /\\;-,/\\   ::  |..ASCII..|\n");
    printf("      |\\ <` >  >._::_.| ':ART:' |\n");
    printf("      | `""`_/   ^^/>/>  |   ':'   |\n");
    printf("      |       |       \\    :   /\n");
    printf("      |       |        \\   :   /\n");
    printf("      |       |___/\\___|`-.:.-`\n");
    printf("      |        \\_ || _/    `\n");
    printf("      |        <_ >< _>\n");
    printf("      |        |  ||  |\n");
    printf("      |        |  ||  |\n");
    printf("      |       _\\.:||:./_\n");
    printf("      |      /____/\\____\\\n");
    printf("\n");
}


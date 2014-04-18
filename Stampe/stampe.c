#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "job.h"
#include "stampe.h"

struct sstampa{
    job cont;
    struct sstampa *sx;
    struct sstampa *dx;
};

stampa nuova_stampa(job cont){
    stampa brum = (stampe)malloc(sizeof(struct sstampe));
    brum->cont = cont;
    brum->sx = NULL;
    brum->dx = NULL;
    return brum;
}

stampa nuova_stampa_random(stampa alb, int num, int max){
    if (!max) return alb;
    while(num){
        alb = inserisci_stampa(alb, nuova_stampa(nuovo_job(rand()%max)));
        num--;
    }
    return alb;
}

stampa cerca_job_stampa(stampa nodo, int jobid){
    if(!nodo) return NULL;
    if(nodo->cont && get_id_job(nodo->cont) > jobid) return cerca_job_stampa(nodo->sx,jobid);
    if(nodo->cont && get_id_job(nodo->cont) < jobid) return cerca_job_stampa(nodo->dx,jobid);
    if(nodo->cont && get_id_job(nodo->cont) == jobid) return nodo;
    stampa tmp = cerca_job_stampa(nodo->sx,jobid);
    if(tmp) return tmp;
    else return cerca_job_stampa(nodo->dx,jobid);
}

stampa cancella_job_stampa(stampa nodo, int jobid){
    if(!nodo) return NULL;
    if(nodo->cont && get_id_job(nodo->cont) > jobid) nodo->sx = cancella_job_stampa(nodo->sx,jobid);
    if(nodo->cont && get_id_job(nodo->cont) < jobid) nodo->dx = cancella_job_stampa(nodo->dx,jobid);
    if(nodo->cont && get_id_job(nodo->cont) == jobid){
        if(!nodo->sx && !nodo->dx){
            cancella_stampa(nodo);
            return NULL;
        }
        else if(nodo->sx && !nodo->dx){
            stampa ret = nodo->sx
            nodo->sx = NULL;
            cancella_stampa(nodo);
            return ret;
        }
        else if(!nodo->sx && nodo->dx){
            stampa ret = nodo->dx
            nodo->dx = NULL;
            cancella_stampa(nodo);
            return ret;
        }
        else{
            stampa min = staccamin(nodo->dx, nodo);
            cancella_job(nodo->cont);
            cont = min->cont;
            min->cont = NULL;
            cancella_stampa(min);
            return nodo;
        }
    }
    if(!nodo->cont){
        nodo->sx = cancella_job_stampa(nodo->sx,jobid);
        nodo->dx = cancella_job_stampa(nodo->dx,jobid);
    }
    return nodo;
}

stampa staccamin(stampa nodo, stampa padre){
    if(!nodo || !padre) return NULL;
    if(nodo->sx) return staccamin(nodo->sx, nodo);
    if(padre->sx == nodo) padre->sx = nodo->dx;
    if(padre->dx == nodo) padre->dx = nodo->dx;
    nodo->dx = NULL;
    return nodo;
}

stampa pop_stampa(stampa *nodo){
    if(!(*nodo)) return NULL;
    if((*nodo)->sx) return staccamin((*nodo)->sx, (*nodo));
    stampa ret = (*nodo);
    (*nodo) = (*nodo)->dx;
    return ret;
}

stampa inserisci_stampa(stampa albero, stampa nodo){
    if(!albero) return nodo;
    if(!nodo || !nodo->cont) return albero;
    if(albero->cont && get_id_job(albero->cont) >= get_id_job(nodo->cont))
        albero->sx = inserisci_stampa(albero->sx, nodo);
    if(albero->cont && get_id_job(albero->cont) < get_id_job(nodo->cont))
        albero->dx = inserisci_stampa(albero->dx, nodo);
    if (!albero->cont) albero->sx = inserisci_stampa(albero->sx, nodo);
    return albero;
}

stampa cerca_inserisci_job_stampa(stampa *nodo, int jobid){
    if(!(*nodo)) {
        (*nodo) = nuova_stampa(nuovo_job(jobid));
        return NULL;
    }
    if((*nodo)->cont && get_id_job((*nodo)->cont) > jobid) return cerca_inserisci_job_stampa(&((*nodo)->sx),jobid);
    if((*nodo)->cont && get_id_job((*nodo)->cont) < jobid) return cerca_inserisci_job_stampa(&((*nodo)->dx),jobid);
    if((*nodo)->cont && get_id_job((*nodo)->cont) == jobid) return nodo;
    stampa ret = cerca_job_stampa((*nodo)->dx, jobid);
    if(!ret) return cerca_inserisci_job_stampa(&((*nodo)->sx),jobid);
    else return ret;
}

int cancella_stampa(stampa nodo){
    if (!nodo) return 0;
    cancella_stampa(nodo->sx);
    cancella_stampa(nodo->dx);
    cancella_job(nodo->cont);
    free(nodo);
    return 1;
}

int stampa_stampe(stampa alb){
    return Istampa_stampe(alb, 0);
}

int Istampa_stampe(stampa alb, int liv){
    if (!alb) return 0;
    Istampa_stampe(alb->sx, liv + 1);
    printf("(%d)", liv);
    stampa_job(alb->cont);
    printf(" ");
    Istampa_stampe(alb->dx, liv + 1);
    return 1;
}

stampa stampa_stampe_ex(stampa alb, stampa story){
    return Istampa_stampe_ex(alb, story, 0);
}

stampa Istampa_stampe_ex(stampa alb, stampa story, int liv){
    if (!alb) return story;
    story = Istampa_stampe_ex(alb->sx, story, liv + 1);
    if(alb->cont && !cerca_job_stampa(story, get_id_job(alb->cont))){
        story = inserisci_stampa(story, nuova_stampa(nuovo_job(get_id_job(alb->cont))));
        printf("(%d)", liv);
        stampa_job(alb->cont);
        printf(" ");
    }
    story = Istampa_stampe_ex(alb->dx, story, liv + 1);
    return story;
}

int is_abr(stampa alb){
    return I_is_abr(alb, INT_MAX, INT_MIN);
}

int I_is_abr(stampa alb, int maxx, int minn){
    if (!alb) return 1;
    if (!alb->cont) return 0;
    if (get_id_job(alb->cont) < minn || get_id_job(alb->cont) > maxx) return 0;
    return I_is_abr(alb->sx, minn, get_id_job(alb->cont)) && I_is_abr(alb->dx, get_id_job(alb->cont), maxx);
}








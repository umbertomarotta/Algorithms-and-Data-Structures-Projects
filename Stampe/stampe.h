#include "job.h"

typedef struct sstampa* stampa;

stampa nuova_stampa(job cont);
stampa nuova_stampa_random(stampa alb, int num, int max);
stampa cerca_job_stampa(stampa nodo, int jobid);
stampa cancella_job_stampa(stampa nodo, int jobid);
stampa staccamin(stampa nodo, stampa padre);
stampa pop_stampa(stampa *nodo);
stampa inserisci_stampa(stampa albero, stampa nodo);
stampa cerca_inserisci_job_stampa(stampa *nodo, int jobid);
int cancella_stampa(stampa nodo);
int stampa_stampe(stampa alb);
stampa stampa_stampe_ex(stampa alb, stampa story);
stampa Istampa_stampe_ex(stampa alb, stampa story, int liv);
int is_abr(stampa alb);
int I_is_abr(stampa alb, int maxx, int minn);
int Istampa_stampe(stampa alb, int liv);

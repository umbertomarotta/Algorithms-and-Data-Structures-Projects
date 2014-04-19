#include "job.h"

typedef struct sstampa* stampa;

stampa nuova_stampa(job cont);
stampa nuova_stampa_random(stampa alb, int num, int max);
stampa cerca_job_stampa(stampa nodo, int jobid);
stampa cancella_job_stampa(stampa nodo, int jobid);
stampa staccamin(stampa nodo, stampa padre);
stampa pop_stampa(stampa *nodo);
stampa inserisci_stampa_testa(stampa albero, stampa nodo);
stampa inserisci_stampa(stampa albero, stampa nodo);
stampa cerca_inserisci_job_stampa(stampa *nodo, long jobid);
int cancella_stampa(stampa nodo);
int stampa_stampe(stampa alb);
<<<<<<< HEAD
stampa stampa_stampe_ex(stampa alb, stampa story, int mute);
stampa Istampa_stampe_ex(stampa alb, stampa story, int liv, int mute);
=======
stampa stampa_stampe_ex(stampa alb, stampa story);
stampa Istampa_stampe_ex(stampa alb, stampa story, int liv);
>>>>>>> 7cbdc228d3de5c716c6f6928d51215cd2cc37968
int is_abr(stampa alb);
int I_is_abr(stampa alb, int maxx, int minn);
int Istampa_stampe(stampa alb, int liv);

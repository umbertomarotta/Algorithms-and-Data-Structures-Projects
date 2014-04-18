
typedef struct sstampa* stampa;

stampa nuova_stampa(job cont);
stampa cerca_job_stampa(stampa nodo, int jobid);
stampa cancella_job_stampa(stampa nodo, int jobid);
stampa staccamin(stampa nodo, stampa padre);
stampa inserisci_stampa(stampa albero, stampa nodo);
int cancella_stampa(stampa nodo);
int stampa_stampe(stampa alb);
int is_abr(stampa alb);



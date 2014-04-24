
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
stampa stampa_stampe_ex(stampa alb, stampa story, int mute);
stampa Istampa_stampe_ex(stampa alb, stampa story, int liv, int mute);
stampa stampa_stampe_lim(stampa alb, stampa story, int lim);
stampa Istampa_stampe_lim(stampa alb, stampa story, int dd, int visite, int start, int lim);
int is_abr(stampa alb);
int I_is_abr(stampa alb, int maxx, int minn);
int Istampa_stampe(stampa alb, int liv);
int get_num_stampe(stampa curr);
int stampa_stampe_totlim(stampa alb, int lim);
int Istampa_stampe_totlim(stampa alb, stampa rad, int dd, int visite, int lim);

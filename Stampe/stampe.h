

struct sstampa{
    job cont;
    int n_nodi;
    struct sstampa *sx;
    struct sstampa *dx;
};
typedef struct sstampa* stampa;

struct ssteck{
    stampa cont;
    struct ssteck *next;
};
typedef struct ssteck* steck;

/*Funzioni Pubbliche*/
stampa nuova_stampa(job cont);
stampa nuova_stampa_random(stampa alb, int num, int max);
stampa cerca_job_stampa(stampa nodo, int jobid);
stampa cancella_job_stampa(stampa nodo, int jobid);
stampa inserisci_stampa(stampa albero, stampa nodo);
stampa cerca_inserisci_job_stampa(stampa *nodo, int jobid);
stampa stampa_stampe_lim(stampa alb, stampa story, int lim);
int stampa_stampe_totlim(stampa alb, int lim);
int cancella_stampa(stampa nodo);
int is_abr(stampa alb);
int get_num_stampe(stampa curr);
stampa cerca_inserisci_job_stampa_iterative(stampa *nodo, int jobid);
stampa stampa_stampe_lim_iterative(stampa alb, stampa story, int lim);
void stampa_stampe_lim_fast(stampa alb, int story[], long long dimstory, int lim);

/*Funzioni Accessorie*/
void inserisci_stampa_fast(stampa albero, stampa nodo);
stampa staccamin(stampa nodo, stampa padre);
int I_is_abr(stampa alb, int maxx, int minn);
int Istampa_stampe_totlim(stampa alb, stampa rad, int dd, int visite, int lim);
stampa Istampa_stampe_lim(stampa alb, stampa story, int dd, int visite, int start, int lim);
stampa Istampa_stampe_lim_iterative(stampa alb, stampa story, int dd, int visite, int start, int lim);
void Istampa_stampe_lim_fast(stampa alb, int story[], long long dimstory, int dd, int visite, int start, int lim);

/*Stack*/
steck nuovo_steck(stampa cont);
steck spush_stampa(steck st, stampa nodo);
stampa spop_stampa(steck *nodo);

/*Funzioni di Sviluppo*/
//stampa inserisci_stampa_testa(stampa albero, stampa nodo);
//stampa pop_stampa(stampa *nodo);
//int stampa_stampe(stampa alb);
//stampa stampa_stampe_ex(stampa alb, stampa story, int mute);
//stampa Istampa_stampe_ex(stampa alb, stampa story, int liv, int mute);
//int Istampa_stampe(stampa alb, int liv);

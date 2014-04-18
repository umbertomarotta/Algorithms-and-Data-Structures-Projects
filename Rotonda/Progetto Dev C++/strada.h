
typedef struct sstrada* strada;

strada nuova_strada(char nom, coda que);
automobile decoda_auto_strada(strada brum);
int cancella_strada(strada brum);
int cancella_auto_strada(strada road, int ID);
int accoda_auto_strada(strada brum, automobile car);
char get_nome_strada(strada brum);
coda get_inizio_strada(strada brum);
int set_nome_strada(strada brum, char nom);

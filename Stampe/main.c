#include <stdio.h>
#include <stdlib.h>
#include <time.h>
<<<<<<< HEAD
//#include "job.h"
//#include "stampe.h"
//#include "pc.h"
//#include "heap.h"
=======
>>>>>>> 7cbdc228d3de5c716c6f6928d51215cd2cc37968
#include "infrastruttura.h"
#include "utils.h"

int main(){
<<<<<<< HEAD
    srand(time(NULL));
    //aspetta(1);
    //printf("0");
    infrastruttura system = get_random_system();
    //printf("1");
=======
    printf("cazzo");
    aspetta(1);
    infrastruttura system = get_random_system();
>>>>>>> 7cbdc228d3de5c716c6f6928d51215cd2cc37968
    simulate(system);
    return 0;
}

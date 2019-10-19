/**/
#include <stdio.h>
#include "function.h"
#include "lista.h"



int main(int argc, char *argv[]){
 //int
 relation Rr_1, Rr_2;
 relation Ss_1, Ss_2;

 Rr_1.num_tuples = 100;	////
 Rr_1.tuples = malloc(Rr_1.num_tuples * sizeof(tuple));
 if(Rr_1.tuples == NULL){
     printf("Error malloc Rr_1.tuples");
     return -1;
 }

 Rr_2.num_tuples = 100; ////
 Rr_2.tuples = malloc(Rr_2.num_tuples * sizeof(tuple));
 if(Rr_2.tuples == NULL){
     printf("Error malloc Rr_2.tuples");
     return -1;
 }



 Ss_1.num_tuples = 100; ////
 Ss_1.tuples = malloc(Ss_1.num_tuples * sizeof(tuple));
 if(Ss_1.tuples == NULL){
     printf("Error malloc Ss_1.tuples");
     return -1;
 }

 Ss_2.num_tuples = 100; ////
 Ss_2.tuples = malloc(Ss_2.num_tuples * sizeof(tuple));
 if(Ss_2.tuples == NULL){
     printf("Error malloc Ss_2.tuples");
     return -1;
 }
 //  mporoume ta parapanw na ta kanoume se sinartisi
 //  tha prepei na einai deiktes omws
 //  create_init_relations(&Rr_1, &Rr_2, &Ss_1, &Ss_2);












    free(Rr_1.tuples);
    free(Rr_2.tuples);
    free(Ss_1.tuples);
    free(Ss_2.tuples);

    return 0;
}

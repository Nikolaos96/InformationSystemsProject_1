/**/
#include <stdio.h>
#include "function.h"
#include "lista.h"
#include "stack.h"


int main(int argc, char *argv[]){
   relation *Rr_1, *Rr_2;
   relation *Ss_1, *Ss_2;
   int *hist, *p_sum;
   int r_size = 1000, s_size = 2000;
   int i;

   create_init_relations(&Rr_1, &Rr_2, &Ss_1, &Ss_2, r_size, s_size);


   hist = malloc(256 * sizeof(int));
   if(hist == NULL){
       printf("Error malloc hist \n");
       return -1;
   }
   p_sum = malloc(256 * sizeof(int));
   if(p_sum == NULL){
       printf("Error malloc p_sum \n");
       return -1;
   }

   make_hist(&Rr_1, r_size, &hist[0], 256);
   make_p_sum(&hist[0], 256, &p_sum[0], 256);

   make_Rr_2(&Rr_1, &Rr_2, r_size, &p_sum[0], 256);



   for(i = 0 ; i < 60 ; i++) printf("%ld \n", Rr_2->tuples[i].key);

   printf("\n\n");

   for(i = 0 ; i < 10 ; i++) printf("%d \n", hist[i]);



















    free(hist);
    free(p_sum);
    free(Rr_1->tuples);
    free(Rr_1);
    free(Rr_2->tuples);
    free(Rr_2);
    free(Ss_1->tuples);
    free(Ss_1);
    free(Ss_2->tuples);
    free(Ss_2);

    return 0;
}

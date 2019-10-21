/* main.c */
#include <stdio.h>
#include "function.h"
#include "lista.h"
#include "stack.h"

#define  MAX_BUCKET_SIZE 5		// kanonika 4096



int main(int argc, char *argv[]){
   relation *Rr_1, *Rr_2;
   relation *Ss_1, *Ss_2;
   int *hist, *p_sum;
   int r_size = 1000, s_size = 1000;
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


/*
   for(i = 0 ; i < 70 ; i++) printf("%ld \n", Rr_2->tuples[i].key);
   printf("\n\n");
   for(i = 0 ; i < 10 ; i++) printf("%d \n", hist[i]);
*/

   int hist_value, start_bucket, end_bucket;
   for(int i = 0 ; i < 256 ; i++){

       if(hist[i] > MAX_BUCKET_SIZE){
	   hist_value = hist[i];
	   start_bucket = p_sum[i] - hist_value;   	// start_bucket = hist[i]
	   end_bucket = start_bucket + hist_value - 1; 	// end_bucket = p_sum[i]
	   //printf("start  %d \n", start_bucket);
	   //printf("end    %d \n", end_bucket);
       }


   }








   //info_deikti list;
   //list = LIST_dimiourgia(&list);
   //Sort_Merge_Join(...................., &list);
   // emfanisi(list);
   //lista_diagrafi(&list);

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

/* main.c */
#include <stdio.h>
#include "function.h"
#include "lista.h"
#include "stack.h"
#include <limits.h>

#define  MAX_BUCKET_SIZE 5		// kanonika 4096



int main(int argc, char *argv[]){
   relation *Rr_1, *Rr_2;
   relation *Ss_1, *Ss_2;
   uint64_t **main_R, **main_S; // megethos 500 kai oi duo

   int r_size = 500, s_size = 500;
   int i;


   create_init_relations(&Rr_1, &Rr_2, &Ss_1, &Ss_2, r_size, s_size, &main_R, &main_S);



	recurseFunc(&Rr_1, &Rr_2, 0, r_size, 7);
  //quickSort(&Rr_1,0,499);


   for(int i=0;i<r_size;i++) {
      // printf("%lu\n",  (Rr_2->tuples[i].key >> (8*7)) & 0xff );
		printf("%lu\n",  Rr_1->tuples[i].key );
   }

//   for(int i=0;i<r_size;i++) {
      // printf("%lu\n",  (Rr_2->tuples[i].key >> (8*7)) & 0xff );
//                printf("%lu\n",  Rr_2->tuples[i].key );
//   }


   //info_deikti list;
   //list = LIST_dimiourgia(&list);
   //Sort_Merge_Join(...................., &list);
   // emfanisi(list);
   //lista_diagrafi(&list);



    // ola ta free na mpoun se sinartisi
    //
    // free main_R
    // free main_S

    free(Rr_1->tuples);
    free(Rr_1);

    free(Rr_2->tuples);	///////
    free(Rr_2);		///////

    free(Ss_1->tuples);	//
    free(Ss_1);		//

    free(Ss_2->tuples);
    free(Ss_2);

    return 0;
}

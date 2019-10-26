/* main.c */
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
   recurseFunc(&Ss_1, &Ss_2, 0, s_size, 7);


   for(int i=0 ; i < r_size ; i++) printf("%lu\n",  Rr_1->tuples[i].key );
   printf("\n\n\n");
   for(int i=0 ; i < s_size ; i++) printf("%lu\n",  Ss_1->tuples[i].key );


   //info_deikti list = NULL;
   //list = LIST_dimiourgia(&list);
   //Sort_Merge_Join(...................., &list);
   // emfanisi(list);
   //lista_diagrafi(&list);


    //delete_all_array(&main_R, &Rr_1, &Rr_2, r_size, &main_S, &Ss_1, &Ss_2, s_size);

    return 0;
}

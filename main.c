/* main.c */
#include "function.h"
#include "lista.h"



int main(int argc, char *argv[]){
   relation *Rr_1, *Rr_2;
   relation *Ss_1, *Ss_2;
   char *table_R, *table_S;
   int r_size, s_size, i;
   clock_t time;


   // take all arguments from command line and init variables
   take_arguments(argc, argv, &table_R, &r_size, &table_S, &s_size);

   // create main relations
   create_init_relations(&Rr_1, &Rr_2, &Ss_1, &Ss_2, r_size, s_size, table_R, table_S);


   // time before sort arrays and join
   time = clock();
   // recurse function for sort the relation Rr_1
   recurseFunc(&Rr_1, &Rr_2, 0, r_size, 7);
   // recurse function for sort the relation Ss_1
   recurseFunc(&Ss_1, &Ss_2, 0, s_size, 7);

   //for(int i=0 ; i < r_size ; i++) printf("%lu\n",  Rr_1->tuples[i].key );
   //for(int i=0 ; i < s_size ; i++) printf("%lu\n",  Ss_1->tuples[i].key );


   // create list for results
   info_deikti list = NULL;
   list = LIST_dimiourgia(&list);

   // join function for relations Rr_1 and Ss_1
   Sort_Merge_Join(&Rr_1, r_size, &Ss_1, s_size, &list);     ///  exei ena provlima edw
   //join(&Rr_1, r_size, &Ss_1, s_size, &list);


   // time after sort arrays and join
   time = clock() - time;

   // print results and cpu time
   emfanisi(&list);
   printf("\nCpu time is  %lf  seconds. \n", ((double)time) / CLOCKS_PER_SEC);

   // delete all relations and list
   lista_diagrafi(&list);
   delete_all_array(&Rr_1, &Rr_2, r_size, &Ss_1, &Ss_2, s_size, &table_R, &table_S);

   return 0;
}

/* main.c */
#include "function.h"
#include "lista.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

   relation *Rr_1, *Rr_2;
   relation *Ss_1, *Ss_2;
   char *table_R, *table_S;
   int r_size, s_size, i;
   


    int test_sorting(relation **Rr_1, int size){
        for(int i = 0; i < size-1; i++) {
            if( (*Rr_1)->tuples[i].key > (*Rr_1)->tuples[i+1].key )
			return 0;
        }
	    return 1;
    }

    void test(void){
		CU_ASSERT( test_sorting( &Rr_1, r_size ) == 1 );
		CU_ASSERT( test_sorting( &Ss_1, s_size ) == 1);	
    }



int main(int argc, char *argv[]){
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
   //quickSort(&Rr_1, 0, r_size - 1);
   //quickSort(&Ss_1, 0, s_size - 1);

    //  for(int i=0 ; i < r_size ; i++) printf("%lu\n",  Rr_1->tuples[i].key );
   //   for(int i=0 ; i < s_size ; i++) printf("%lu\n",  Ss_1->tuples[i].key );


////////////////// UNIT TESTING

    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("testSortingSuite", 0, 0);

    CU_add_test(suite, "SortingTestCase", test);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();


   // create list for results
   info_deikti list = NULL;
   list = LIST_dimiourgia(&list);

   // join function for relations Rr_1 and Ss_1
   Sort_Merge_Join(&Rr_1, r_size, &Ss_1, s_size, &list);     ///  exei ena provlima edw

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

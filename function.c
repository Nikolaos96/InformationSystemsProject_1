/**/
#include "function.h"
#include <stdio.h>

 int64_t produce_random(void){
     int64_t a, b;
     a = rand();
     a = a << 16;
     b = rand();
     a = a | b;
     b = rand();
     a = a << 16;
     a = a | b;

     // return a;
     return rand() % 256;
 }


 void create_init_relations(relation **Rr_1, relation **Rr_2, relation **Ss_1, relation **Ss_2, int size_r, int size_s,
			    uint64_t **main_R, uint64_t **main_S){

     int i;

     main_R = malloc(size_r * sizeof(uint64_t));
     if(main_R == NULL){
	 printf("Error malloc main_R \n");
         exit(1);
     }
     for(i = 0 ; i < size_r ; i++){
         main_R[i] = malloc(5 * sizeof(uint64_t));	// 5 stiles
	 if(main_R[i] == NULL){
	     printf("Error malloc main_R[i] \n");
	     exit(1);
	 }
     }

     main_S = malloc(size_s * sizeof(uint64_t));
     if(main_S == NULL){
	 printf("Error malloc main_S \n");
	 exit(1);
     }
     for(i = 0 ; i < size_s ; i++){
         main_S[i] = malloc(5 * sizeof(uint64_t));	// 5 stiles
	 if(main_S[i] == NULL){
	     printf("Error malloc main_S[i] \n");
	     exit(1);
	 }
     }


     FILE *f1, *f2;
     f1 = fopen("table_R", "r");
     if(f1 == NULL){
	 printf("File table_R doesn't exist. \n");
	 exit(1);
     }
     for(i = 0 ; i < size_r ; i++){
         fscanf(f1, "%lu", &main_R[i][0]);
         fscanf(f1, "%lu", &main_R[i][1]);
	 fscanf(f1, "%lu", &main_R[i][2]);
	 fscanf(f1, "%lu", &main_R[i][3]);
	 fscanf(f1, "%lu", &main_R[i][4]);
     }
     fclose(f1);

     f2 = fopen("table_S", "r");
     if(f2 == NULL){
         printf("File table_S doesn't exist. \n");
         exit(1);
     }
     for(i = 0 ; i < size_s ; i++){
	 fscanf(f1, "%lu", &main_S[i][0]);
         fscanf(f1, "%lu", &main_S[i][1]);
         fscanf(f1, "%lu", &main_S[i][2]);
         fscanf(f1, "%lu", &main_S[i][3]);
         fscanf(f1, "%lu", &main_S[i][4]);
     }
     fclose(f2);








     *Rr_1 = malloc(sizeof(relation)); // if == NULL
     *Rr_2 = malloc(sizeof(relation));
     *Ss_1 = malloc(sizeof(relation));
     *Ss_2 = malloc(sizeof(relation)); // if == NULL


     (*Rr_1)->num_tuples = size_r;
     (*Rr_1)->tuples = malloc((*Rr_1)->num_tuples * sizeof(tuple)); // if == NULL

     (*Rr_2)->num_tuples = size_r;
     (*Rr_2)->tuples = malloc((*Rr_2)->num_tuples * sizeof(tuple));

     (*Ss_1)->num_tuples = size_s;
     (*Ss_1)->tuples = malloc((*Ss_1)->num_tuples * sizeof(tuple));

     (*Ss_2)->num_tuples = size_s;
     (*Ss_2)->tuples = malloc((*Ss_2)->num_tuples * sizeof(tuple)); // if == NULL




     for(i = 0 ; i < (*Rr_1)->num_tuples ; i++){
         (*Rr_1)->tuples[i].key = main_R[i][0];
	 (*Rr_1)->tuples[i].payload = i+1;
     }

     for(i = 0 ; i < (*Ss_1)->num_tuples ; i++){
	 (*Ss_1)->tuples[i].key = main_S[i][0];
	 (*Ss_1)->tuples[i].payload = i+1;
     }
 }


 void make_hist(relation **Rr_1, int r_size, int *hist, int hist_size){
    int i, a;

    for(i = 0 ; i < hist_size ; i++) hist[i] = 0;

    for(i = 0 ; i < r_size ; i++){
         a = (*Rr_1)->tuples[i].key & 0x00000000000000ff;	////////////// thelei allagi se 0xff00000000000000
	 hist[a]++;
    }
 }



 // ti kanoume an kappoi hist einai 0  ///////
//////
//////
 void make_p_sum(int *hist, int hist_size, int *p_sum, int p_sum_size){
     int i;

     p_sum[0] = 0;
     for(i = 1 ; i < hist_size ; i++){
         p_sum[i] = hist[i-1] + p_sum[i-1];
     }
 }



 void make_Rr_2(relation **Rr_1, relation **Rr_2, int r_size, int *p_sum, int p_sum_size){
     int a, i, pos;

     for(i = 0 ; i < r_size ; i++){
         a = (*Rr_1)->tuples[i].key & 0x00000000000000ff;	/////// thelei allagi se 0xff00000000000000
	 pos = p_sum[a];

	 (*Rr_2)->tuples[pos].key = (*Rr_1)->tuples[i].key;
	 (*Rr_2)->tuples[pos].payload = (*Rr_1)->tuples[i].payload;

	 p_sum[a]++;
     }
 }





 void Sort_Merge_Join(relation **Rr, int r_size, relation **Ss, int s_size, info_deikti *list){
	/*


     int index_r = 0, index_ s = 0;
     do{


     }while(index_r <= r_size && s_size <= s_size);



	*/
 }


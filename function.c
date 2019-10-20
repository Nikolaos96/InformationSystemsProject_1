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


 void create_init_relations(relation **Rr_1, relation **Rr_2, relation **Ss_1, relation **Ss_2, int size_r, int size_s){
     int i;
     *Rr_1 = malloc(sizeof(relation));
     *Rr_2 = malloc(sizeof(relation));
     *Ss_1 = malloc(sizeof(relation));
     *Ss_2 = malloc(sizeof(relation));


     (*Rr_1)->num_tuples = size_r;
     (*Rr_1)->tuples = malloc((*Rr_1)->num_tuples * sizeof(tuple));

     (*Rr_2)->num_tuples = size_r;
     (*Rr_2)->tuples = malloc((*Rr_2)->num_tuples * sizeof(tuple));

     (*Ss_1)->num_tuples = size_s;
     (*Ss_1)->tuples = malloc((*Ss_1)->num_tuples * sizeof(tuple));

     (*Ss_2)->num_tuples = size_s;
     (*Ss_2)->tuples = malloc((*Ss_2)->num_tuples * sizeof(tuple));

     for(i = 0 ; i < (*Rr_1)->num_tuples ; i++){
         (*Rr_1)->tuples[i].key = produce_random();
	 (*Rr_1)->tuples[i].payload = 1;
     }

     for(i = 0 ; i < (*Ss_1)->num_tuples ; i++){
	 (*Ss_1)->tuples[i].key = produce_random();
	 (*Ss_1)->tuples[i].payload = 1;
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

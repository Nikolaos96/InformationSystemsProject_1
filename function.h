#ifndef __FUNCTION__
#define __FUNCTION__

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "lista.h"


void create_init_relations(relation **Rr_1, relation **Rr_2, relation **Ss_1, relation **Ss_2, int size_r, int size_s, uint64_t ***main_R, uint64_t ***main_S);


void make_hist(relation **Rr_1, int start, int end, int *hist, int hist_size, int bytePos);
void make_p_sum(int *hist, int hist_size, int *p_sum, int p_sum_size, int start);
void make_Rr_2(relation **Rr_1, relation **Rr_2, int start, int end, int *p_sum, int p_sum_size, int bytePos);


int partition (relation **Rr, int low, int high);
void quickSort(relation **Rr, int low, int high);
int recurseFunc(relation **Rr_1, relation **Rr_2, int start, int end, int bytePos);


void Sort_Merge_Join(relation **Rr, int r_size, relation **Ss, int s_size, info_deikti *list);
void delete_all_array(uint64_t ***main_R, relation **Rr_1, relation **Rr_2, int r_size, uint64_t ***main_S, relation **Ss_1, relation **Ss_2, int s_size);

#endif

#ifndef __FUNCTION__
#define __FUNCTION__

#include <stdlib.h>
#include "structs.h"
#include "lista.h"


void create_init_relations(relation **Rr_1, relation **Rr_2, relation **Ss_1, relation **Ss_2, int size_r, int size_s, uint64_t ***main_R, uint64_t ***main_S);
void make_hist(relation **Rr_1, int r_size, int *hist, int hist_size);
void make_p_sum(int *hist, int hist_size, int *p_sum, int p_sum_size);
void make_Rr_2(relation **Rr_1, relation **Rr_2, int r_size, int *p_sum, int p_sum_size);


void sort(relation **Rr_1, relation **Rr_2, int r_size, int *hist, int *p_sum, int size_psum_hist);

void Sort_Merge_Join(relation **Rr, int r_size, relation **Ss, int s_size, info_deikti *list);
#endif

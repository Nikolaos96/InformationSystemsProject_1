#ifndef __FUNCTION__
#define __FUNCTION__

#include <stdint.h>
#include <stdlib.h>



typedef struct tuple{
	int64_t key;
	int64_t payload;
}tuple;


typedef struct relation{
        tuple *tuples;
        uint64_t num_tuples;
}relation;




void create_init_relations(relation **Rr_1, relation **Rr_2, relation **Ss_1, relation **Ss_2, int size_r, int size_s);
void make_hist(relation **Rr_1, int r_size, int *hist, int hist_size);
void make_p_sum(int *hist, int hist_size, int *p_sum, int p_sum_size);
void make_Rr_2(relation **Rr_1, relation **Rr_2, int r_size, int *p_sum, int p_sum_size);

void Sort_Merge_Join(relation **Rr, int r_size, relation **Ss, int s_size);
#endif

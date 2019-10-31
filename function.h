#ifndef __FUNCTION__
#define __FUNCTION__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "lista.h"


void take_arguments(int argc,char *argv[],char **file1, int *s_file1, char **file2, int *s_file2);
void create_init_relations(relation **Rr_1, relation **Rr_2, relation **Ss_1, relation **Ss_2, int size_r, int size_s,
		           char *table_R, char *table_S);


void make_hist(relation **Rr_1, int start, int end, int *hist, int hist_size, int bytePos);
void make_p_sum(int *hist, int hist_size, int *p_sum, int p_sum_size, int start);
void make_Rr_2(relation **Rr_1, relation **Rr_2, int start, int end, int *p_sum, int p_sum_size, int bytePos);


int partition (relation **Rr, int low, int high);
void quickSort(relation **Rr, int low, int high);
void recurseFunc(relation **Rr_1, relation **Rr_2, int start, int end, int bytePos);


void Sort_Merge_Join(relation **Rr, int r_size, relation **Ss, int s_size, info_deikti *list);
void delete_all_array(relation **Rr_1, relation **Rr_2, int r_size, relation **Ss_1,
		      relation **Ss_2, int s_size, char **file1, char **file2);


void join(relation **Rr, int r_size, relation **Ss, int s_size, info_deikti *list);
#endif

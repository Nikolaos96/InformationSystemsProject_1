/* function.c */
#include "function.h"


/*



*/
 void create_init_relations(relation **Rr_1, relation **Rr_2, relation **Ss_1, relation **Ss_2, int size_r, int size_s,
			    uint64_t ***main_R, uint64_t ***main_S){

     int i;

     *main_R = malloc(size_r * sizeof(uint64_t));
     if(*main_R == NULL){
	 printf("Error malloc main_R \n");
         exit(1);
     }
     for(i = 0 ; i < size_r ; i++){
         (*main_R)[i] = malloc(5 * sizeof(uint64_t));	// 5 stiles
	 if((*main_R)[i] == NULL){
	     printf("Error malloc main_R[i] \n");
	     exit(1);
	 }
     }

     *main_S = malloc(size_s * sizeof(uint64_t));
     if(*main_S == NULL){
	 printf("Error malloc main_S \n");
	 exit(1);
     }
     for(i = 0 ; i < size_s ; i++){
         (*main_S)[i] = malloc(5 * sizeof(uint64_t));	// 5 stiles
	 if((*main_S)[i] == NULL){
	     printf("Error malloc main_S[i] \n");
	     exit(1);
	 }
     }


     FILE *f1, *f2;
     f1 = fopen("table_R.txt", "r");
     if(f1 == NULL){
	 printf("File table_R.txt doesn't exist. \n");
	 exit(1);
     }
     for(i = 0 ; i < size_r ; i++){
         fscanf(f1, "%lu", &(*main_R)[i][0]);
         fscanf(f1, "%lu", &(*main_R)[i][1]);
	 fscanf(f1, "%lu", &(*main_R)[i][2]);
	 fscanf(f1, "%lu", &(*main_R)[i][3]);
	 fscanf(f1, "%lu", &(*main_R)[i][4]);
     }
     fclose(f1);
     f2 = fopen("table_S.txt", "r");
     if(f2 == NULL){
         printf("File table_S.txt doesn't exist. \n");
         exit(1);
     }
     for(i = 0 ; i < size_s ; i++){
	 fscanf(f1, "%lu", &(*main_S)[i][0]);
         fscanf(f1, "%lu", &(*main_S)[i][1]);
         fscanf(f1, "%lu", &(*main_S)[i][2]);
         fscanf(f1, "%lu", &(*main_S)[i][3]);
         fscanf(f1, "%lu", &(*main_S)[i][4]);
     }
     fclose(f2);


     *Rr_1 = malloc(sizeof(relation));  if(*Rr_1 == NULL){ printf("Error malloc Rr_1 \n"); exit(1); }
     *Rr_2 = malloc(sizeof(relation));  if(*Rr_2 == NULL){ printf("Error malloc Rr_2 \n"); exit(1); }
     *Ss_1 = malloc(sizeof(relation));  if(*Ss_1 == NULL){ printf("Error malloc Ss_1 \n"); exit(1); }
     *Ss_2 = malloc(sizeof(relation));  if(*Ss_2 == NULL){ printf("Error malloc Ss_2 \n"); exit(1); }


     (*Rr_1)->num_tuples = size_r;
     (*Rr_1)->tuples = malloc((*Rr_1)->num_tuples * sizeof(tuple));
     if((*Rr_1)->tuples == NULL){ printf("Error malloc (*Rr_1)->tuples \n"); exit(1); }

     (*Rr_2)->num_tuples = size_r;
     (*Rr_2)->tuples = malloc((*Rr_2)->num_tuples * sizeof(tuple));
     if((*Rr_2)->tuples == NULL){ printf("Error malloc (*Rr_2)->tuples \n"); exit(1); }

     (*Ss_1)->num_tuples = size_s;
     (*Ss_1)->tuples = malloc((*Ss_1)->num_tuples * sizeof(tuple));
     if((*Ss_1)->tuples == NULL){ printf("Error malloc (*Ss_1)->tuples \n"); exit(1); }

     (*Ss_2)->num_tuples = size_s;
     (*Ss_2)->tuples = malloc((*Ss_2)->num_tuples * sizeof(tuple));
     if((*Ss_2)->tuples == NULL){ printf("Error malloc (*Ss_2)->tuples \n"); exit(1); }


     for(i = 0 ; i < (*Rr_1)->num_tuples ; i++){
         (*Rr_1)->tuples[i].key = (*main_R)[i][0];
	 (*Rr_1)->tuples[i].payload = i;
     }

     for(i = 0 ; i < (*Ss_1)->num_tuples ; i++){
	 (*Ss_1)->tuples[i].key = (*main_S)[i][0];
	 (*Ss_1)->tuples[i].payload = i;
     }
 }


/*

*/
 void make_hist(relation **Rr_1, int start, int end, int *hist, int hist_size, int bytePos){
    int i, a;

    for(i = 0 ; i < hist_size ; i++) hist[i] = 0;

    for(i = start ; i < end ; i++){
         a = ( (*Rr_1)->tuples[i].key >> (8*bytePos) ) & 0x00000000000000ff;
	 hist[a]++;
    }
 }


/*

*/
 void make_p_sum(int *hist, int hist_size, int *p_sum, int p_sum_size, int start){
     int i, j;

     if(hist[0] != 0) p_sum[0] = start; //// eixame 0
     else p_sum[0] = -1;
     for(i = 1 ; i < hist_size ; i++){

		if(hist[i] == 0){
			p_sum[i] = -1;
			continue;
		}
		int sum = 0;
		for(j = 0 ; j < i ; j++)
			sum += hist[j];

		p_sum[i] = sum + start;	///////// prostheto to start
     }
 }


/*

*/
 void make_Rr_2(relation **Rr_1, relation **Rr_2,  int start, int end, int *p_sum, int p_sum_size, int bytePos){
     int a, i, pos;

     for(i = start ; i < end ; i++){
         a = ((*Rr_1)->tuples[i].key >> (8*bytePos) ) & 0x00000000000000ff;	/////////////////////
	       pos = p_sum[a];

	 (*Rr_2)->tuples[pos].key = (*Rr_1)->tuples[i].key;
	 (*Rr_2)->tuples[pos].payload = (*Rr_1)->tuples[i].payload;

	 p_sum[a]++;
     }
 }


/*

*/
 int partition (relation **Rr, int low, int high) {
	uint64_t pivot = (*Rr)->tuples[high].key;
	int i = (low - 1);
        uint64_t tempKey;
        uint64_t tempPayload;

	for (int j = low; j <= high- 1; j++) {
		if ((*Rr)->tuples[j].key < pivot) { // merikoi grafoun <=
			i++;
			 tempKey = (*Rr)->tuples[i].key;
		   tempPayload = (*Rr)->tuples[i].payload;
			(*Rr)->tuples[i].key = (*Rr)->tuples[j].key;
			(*Rr)->tuples[i].payload = (*Rr)->tuples[j].payload;

			(*Rr)->tuples[j].key = tempKey;
			(*Rr)->tuples[j].payload = tempPayload;
		}
	}
	tempKey = (*Rr)->tuples[i + 1].key;
        tempPayload = (*Rr)->tuples[i + 1].payload;
	(*Rr)->tuples[i + 1].key = (*Rr)->tuples[high].key;
	(*Rr)->tuples[i + 1].payload = (*Rr)->tuples[high].payload;
	(*Rr)->tuples[high].key = tempKey;
	(*Rr)->tuples[high].payload = tempPayload;
	return (i + 1);
 }


/*

*/
 void quickSort(relation **Rr, int low, int high) {
	if (low < high) {
		int pi = partition(Rr, low, high);
		quickSort(Rr, low, pi - 1);
		quickSort(Rr, pi + 1, high);
	}
 }


/*

*/
 int recurseFunc(relation **Rr_1, relation **Rr_2, int start, int end, int bytePos) {
   if( end - start >= 18 ) {     // 4096

	   int *hist, *p_sum;
	   hist = malloc(256 * sizeof(int));
	   if(hist == NULL){
		   printf("Error malloc hist \n");
		   return -1;
	   }
	   p_sum = malloc(256 * sizeof(int));
	   if(p_sum == NULL){
		   printf("Error malloc p_sum \n");
		   return -1;
	   }


	   make_hist(Rr_1, start, end, &hist[0], 256, bytePos);
	   make_p_sum(&hist[0], 256, &p_sum[0], 256, start); //////////// evala to start
	   make_Rr_2(Rr_1, Rr_2, start, end, &p_sum[0], 256, bytePos);


	   relation *temp = *Rr_1;	////////  1
	   *Rr_1 = *Rr_2;		///////// 2
	   *Rr_2 = temp;		///////// 3


	   bytePos--;

	   for(int i = 0; i < 256; i++) {

			if( hist[i] == 0)
			    continue;
			else{
			    if( bytePos > 0) {
				//recurseFunc( Rr_2, Rr_1, p_sum[i] - hist[i], p_sum[i], bytePos);
				recurseFunc( Rr_1, Rr_2, p_sum[i] - hist[i], p_sum[i], bytePos);
			    }else{
				//quickSort(Rr_2, start, end);
				quickSort(Rr_1, start, end - 1);			//////////////////// 4
//				for(int k = start; k < end; k++) {				// 5
//				    (*Rr_1)->tuples[k].key = (*Rr_2)->tuples[k].key;		// 6
//				    (*Rr_1)->tuples[k].payload = (*Rr_2)->tuples[k].payload;	// 7
//				}

			    }
			}
	   }

	   free(p_sum);
	   free(hist);
   }else{
	  quickSort(Rr_1, start, end - 1);
//	  for(int k = start; k < end; k++) {					// 8
//		(*Rr_2)->tuples[k].key = (*Rr_1)->tuples[k].key;		// 9
//		(*Rr_2)->tuples[k].payload = (*Rr_1)->tuples[k].payload;	// 10
//	  }
   }


 }


/*

*/
void Sort_Merge_Join(relation **Rr, int r_size, relation **Ss, int s_size, info_deikti *list){

     int mark = -1;
     int r = 0, s = 0;


     do{
         if(mark == -1){
	     while( (*Rr)->tuples[r].key < (*Ss)->tuples[s].key ) { r++; }
	     while( (*Rr)->tuples[r].key > (*Ss)->tuples[s].key ) { s++; }
	     mark = s;
	 }

	 if( (*Rr)->tuples[r].key == (*Ss)->tuples[s].key ){
	     // eisagwgi stin lista to
	     // (*Rr)->tuples[r].payload - (*Ss)->tuples[s].payload
	     s++;
	 }else{
	     s = mark;
	     r++;
	     mark = -1;
	 }
     }while( r < (*Rr)->num_tuples && s < (*Ss)->num_tuples );

 }


 /*

 */
 void delete_all_array(uint64_t ***main_R, relation **Rr_1, relation **Rr_2, int r_size, uint64_t ***main_S, relation **Ss_1, relation **Ss_2, int s_size){
     int i;

     for(i = 0 ; i < r_size ; i++) free((*main_R)[i]);
     free(*main_R);

     for(i = 0 ; i < s_size ; i++) free((*main_S)[i]);
     free(*main_S);


     for(i = 0 ; i < r_size ; i++){
         free((*Rr_1)->tuples[i]);
	 free((*Rr_2)->tuples[i]);
     }
     free(*Rr_1);
     free(*Rr_2);

     for(i = 0 ; i < s_size ; i++){
	 free((*Ss_1)->tuples[i]);
	 free((*Ss_2)->tuples[i]);
     }
     free(*Ss_1);
     free(*Ss_2);

     return;
 }

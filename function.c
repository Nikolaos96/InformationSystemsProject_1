/* function.c */
#include "function.h"



 /*
   take arguments from command line and init variables
 */
 void take_arguments(int argc,char *argv[],char **file1, int *s_file1, char **file2, int *s_file2){

    char *arg;
    if(argc != 9 ){
        printf("\nError in arguments command line. \n\n");
        exit(1);
    }

    while(--argc){
        arg = *++argv;
        if(!strcmp(arg, "-f1")){
	  *file1 = malloc((strlen(*++argv) + 1) * sizeof(char));
	  strcpy(*file1, *argv);
        }else if(!strcmp(arg, "-s1")){
	    *s_file1 = atoi(*++argv);

        }else if(!strcmp(arg, "-f2")){
	    *file2 = malloc((strlen(*++argv) + 1) * sizeof(char));
	    strcpy(*file2, *argv);
        }else if(!strcmp(arg, "-s2")){
	    *s_file2 = atoi(*++argv);
	}

        if(argc > 1) argc--;
     }

     return;
 }



 /*
  create relations Rr_1, Rr_2, Ss_1, Ss_2 and init the first relations Rr_1 and Ss_1
  read from files the numbers for Rr_1 and Ss_1
  the files are given by the command line
 */
 void create_init_relations(relation **Rr_1, relation **Rr_2, relation **Ss_1, relation **Ss_2, int size_r, int size_s,
			    char *table_R, char *table_S){

     int i;

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



     FILE *f1, *f2;
     f1 = fopen(table_R, "r");
     if(f1 == NULL){
         printf("File %s doesn't exist. \n", table_R);
         exit(1);
     }

     for(i = 0 ; i < (*Rr_1)->num_tuples ; i++){
         fscanf(f1, "%lu", &(*Rr_1)->tuples[i].key);
	 (*Rr_1)->tuples[i].payload = i;
     }
     fclose(f1);


     f2 = fopen(table_S, "r");
     if(f2 == NULL){
         printf("File %s doesn't exist. \n", table_S);
         exit(1);
     }

     for(i = 0 ; i < (*Ss_1)->num_tuples ; i++){
	 fscanf(f2, "%lu", &(*Ss_1)->tuples[i].key);
	 (*Ss_1)->tuples[i].payload = i;
     }
     fclose(f2);

     return;
 }



 /*
  make hist array for relation Rr_1
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
  make p_sum array
 */
 void make_p_sum(int *hist, int hist_size, int *p_sum, int p_sum_size, int start){
     int i, j;

     if(hist[0] != 0) p_sum[0] = start;
     else p_sum[0] = -1;
     for(i = 1 ; i < hist_size ; i++){

		if(hist[i] == 0){
			p_sum[i] = -1;
			continue;
		}
		int sum = 0;
		for(j = 0 ; j < i ; j++)
			sum += hist[j];

		p_sum[i] = sum + start;
     }
 }


 /*
  make Rr_2 relation
 */
 void make_Rr_2(relation **Rr_1, relation **Rr_2,  int start, int end, int *p_sum, int p_sum_size, int bytePos){
     int a, i, pos;

     for(i = start ; i < end ; i++){
         a = ((*Rr_1)->tuples[i].key >> (8*bytePos) ) & 0x00000000000000ff;
	       pos = p_sum[a];

	 (*Rr_2)->tuples[pos].key = (*Rr_1)->tuples[i].key;
	 (*Rr_2)->tuples[pos].payload = (*Rr_1)->tuples[i].payload;

	 p_sum[a]++;
     }
 }


 /*
  part of quicksort
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
  quicksort
 */
 void quickSort(relation **Rr, int low, int high) {
	if (low < high) {
		int pi = partition(Rr, low, high);
		quickSort(Rr, low, pi - 1);
		quickSort(Rr, pi + 1, high);
	}
 }


 /*
  recurse function for sorting relations
 */
 void recurseFunc(relation **Rr_1, relation **Rr_2, int start, int end, int bytePos) {

     if( end - start > 4096) {

	   int *hist, *p_sum;
	   hist = malloc(256 * sizeof(int));
	   if(hist == NULL){
		   printf("Error malloc hist \n");
		   exit(1);
	   }
	   p_sum = malloc(256 * sizeof(int));
	   if(p_sum == NULL){
		   printf("Error malloc p_sum \n");
		   exit(1);
	   }


	   make_hist(Rr_1, start, end, &hist[0], 256, bytePos);
	   make_p_sum(&hist[0], 256, &p_sum[0], 256, start);
	   make_Rr_2(Rr_1, Rr_2, start, end, &p_sum[0], 256, bytePos);

	   bytePos--;

	   for(int i = 0; i < 256; i++) {
		if( hist[i] == 0)
		    continue;
		else{
		    if( bytePos > 0){
			recurseFunc(Rr_2, Rr_1, p_sum[i] - hist[i], p_sum[i], bytePos);
		    }else{
			quickSort(Rr_2, start, end - 1);
//			for(int k = start ; k < end ; k++){
//			    (*Rr_1)->tuples[k].key = (*Rr_2)->tuples[k].key;
//			    (*Rr_1)->tuples[k].payload = (*Rr_2)->tuples[k].payload;
//			}
		    }
		}
	   }

	   free(p_sum);
	   free(hist);
     }else{
	  quickSort(Rr_1, start, end - 1);
	  for(int k = start; k < end ; k++){
	      (*Rr_2)->tuples[k].key = (*Rr_1)->tuples[k].key;
 	      (*Rr_2)->tuples[k].payload = (*Rr_1)->tuples[k].payload;
	  }
     }

     return;
 }


 /*
  function for join relation Rr - relation Ss
 */
 void Sort_Merge_Join(relation **Rr, int r_size, relation **Ss, int s_size, info_deikti *list){
     int mark = -1;
     int r = 0, s = 0;


     do{
         if(mark == -1){
	     while( (*Rr)->tuples[r].key < (*Ss)->tuples[s].key && (r < (*Rr)->num_tuples) && (s < (*Ss)->num_tuples)) { r++; }
	     while( (*Rr)->tuples[r].key > (*Ss)->tuples[s].key && (r < (*Rr)->num_tuples) && (s < (*Ss)->num_tuples)) { s++; }
	     mark = s;
	 }

	 if((r > (*Rr)->num_tuples-1) || (s > (*Ss)->num_tuples-1)) break;

	 if( (*Rr)->tuples[r].key == (*Ss)->tuples[s].key ){
	     eisagogi_eggrafis(list, (*Rr)->tuples[r].payload, (*Ss)->tuples[s].payload);
	     s++;
	 }else{
	     s = mark;
	     r++;
	     mark = -1;
	 }
     }while( (r < (*Rr)->num_tuples) && (s < (*Ss)->num_tuples) );  // evala -1 kai sta duo

     return;
 }


 /*
  deletes all the reserved memory
 */
 void delete_all_array(relation **Rr_1, relation **Rr_2, int r_size, relation **Ss_1,
		       relation **Ss_2, int s_size, char **file1, char **file2){
     int i;

     free(*file1);
     free(*file2);

     free((*Rr_1)->tuples);
     free(*Rr_1);
     free((*Rr_2)->tuples);
     free(*Rr_2);

     free((*Ss_1)->tuples);
     free(*Ss_1);
     free((*Ss_2)->tuples);
     free(*Ss_2);

     return;
 }




 void join(relation **Rr, int r_size, relation **Ss, int s_size, info_deikti *list){

     int r = 0;
     int s = 0, ss;


     while( (r < (*Rr)->num_tuples) && (s < (*Ss)->num_tuples) ){
         while( (*Rr)->tuples[r].key < (*Ss)->tuples[s].key ) { r++; }
         while( (*Rr)->tuples[r].key > (*Ss)->tuples[s].key ) { s++; }

	 ss = s;
	 while( (*Rr)->tuples[r].key == (*Ss)->tuples[ss].key){
	     s = ss;
	     while( (*Rr)->tuples[r].key == (*Ss)->tuples[s].key ){
		 eisagogi_eggrafis(list, (*Rr)->tuples[r].payload, (*Ss)->tuples[s].payload);
		 s++;
	     }
	     r++;
	 }
     }

 }

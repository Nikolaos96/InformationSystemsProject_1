//File: lista.c
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

 typedef struct info_node{
 	int size;
	typos_deikti arxi;
	typos_deikti telos;
 }info_node;


 typedef struct typos_komvou{
 	int   **array;     // thelou pinaka 2D uint64_t 65500
	int   index;
	int   size;


	typos_deikti epomenos;
 }typos_komvou;



 info_deikti LIST_dimiourgia(info_deikti* lista){

 	info_deikti linfo;
 	linfo = malloc(sizeof(info_node));
 	linfo->size = 0;
 	linfo->arxi = NULL;
	linfo->telos = NULL;
 	return linfo;
 }



 void eisagogi_komvou(info_deikti* linfo){

	int i;
 	typos_deikti prosorinos;
 	prosorinos = malloc(sizeof(typos_komvou));




	prosorinos->size = 65000;
	prosorinos->array = malloc(prosorinos->size * sizeof(int));
	if(prosorinos->array == NULL){
	    printf("Error malloc prosorinos->array  \n");
	    exit(1);
	}
	for(i = 0 ; i < prosorinos->size ; i++){
	    prosorinos->array[i] = malloc(2 * sizeof(int));
	    if(prosorinos->array[i] == NULL){
	        printf("Error malloc prosorinos->array[i]  \n");
	    }
	}
	prosorinos->index = 0;





 	if((*linfo)->size == 0){
 		(*linfo)->arxi = prosorinos;
		(*linfo)->telos = prosorinos;
		prosorinos->epomenos = NULL;

 	}
 	if((*linfo)->size > 0){
		prosorinos->epomenos = NULL;
 		(*linfo)->telos->epomenos = prosorinos;
		(*linfo)->telos = prosorinos;
 	}
 	(*linfo)->size++;
 }


 void eisagogi_eggrafis(info_deikti* linfo, int a, int b){
	//prepei na kanoume eisagwgi ston pinaka tou teleutaiou komvou
	//an o pinakas autos einai gematos prepei na dimiourgisoume ne komvo kai na kanoume eisagwgi


	typos_deikti mapas = (*linfo)->telos;
	if(mapas->index == mapas->size - 1){
	    eisagogi_komvou(linfo);
	    eisagogi_eggrafis(linfo, a, b);
	}else{

	    mapas->array[mapas->index][0]  = a;
	    mapas->array[mapas->index][1] = b;
	    mapas->index++;
	}

 }


 void emfanisi(info_deikti* linfo){

	typos_deikti mapas = (*linfo)->arxi;
	printf(" \n ");
 	while(mapas != NULL){
 //		printf("%d\n", mapas->dedomena);	//////////
		mapas = mapas->epomenos;
 	}
	printf(" \n ");
 }


 void lista_diagrafi(info_deikti* linfo){

	int i;
 	typos_deikti mapas = (*linfo)->arxi;
	typos_deikti mapas2;

 	while(mapas != NULL){
		mapas2 = mapas;
		mapas = mapas->epomenos;
		for(i = 0 ; i < mapas2->size ; i++) free(mapas2->array[i]);
		free(mapas2);
	}
	(*linfo)->arxi = NULL;
	(*linfo)->telos = NULL;
	(*linfo)->size = 0;
	free(*linfo);
	(*linfo) = NULL;
 }

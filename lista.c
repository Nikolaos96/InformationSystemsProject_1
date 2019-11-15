//File: lista.c
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "structs.h"


 typedef struct info_node{
 	int size;
	typos_deikti arxi;
	typos_deikti telos;
 }info_node;


 typedef struct typos_komvou{
 	tuple *array;
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


	prosorinos->index = 0;
	prosorinos->size = 65000;
	prosorinos->array = malloc(prosorinos->size * sizeof(tuple));
	if(prosorinos->array == NULL){
	    printf("Error malloc prosorinos->array  \n");
	    exit(1);
	}

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


 void eisagogi_eggrafis(info_deikti* linfo, uint64_t a, uint64_t b){

        if((*linfo)->telos == NULL) eisagogi_komvou(linfo);
	typos_deikti mapas = (*linfo)->telos;

	if(mapas->index == mapas->size){
	    eisagogi_komvou(linfo);
	    eisagogi_eggrafis(linfo, a, b);
	}else{

	    mapas->array[mapas->index].key  = a;
	    mapas->array[mapas->index].payload  = b;
	    mapas->index++;
	}
 }



 void emfanisi(info_deikti* linfo){
        int i;
	typos_deikti mapas = (*linfo)->arxi;

        FILE *f;
        if(mapas != NULL){
	    f = fopen("results.csv", "w");
	    if(f == NULL){
	        printf("Error file for results. \n");
		exit(1);
	    }
        }

 	while(mapas != NULL){
 	    for(int i = 0 ; i < mapas->index ; i++) fprintf(f, "%lu  -  %lu \n", mapas->array[i].key, mapas->array[i].payload);
	    mapas = mapas->epomenos;
 	}

        if( (mapas = (*linfo)->arxi) != NULL) fclose(f);
 }



 void lista_diagrafi(info_deikti* linfo){
	int i;

        if((*linfo)->arxi != NULL){

 	    typos_deikti mapas = (*linfo)->arxi;
	    typos_deikti mapas2;

 	    while(mapas != NULL){
		mapas2 = mapas;
		mapas = mapas->epomenos;
		free(mapas2->array);
		free(mapas2);
	    }
	    (*linfo)->arxi = NULL;
	    (*linfo)->telos = NULL;
	    (*linfo)->size = 0;
        }
	free(*linfo);
	(*linfo) = NULL;
 }

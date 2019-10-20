//File: stack.c
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

 typedef struct info_node{
 	int size;
	typos_deikti arxi;
 }info_node;


 typedef struct typos_komvou{
 	tuple new_tuple;

	typos_deikti epomenos;
 }typos_komvou;



 info_deikti STACK_dimiourgia(info_deikti* lista){

 	info_deikti linfo;
 	linfo = malloc(sizeof(info_node));
 	linfo->size = 0;
 	linfo->arxi = NULL;
 	return linfo;
 }



 void push(info_deikti* linfo, tuple t){

 	typos_deikti prosorinos;
 	prosorinos = malloc(sizeof(typos_komvou));


 	prosorinos->new_tuple.key = t.key;
  	prosorinos->new_tuple.payload = t.payload;



 	if((*linfo)->size == 0){
 		(*linfo)->arxi = prosorinos;
		prosorinos->epomenos = NULL;
 	}
 	if((*linfo)->size > 0){
		prosorinos->epomenos = (*linfo)->arxi;
 		(*linfo)->arxi= prosorinos;
 	}
 	(*linfo)->size++;
 }



 void remove_stack(info_deikti* linfo){

 	typos_deikti mapas = (*linfo)->arxi;
	typos_deikti mapas2;

 	while(mapas != NULL){
		mapas2 = mapas;
		mapas = mapas->epomenos;
		free(mapas2);
	}
	(*linfo)->arxi = NULL;
	(*linfo)->size = 0;
	free(*linfo);
	(*linfo) = NULL;
 }

 void pop(info_deikti* linfo, int komvos){
	int k;

	if((*linfo)->size > 0){
	    typos_deikti mapas = (*linfo)->arxi;
	    (*linfo)->arxi = mapas->epomenos;

	    free(mapas);
	    (*linfo)->size--;
	}
 }

/**/

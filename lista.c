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
 	tuple *tuples;
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

 	typos_deikti prosorinos;
 	prosorinos = malloc(sizeof(typos_komvou));



	prosorinos->size = 65000;		//// megethos pinaka apo eggrafes    1024 x 1024 / 16 = 65536
	prosorinos->tuples = malloc(prosorinos->size * sizeof(tuple));
	prosorinos->index = 0;
	if(prosorinos->tuples== NULL){
		printf("Error in malloc array for results \n");
		exit(-1);
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


 void eisagogi_eggrafis(info_deikti* linfo, tuple eggrafi){
	//prepei na kanoume eisagwgi ston pinaka tou teleutaiou komvou
	//an o pinakas autos einai gematos prepei na dimiourgisoume ne komvo kai na kanoume eisagwgi


	typos_deikti mapas = (*linfo)->telos;
	if(mapas->index == mapas->size - 1){	// elegxw an o pinakas tou komvou exei xoro
	//den exei xoro					// xreiazomai mia metavliti index pou na mou deixmnei tin epomeni adeia thesi tou pinaka
							 // wste na paw na grapsw tin nea eggrafi
	    eisagogi_komvou(linfo);
	    eisagogi_eggrafis(linfo, eggrafi);
	}else{

	    mapas->tuples[mapas->index].key = eggrafi.key;		//////////
	    mapas->tuples[mapas->index].payload = eggrafi.key;		/////////
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

 	typos_deikti mapas = (*linfo)->arxi;
	typos_deikti mapas2;

 	while(mapas != NULL){
		mapas2 = mapas;
		mapas = mapas->epomenos;
		free(mapas2->tuples);
		free(mapas2);
	}
	(*linfo)->arxi = NULL;
	(*linfo)->telos = NULL;
	(*linfo)->size = 0;
	free(*linfo);
	(*linfo) = NULL;
 }


/**/

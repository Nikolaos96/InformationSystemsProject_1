#ifndef __LISTA__
#define __LISTA__
#include "structs.h"

typedef struct info_node    *  info_deikti;
typedef struct typos_komvou *  typos_deikti;



info_deikti LIST_dimiourgia(info_deikti*);
void eisagogi_komvou(info_deikti* linfo);
void eisagogi_eggrafis(info_deikti* linfo, int a, int b);

void emfanisi(info_deikti* linfo);
void lista_diagrafi(info_deikti* linfo);

#endif

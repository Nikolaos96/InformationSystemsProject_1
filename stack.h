#ifndef __STACK__
#define __STACK__
#include "function.h"

typedef struct info_node * info_deikti;
typedef struct typos_komvou * typos_deikti;



info_deikti STACK_dimiourgia(info_deikti*);
void push(info_deikti* linfo, tuple t);
void remove_stack(info_deikti* linfo);
void pop(info_deikti* linfo, int komvos);

#endif

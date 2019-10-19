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




void create_init_relations(relation **Rr_1, relation **Rr_2, relation **Ss_1, relation **Ss_2);



#endif

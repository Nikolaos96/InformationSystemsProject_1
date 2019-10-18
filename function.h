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





#endif

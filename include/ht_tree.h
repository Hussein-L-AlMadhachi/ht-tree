#include <stdint.h>
#include <stdlib.h>

#define N_KEYS_PER_NODE 8  // must be a power of two
#define BITS_SELECTOR N_KEYS_PER_NODE-1
#define SHIFTED_BITS 3

#define NODE_SIZE (N_KEYS_PER_NODE * sizeof(HT_KeyValue))



typedef enum
{
	SUCCESS = 0,
	FAIL_ATOMIC = 1,
	FAIL_NONATOMIC = 4,

	F_OS = 8,			//OS's error
	F_BAD_USE = 16,		//User fault
	F_UNEXPECTED = 32	//Very unexpected error that shopuldn't be there
}
Status;



typedef struct
{
	char * key;
	char * value;
	void * child_node;
	uint64_t hash;		/*	used to compare hashes first
							before comparing whole strings */
}
HT_KeyValue;



typedef struct
{
	HT_KeyValue * root_node;
	unsigned n_allocations;
	unsigned n_free;
}
HT_Tree;



Status ht_init_tree ( HT_Tree * tree );
Status ht_create_item ( HT_Tree * tree , char * key , size_t key_length , char * value );
char * ht_get_item ( HT_Tree * tree , char * key , size_t key_length );
Status ht_remove_item ( HT_Tree * tree , char *  key , size_t key_length );


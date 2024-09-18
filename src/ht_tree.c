#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include <stdio.h>

#include "../include/ht_tree.h"
#include "../include/rapidhash.h"






/**
 *  Node Memory Layout:
 *
 *
 *    ┌────────────────────────────────────────────────────────────────────────────────┐
 *    │                                  HT-Tree Node                                  │
 *    ├────────────────────────────────────────────────────────────────────────────────┤
 *    │   hash table containing key-value pairs (size calculation is detailed below)   │
 *    └────────────────────────────────────────────────────────────────────────────────┘
 *
 *    NOTE: Hashtable size must be a power of 2. according to my benchmarks 32 showed the best performance.
 *          while 16 showed a comprimise between memory consumption and performance
 *
 *
 *
 *
 *  HT-Tree Diagram:
 *  
 *
 *                                         ┌───────────────────────────────────────────────┐
 *                                         │                   Root Node                   │
 *                                         ├───────────────────────────────────────────────┤
 *                                         │               Hash table (size 4)             │
 *                                         ├───────────┬───────────┬───────────┬───────────┤
 *                                         │ Key-value │ Key-value │ Key-value │ Key-value │
 *                                         └─────┬─────┴─────┬─────┴─────┬─────┴─────┬─────┘  
 *       ┌───────────────────────────────────────┘           └───┐   ┌───┘           └───────────────────────────────────────┐
 *       │             child pointer                             │   │                             child pointer             │
 *       │                                                       │   │                                                       │
 *       │                                                       │   │                                                       │
 * ┌─────┴─────────────────────────────────────────┐             │   │             ┌─────────────────────────────────────────┴─────┐
 * │                  child Node                   │             │   │             │                  child Node                   │
 * ├───────────────────────────────────────────────┤             │   │             ├───────────────────────────────────────────────┤
 * │               Hash table (size 4)             │             │   │             │               Hash table (size 4)             │
 * ├───────────┬───────────┬───────────┬───────────┤             │   │             ├───────────┬───────────┬───────────┬───────────┤
 * │ Key-value │ Key-value │ Key-value │ Key-value │             │   │             │ Key-value │ Key-value │ Key-value │ Key-value │
 * └───────────┴───────────┴───────────┴───────────┘             │   │             └───────────┴───────────┴───────────┴───────────┘
 *                                                               │   │
 *                                               child pointer   │   │   child pointer
 *                                           ┌───────────────────┘   └───────────────────┐
 *                                           │                                           │
 *     ┌─────────────────────────────────────┴─────────┐                       ┌─────────┴─────────────────────────────────────┐
 *     │                  child Node                   │                       │                  child Node                   │
 *     ├───────────────────────────────────────────────┤                       ├───────────────────────────────────────────────┤
 *     │               Hash table (size 4)             │                       │               Hash table (size 4)             │
 *     ├───────────┬───────────┬───────────┬───────────┤                       ├───────────┬───────────┬───────────┬───────────┤
 *     │ Key-value │ Key-value │ Key-value │ Key-value │                       │ Key-value │ Key-value │ Key-value │ Key-value │
 *     └───────────┴───────────┴───────────┴───────────┘                       └───────────┴───────────┴───────────┴───────────┘
 *
 *
 *
 *      Notes:
 *        1. Each key-value pair is a part of a hashtable (in this eaxmple each hashtable has a size of 4).
 *        2. If a key-value pair is allocated in memory but it is not occupied, it should be overwritten with Zeros.
 *
 *
 *
 *  Key-Value Pairs:
 *
 *    each key value pair contain a key (char *) a value (char *) a hash (64 bit integer)
 *    to speed up the comparason process and a pointer to a child node (void *)
 *      
 *      on a modern computer the size of each key-value pair is 32 bytes
 *
 *
 *
 *  The search Algorithm:
 *
 *    the size of the hash table must be a power of two (which in this implementation will be refered as N_KEYS_PER_NODE).
 *    because N_KEYS_PER_NODE is a power of two N_KEYS_PER_NODE-1 in binary number made of ones only
 *
 *    let N_KEYS_PER_NODE = 4, the number of ones in N_KEYS_PER_NODE-1 is 2; this means when we do hashtable lookup we only
 *    need 2 bits.
 *
 *    the hash function used usually produces 64 bit hash (8 bytes)
 *    by iterating on every two bits in the 64 bit hash value of the key you are looking for to use as in index to do a
 *    hash table lookup, we can navigate the whole tree... How? Remember the key-value pairs section above? it has a 
 *    child_node pointer which will point to one of the children of our current node.
 *
 *    After looking up the key in the hash table of the root node. if the key was not found, we take the child pointer in the
 *    key-value pair to do a hash table lookup. if not found we move to the child of the child and so on until we find our key
 *    or we reach a null pointer which means there are no more hashtables that might have our tree. thus it was never added on
 *    the tree.
 *
 *
 *
 *  The Insertion Algorithm:
 *
 *
 *    Assuming N_KEYS_PER_NODE = 4; divide the hash value of the new key into 2 bits
 *    In a loop use each two bits to do a hashtable lookup (using the lookup algorithm detailed in the previous section).
 *    if the key-value pair is not occupied (can be determinded if key in the key-value pair slot is NULL), then simply copy your
 *    value and key to this un occupied slot and exit the function.
 *
 *    otherwise when performing a hash table lookup, if you had a collision (the slot that the hash table brought you is occupied
 *    and already has a key and value), then take the child_node pointer in the key-value pair and repeat this process again until
 *    one of the two following conditions is met:
 *    
 *    1. You reach an unoccupied key-value pair slot in one of the hash tables in any particular node you encounter. in this case
 *      just copy your key and value and exit the function.
 *    
 *    2. You reach a NULL pointer for a child_node in the key-value pair. in this case, allocate memory for a new a child node then
 *      initialise it to zero. finally, do a final hash table lookup (using the method provided above and in the previous section)
 *      to locate the position of the new key-value pair to copy your new key and new value over to it. 
 *
 *
 *
 *  The Removal Algorithm:
 *
 *
 *    the size of the hash table must be a power of two (which in this implementation will be refered as N_KEYS_PER_NODE).
 *    because N_KEYS_PER_NODE is a power of two N_KEYS_PER_NODE-1 in binary number made of ones only
 *
 *    let N_KEYS_PER_NODE = 4, the number of ones in N_KEYS_PER_NODE-1 is 2; this means when we do hashtable lookup we only
 *    need 2 bits.
 *
 *    the hash function used usually produces 64 bit hash (8 bytes)
 *    by iterating on every two bits in the 64 bit hash value of the key you are looking for to use as in index to do a
 *    hash table lookup, we can navigate the whole tree... How? Remember the key-value pairs section above? it has a 
 *    child_node pointer which will point to one of the children of our current node.
 *    
 *    after the key-value pair is found mark it and continue the lookup operation to reach a leaf node and move a key-value
 *    pair from this leaf node to replace the key-value pair you wanna remove overwriting it then overwirte the slot of the
 *    key-value pair that was displaced at the leaf node with Zeros.
 *
 *
**/







/* this is a tree of hashtables with size N_KEYS_PER_NODE */
Status
ht_init_tree( HT_Tree * tree )
{
	tree->root_node = malloc( NODE_SIZE );
	/* +1 to store number of key-value pairs in each hash table */
	if ( tree->root_node == NULL )  return FAIL_ATOMIC | F_OS;
	memset(tree->root_node, 0 , NODE_SIZE ); // initialize with zeros

	tree->n_allocations=0;
	tree->n_free=0;
	
	return SUCCESS;
}






/**
 *  Returns on error:
 *    FAIL_ATOMIC | F_BAD_USE      the key-value pair alraedy exist and cannot
 *                                be added.
 *    FAIL_ATOMIC | F_OS          failed to allocate memory.
 *
 *  Returns on success:
 *    SUCCESS
**/
Status
ht_create_item ( HT_Tree * tree , char * key ,
								 size_t key_length , char * value )
{
	uint64_t hash = rapidhash( key , key_length );
	uint64_t bits_selector = BITS_SELECTOR;
	unsigned shift_amount = 0;

	HT_KeyValue * node_iterator = tree->root_node;

	HT_KeyValue * keyval_pair_ptr;
	unsigned item_position;

	while ( node_iterator != NULL )
	{
		item_position = (hash & bits_selector) >> shift_amount;
		bits_selector<<=SHIFTED_BITS;
		shift_amount+=SHIFTED_BITS;

		keyval_pair_ptr = node_iterator + item_position;

		if ( keyval_pair_ptr->key == 0 )
		{
			keyval_pair_ptr->key = key;
			keyval_pair_ptr->value = value;
			keyval_pair_ptr->hash = hash;
			return SUCCESS;
		}

		if ( keyval_pair_ptr->hash == hash &&
				strcmp(keyval_pair_ptr->key , key)==0 )
		{
			return FAIL_ATOMIC | F_BAD_USE;
		}

		node_iterator = keyval_pair_ptr->child_node;
	}

	/** WARNING: node_iterator is NULL do not use it. Use keyval_pair_ptr instead. */

	// allocate memory
	keyval_pair_ptr->child_node = malloc( NODE_SIZE );
	if ( keyval_pair_ptr->child_node == NULL )  return FAIL_ATOMIC | F_OS;

	memset( keyval_pair_ptr->child_node , 0 , NODE_SIZE );
	tree->n_allocations++;

	item_position = (hash & bits_selector) >> shift_amount;

	keyval_pair_ptr = keyval_pair_ptr->child_node; 
	keyval_pair_ptr+= item_position;

	keyval_pair_ptr->key = key;
	keyval_pair_ptr->value = value;
	keyval_pair_ptr->hash = hash;

	return SUCCESS;
}






/**
 *  Returns on error:
 *    NULL      Item not found
 *
 *  Returns on success:
 *    the value of the key you are looking for
 *
**/
char *
ht_get_item ( HT_Tree * tree , char * key , size_t key_length )
{
	uint64_t hash = rapidhash( key , key_length );
	uint64_t bits_selector = BITS_SELECTOR;
	unsigned shift_amount = 0;

	HT_KeyValue * node_iterator = tree->root_node;

	HT_KeyValue * keyval_pair_ptr;
	unsigned item_position;

	while( node_iterator != NULL )
	{
		item_position = (hash & bits_selector) >> shift_amount;
		bits_selector<<=SHIFTED_BITS;
		shift_amount+=SHIFTED_BITS;

		keyval_pair_ptr = node_iterator + item_position;

		if ( keyval_pair_ptr->key == 0 )
			return NULL;  

		if ( keyval_pair_ptr->hash == hash && 
				strcmp(keyval_pair_ptr->key , key)==0 )
			return keyval_pair_ptr->value;

		node_iterator = keyval_pair_ptr->child_node;
	}

	/** WARNING: node_iterator is NULL do not use it. Use keyval_pair_ptr instead. */

	return NULL;
}





/**
 *  Returns on error:
 *    FAIL_ATOMIC | F_BAD_USE    the key-value pair not found
 *
 *  Returns on success:
 *    SUCCESS            the key-value pair has been removed
**/
Status
ht_remove_item ( HT_Tree * tree , char *  key , size_t key_length )
{
	uint64_t hash = rapidhash( key , key_length );
	uint64_t bits_selector = BITS_SELECTOR;
	unsigned shift_amount = 0;

	HT_KeyValue * node_iterator = tree->root_node;
	HT_KeyValue * last_node = tree->root_node;

	HT_KeyValue * keyval_pair_ptr = NULL;
	HT_KeyValue * last_keyval_ptr;
	HT_KeyValue * keyval_2_remove_ptr = NULL;
	unsigned item_position;

	while ( node_iterator != NULL )
	{
		item_position = (hash & bits_selector) >> shift_amount;
		bits_selector<<=SHIFTED_BITS;
		shift_amount+=SHIFTED_BITS;

		last_keyval_ptr = keyval_pair_ptr;
		keyval_pair_ptr = node_iterator + item_position;

		if ( keyval_pair_ptr->hash == hash &&
				strcmp(keyval_pair_ptr->key , key)==0 )
		{
			keyval_2_remove_ptr = keyval_pair_ptr;

			// remove keyvals in leaf nodes directly because they
			// have no children to worry about
			if ( keyval_2_remove_ptr->child_node == NULL )
			{
				/*  Iterate over the key-value pairs in the node to calculate
					how much occupied key-value pairs your have left in your node*/
				unsigned n_occupied_keyvals = 0;

				for ( int i=0 ; i<N_KEYS_PER_NODE ; i++ )
				{
					if( last_node[i].key != NULL )
					{
						n_occupied_keyvals++;
						keyval_pair_ptr = last_node + i;
					}
				}


				memset(keyval_2_remove_ptr, 0 , sizeof(HT_KeyValue));
				return SUCCESS;
			}
		}
		
		last_node = node_iterator;
		node_iterator = keyval_pair_ptr->child_node;
	}

	/** WARNING: node_iterator is NULL do not use it. Use keyval_pair_ptr instead. */


	unsigned n_occupied_keyvals = 0;

	if( keyval_2_remove_ptr == NULL )	return FAIL_ATOMIC | F_BAD_USE;


	/** NOTE:
	 *    after this loop keyval_pair_ptr this will be a candidate to replace
	 *    the key you wanna remove.
	**/
	keyval_pair_ptr = NULL; 
	for ( int i=0 ; i<N_KEYS_PER_NODE ; i++ )
	{
		if( last_node[i].key != NULL )
		{
			n_occupied_keyvals++;
			keyval_pair_ptr = last_node + i;
		}
	}

	// copying data 

	/** WARNING:
	 *  DO NOT copy the child_node pointer from keyval_pair_ptr to
	 *  keyval_2_remove_ptr because you will lose access to all the
	 *  children keyval_2_remove_ptr has.
	**/
	keyval_2_remove_ptr->value = keyval_pair_ptr->value;
	keyval_2_remove_ptr->key = keyval_pair_ptr->key;
	keyval_2_remove_ptr->hash = keyval_pair_ptr->hash;


	// keyval_pair_ptr->hash = 0;
	// keyval_pair_ptr->key = NULL;
	// keyval_pair_ptr->value = NULL;
	memset( keyval_pair_ptr , 0 , sizeof(HT_KeyValue) );

	//printf( "DEBUG: n_occupied_keyvals: %u\n" , n_occupied_keyvals );

	if ( n_occupied_keyvals == 1 )
	{
		free( last_keyval_ptr->child_node );
		last_keyval_ptr->child_node = NULL;
		tree->n_free++;
	}

	return SUCCESS;
}






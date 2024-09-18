#include <stdio.h>
#include <stdlib.h>

#include "../include/test_cfg.h"
#include "../include/ht_tree.h"



char charset[] = {
		'0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' ,
		'8' , '9' , 'A' , 'B' , 'C' , 'D' , 'E' , 'F'
};


char * int_2_str_hex( uint32_t num )
{
	uint32_t shift_amount = 0;
	uint32_t bits_selector = 0b1111;

	char * buffer = malloc( 17 );
	buffer[16] = '\0';

	char * ptr = buffer+15;

	for( unsigned i=0 ; i<16 ; i++ )
		{
			uint32_t index = (num & bits_selector) >> shift_amount;
			shift_amount+=4;
			bits_selector<<=4;

			*ptr = charset[ index ];
			ptr--;
		}

	return buffer;
}





int main ()
{
	printf( "sizeof HN_Node: %lu\n" , sizeof( HT_KeyValue ) );
	printf( "Number of child nodes: %u\n" , N_KEYS_PER_NODE );

	HT_Tree tree;
	Status status = ht_init_tree( &tree );

	if ( status != SUCCESS )
	{
		printf( "failed to initialise!!\n" );
		return -1;
	}

	char * item;
	char * str_num;
	size_t str_len = 0;
	
	unsigned passed_tests = 0;

	for ( uint64_t i=1; i<ITERATIONS+1 ; i++ )
	{
		str_num = int_2_str_hex( i );
		status = ht_create_item( &tree , str_num , 16 , str_num );

		if (  status != SUCCESS  )
		{
			printf( "E: test failed could not create new elements\n" );
			break;
		}

		item = ht_get_item( &tree , str_num , 16 );
		//printf( "str: %p\n", item );

		if( item != str_num )
		{
			printf( "E: test failed keys create are unmatched when searched\n" );
			break;
		}

		passed_tests++;
	}

	printf( " [*] %u insert tests completed successfully  (expected %u) \n" , passed_tests , ITERATIONS );



	// statistics
	printf( "\n\n\nStatistics:\n\n" );

	printf( "  node size: %lu bytes\n" , NODE_SIZE );
	printf( "  number of key-value pair per node: %u\n" , N_KEYS_PER_NODE );

	printf( "\n  node allocated: %u \n" , tree.n_allocations );
	printf( "  nodes deallocated: %u  \n" , tree.n_free );

	long unsigned allocated_size = tree.n_allocations * sizeof(HT_KeyValue) * N_KEYS_PER_NODE;
	long unsigned freed_size = tree.n_free * sizeof(HT_KeyValue) * N_KEYS_PER_NODE;

	printf( "\n  size of total allocated memory: %lu bytes\n" , allocated_size );
	printf( "  size of total deallocated memory: %lu bytes\n" , freed_size );
	
	printf( "\n  nodes current total memory consumption: %lu bytes\n" , allocated_size - freed_size );

	return 0;
}

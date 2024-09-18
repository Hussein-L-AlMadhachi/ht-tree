#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "../include/ht_tree.h"




int main ()
{
	HT_Tree tree;
	ht_init_tree( &tree );

	unsigned tests_passed = 0;


	char user_key[1024];
	char user_value[1024];
	char command;

	while( true )
	{
		printf( "" );
		scanf("%c %s=%s\n" , &command , user_key , user_key );
		switch( command )
		{
			Status s;

			case 'c':
				s = ht_create_item( &tree , user_key , strlen(user_key) , user_key );                
				if( s != SUCCESS )
				{
					printf( "failed with status code: %u\n" , s );
					return -1;
				}
				break;

			case 'g':
				printf( "str[%s] = %s\n" , user_key , ht_get_item(&tree , user_key , strlen(user_key))  );
				break;

			case 'r':
				s = ht_remove_item( &tree , user_key , strlen(user_key) );                
				if( s != SUCCESS )
				{
					printf( "failed with status code: %u\n" , s );
					return -1;
				}
				break;

		}
	}



	// stats
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
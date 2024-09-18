#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
	HT_Tree tree;
	ht_init_tree( &tree );

	unsigned tests_passed = 0;

	// create test
	ht_create_item( &tree , "key1" , 4 , "value1" );
	ht_create_item( &tree , "key2" , 4 , "value2" );
	ht_create_item( &tree , "key3" , 4 , "value3" );
	ht_create_item( &tree , "key4" , 4 , "value4" );
	ht_create_item( &tree , "key5" , 4 , "value5" );
	ht_create_item( &tree , "key6" , 4 , "value6" );
	ht_create_item( &tree , "key7" , 4 , "value7" );
	ht_create_item( &tree , "key8" , 4 , "value8" );
	ht_create_item( &tree , "key9" , 4 , "value9" );
	ht_create_item( &tree , "key10" , 5 , "value10" );
	ht_create_item( &tree , "key11" , 5 , "value11" );
	ht_create_item( &tree , "key12" , 5 , "value12" );
	ht_create_item( &tree , "key13" , 5 , "value13" );
	ht_create_item( &tree , "key14" , 5 , "value14" );
	ht_create_item( &tree , "key15" , 5 , "value15" );
	ht_create_item( &tree , "key16" , 5 , "value16" );
	ht_create_item( &tree , "key17" , 5 , "value17" );
	ht_create_item( &tree , "key18" , 5 , "value18" );
	ht_create_item( &tree , "key19" , 5 , "value19" );
	ht_create_item( &tree , "key20" , 5 , "value20" );
	ht_create_item( &tree , "key21" , 5 , "value21" );
	ht_create_item( &tree , "key22" , 5 , "value22" );
	ht_create_item( &tree , "key23" , 5 , "value23" );
	ht_create_item( &tree , "key24" , 5 , "value24" );
	ht_create_item( &tree , "key25" , 5 , "value25" );
	ht_create_item( &tree , "key26" , 5 , "value26" );
	ht_create_item( &tree , "key27" , 5 , "value27" );
	ht_create_item( &tree , "key28" , 5 , "value28" );
	ht_create_item( &tree , "key29" , 5 , "value29" );
	ht_create_item( &tree , "key30" , 5 , "value30" );
	ht_create_item( &tree , "key31" , 5 , "value31" );
	ht_create_item( &tree , "key32" , 5 , "value32" );
	ht_create_item( &tree , "key33" , 5 , "value33" );
	ht_create_item( &tree , "key34" , 5 , "value34" );
	ht_create_item( &tree , "key35" , 5 , "value35" );
	ht_create_item( &tree , "key36" , 5 , "value36" );
	ht_create_item( &tree , "key37" , 5 , "value37" );
	ht_create_item( &tree , "key38" , 5 , "value38" );
	ht_create_item( &tree , "key39" , 5 , "value39" );
	ht_create_item( &tree , "key40" , 5 , "value40" );
	ht_create_item( &tree , "key41" , 5 , "value41" );
	ht_create_item( &tree , "key42" , 5 , "value42" );
	ht_create_item( &tree , "key43" , 5 , "value43" );
	ht_create_item( &tree , "key44" , 5 , "value44" );






	// remove test
	ht_remove_item( &tree , "key1" , 4  );
	ht_remove_item( &tree , "key2" , 4  );
	ht_remove_item( &tree , "key3" , 4  );
	ht_remove_item( &tree , "key4" , 4  );
	ht_remove_item( &tree , "key5" , 4  );
	ht_remove_item( &tree , "key6" , 4  );
	ht_remove_item( &tree , "key7" , 4  );
	ht_remove_item( &tree , "key8" , 4  );
	ht_remove_item( &tree , "key9" , 4  );
	ht_remove_item( &tree , "key10" , 5);
	ht_remove_item( &tree , "key11" , 5);

	ht_remove_item( &tree , "key14" , 5);

	ht_remove_item( &tree , "key16" , 5);
	ht_remove_item( &tree , "key17" , 5);
	ht_remove_item( &tree , "key18" , 5);
	ht_remove_item( &tree , "key19" , 5);
	
	ht_remove_item( &tree , "key22" , 5);
	ht_remove_item( &tree , "key23" , 5);
	ht_remove_item( &tree , "key24" , 5);
	ht_remove_item( &tree , "key25" , 5);
	ht_remove_item( &tree , "key26" , 5);
	ht_remove_item( &tree , "key27" , 5);
	ht_remove_item( &tree , "key28" , 5);
	ht_remove_item( &tree , "key29" , 5);

	ht_remove_item( &tree , "key39" , 5);

	ht_remove_item( &tree , "key40" , 5);

	ht_remove_item( &tree , "key42" , 5);





	// fetch test
	printf( "check value key1: %s\n" , ht_get_item( &tree , "key1" , 4  ) );
	printf( "check value key2: %s\n" , ht_get_item( &tree , "key2" , 4  ) );
	printf( "check value key3: %s\n" , ht_get_item( &tree , "key3" , 4  ) );
	printf( "check value key4: %s\n" , ht_get_item( &tree , "key4" , 4  ) );
	printf( "check value key5: %s\n" , ht_get_item( &tree , "key5" , 4  ) );
	printf( "check value key6: %s\n" , ht_get_item( &tree , "key6" , 4  ) );
	printf( "check value key7: %s\n" , ht_get_item( &tree , "key7" , 4  ) );
	printf( "check value key8: %s\n" , ht_get_item( &tree , "key8" , 4  ) );
	printf( "check value key9: %s\n" , ht_get_item( &tree , "key9" , 4  ) );
	printf( "check value key10: %s\n" , ht_get_item( &tree , "key10" , 5) );
	printf( "check value key11: %s\n" , ht_get_item( &tree , "key11" , 5) );
	printf( "check value key12: %s\n" , ht_get_item( &tree , "key12" , 5) );
	printf( "check value key13: %s\n" , ht_get_item( &tree , "key13" , 5) );
	printf( "check value key14: %s\n" , ht_get_item( &tree , "key14" , 5) );
	printf( "check value key15: %s\n" , ht_get_item( &tree , "key15" , 5) );
	printf( "check value key16: %s\n" , ht_get_item( &tree , "key16" , 5) );
	printf( "check value key17: %s\n" , ht_get_item( &tree , "key17" , 5) );
	printf( "check value key18: %s\n" , ht_get_item( &tree , "key18" , 5) );
	printf( "check value key19: %s\n" , ht_get_item( &tree , "key19" , 5) );
	printf( "check value key20: %s\n" , ht_get_item( &tree , "key20" , 5) );
	printf( "check value key21: %s\n" , ht_get_item( &tree , "key21" , 5) );
	printf( "check value key22: %s\n" , ht_get_item( &tree , "key22" , 5) );
	printf( "check value key23: %s\n" , ht_get_item( &tree , "key23" , 5) );
	printf( "check value key24: %s\n" , ht_get_item( &tree , "key24" , 5) );
	printf( "check value key25: %s\n" , ht_get_item( &tree , "key25" , 5) );
	printf( "check value key26: %s\n" , ht_get_item( &tree , "key26" , 5) );
	printf( "check value key27: %s\n" , ht_get_item( &tree , "key27" , 5) );
	printf( "check value key28: %s\n" , ht_get_item( &tree , "key28" , 5) );
	printf( "check value key29: %s\n" , ht_get_item( &tree , "key29" , 5) );
	printf( "check value key30: %s\n" , ht_get_item( &tree , "key30" , 5) );
	printf( "check value key31: %s\n" , ht_get_item( &tree , "key31" , 5) );
	printf( "check value key32: %s\n" , ht_get_item( &tree , "key32" , 5) );
	printf( "check value key33: %s\n" , ht_get_item( &tree , "key33" , 5) );
	printf( "check value key34: %s\n" , ht_get_item( &tree , "key34" , 5) );
	printf( "check value key35: %s\n" , ht_get_item( &tree , "key35" , 5) );
	printf( "check value key36: %s\n" , ht_get_item( &tree , "key36" , 5) );
	printf( "check value key37: %s\n" , ht_get_item( &tree , "key37" , 5) );
	printf( "check value key38: %s\n" , ht_get_item( &tree , "key38" , 5) );
	printf( "check value key39: %s\n" , ht_get_item( &tree , "key39" , 5) );
	printf( "check value key40: %s\n" , ht_get_item( &tree , "key40" , 5) );
	printf( "check value key41: %s\n" , ht_get_item( &tree , "key41" , 5) );
	printf( "check value key42: %s\n" , ht_get_item( &tree , "key42" , 5) );
	printf( "check value key43: %s\n" , ht_get_item( &tree , "key43" , 5) );
	printf( "check value key44: %s\n" , ht_get_item( &tree , "key44" , 5) );






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
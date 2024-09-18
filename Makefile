debug:
	gcc -g src/*.c test/benchmarks.c -o benchmarks
	gcc -g src/*.c test/test.c -o tests

release:
	gcc -O3 src/*.c test/*.c -o ht_test

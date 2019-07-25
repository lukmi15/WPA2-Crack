#run: test.out Makefile
#	./$<

test: main.cpp wpa2_hash_wrapper.hpp wpa2_hash_wrapper.cpp sha1.c sha1.h Makefile wpa2_hash.h wpa2_hash.c
	g++ --std=c++11 -Wall -o $@.out $< wpa2_hash.c sha1.c wpa2_hash_wrapper.cpp -fopenmp -O3 -march=native

.PHONY: run

test.out: main.cpp wpa2_hash_wrapper.hpp wpa2_hash_wrapper.cpp sha1.c sha1.h Makefile wpa2_hash.h wpa2_hash.c
	mpiCC --std=c++11 -Wall -o $@ $< wpa2_hash.c sha1.c wpa2_hash_wrapper.cpp -O3 -march=native

run: test.out Makefile
	mpirun --use-hwthread-cpus $<

clean:
	@sh -c 'rm *.out -v 2>/dev/null'; exit 0

.PHONY: run clean

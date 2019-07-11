run: test Makefile
	./$<

test: test.cpp wpa2_hash_wrapper.hpp wpa2_hash_wrapper.cpp sha1.c sha1.h Makefile wpa2_hash.h wpa2_hash.c
	g++ -Wall -o $@ $< $> sha1.c wpa2_hash_wrapper.cpp

.PHONY: run
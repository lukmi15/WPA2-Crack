/*Calculating WPA2 PSK hashes
Author(s)		: Lukas Mirow, contributors of the wpa_supplicant project
*/

#define HASHES_PER_RUN 180
#define RUNS 5
#define DEBUG
#define FAKE_SSID "ssid"
#define FAKE_PSK "psk"

#include <iostream>
#include "wpa2_hash_wrapper.hpp"
#include <mpi.h>
#include <cmath>
using namespace std;

float calc_hashes_per_second(unsigned& amount, struct timespec& start, struct timespec& end)
{
	float ret;
	ret = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
	ret = (float)amount / ret;
	return ret;
}

float execute_benchmarks(unsigned amount)
{
	int id, process_count;
	struct timespec t_start, t_end;
	unsigned h_start, h_end;
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	h_start = HASHES_PER_RUN / process_count * id;
	h_end = h_start + HASHES_PER_RUN/ process_count;
#ifdef DEBUG
		cout << "Process " << id << " from " << h_start << " to " << h_end << endl;
#endif //DEBUG
	clock_gettime(CLOCK_MONOTONIC_RAW, &t_start);
	for (size_t i = h_start; i < h_end; i++)
		calc_wpa2_hash(FAKE_SSID, FAKE_PSK);
	clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
	return calc_hashes_per_second(amount, t_start, t_end);
}

void print_benchmark_result(float *res)
{
	float min, lowq, mean, highq, max;
	min = INFINITY;
	mean = 0;
	max = -INFINITY;
	for (unsigned i = 0; i < RUNS; i++)
	{
		if (res[i] < min)
			min = res[i];
		if (res[i] > max)
			max = res[i];
		mean += res[i];
	}
	mean /= RUNS;
	cout << RUNS << " times " << HASHES_PER_RUN << " hashes were calculated" << endl;
	cout << "Minimum hashes per second: " << min << endl;
	cout << "Average hashes per second: " << mean << endl;
	cout << "Maximum hashes per second: " << max << endl;
}

int main(int argc, char **argv)
{
	float res[RUNS];
	if (MPI_Init(&argc, &argv) != 0)
		exit(1);
	for (unsigned j = 0; j < RUNS; j++)
		res[j] = execute_benchmarks(HASHES_PER_RUN);
	MPI_Finalize();
	print_benchmark_result(res); //FIXME: Is printed in every process...
	return 0;
}

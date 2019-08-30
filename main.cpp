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
#include <sstream>
#include <mpi.h>
#include <utility>
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
	struct timespec t_start, t_end;
	unsigned h_start, h_end;
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	h_start = HASHES_PER_RUN / process_count * id;
	h_end = start + HASHES_PER_RUN/ process_count;
	clock_gettime(CLOCK_MONOTONIC_RAW, &t_start);
	for (size_t i = start; i < end; i++)
		calc_wpa2_hash(FAKE_SSID, FAKE_PSK);
	clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);
	return calc_hashes_per_second(amount, t_start, t_end);
}

void print_benchmark_result(float& res)
{
	cout << "Average hashes per second of " << HASHES_PER_RUN << " hashes per run: " << res;
}

int main(int argc, char **argv)
{
	int id, process_count;
	size_t start, end;
	float sum = 0;
	if (MPI_Init(&argc, &argv) != 0)
		exit(1);
	for (unsigned j = 0; j < RUNS; j++)
	{
#ifdef DEBUG
		cout << "Process " << id << " from " << start << " to " << end << endl;
#endif //DEBUG
		print_benchmark_result(execute_benchmarks(HASHES_PER_RUN));
	}
	MPI_Finalize();
	return 0;
}

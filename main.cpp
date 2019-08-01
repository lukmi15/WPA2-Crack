/*Calculating WPA2 PSK hashes
Author(s)		: Lukas Mirow, contributors of the wpa_supplicant project
*/

#define HASHES 1800
#define DEBUG

#include <iostream>
#include "wpa2_hash_wrapper.hpp"
#include <sstream>
#include <mpi.h>
using namespace std;

int main(int argc, char **argv)
{
	int id, process_count;
	size_t start, end;
	if (MPI_Init(&argc, &argv) != 0)
		exit(1);
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	start = HASHES / process_count * id;
	end = start + HASHES / process_count;
#ifdef DEBUG
	cout << "Process " << id << " from " << start << " to " << end << endl;
#endif //DEBUG
	for (size_t i = start; i < end; i++)
		calc_wpa2_hash("ssid", "1");
	MPI_Finalize();
	return 0;
}

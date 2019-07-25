/*Calculating WPA2 PSK hashes
Author(s)		: Lukas Mirow, contributors of the wpa_supplicant project
*/

#include <iostream>
#include "wpa2_hash_wrapper.hpp"
#include <sstream>
#include <omp.h>
using namespace std;

int main(int argc, char **argv)
{
#pragma omp parallel for
	for (size_t i = 0; i < 1800; i++)
	{
		stringstream ss;
		ss << i;
		calc_wpa2_hash("ssid", ss.str().c_str());
	}
	return 0;
}

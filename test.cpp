/*First test to calculate the hash of a WPA2 network password
Author(s)		: Lukas Mirow, contributors of the wpa_supplicant project
*/

#include <iostream>
#include "wpa2_hash_wrapper.hpp"
using namespace std;

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		printf("Too few arguments!\n");
		exit(1);
	}
	cout << hex << calc_wpa2_hash(argv[1], argv[2]) << endl;
	return 0;
}

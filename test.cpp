/*First test to calculate the hash of a WPA2 network password
Author(s)		: Lukas Mirow, contributors of the wpa_supplicant project
*/

#include <iostream>
#include "wpa2_hash_wrapper.hpp"
using namespace std;

int main(int argc, char ** argv)
{
	cout << calc_wpa2_hash("SSID", "PASS") << endl;
	return 0;
}

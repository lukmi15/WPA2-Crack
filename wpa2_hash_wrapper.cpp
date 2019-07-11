/*Wrapper for the WPA2 hash algorithm for the WPA2 crack project in SCE2
Author(s)		: Lukas Mirow
Date of creation	: 7/11/2019
*/

#include "wpa2_hash_wrapper.hpp"
#include <sstream>
#include <string.h>
using namespace std;

string data2hex(unsigned char data)
{
	stringstream ss;
	ss << hex << data;
	return ss.str();
}

string calc_wpa2_hash(const string& ssid, const string& pass)
{
	char cpass[pass.length() + 1];
	unsigned char res[RES_LEN];
	uint8_t cssid[ssid.length() + 1];
	strcpy(cssid, static_cast<uint8_t*>(ssid.c_str()));
	strcpy(cpass, pass.c_str());
	pbkdf2_sha1(cpass, cssid, ssid.length(), ITERATIONS, res, RES_LEN); //FIXME: Does the 3rd parameter contain the null byte of the string?
	return data2hex(res);
}

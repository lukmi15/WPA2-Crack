/*Wrapper for the WPA2 hash algorithm for the WPA2 crack project in SCE2
Author(s)		: Lukas Mirow
Date of creation	: 7/11/2019
*/

#define RES_LEN 32
#define ITERATIONS 4096

#include "wpa2_hash_wrapper.hpp"
#include <sstream>
#include <string.h>
using namespace std;

#include <iostream>
#include <ios>

string data2hex(unsigned *data)
{
	stringstream ss;
	ss << hex << data;
	return ss.str();
}

string calc_wpa2_hash(const string& ssid, const string& pass)
{
	char cpass[pass.length() + 1], cssid[ssid.length() + 1];
	uint8_t res[RES_LEN];
	strcpy(cssid, ssid.c_str());
	strcpy(cpass, pass.c_str());
	fprintf(stderr, "Calling with: (`%s`, `%s`, %u, %u, %p, %u)\n", cpass, cssid, ssid.length(), ITERATIONS, res, RES_LEN);//DEBUG
	if (pbkdf2_sha1(cpass, (const uint8_t*)cssid, ssid.length(), ITERATIONS, res, RES_LEN)) //FIXME: Does the 3rd parameter contain the null byte of the string?
		return "";
	return data2hex((unsigned*)res);
}

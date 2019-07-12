/*Header for WPA2 hash algorithm wrapper for the WPA2 crack project in SCE2
Author(s)		: Lukas Mirow
Date of creation	: 7/11/2019
*/

#ifndef WPA2_HASH_WRAPPER_H
#define WPA2_HASH_WRAPPER_H

#define RES_LEN 32
#define ITERATIONS 4096

#include <string>
#include "wpa2_hash.h"

std::string data2hex(uint8_t *data);
std::string calc_wpa2_hash(const std::string& ssid, const std::string& pass);

#endif //WPA2_HASH_WRAPPER_H

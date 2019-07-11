/*Header for the WPA2 hash algorithm for the WPA2 crack project of SCE2
Author(s)		: Lukas Mirow, contributors of the wpa_supplicant project
Date of creation	: 7/11/2019
The code from this file was adapted from the wpa_supplicant project.
*/

#ifndef WPA2_HASH_H
#define WPA2_HASH_H

#define TEST_FAIL ret_false
#define SHA1_MAC_LEN 20

int sha1_vector(size_t num_elem, const uint8_t *addr[], const size_t *len, uint8_t *mac);
int hmac_sha1_vector(const uint8_t *key, size_t key_len, size_t num_elem, const uint8_t *addr[], const size_t *len, uint8_t *mac);
int hmac_sha1(const uint8_t *key, size_t key_len, const uint8_t *data, size_t data_len, uint8_t *mac);
int pbkdf2_sha1_f(const char *passphrase, const uint8_t *ssid, size_t ssid_len, int iterations, unsigned int count, uint8_t *digest);
int pbkdf2_sha1(const char *passphrase, const uint8_t *ssid, size_t ssid_len, int iterations, uint8_t *buf, size_t buflen);


#endif /*WPA2_HASH_H*/

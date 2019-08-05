# WPA2-Crack
Project of the seminar Special Computer Engineering in summer semester 2019 at HTW Berlin


## Project goal
Goal of this project is to create a program using OpenMP to be able to generate as many hashes of a WPA2 key as possible.
Optionally, we may use a dictionary, GPU acceleration, or computing clusters using Open MPI.


## References
Thanks to the project [wpa_supplicant](https://w1.fi/wpa_supplicant/) which we are using as reference for the hash algorithm.

The code adapted from wpa_supplicant are in the `wpa2_hash.*` and `sha1.*` files.

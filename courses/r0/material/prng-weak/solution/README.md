
Main problems:

* open() and read() return values not checked
* Seed is too short (32 bits only)
* Weak underlying PRNG and entropy source (libc's random())
* Sampling algorithm is biased
* memset() may be optimized out
* memset() has inverted arguments

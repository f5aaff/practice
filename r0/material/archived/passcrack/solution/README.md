Below are the hash functions used, password, and a hashcat command that
recovers the password efficiently:

HASH1 = SHA-1("pizza")
hashcat -m 100 -a 3 HASH1 "?l?l?l?l?l"

HASH2 = MD5("Crypt0")
hashcat -m 0 -a 3 HASH2 "?u?l?l?l?l?d"

HASH3 = SHA-256("Pa55!")
hashcat -m 1400 -a 3 HASH3 "?a?a?a?a?a"

HASH4 = SHA-1("L58jkdjP!")
hashcat -m 100 HASH4 top100kpasswords.txt

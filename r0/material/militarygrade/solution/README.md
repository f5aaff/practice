# Solution

Keys as short as 31 bits, and as long as at least 1000000000 bits can be
generated. 

Very short keys might be used for pedagogical purposes, but are of
course insecure, as well as keys of less than 1024 bits. However,
completely disabling the support for short keys might break certain
applications, so a reasonable option might be to add clear warnings
about the insecurity of such keys.

Regarding long keys, the supported values lead to public keys or dozens
of megabytes, and have no reason to be used (except maybe to get better
quantum protection <http://cr.yp.to/papers/pqrsa-20170419.pdf>).

However, we would recommend to add a warning, and ask for user
confirmation to generate such abnormal keys.



$ openssl genrsa 1000000000000                                                                                         
usage: genrsa [args] [numbits]
 -des            encrypt the generated key with DES in cbc mode
 -des3           encrypt the generated key with DES in ede cbc mode (168 bit key)
 -aes128, -aes192, -aes256
                 encrypt PEM output with cbc aes
 -camellia128, -camellia192, -camellia256
                 encrypt PEM output with cbc camellia
 -out file       output the key to 'file
 -passout arg    output file pass phrase source
 -f4             use F4 (0x10001) for the E value
 -3              use 3 for the E value

$ openssl genrsa 100000000000                                                                                            
Generating RSA private key, 1215752192 bit long modulus
4721958572:error:03FFF072:bignum routines:CRYPTO_internal:bignum too long:/System/Volumes/Data/SWE/macOS/BuildRoots/e90674e518/Library/Caches/com.apple.x
bs/Sources/libressl/libressl-56.60.2/libressl-2.8/crypto/bn/bn_lib.c:274:
4721958572:error:04FFF003:rsa routines:CRYPTO_internal:BN lib:/System/Volumes/Data/SWE/macOS/BuildRoots/e90674e518/Library/Caches/com.apple.xbs/Sources/l
ibressl/libressl-56.60.2/libressl-2.8/crypto/rsa/rsa_gen.c:221:

$ openssl genrsa 10000000000                                                                                             
Generating RSA private key, 1410065408 bit long modulus
4640489132:error:03FFF072:bignum routines:CRYPTO_internal:bignum too long:/System/Volumes/Data/SWE/macOS/BuildRoots/e90674e518/Library/Caches/com.apple.x
bs/Sources/libressl/libressl-56.60.2/libressl-2.8/crypto/bn/bn_lib.c:274:
4640489132:error:04FFF003:rsa routines:CRYPTO_internal:BN lib:/System/Volumes/Data/SWE/macOS/BuildRoots/e90674e518/Library/Caches/com.apple.xbs/Sources/l
ibressl/libressl-56.60.2/libressl-2.8/crypto/rsa/rsa_gen.c:221:

$ openssl genrsa 1000000000                                                                                              
Generating RSA private key, 1000000000 bit long modulus
^C

$ openssl genrsa 30                                                                                                    
Generating RSA private key, 30 bit long modulus
.+++++++++++++++++++++++++++
.+++++++++++++++++++++++++++.+++++++++++++++++++++++++++.+++++++++++++++++++++++++++4650303148:error:04FFF078:rsa routines:CRYPTO_internal:key size too s
mall:/System/Volumes/Data/SWE/macOS/BuildRoots/e90674e518/Library/Caches/com.apple.xbs/Sources/libressl/libressl-56.60.2/libressl-2.8/crypto/rsa/rsa_gen.
c:165:

$ openssl genrsa 31                                                                                                      
Generating RSA private key, 31 bit long modulus
.+++++++++++++++++++++++++++
.+++++++++++++++++++++++++++
e is 65537 (0x10001)
-----BEGIN RSA PRIVATE KEY-----
MCsCAQACBQCGmThdAgMBAAECBHSK8dECAwD12wIDAIwnAgJ5LQICTGsCAgND
-----END RSA PRIVATE KEY-----

$ openssl genrsa 9000000000 
Generating RSA private key, 410065408 bit long modulus
^C

$ openssl genrsa 9900000000
Generating RSA private key, 1310065408 bit long modulus
4538351276:error:03FFF072:bignum routines:CRYPTO_internal:bignum too
long:/System/Volumes/Data/SWE/macOS/BuildRoots/e90674e518/Library/Caches/com.apple.xbs/Sources/libressl/libressl-56.60.2/libressl-2.8/crypto/bn/bn_lib.c:274:
4538351276:error:04FFF003:rsa routines:CRYPTO_internal:BN
lib:/System/Volumes/Data/SWE/macOS/BuildRoots/e90674e518/Library/Caches/com.apple.xbs/Sources/libressl/libressl-56.60.2/libressl-2.8/crypto/rsa/rsa_gen.c:221:

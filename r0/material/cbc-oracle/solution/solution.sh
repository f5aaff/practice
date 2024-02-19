# The following gives the solution to CBCoracle. The source of the
# program is provided in CBCoracle.go (it contains the secret key used,
# but the goal wasn't to reverse engineer the program and get the key :-)
#
# We have the block 8f5fc4678ae5de69cc987d0c1207acbe = AES_enc(K,P) for some
# unknown plaintext P, and we want P
# 
# Given a ciphertext block C and an IV, the CBC decryption oracle will compute
# IV xor AES_dec(K, C)
# and will check that the *padding* is correct, that is, that the block
# finishes with either
# 01
# 02 02
# 03 03 03
# etc. til ff sixteen times
# 
# If we're lucky, maybe our block will decrypt to a block with valid
# padding (note the all-zero IV here):
# 
# $ ./CBCoracle d 00000000000000000000000000000000 8f5fc4678ae5de69cc987d0c1207acbe
# INVALID PADDING
# 
# No luck! Padding is invalid!
# 
# What we can do, however, is find an IV that give a raw plaintext with
# valid padding so that we obtain the decrypted ciphertext.
# 
# Now let's script a search for the most likely valid padding: a last
# byte equal to 01. Here we'll just bruteforce the last byte until we
# find a valid padding (most likely, last byte 0x01):
# 
# But the ciphertext obtained won't exactly be what we need: we'll get
# P = IV xor AES_dec(K, C)
# but we want only AES_dec(K, C), so we'll just compute P xor IV to
# recover that value.

IVPREFIX="000000000000000000000000000000"
BLOCK="8f5fc4678ae5de69cc987d0c1207acbe"

for nibble1 in "0" "1" "2" "3" "4" "5" "6" "7" "8" "9" "a" "b" "c" "d" "e" "f"; do
    for nibble2 in "0" "1" "2" "3" "4" "5" "6" "7" "8" "9" "a" "b" "c" "d" "e" "f"; do
        IV=$IVPREFIX$nibble1$nibble2
        echo "trying IV = $IV"
        ./CBCOracle d $IV $BLOCK | grep -v "INVALID"
    done
done

# and indeed, with the IV 000000000000000000000000000000ab
# we obtain the plaintext badab00d00daaaaaaaaaaaaaaaaaaa
# but this plaintext is only 15-byte, since CBC decryption stripped the
# last byte off. We can recover it by woring 0xab (from the IV) with
# 0x01 (the expected plaintext byte), so that we get the complete block:
# badab00d00daaaaaaaaaaaaaaaaaaaaa
#

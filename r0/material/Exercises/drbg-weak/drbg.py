#!/usr/bin/env python3

INTERNAL_STATE =  0

MASK = 0xffffffffffffffff

def update(seed):
    global INTERNAL_STATE
    INTERNAL_STATE = ( INTERNAL_STATE * 0x123111 ) & MASK
    INTERNAL_STATE += ( INTERNAL_STATE >> 31 )
    INTERNAL_STATE += ( INTERNAL_STATE << 12 )
    INTERNAL_STATE ^= ( seed & ( MASK & 0x77 ))
    INTERNAL_STATE = ( INTERNAL_STATE * 0x99999f ) & MASK
    INTERNAL_STATE += ( INTERNAL_STATE >> 1 )

def mix(word):
    word = (0xdeadbeef * word) ^ word
    word = word & 0xffffffff
    word = ( word >> 1 ) ^ 0x7890abcd
    return word

# initializes the internal state, given a 32-bit seed
def drbg_init(seed):
    global INTERNAL_STATE
    INTERNAL_STATE =  0
    update(seed)
    print(INTERNAL_STATE)

def drbg_get_random_word():
    update(0)
    word = INTERNAL_STATE & 0xffffffff
    return mix(word)

def main():
    import sys
    if len(sys.argv) < 2:
        print("missing seed")
        sys.exit(0)
    try:
        seed = int(sys.argv[1])
        if ( seed < 0 ) or ( seed >= 2**32 ):
            raise Exception()
    except:
        print("invalid seed, should be a 32-bit number")
        sys.exit(0)
    print("using seed %d" % seed)
    drbg_init(seed)
    print("computing 8 random words:")
    for i in range(8):
        sys.stdout.write("%08x " % drbg_get_random_word())
    print()

if __name__ == '__main__':
    main()

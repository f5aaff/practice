#!/usr/bin/env python3

KEYKCV="4b12cc98a7716463fff2841c5d45beb687b5e804103ab5c7e40811e96a20656aa9c020fd"

KEY=bytes.fromhex(KEYKCV[:64])
LAST4=KEYKCV[-8:]

import hashlib
KCV=hashlib.blake2s(KEY).digest()[:4]

if KCV.hex() == LAST4:
    print("You win")
else:
    print("Failed")



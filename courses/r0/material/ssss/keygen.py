#!/usr/bin/env python3

import secrets
KEY=secrets.token_bytes(32)

import hashlib
KCV=hashlib.blake2s(KEY).digest()[:4]

SECRET=KEY.hex()+KCV.hex()
print(SECRET)






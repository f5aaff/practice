# AES-CTR

#### Requirements

- [python3](https://www.python.org/)
- [pycryptodome](https://github.com/Legrandin/pycryptodome)

#### Exercise

You obtained a file `encrypted.log` which includes logs of a decryption server
in the following format:

```
(nonce, 16-byte);(ciphertext, any size);(plaintext, same size a ciphertext)
```

Unfortunately, the decryption server was destroyed and the secret key needed to
decrypt was lost. Can you nevertheless decrypt the following ciphertext by using
information from the logs?

```
     nonce = d99795161dc142b732e6eb7785090742
ciphertext = b84cb4d782b0deb4a38e3a431ecf07124ee4508d125d7d5d99168a42020a1cba51a8462eb6091f2ddc4a6be71e0ec151ff8f83502809
```

You also obtained `encrypt.py`, the Python program used to generate this
ciphertext, where the key and plaintext were passed as command-line arguments.


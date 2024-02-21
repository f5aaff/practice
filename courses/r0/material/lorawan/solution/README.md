1. AES in CTR mode, AES-CMAC for authentication, see 4.3.3 and 4.4; MAC
computed over the ciphertext (best option)
2. Confidentiality and authenticity
3. No, if a symmetric key leaks all previous ciphertexts can be
decrypted.
4. Since a key is shared between a client and the server, if the server
is compromised all client keys can be compromised.
5. Avoid using same key for cipher and MAC. Use longer MAC tags.

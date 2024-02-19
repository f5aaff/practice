# OpenSSL - Solutions

1. To encrypt the message use:

  ```
  openssl enc \
    -aes-128-cbc \
    -base64 \
    -pass pass:cryptorulez \
    -in msg.txt \
    -out msg.txt.enc
  ```

  To decrypt the corresponding ciphertext use:

  ```
  openssl enc -d \
    -aes-128-cbc \
    -base64 \
    -pass pass:cryptorulez \
    -in msg.txt.enc \
    -out msg.txt.dec
  ```

2. The SHA256 fingerprints of the modified passphrases can be computed as follows:

  ```
  openssl dgst -sha256 enc.pw
  SHA256(enc.pw)= 7a5e892e642ee6ea13838dd6f795ce72d4653fe06177585b30573478ce9d400c
  openssl dgst -sha256 mac.pw
  SHA256(mac.pw)= 4039efbb28529ace4663501ff79a5ef9bde4a3228ec6ab85522e2023f5b1264d
  ```

3. To decrypt the message save the ciphertext in a file `msg.txt.enc` and then decrypt it via:

  ```
  openssl enc -d \
    -chacha20 \
    -base64 \
    -K 7a5e892e642ee6ea13838dd6f795ce72d4653fe06177585b30573478ce9d400c \
    -iv c0dec0dec0dec0dec0dec0dec0dec0de \
    -in msg.txt.enc \
    -out msg.txt.dec
  ```

  The decrypted message is: 
  
  ```
  Do. Or do not. There is no try. -Yoda
  ```

4. It is correct. To verify the tag use:

  ```
  openssl dgst \
    -sha256 \
    -hmac 4039efbb28529ace4663501ff79a5ef9bde4a3228ec6ab85522e2023f5b1264d \
    msg.txt.enc
  ```

5. The private key corresponding to the given RSA public key is:

  ```
  -----BEGIN RSA PRIVATE KEY-----
  MIIEpAIBAAKCAQEA1Zi1M5x6TUmjpf8sV4Op3RpfjAs0CFvzjzE+C6HxJeMYj8KC
  ZfyuBcVFwz5zaLOYULTPjzz+l98cVIZE5FN/2t+2mXFbJN+0vvi5A43JY9YHt81F
  Msc+MF7XQoLpXwUhkSw3TkrMIhjCmoexCB9Vr+lUE3sWamEPh61d2pnwm2L2ZyU3
  BikNPgUUO6U7hd8h/urBIZLkDUsxOaD2HTYgHqHwLRELS3ewGbQqx9idEkKVtfZg
  pkIa8GiIpB1m+WqHX2zqlwyGLPAhzgCbBiP9RpO/0DlI+jnZzuQ+Drd1zXyPSxez
  MKhoXspXoxuT0IP9CQaUmUnYUxsRFfiYvI1MjQIDAQABAoIBAQCipitthr129xlf
  wUURyxfhX0Dc0ncn2mVIZ9X4Y7PPBvRgHFzRrq0RhdwOxhJ56zCUXGslhuvT2Dip
  gKkbOR5GHE7e33vpQ1ROi/XO5/wwQv4Tj4MfHKuVh9LhOfDdw3mBI6tluf1iBXrC
  04sSRVIpp0K3puY10X1S8shiOxEGMNtUzTU+Xin8prGKH1/coWstVCUMpnsKW173
  UMEBn4qHn3y+nDYUHtnmBMtmsDOdLsfoPlsVAmWHBy0jhAnSZAyZYHG88n8TvclQ
  F+7QGAx7lB/t9sklfI34ZOvf0mCEq2wt2UwKUHKZ+6l9bqTkEnOEoMz+hbgsMFY5
  npWdBomBAoGBAP4oOBFXbYH70ChO0pjL5hvis41a/Xc70qjCbj+7Gu95b1rDqHv7
  K1CcsElkXvdXP89hnR6qT1eN39jWhnahnJIaVWIpzRrcqeS1+AEzFEhNn4OrqAG8
  2Z1VYmov3H8/kqAHaC6NazKH94Z+tRR02IT4gV2RtsIcPcfsRmMx5p/tAoGBANcl
  MqpQd14p+baLv3dDGDVlw6hsDRvYlWwRpqyAW9BUDh/oxm+PD6bvpWNqN7vVJmZ9
  hMbfno+RMMRj7Rn5S3PHCyd86FtlDkCXzdcRgFfK5BQpQJ4ZsJdjr42EcoestT4e
  EmZRVcbv3EYW9GJ2s6nOqb2d+Z3YZHKGNPsHUYshAoGALRgdupX0jBeNu1kg7JNg
  5Jm4meAHENzAZ8j3nr8n7E1zgHsurbDG4qqqbJsublxAqh77rbEyGqrFiMenW+0Y
  xqN9eslH5vg3/Kh8tFnHw3xiTQ5r5MMJKW045PZQ/RLehR5LUdctqe2N8YMRxetl
  b1JYQa3U62PvYkV9x6PW85ECgYEAv1GV33yU2cjMBff5+K1SjtGDD3eepJ+SKLr9
  k7LFctn8gYW3SKdYjOPZGDHxg/gFIOkHtO5Qi2zaiBowU4OsBDYBhkj+O5/+75PO
  +SzYC7oh3ofcrXs83TNJfrhEPMBpn+aQCCrV84WDRVTOV+0k0aE0sqkTu7kdgfY0
  kPKuIeECgYBMTTTRfpDiQB/3FQlsaPtZtvf2bY/E172vzM38mPS6RD2WtBDDEZyg
  dGxqFlmyb2j7kW6gq8lATT1RM/rAyH4o4uHMkx7MUAg6XodHpT6zJc39eqEBYkfp
  pzPlvfU3VTJq3oZvYMHbrJ9vuYRJxzqJYX/Q2Wdt03tQRiO/OMML9g==
  -----END RSA PRIVATE KEY-----
  ```

  To encrypt a message towards an RSA public key and encode the ciphertext in base64 use:

  ```
  echo "Alan Turing" >> msg.txt
  openssl rsautl -encrypt -pubin -inkey public.pem -in msg.txt -out msg.enc
  openssl base64 -in msg.enc -out msg.enc.base64
  ```

  To decrypt a base64-encoded RSA ciphertext use:

  ```
  openssl base64 -d -in msg.enc.base64 -out msg.enc
  openssl rsautl -decrypt -inkey key.pem -in msg.enc -out msg.txt
  cat msg.txt
  ```

6. The private key corresponding to the above DH public key is:

  ```
  -----BEGIN PRIVATE KEY-----
  MIIBIQIBADCBlQYJKoZIhvcNAQMBMIGHAoGBAL0S3BTNhjlcy2ChLWCxyMzdMEoC
  Y2MOu9VmxlGoiPcLNkUAmCptJD4F1d95FOswggSgdDCTgaDWizZaefyhH8X1bYNq
  NrtUyZVjw1KjSzSt/Cq0Cy7h0BvIqtmfviCcAnovb3CgAp9WuLmagruqv+s2/Sgp
  mebHQAIW/qnH2DMLAgECBIGDAoGAW2MQ3Sng1RnG+J/MD2mpbnkDT/qXHheKAl3x
  YZL8/+1u2qqvn41mfvbVkxF91F1Cgo5G86A3Vo2On4nw0cTEE4J5mFTXKmk+jTqi
  6ibP9E+x9LqCiUA+bb+lak4iaVck1QNK+NzfTib/5SE5aKgm/diOMHluQVqhzrDm
  wTx5cWE=
  -----END PRIVATE KEY-----
  ```

  To do a DH key exchange using the given DH parameters and the given public
  key and derive a shared key use:

  ```
  openssl genpkey -paramfile dhp.pem -out dhkey1.pem
  openssl pkey -in dhkey1.pem -pubout -out dhpub1.pem
  openssl genpkey -paramfile dhp.pem -out dhkey2.pem
  openssl pkey -in dhkey2.pem -pubout -out dhpub2.pem
  openssl pkeyutl -derive -inkey dhkey1.pem -peerkey dhpub2.pem -out secret1.bin
  openssl pkeyutl -derive -inkey dhkey2.pem -peerkey dhpub1.pem -out secret2.bin
  openssl base64 -in secret1.bin -out secret1.bin.base64
  openssl base64 -in secret2.bin -out secret2.bin.base64
  ```

7. To create an 2048-bit RSA key pair use: 

  ```
  openssl genrsa -out key.pem 2048
  openssl rsa -in key.pem -outform PEM -pubout -out public.pem
  ```

  To create and sign a message use:

  ```
  echo "Alan Turing" >> msg.txt
  openssl dgst -sha256 -sign key.pem -out sig.sha256 msg.txt
  openssl base64 -in sig.sha256 -out sig.sha256.base64
  ```

  To verify a signature in base64 format for a given message use:

  ```
  openssl base64 -d -in sig.sha256.base64 -out sig.sha256
  openssl dgst -sha256 -verify public.pem -signature sig.sha256 msg.txt
  ```

8. Certificates can be inspected via: 

  ```
  openssl x509 -text -noout -in certificate.pem
  ```

  - From the above overview we can conclude that `HOST=cloudflare.com` and `PORT=443` (HTTPS).
  - A certificate's serial number can be determined either from the overview above or via:

    ```
    openssl x509 -serial -noout -in certificate.pem
    ```

    Result: `serial=0FD585D44B7DB37F5C3E653BF4B226F7`.

  - A certificate's validity can be determined via:

    ```
    openssl x509 -enddate -noout -in certificate.pem
    ```

    Result: `notAfter=Jul  4 12:00:00 2021 GMT`.

  - The signature algorithm is included in above the overview. Result: `ecdsa-with-SHA256`.

  - The fingerprint can be retrieved via:

    ```
    openssl x509 -fingerprint -noout -in certificate.pem
    ```

    Result: `SHA1 Fingerprint=D1:33:8B:C2:B2:C1:EB:3E:F7:97:FE:55:DE:D1:3A:75:64:95:62:26`.



# OpenSSL

The purpose of this exercise is to familiarize yourself with the usage of OpenSSL, an open source library that allows you to generate keys, encrypt messages, sign messages, etc. In many cases the OpenSSL tool comes already pre-installed with your operating system. If that's not the case, you can usually install it through your favorite package manager or download it, e.g., at https://www.openssl.org/. Make sure you have the latest stable version. Use OpenSSL to answer the following questions:

1. Save your name in a plaintext file `msg.txt`. Then symmetrically encrypt this file via OpenSSL using AES128-CBC and the passphrase `cryptorulez`. What is the base64-encoded ciphertext of your message?
2. Save the two modified passphrases `enc-cryptorulez` and `mac-cryptorulez` in the text files `enc.pw` and `mac.pw`, respectively. What are the SHA256 fingerprints of the passphrases?
3. You received the following encrypted message:

  ```
  UJb/1pBjhz4wKSQ1E6lu4hCHOjI+Hja2vYmNji+SUDMrCJUjB4c=
  ```

  This ciphertext was produced with the ChaCha20 stream cipher using the SHA256 fingerprint of `enc-cryptorulez` as a key and `c0dec0dec0dec0dec0dec0dec0dec0de` as an IV. What was the message?
4. Next to the above ciphertext you also received the following authentication tag for it:

  ```
  HMAC-SHA256(msg.txt.enc)= 8b66f744d6b2bc76933866710088f43456fe05b2121ccbb8363711f9f835f456
  ```

  It was created with the HMAC-SHA256 message authentication code using the SHA256 fingerprint of `mac-cryptorulez` as a key. Is it correct? What OpenSSL command did you use to verify it?
5. Consider the following RSA public key:

  ``` 
  -----BEGIN PUBLIC KEY-----
  MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA1Zi1M5x6TUmjpf8sV4Op
  3RpfjAs0CFvzjzE+C6HxJeMYj8KCZfyuBcVFwz5zaLOYULTPjzz+l98cVIZE5FN/
  2t+2mXFbJN+0vvi5A43JY9YHt81FMsc+MF7XQoLpXwUhkSw3TkrMIhjCmoexCB9V
  r+lUE3sWamEPh61d2pnwm2L2ZyU3BikNPgUUO6U7hd8h/urBIZLkDUsxOaD2HTYg
  HqHwLRELS3ewGbQqx9idEkKVtfZgpkIa8GiIpB1m+WqHX2zqlwyGLPAhzgCbBiP9
  RpO/0DlI+jnZzuQ+Drd1zXyPSxezMKhoXspXoxuT0IP9CQaUmUnYUxsRFfiYvI1M
  jQIDAQAB
  -----END PUBLIC KEY-----
  ```

  Create a plaintext file containing your name and encrypt it towards the above RSA public key. Provide the ciphertext in base64 format as your answer.

6. Consider the following Diffie-Hellman parameters and public key:

  ``` 
  -----BEGIN DH PARAMETERS-----
  MIGHAoGBAL0S3BTNhjlcy2ChLWCxyMzdMEoCY2MOu9VmxlGoiPcLNkUAmCptJD4F
  1d95FOswggSgdDCTgaDWizZaefyhH8X1bYNqNrtUyZVjw1KjSzSt/Cq0Cy7h0BvI
  qtmfviCcAnovb3CgAp9WuLmagruqv+s2/SgpmebHQAIW/qnH2DMLAgEC
  -----END DH PARAMETERS-----
  
  -----BEGIN PUBLIC KEY-----
  MIIBIDCBlQYJKoZIhvcNAQMBMIGHAoGBAL0S3BTNhjlcy2ChLWCxyMzdMEoCY2MO
  u9VmxlGoiPcLNkUAmCptJD4F1d95FOswggSgdDCTgaDWizZaefyhH8X1bYNqNrtU
  yZVjw1KjSzSt/Cq0Cy7h0BvIqtmfviCcAnovb3CgAp9WuLmagruqv+s2/SgpmebH
  QAIW/qnH2DMLAgECA4GFAAKBgQCEUQc+0TuYPrnNP7KP/1tR1X0tV4B/GtbKrCFU
  863vMPHzozchNvxz+uI2OJGet0evMnz7xCOoZ+w5fE00sldFegAwIaC4QW6BBZcO
  V2Twtbggz+95r7yKfNRM2ty0SV5CE8fdCeRBoMPver9gJk4uN7KyHFXWbOUzt9YR
  tiJVTQ==
  -----END PUBLIC KEY-----
  ``` 

  Do a DH key exchange and provide your public key and the shared key in base64 format as your answer.

7. Generate an RSA key pair with 2048 bits in PEM format. Then create a plaintext file containing your name and sign it using your new RSA key and SHA256. Provide your message in plaintext, signature in base64 format, and your public key in PEM format as your solution.

8. The following command sequence allows to download TLS certificates: 

  ```
  echo | openssl s_client -connect HOST:PORT |\
  sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' > certificate.pem
  ```

  Consider the following TLS certificate downloaded from a website:

  ```
  -----BEGIN CERTIFICATE-----
  MIIE7zCCBJSgAwIBAgIQD9WF1Et9s39cPmU79LIm9zAKBggqhkjOPQQDAjBKMQsw
  CQYDVQQGEwJVUzEZMBcGA1UEChMQQ2xvdWRmbGFyZSwgSW5jLjEgMB4GA1UEAxMX
  Q2xvdWRmbGFyZSBJbmMgRUNDIENBLTMwHhcNMjAwNzA0MDAwMDAwWhcNMjEwNzA0
  MTIwMDAwWjBmMQswCQYDVQQGEwJVUzELMAkGA1UECBMCQ0ExFjAUBgNVBAcTDVNh
  biBGcmFuY2lzY28xGTAXBgNVBAoTEENsb3VkZmxhcmUsIEluYy4xFzAVBgNVBAMT
  DmNsb3VkZmxhcmUuY29tMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEG8yJrKWY
  lPQG6J3KgKis4XeOY3/cL5qEQ+mP3zgl4ylipgX7/XJLiQ5361b8fJhj/UjIudFJ
  0xL9ibOrs6JTDqOCAz4wggM6MB8GA1UdIwQYMBaAFKXON+rrsHUOlGeItEX62SQQ
  h5YfMB0GA1UdDgQWBBTUxXwi2+exV6YsgMeQajzIlUvqnTBxBgNVHREEajBoghAq
  LmNsb3VkZmxhcmUuY29tgg5jbG91ZGZsYXJlLmNvbYIUKi5kbnMuY2xvdWRmbGFy
  ZS5jb22CFCouYW1wLmNsb3VkZmxhcmUuY29tghgqLnN0YWdpbmcuY2xvdWRmbGFy
  ZS5jb20wDgYDVR0PAQH/BAQDAgeAMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEF
  BQcDAjB7BgNVHR8EdDByMDegNaAzhjFodHRwOi8vY3JsMy5kaWdpY2VydC5jb20v
  Q2xvdWRmbGFyZUluY0VDQ0NBLTMuY3JsMDegNaAzhjFodHRwOi8vY3JsNC5kaWdp
  Y2VydC5jb20vQ2xvdWRmbGFyZUluY0VDQ0NBLTMuY3JsMEwGA1UdIARFMEMwNwYJ
  YIZIAYb9bAEBMCowKAYIKwYBBQUHAgEWHGh0dHBzOi8vd3d3LmRpZ2ljZXJ0LmNv
  bS9DUFMwCAYGZ4EMAQICMHYGCCsGAQUFBwEBBGowaDAkBggrBgEFBQcwAYYYaHR0
  cDovL29jc3AuZGlnaWNlcnQuY29tMEAGCCsGAQUFBzAChjRodHRwOi8vY2FjZXJ0
  cy5kaWdpY2VydC5jb20vQ2xvdWRmbGFyZUluY0VDQ0NBLTMuY3J0MAwGA1UdEwEB
  /wQCMAAwggEDBgorBgEEAdZ5AgQCBIH0BIHxAO8AdQD2XJQv0XcwIhRUGAgwlFaO
  400TGTO/3wwvIAvMTvFk4wAAAXMbCD9JAAAEAwBGMEQCIGvGTxZeBYgdbs+vnp0c
  9y45gwRMOZnKz4eE1d4LdagwAiARwrwO1jORk0C5/VTj+RPxK5HRwK169bwkdVL8
  0pB7lAB2AFzcQ5L+5qtFRLFemtRW5hA3+9X6R9yhc5SyXub2xw7KAAABcxsIP38A
  AAQDAEcwRQIhAMWV1BR5WmEVEfpfyBAJErAa7zbUmn9yqwLzdVDesRcuAiAePxqr
  LJBQ5ysyisJOIt6GzfUOg1rDmsgmmdj7zz9lgDAKBggqhkjOPQQDAgNJADBGAiEA
  42x0wUe7wq/QbXOvyaYX8IXvORQ0L+/cOM4TrVCEG9ECIQDaDyZCKGGpi+MqdDmy
  dLIonPk4USKu95+gu0CQPQTglQ==
  -----END CERTIFICATE-----
  ```

    - Which `HOST` and `PORT` parameters were used to download the above certificate?
    - What is the certificate's serial number?
    - Until when is the certificate valid?
    - What signature algorithm was used to sign the certificate?
    - What is the certificate's fingerprint?

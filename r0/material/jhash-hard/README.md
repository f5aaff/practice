# jhash hard

jhash is a not-really-cryptographic hash used in the Linux kernel. Your
goal: find two messages that hash to the same value, given a same
`initval` parameter. See jhash.c for the code of the function.

Hints: 

* Messages should be of the same size
* Easier when using the word-oriented `jhash2()` function, than with the
  byte-oriented `jhash()` function.

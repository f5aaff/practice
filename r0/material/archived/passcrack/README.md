# Passcrack

Crack the password hashes using the hashcat utility, using the following
hints:

* HASH1 is the hash of a password with 5 lower-case letters

* HASH2 is the hash of a password starting with a capital, ending
  with a digit in 0-9, with 4 lower-case letters in between

* HASH3 is the hash of a 5-character password, with possibly lower-case
  letters, upper-case letters, digits, and special characters

* HASH4 is the hash of a 8-character password, with possibly lower-case
  letters, upper-case letters, digits, and special characters

General hints: The hints above will help you set the right mask (pattern
describing the password sought), when needed. You'll have to first determine
the hash function used, and then set the -m parameter appropriately. The
passwords recovered will be in the file ~/.hashcat/hashcat.pot. A list of common passwords is provided too.

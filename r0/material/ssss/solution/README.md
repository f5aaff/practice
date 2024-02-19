# Solution

You knew the number of shares (n) but not the threshold (t), so the only
way to guess was to try repeatedly the command ssss-combine with
different t values until you found one for which the KCV matched.

Given a the hex encoding of a 36-byte value, you could verify its
checksum by using the Python script kcvcheck.py.

The result was the following, for t=4, and any combination of 4 shares
did the trick:

KEY+KCV in hex is:
4b12cc98a7716463fff2841c5d45beb687b5e804103ab5c7e40811e96a20656aa9c020fd

the KCV is the last 4 bytes:
a9c020fd

Alernatively, you can use verifiable secret sharing (VSS), to avoid the
need for a manual integrity check.

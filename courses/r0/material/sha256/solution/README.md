# Solution

The SHA256 implementation has the following bugs:

1. line 29: wrong rotation constant, replace 17 with 13
1. line 87: data is zeroed, remove `& 0x00`
1. line 107: wrong padding constant, replace `0x88` with `0x80`

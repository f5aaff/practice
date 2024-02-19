#### Main problems

- First seed input useless; entropy of 6 bits only (`0x77` mask)
- Too short seeds, 32 bits only (can be bruteforced)
- Too short internal state, 64 bits only 
- If the seed is zero, the internal state remains 0 (and returns always the same word)
- Equivalent seeds (map to the same internal state), e.g., 1024 & 1032
- MSB of the returned word is always 0
- `word` leaks info on the state, allowing recovery of the state by exploiting its linearity

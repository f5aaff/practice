# Extended Euclidean Algorithm

#### Exercise

Implement a function `t = invert(a,n)` that on input of integers `a` and `n` returns an integer `t` that is the inverse of `a` modulo `n`, i.e., `t = a^{-1} mod n`. Use the Extended Euclidean Algorithm to compute inverses.

For your implementation you can either use the Python 3 template given in `euclid.py` or use any other language of your choice.

To test whether your function works correctly, check that the following equations hold:

```
a = 7
t = 98
n = 137
assert(t == invert(a,n))
a = 7
t = 882283
n = 1543995
assert(t == invert(a,n))
a = 7
t = 2300875338
n = 3 * 2**30 + 1
assert(t == invert(a,n))
```


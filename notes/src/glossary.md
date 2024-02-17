# Glossary

| term | definition |
-------|-------------
|<span id="stack">stack</span> |this is an abstract region of memory consisting of data stored in a *Last In First Out* system, items are pushed into the stack arbitrarily, then taken out by their given offset. In assembly in particular, this is used to store values for given functions. |
| <span id="heap">heap</span> | a heap is similar to a stack, except the size is undetermined until run time. This is still pre-reserved |
|<span id=stack-frame>Stack Frame</span> | a region of memory used to store a functions incoming parameters, local variables, and sometimes temporary variables. this is allocated on the stack |
| <span id="frame-pointer">Frame Pointer</span> | contains the base address of a function's stack frame. this is stored in the ebp register on x86 architecture and rbp on 64-bit architectures |
|<span id="thunk-function">THUNK Function</span> | often placeholders, used for code loaded at *runtime* as opposed to build time |

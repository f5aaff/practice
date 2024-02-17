# Chapt9

## fio(file I/O)
- This is a very simple function. Starts by printing a string, then
using fprintf, writes directly to stdout:

    ```
    void fio(void){
        /*
          in any typical POSIX shell, you can direct the standard out, and standard
          error to seperate locations:
            ./foo > output 2> errors
            the above, will send 2, the standard error, to a file called errors;
            whilst sending the former, the standard out, to output.
            the below fprint statement writes the given string to standard output
            to specify what is written in such an operation.
         */
        printf("this is a string");
        fprintf(stdout,"this is a string to file\n");

    }
    ```
- when compiled to assembly using gcc, this is the same function:
```
![fio() in assembly, as derived by Ghidra](res/chapt.9/fioavr.png)
```

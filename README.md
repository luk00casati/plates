## PIATTI A STACK BASED PROGRAMMING LANGUAGE

[stack reference](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

# installation:

`make install` probably use sudo

# tools:

`cpiattitc` the transpiler for the language compile to C 
need a source file and name for the output file if not provided the output name will be out.c
example `cpiattict main.cpiatti main.c`
if you need to compile the C code, set the `-lcpiatti` flag

there is a script named ccpiatti in the repo that will help you

# all the key words:

`DEBUG` will activate debug information

`NOOUT` will deativate the stdout

`POP` will remove the last item of the stack

`PUSH` will add one item to the stack need a value

`GETC` will ask for an input of a character and will put in the stack

`GETS` need a string and will put the character of the string in the stack

`GETI` will ask for an input of a digit and will put in the stack

`STPOP` will remove the last item of the stack and store the value in STORE

`ROT` will rotate the stack

`PUT` will remove the last item of the stack and print the value

`APUT` will remove the last item of the stack and print the ascii value

`COPY` will copy the value of the last item of the stack and to the stack

`SWAP` will swap the last two item of the stack

`SUM` will remove the last two item of the stack and add the sum to the stack

`SUB` will remove the last two item of the stack and add the subtraction to the stack

`MUL` will remove the last two item of the stack and add the multiplication to the stack

`DIV` will remove the last two item of the stack and add the division to the stack

`REM` will remove the last two item of the stack and add the reminder to the stack

`DROP` will remove all the item from the stack

`STPEEK` will store the value of the last item in the stack in STORE

# examples:

fibonacci

```
PUSH 1
PUSH 2

REPEAT 20 {
    COPY
    ROT
    SUM
}

PUT
EXIT 0
```

upper

```
GETS "hello" ROT

REPEAT SIZE {
    PUSH 32
    SWAP
    SUB
    APUT
}

EXIT 0
```

truth machine

```
GETI STPOP

IF STORE == 0 {
    PUSH 0 PUT
}
ELSE {
    LOOP {
        PUSH 1 PUT
    }
}

EXIT 0
```
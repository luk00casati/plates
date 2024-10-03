## PIATTI A STACK BASED PROGRAMMING LANGUAGE

[stack reference](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

# installation:

`make install` probably use sudo

# all the key words:

`DEBUG` will activate debug information

`POP` will remove the last item of the stack

`PUSH` will add one item to the stack need a value

`ROT` will rotate the stack

`PUT` will remove the last item of the stack and print the value

`PUTC` will remove the last item of the stack and print the ascii value

`PUTNL` will remove the last item of the stack and print new line

`COPY` will copy the value of the last item of the stack and to the stack

`SWAP` will swap the last two item of the stack

`SUM` will remove the last two item of the stack and add the sum to the stack

`SUB` will remove the last two item of the stack and add the subtraction to the stack

`MUL` will remove the last two item of the stack and add the multiplication to the stack

`DIV` will remove the last two item of the stack and add the division to the stack

`REM` will remove the last two item of the stack and add the reminder to the stack

`DROP` will remove all the item from the stack

`PEEK` will store the value of the first item in the stack

`PEEK` will store the value of the size of the stack

# examples:

fibonacci

```
PUSH 1;
PUSH 2;

REPEAT 20 DO
    COPY;
    ROT;
    SUM;
END

PUT;
PUTNL;
```

upper

```
PUSH 97

REPEAT SIZE DO
    PUSH 32;
    SWAP;
    SUB;
    PUTC;
    PUTNL;
END
```

truth machine

```
PUSH 1; //or 0

IF POP == 0 DO
    PUSH 0;
    PUT;
    PUTNL;
END
ELSE DO
    LOOP DO
        PUSH 1;
        PUT;
        PUTNL;
    END
END
```
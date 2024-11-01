## PIATTI A STACK BASED PROGRAMMING LANGUAGE

[stack reference](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

# compilation:

```
meson setup builddir
meson compile -C builddir
```

cross-compile
```
meson setup builddir --cross-file windows-cross.ini
meson compile -C builddir
```

# examples:

fibonacci

```
PUSH 1
PUSH 2

REPEAT 20 DO
    COPY
    ROT
    SUM
END

PUT
PUTNL
```

upper

```
PUSH 97

REPEAT SIZE DO
    PUSH 32
    SWAP
    SUB
    PUTC
    PUTNL
END
```

truth machine

```
PUSH 1 #or 0

IF TOP == 0 DO
    PUSH 0
    PUT
    PUTNL
END
ELSE DO
    LOOP DO
        PUSH 1
        PUT
        PUTNL
    END
END
```
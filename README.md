## Forth Oriented Rational Wacky Arithmetic Reason Determinator
An interpreter of the bare essentials of Forth in 150~ lines.
Supported are the usual arithmetic operations, a few stack/print ones and the heart of Forth, names. Support for arrays and branching has yet to be figured out.

### Compiling & Time
`gcc -Ofast -march=native -mtune=native -s -static -static-libgcc forward.c -o forward`

Compilation on a AMD FX-8350 yielded a time of:
```
real    0m0.163s
user    0m0.118s
sys     0m0.045s
```

### Example
```forth
: STAR 42 EMIT ;
: LINE STAR STAR STAR STAR STAR ;
LINE CR STAR CR LINE CR STAR CR STAR CR
```
This shall give you a nice F.

### Implementation of Names
I made a structure which contains the name itself and what follows after until `;`. Then whenever the evaluator finds a letter, it checks against the currently stored names, and if a match is found, *it evaluates the name's buffer*. The fact this process is recursive highlights one of the powers of Forth. Currently however, replacement of pre-defined names is not implemented. Be careful making when names that are already pre-defined in the interpreter. Or not, that's your call.

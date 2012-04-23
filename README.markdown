DCPU-Asm
========

A simple assembler for use with Notch's dcpu.

A description of the dcpu can be found at: http://0x10c.com/doc/dcpu-16.txt.

Comments
========

Not sure if strings are in the spec or not. Notch's earlier examples showed the use of strings, as well as a "DAT" tag. Both have been added to my implementation.

Syntax
======

Here's the simplified BNF the parser uses (starts at stmt):

```
b_op ::= SET | ADD | SUB | MUL | DIV | MOD | SHL | SHR | AND | BOR | XOR | IFE | IFN | IFG | IFB

preproc ::= DAT <dat_expr>

dat_expr ::= <dat_term> , <dat_expr> | <dat_term>

dat_term ::= <name> | <num> | <string>

expr ::= <name> + <reg> | <num> + <reg> | <name> | <num> | <reg>

nb_op ::= JSR

num ::= <numeric> | <hex_numeric>

op ::= <b_op> <oper> , <oper> | <nb_op> <oper> | <preproc>

oper ::= [ <expr> ] | <term>

reg ::= A | B | C | X | Y | Z | I | J

st_op ::= POP | PEEK | PUSH

stmt ::= <op> | : <name>

sys_reg ::= SP | PC | O

term ::= <name> | <num> | <reg> | <sys_reg> | <st_op>
```

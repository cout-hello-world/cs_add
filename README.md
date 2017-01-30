# `cs_add` Readme

This repository contains a carry select adder implemented with the GNU MP
library. It’s still slower than [GNU MP](https://gmplib.org/) by about a factor
of two so it has no real practical purpose. It may have bugs as well. If you
can help with any of these issues, send me a pull request.

## Building
The [GNU MP](https://gmplib.org/) library is required. The test program also
requires a C++ 11 compiler.

To build the test program
```
git clone https://github.com/cout-hello-world/cs_add.git
cd cs_add
make
```
The test program will be in the `test` directory, and the object code for the
parallel adder will be in the `src` directory.

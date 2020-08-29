# About this reposity

This repository contains work done by me during MIPT's 2020 Summer School on Prog - RT and IVT.
Each directory contains a different program.

# Building

The build directory contains scripts to build every program.
GCC with C99 support is required. 

# Running the tests

Along with build scripts the build directory also contains test scripts. Run these scripts 
to test their programs. Note that you must have [check](https://libcheck.github.io/check) installed for this.

# Documentation

This project's documentation is located in the docs folder. It can also be accessed [here](https://attractadore.github.io/DedLeto2020).
If you want to generate the docmentation yourself, you will need [doxygen](https://www.doxygen.nl). Once you have doxygen, you
should run the following in the repository's root directory:

```
doxygen Doxyfile
```

The generated documentation can now be found in the docs folder.


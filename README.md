# About this reposity

This repository contains work done by me during MIPT's 2020 Summer School on Prog - RT and IVT.

# Building

CMake is used as this project's build system. To compile all of the available examples, 
run the following commands in the cloned repository's root folder:

```
mkdir build
cd build
cmake ..
cmake --build .
```

By default, this also builds the various example's unit tests. If you don't want to build the tests
or don't have [check](https://libcheck.github.io/check) installed, you should replace

```
cmake ..
```
with 
```
cmake -DBUILD_TESTING=OFF ..
```

Now you can browse the various subdirectories and run the examples.

# Running the tests

CTest is used to run the tests. After building the project, navigate to an example's subdirectory
and run

```
ctest .
```

# Documentation

This project's documentation is located in the docs/ folder. It can also be accessed [here](https://attractadore.github.io/DedLeto2020).
If you want to generate the docmentation yourself, you will need [doxygen](https://www.doxygen.nl). Once you have doxygen, you
should run the following in the repository's root directory:

```
doxygen Doxyfile
```

The generated documentation can than be found in the docs/ folder.


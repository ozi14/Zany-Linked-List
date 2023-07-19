

# Zany Linked List (ZLL)

The Zany Linked List (ZLL) is a C++ implementation of a doubly linked list with support for storing and manipulating data with zany properties. The list can contain various data types, including integers, strings, and custom objects like `Thing`. It provides functionalities to add elements at the front and back, remove zany and non-zany elements, join lists together, and more.

## Table of Contents

- [Introduction](#introduction)
- [Files](#files)
- [Usage](#usage)
- [Compilation](#compilation)
- [Examples](#examples)
- [Contributing](#contributing)


## Introduction

The Zany Linked List (ZLL) project consists of several C++ files that collectively implement a versatile doubly linked list with zany data properties. It includes the main `ZLL` class along with supporting files for custom data types and test programs.

## Files

- `Thing.cpp`, `Thing.h`: Files defining the custom `Thing` class, representing an item with attributes `item` and `color`. It provides constructors, an equality operator, and a custom `<<` operator for printing.

- `ZLL.cpp`, `ZLL.h`: Files containing the main implementation of the Zany Linked List. The `ZLL` class is a templated class that supports different data types, thanks to its generic design. It provides functionalities to work with the list, such as `front()`, `back()`, `join()`, `removeZany()`, `removeNonZany()`, `promoteZany()`, and iterators (`start()`, `getNext()`, `done()`).

- `makefile`: The makefile provides rules to compile the project and generate executable files for `zll_sample` and `zll_int_test`.

- `zany.cpp`, `zany.h`: Files defining the `isZany` function for `int` and `std::string` data types.

- `zll_int_test.cpp`: A test program to verify the functionality of the ZLL with integer elements.

- `zll_sample.cpp`: A sample program demonstrating the usage of the ZLL with different data types.

## Usage

To use the ZLL in your project, include the necessary header files (`ZLL.h`, `Thing.h`, and `zany.h`) and compile your program along with the required source files (`ZLL.cpp`, `Thing.cpp`, and `zany.cpp`).

The ZLL class provides various member functions for working with the list, such as `front()`, `back()`, `join()`, `removeZany()`, `removeNonZany()`, `promoteZany()`, and iterators (`start()`, `getNext()`, `done()`).

For custom data types, define the `isZany` function to check if an item is zany.

## Compilation

To compile the ZLL, you can use the provided `makefile`. Make sure you have `g++` installed on your system.

To compile the main `zll_sample` program and the test program `zll_int_test`, run the following command:

```bash
make all
```

This will generate the executable files `zll_sample` and `zll_int_test`.

To clean the generated files, run:

```bash
make clean
```

## Examples

Here are some basic examples of using the ZLL:

```cpp
#include "ZLL.h"
#include "Thing.h"
#include "zany.h"

int main() {
    // Example with integer elements
    ZLL<int> zll;
    zll.front(1);
    zll.back(2);
    zll.back(3);

    zll.start();
    while (!zll.done()) {
        int value = zll.getNext();
        // Do something with the value
    }

    // Example with string elements
    ZLL<std::string> zll_str;
    zll_str.front("hello");
    zll_str.back("world");

    // Example with custom Thing objects
    ZLL<Thing> zll_thing;
    Thing grape("Grape", "purple");
    Thing blueberry("Blueberry", "blue");

    zll_thing.back(grape);
    zll_thing.back(blueberry);
}
```

## Contributing

Contributions to this project are welcome! If you find any issues or want to add new features, feel free to open a pull request.

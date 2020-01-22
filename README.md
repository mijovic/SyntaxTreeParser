# Arithmetic expression syntax tree parser

AST parser class in C++11 for arithmetic expressions.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

Folder structure:
* include: public include files
* src: library source files
* tests: tests project including unit tests
* thirdparty: directory including all of third party sources, in this case only doctest

### Prerequisites

You will need cmake and working C++11 compiler. On ubuntu you can install it by:

```
apt-get install build-essential
apt-get install cmake
```

### Building

CMake was used in development of SyntaxTree. You can build it on your own with(BUILD_DIR used as placeholder for desired directory name):

```
mkdir ${BUILD_DIR}
cd ${BUILD_DIR}
cmake ..
make -j4
```

Or you can use bash script created for that

```
./build.sh
```

## Running the tests

You can run tests with:
```
${BUILD_DIR}/SyntaxTreeTests
```


Or, if you have build using build.sh you can run the tests using:
```
./test.sh
```

### About tests

Tests are unit tests which are testing base functionality of the parser with majority of edge cases.

[Doctest](https://github.com/onqtam/doctest) was used as a testing framework. 

Sample output of all tests passing:

```
[doctest] doctest version is "2.2.3"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases:      2 |      2 passed |      0 failed |      0 skipped
[doctest] assertions:     16 |     16 passed |      0 failed |
[doctest] Status: SUCCESS!
``` 


## Authors

* **Đorđe Mijović** - *Initial work* - [mijovic](https://github.com/mijovic)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

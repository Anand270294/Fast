# Full Installation Guide 
A step-by-step guide on how fulfill all dependencies before [installing the library](https://github.com/Anand270294/Fast/tree/v1.1_Ex#quick-installation). To use **__Fast__** , the user must meet multiple system requirements since this would allow the users to modify and update thier library.

## 1. Installing Python
Most users would already have `python` installed in thier system by now and **__Fast__** requires the `python` version to be `python 3.x`. To check if you meet the version requirement:

```
$ python --version
```

If you do not have the required version or the language support install in your PC, you download it from [python website](https://www.python.org/downloads/)


## 2. Installing C++ 
Installing C++ would mean installing the g++ compiler. First the user should check if g++ compiler is available on the OS:
```
$ g++ --version

g++ (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

```

If you get similar result as shown above, you are good to go! However, If you did not get a similar result you can try:
```
$ sudo apt install build-essential
```
or :
```
$ sudo apt install g++
```
This should install the g++ compiler into your OS.

## 3. Make CMake
[**CMake**](https://cmake.org/) is an essential build tool for the library. As such you should check the available version on your PC:
```
$ cmake --version
```

Similar to most installation on linux systems, you can install by typing the following into the terminal:
```
$ sudo apt-get -y install cmake
```
 Now you have [**CMake**](https://cmake.org/) and almost half way there! Keep it up!







**WOrk iN PrOGresS**
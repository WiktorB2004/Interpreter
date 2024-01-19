## WLang interpreter in C

Project start date: 9.11.2023 <br>
About: The project involves creation of a custom language interpreter for WLang using the C programming language. <br>

- WLang Interpreter source code documentation - [WLang Docs](https://wiktorb2004.github.io/WLang_interpreter-C/)

## How to use

#### Interpreter

- Use bash script (currently tested and compatible with Ubuntu)
```
$ curl -O -L https://raw.githubusercontent.com/WiktorB2004/WLang_interpreter-C/master/scripts/Setup.sh
# or wget https://raw.githubusercontent.com/WiktorB2004/WLang_interpreter-C/master/scripts/Setup.sh
$ sudo chmod +x Setup.sh
$ ./Setup.sh
$ wlang PATH_TO_YOUR_FILE
```
- Use docker image
```
$ docker pull ghcr.io/wiktorb2004/wlang_interpreter-c:master
$ docker run -v "$(pwd):/app/exec" ghcr.io/wiktorb2004/wlang_interpreter-c:master /app/exec/PATH_TO_YOUR_FILE
$ sudo chmod +x Setup.sh
$ ./Setup.sh
``` 
- Download repository and build the source code
```
$ git clone https://github.com/WiktorB2004/WLang_interpreter-C.git
$ cd WLang_interpreter-C/
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ cd ..
$ ./bin/WLang PATH_TO_WLANG_FILE (eg. examples/example.wlg)
```

#### Generating documentation - you need to have Doxygen installed

```
$ git clone https://github.com/WiktorB2004/WLang_interpreter-C.git
$ cd WLang_interpreter-C/
$ doxygen Doxyfile
```
The documentation will be available inside /docs folder

## Project Plan / Phases

The development process consisted of several key phases, each contributing to the successful implementation of the interpreter.

1. Understanding Interpreter Architecture
2. Planning and Designing the Interpreter:
3. Writing the Code:
4. Testing, bug fixing and implementing missing features:
5. Iterative Development

## Portfolio Project Summary

The project to build a custom language interpreter for WLang in C was an intensive process that demanded a strong understanding of interpreter design principles, meticulous planning, and systematic implementation. The outcome was an interpreter capable of parsing and executing code written in the WLang language, demonstrating the ability to create a functional interpreter from scratch in the C programming language.

### Why C?

C was chosen for the WLang interpreter project due to its high performance, efficiency, portability across platforms, rich library support, and fine-grained control over system resources. Its mature ecosystem and compatibility made it an ideal language for crafting a fast and robust custom language interpreter.

- - - -
Thank you for exploring this project, and I hope it demonstrates my dedication to the craft of software development and my commitment to delivering high-quality solutions. If you have any questions or would like to collaborate with me, please feel free to get in touch.

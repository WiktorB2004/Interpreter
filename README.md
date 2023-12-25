## WLang interpreter in C

Project start date: 9.11.2023 <br>
Project status: Mostly completed - few enhancements needed <br>
About: The project involved the creation of a custom language interpreter for WLang using the C programming language. <br>

- WLang language (project) docs - Under Development

## How to use

```
git clone https://github.com/WiktorB2004/WLang_interpreter-C.git
cd WLang_interpreter-C/
mkdir build
cd build
cmake ..
cmake --build .
cd ..
./bin/WLang PATH_TO_WLANG_FILE (eg. examples/example.wlg)
```

## Project Plan / Phases

The development process consisted of several key phases, each contributing to the successful implementation of the interpreter.

1. Understanding Interpreter Architecture:
   - Initially, the project required a comprehensive understanding of interpreter architecture. This involved studying the theoretical foundations of interpreters, parsing techniques, lexing, abstract syntax trees (ASTs), tokenization, and interpreting code execution flow. This phase involved learning a lot from online resources.

3. Planning and Designing the Interpreter:
   - Once the foundational knowledge was acquired, the next step was to devise an overall plan for the interpreter's architecture and functionality. This phase involved outlining the grammar rules of the WLang language in EBNF, defining the tokenization and parsing processes, creating the AST structure, and designing the execution flow. The plan also included breaking down the project into smaller manageable tasks and establishing a roadmap for development.

5. Writing the Code:
   - With a plan in place, the implementation phase began. This step includes implementing lexing and parsing functions to tokenize the input code and construct the AST. Additionally, coding the interpreter requires defining execution logic for interpreting the AST nodes and executing the WLang code according to its defined grammar rules.

7. Testing, bug fixing and implementing missing features:
   - Throughout the coding phase, rigorous testing and debugging will be essential. This involves creating test cases to validate the interpreter's functionality, identifying and resolving bugs, and refining the code for optimal performance and correctness.

9. Iterative Development:
   - The process of building the interpreter is planned to be iterative, requiring continuous refinement and enhancement. This involves revisiting the codebase to optimize performance, add new features, handle edge cases, and improve the interpreter's overall robustness.

### Summary

The project to build a custom language interpreter for WLang in C was an intensive process that demanded a strong understanding of interpreter design principles, meticulous planning, and systematic implementation. The outcome was an interpreter capable of parsing and executing code written in the WLang language, demonstrating the ability to create a functional interpreter from scratch in the C programming language.

## Why C?

C was chosen for the WLang interpreter project due to its high performance, efficiency, portability across platforms, rich library support, and fine-grained control over system resources. Its mature ecosystem and compatibility made it an ideal language for crafting a fast and robust custom language interpreter.

- - - -
Thank you for exploring this project, and I hope it demonstrates my dedication to the craft of software development and my commitment to delivering high-quality solutions. If you have any questions or would like to collaborate with me, please feel free to get in touch.

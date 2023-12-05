# CS 377 Final Project: Shell

In this project, we have implemented a shell using C++ using system calls and process management. It is an extension of Project 2 of COMPSCI 377. We have used system calls such as ``fork``, `exec`, and `wait`. We have also implemented piping commands. In addition to numerous commands that can be run using the system call ``execvp``, we currently support and have tested the shell for the following:

- `cd`
- `echo`
-  `pwd`
- `ls`

# Setup
- Clone this repository.
- Run `make` . This command will run the C++ compiler to build the program and the test executables.
- Run  `./tsh_app`. This command will launch the shell program.
- Run `./tsh_test`. This command will run tests.

## Project Structure


-   **include**: This is where we keep the header files.
-   **obj**: This folder is used for  object files that are generated from the C compilation process.
-   **src**: This is the source folder where all the source code is.
-   **test**: This is the test folder where all the tests are.
-   **Makefile**  - this is a "build" file. This file is used to compile the code.

# Tests

- Test 1 is the test from project 2. It checks if the user wants to quit the shell.
- Test 2 test commands "pwd", to display the present working directory. 
- Test 3 test commands "echo", to print a string of text or value of a variable to the terminal. 
- Test 4 is our free command execution. It is able to execute any command under user privilege. Here we use "mkdir" make directory ot test this command.
- Test 5 is command + piping, we can enter multiple commands to run many legal commands under the user privilege. In this test we use `ps -l | mkdir test_temp | ls -l | echo print something |Is -l` to test piping execution.
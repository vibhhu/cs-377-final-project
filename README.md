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


-   **include**: This is where we keep  [C/C++ header filesLinks to an external site.](https://flaviocopes.com/c-header-files/). Header files are used in C/C++ to share definitions across many C/C++ source files.
-   **lib**: This is where we keep any libraries that we might use. It will often be empty.
-   **obj**: This folder is used for  [object filesLinks to an external site.](http://t.ly/LiKq)  that are generated from the C compilation process. This folder is initially empty until you compile your code.
-   **src**: This is the source folder where all code you are submitting must go. You can change anything you want in this folder (unless otherwise specified in the problem description and in the code we provide), you can add new files, etc.
-   **test**: This is the test folder where you can find all of the public unit tests - if any are given.
-   **Makefile**  - this is a "build" file. This file is used to compile your code.






Hi! I'm your first Markdown file in **StackEdit**. If you want to learn about StackEdit, you can read me. If you want to play with Markdown, you can edit me. Once you have finished with me, you can create new files by opening the **file explorer** on the left corner of the navigation bar.


# Tests

- Test 1 is the test from project 2.
- Test 2 test commands "pwd", to display the present working directory. 
- Test 3 test commands "echo", to print a string of text or value of a variable to the terminal. 
- Test 4 is our free command execution. It is able to execute any command under user privilege. Here we use "mkdir" make directory ot test this command.
- Test 5 is command + piping, we can enter multiple commands to run many legal commands under the user privilege. In this test we use `ps -l | mkdir test_temp | ls -l | echo print something |Is -l` to test piping execution.
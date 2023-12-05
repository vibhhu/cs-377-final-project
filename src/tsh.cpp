#include <tsh.h>

#include <iostream>

#include <cstring>

using namespace std;

// Array of built-in commands supported by the shell
char * builtin_cmds[] = {
    "echo",
    "pwd",
    "help",
    "quit"
};

// Number of built-in commands
const int num_builtin = 4;

// Function to remove extra spaces from the command string
void remove_extra_spaces(char * cmd) {

    if (cmd == NULL) {
        return;
    }

    // Trim leading spaces
    while ( * cmd && std::isspace( * cmd)) {
        ++cmd;
    }

    char * last = cmd + std::strlen(cmd) - 1;

    // Trim trailing spaces
    while (last >= cmd && std::isspace( * last)) {
        * last = '\0';
        --last;
    }

}

// Function to parse the command string into tokens
void simple_shell::parse_command(char * cmd, char ** cmdTokens) {

    if (cmd == NULL) {
        return;
    }

    while ( * cmd && std::isspace( * cmd)) {
        ++cmd;
    }

    char * end = cmd + std::strlen(cmd) - 1;

    while (end >= cmd && std::isspace( * end)) {
        * end = '\0';
        --end;
    }

    // Tokenize the command string using space as delimiter
    char * token = strtok(cmd, " ");
    int index = 0;

    // Store tokens in cmdTokens array
    while (token != NULL) {
        cmdTokens[index] = token;
        token = strtok(NULL, " ");
        index++;
    }

    cmdTokens[index] = NULL;

}

// Function to execute the given command
void simple_shell::exec_command(char ** allArgv) {
    // forks a child process to execute the command.
    // parent process waits for the child process to complete and reap it

    char * command[25][25];
    char ** argv;
    int curToken = 0;
    int cntCommand = 0;

    while (allArgv[curToken] != NULL) {
        int index = 0;

        while (allArgv[curToken] != NULL && strcmp(allArgv[curToken], "|") != 0) {
            command[cntCommand][index] = allArgv[curToken];
            index++;
            curToken++;
        }

        command[cntCommand][index] = NULL;

        // skip "|"
        if (allArgv[curToken] != NULL) curToken++;
        cntCommand++;
    }

    int fd[cntCommand][2];
    int pids[cntCommand];

    for (int pipe_index = 0; pipe_index < cntCommand; pipe_index++) {
        if (pipe(fd[pipe_index]) < 0) {
            cout << "error while creating pipe " << pipe_index << endl;
            exit(1);
        }
    }

    for (int command_index = 0; command_index < cntCommand; ++command_index) {
        argv = command[command_index];
        int pid = fork();

        if (pid < 0) {
            std::cerr << "Error during forking" << std::endl;
        } else if (pid == 0) {
            // The first command will not read from the pipe
            if (command_index > 0) {
                dup2(fd[command_index - 1][0], STDIN_FILENO);
            }

            // The last command will not write to pipe
            if (command_index + 1 < cntCommand) {
                dup2(fd[command_index][1], STDOUT_FILENO);
            }

            for (int i = 0; i < cntCommand; ++i) {
                close(fd[i][0]);
                close(fd[i][1]);
            }

            if (strcmp(argv[0], "echo") == 0) {
                int i = 1;
                while (argv[i] != NULL) {
                    cout << argv[i] << " ";
                    i++;
                }
                cout << endl;
                exit(0);
            } else if (strcmp(argv[0], "pwd") == 0) {
                char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) == NULL) {
                    cout << "Error while calling cwd" << endl;
                    exit(1);
                } else {
                    cout << cwd << endl;
                    exit(0);
                }
            } else if (strcmp(argv[0], "help") == 0) {
                if (argv[1] == NULL) {
                    printf("Simple Shell:\n");
                    printf("Type command and arguments then hit enter to run\n");
                    printf("Built in commands:");
                    for (int i = 0; i < num_builtin; i++) {
                        printf(" %s\n", builtin_cmds[i]);
                    }
                } else if ((strcmp(argv[1], "echo") == 0)) {
                    printf("builtin command \"echo\": outputs the arguments\n");
                } else if ((strcmp(argv[1], "pwd") == 0)) {
                    printf("builtin command \"pwd\": outputs the path\n");
                } else if ((strcmp(argv[1], "quit") == 0)) {
                    printf("builtin command \"quit\": quit the shell\n");
                }
                exit(0);
            } else {
                int exec = execvp(argv[0], argv);
                if (exec == -1) {
                    std::cerr << "Error during command execution" << std::endl;
                }
            }
        } else {
            pids[command_index] = pid;
        }
    }

    for (int i = 0; i < cntCommand; i++) {
        close(fd[i][0]);
        close(fd[i][1]);
    }

    for (int i = 0; i < cntCommand; i++) {
        waitpid(pids[i], NULL, 0);
    }
}

// Function to check if the command is "quit" to terminate the shell
bool simple_shell::isQuit(char * cmd) {
    return strcmp(cmd, "quit") == 0;
}

// Function to check if the command is for changing directory (cd)
bool simple_shell::isChangeDir(char ** argv) {
    return strcmp(argv[0], "cd") == 0;
}
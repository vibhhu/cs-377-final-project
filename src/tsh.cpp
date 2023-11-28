#include <tsh.h>
#include <iostream>
#include <cstring>

using namespace std;


void remove_extra_spaces(char* cmd) {
    
    if (cmd == NULL) {
        return;
    }

    while (*cmd && std::isspace(*cmd)) {
        ++cmd;
    }

    char* last = cmd + std::strlen(cmd) - 1;

    while (last >= cmd && std::isspace(*last)) {
        *last = '\0';
        --last;
    }

}

void simple_shell::parse_command(char* cmd, char** cmdTokens) {

    if (cmd == NULL) {
        return;
    }

    while (*cmd && std::isspace(*cmd)) {
        ++cmd;
    }

    char* end = cmd + std::strlen(cmd) - 1;


    while (end >= cmd && std::isspace(*end)) {
        *end = '\0';
        --end;
    }

    char* token = strtok(cmd, " ");
    int index = 0;

    while (token != NULL) {
        cmdTokens[index] = token;
        token = strtok(NULL, " ");
        index++;
    }

    cmdTokens[index] = NULL;
}

void simple_shell::exec_command(char** argv) {
    // TODO: fork a child process to execute the command.
    // parent process should wait for the child process to complete and reap it
    
    int pid = fork();
    if (pid < 0) {
        std::cerr << "Error during forking" << std::endl;
    }

    else if (pid == 0) {

        if (strcmp(argv[0], "echo") == 0) {
            int i = 1;
            while (argv[i] != NULL) {
                cout << argv[i] << " ";
                i++;
            }
            cout << endl;
            exit(0);
            
        }

        else if (strcmp(argv[0], "pwd") == 0) {
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                cout << "Error while calling cwd" << endl;
                exit(1);
            }
            else {
                cout << cwd << endl;
                exit(0);
            }
        }

        else if (strcmp(argv[0], "cd") == 0) {
            if (argv[1] != NULL) {
                if (chdir(argv[1]) == 0) {
                    cout << "Successfully changed directory to: " << argv[1] << endl;
                    exit(0);
                }
                else {
                    cout << "The specified directory does not exist." << endl;
                    exit(1);
                }
            }
            else {
                cout << "Please specify a directory" << endl;
                exit(1);
            }
        }
        
        else {
            int exec = execvp(argv[0], argv);
            if (exec == -1) {
                std::cerr << "Error during command execution" << std::endl;
            }
        }
    }

    else {
        waitpid(pid, NULL, 0);
    }
    
}

bool simple_shell::isQuit(char* cmd) {
    // TODO: check for the command "quit" that terminates the shell
    return strcmp(cmd, "quit") == 0;
}

bool simple_shell::isChangeDir(char** argv) {
    return strcmp(argv[0], "cd") == 0;
}
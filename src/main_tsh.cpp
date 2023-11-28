#include <tsh.h>

using namespace std;

int main() {
  char cmd[81];
  char *cmdTokens[25];
  simple_shell *shell = new simple_shell();
  cout << "tsh> ";
  while (fgets(cmd, sizeof(cmd), stdin)) {
    if (cmd[0] != '\n') {
      shell->parse_command(cmd, cmdTokens);
      if (shell->isQuit(*cmdTokens)) {
        exit(0);
      } else if (shell->isChangeDir(cmdTokens)) {
        if (strcmp(cmdTokens[0], "cd") == 0) {
          if (chdir(cmdTokens[1]) == 0) {
            cout << "Successfully changed directory to: " << cmdTokens[1] << endl;
          } else {
            cout << "The specified directory does not exist." << endl; 
          }
        } else {
          cout << "Please specify a directory" << endl;
        }
      } else {
        shell->exec_command(cmdTokens);
      }
    }
    cout << "tsh> ";
  }
  cout << endl;
  exit(0);
}

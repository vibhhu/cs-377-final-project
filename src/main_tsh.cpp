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
      } else {
        shell->exec_command(cmdTokens);
      }
    }
    cout << "tsh> ";
  }
  cout << endl;
  exit(0);
}

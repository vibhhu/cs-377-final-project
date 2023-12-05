#include <gtest/gtest.h>
#include <tsh.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class ShellTest : public ::testing::Test {
 protected:
  ShellTest() {}              // constructor runs before each test
  virtual ~ShellTest() {}     // destructor cleans up after tests
  virtual void SetUp() {}     // sets up before each test (after constructor)
  virtual void TearDown() {}  // clean up after each test, (before destructor)
};

// Testing isQuit for "quit"
TEST(ShellTest, Test1) {
  simple_shell s;
  EXPECT_TRUE(s.isQuit((char*)"quit"));
}

//displays the present working directory.
TEST(ShellTest, Test2) {
  char cmd[81] ="pwd";
  char *cmdTokens[25];
  
  simple_shell s;
  s.parse_command(cmd,cmdTokens);
  s.exec_command(cmdTokens);
}

//print a string of text, or value of a variable to the terminal
TEST(ShellTest, Test3) {
  char cmd[81] ="echo Hello bash \n test output!";
  char *cmdTokens[25];
  
  simple_shell s;
  s.parse_command(cmd,cmdTokens);
  s.exec_command(cmdTokens);
}

//bash for any command
//here we are create a directory.
TEST(ShellTest, Test4) {
  simple_shell s;
  char cmd[81] ="mkdir test_temp";
  char *cmdTokens[25];
  s.parse_command(cmd,cmdTokens);
  s.exec_command(cmdTokens);
}


TEST(ShellTest, Test5) {
  simple_shell s;
  
  char cmd[81] ="ps -l | mkdir test_temp | ls -l | echo print something | ls -l";
  char *cmdTokens[25];
  
    s.parse_command(cmd,cmdTokens);
    
    cout << "print cmd tokens : " ;
    
    for (int i = 0; i < strlen((*cmdTokens)); i++)
    {
        cout << cmdTokens[i];
    }
    
    cout <<" " << endl;

  s.exec_command(cmdTokens);
}



int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
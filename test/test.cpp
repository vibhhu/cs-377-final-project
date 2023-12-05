#include <gtest/gtest.h>

#include <tsh.h>

#include <fstream>

#include <iostream>

#include <string>

using namespace std;

// Declaring a test class inheriting from Google Test's ::testing::Test
class ShellTest: public::testing::Test {
    protected: ShellTest() {} // constructor runs before each test
    virtual~ShellTest() {} // destructor cleans up after tests
    virtual void SetUp() {} // sets up before each test (after constructor)
    virtual void TearDown() {} // clean up after each test, (before destructor)
};

// Testing isQuit for "quit"
TEST(ShellTest, Test1) {
    simple_shell s;
    EXPECT_TRUE(s.isQuit((char * )
        "quit"));
}

// Testing the 'pwd' command functionality
TEST(ShellTest, Test2) {
    // Command: Present Working Directory
    char cmd[81] = "pwd";
    // Array to store parsed tokens
    char * cmdTokens[25];

    simple_shell s;

    // Parsing the command
    s.parse_command(cmd, cmdTokens);
    // Executing the parsed command
    s.exec_command(cmdTokens);
}

// Testing the 'echo' command functionality
// Prints a string of text, or value of a variable to the terminal
TEST(ShellTest, Test3) {
    // Command: Echo a string including the newline character
    char cmd[81] = "echo Hello bash \n test output!";
    // Array to store parsed tokens
    char * cmdTokens[25];

    simple_shell s;
    // Parsing the command
    s.parse_command(cmd, cmdTokens);
    // Executing the parsed command
    s.exec_command(cmdTokens);
}

// Testing running a bash command to create a directory
TEST(ShellTest, Test4) {
    simple_shell s;
    // Command: Make Directory
    char cmd[81] = "mkdir test_temp";
    // Array to store parsed tokens
    char * cmdTokens[25];

    // Parsing the command
    s.parse_command(cmd, cmdTokens);
    // Executing the parsed command
    s.exec_command(cmdTokens);
}

// Testing multiple commands separated by pipes
TEST(ShellTest, Test5) {
    simple_shell s;

    char cmd[81] = "ps -l | mkdir test_temp | ls -l | echo print something | ls -l";
    // Array to store parsed tokens
    char * cmdTokens[25];

    s.parse_command(cmd, cmdTokens);

    // Printing parsed tokens
    cout << "print cmd tokens : ";

    for (int i = 0; i < strlen(( * cmdTokens)); i++) {
        cout << cmdTokens[i];
    }

    cout << " " << endl;

    // Executing the parsed command with pipes
    s.exec_command(cmdTokens);
}

// Main function initializing Google Test and running all tests
int main(int argc, char ** argv) {
    testing::InitGoogleTest( & argc, argv);
    return RUN_ALL_TESTS();
}
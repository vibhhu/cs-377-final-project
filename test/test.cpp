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


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

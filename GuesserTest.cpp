/**
 * Unit Tests for the class
 **/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
  protected:
    GuesserTest(){} //constructor runs before each test
    virtual ~GuesserTest(){} //destructor cleans up after tests
    virtual void SetUp(){} //sets up before each test (after constructor)
    virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(GuesserTest, happy_test)
{
  std::string input = "hello";
  Guesser guess(input);
  bool act = guess.match(input);
  ASSERT_TRUE(act);
}

TEST(GuesserTest, three_fails_test)
{
  std::string input = "hello";
  std::string close = "hello1";
  Guesser guess(input);
  bool act = guess.match(close);
  act = guess.match(close);
  act = guess.match(close);
  int rem = guess.remaining();
  ASSERT_EQ(0, rem);
}

TEST(GuesserTest, brute_locked_test)
{
  std::string input = "hello";
  std::string brute = "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj";
  Guesser guess(input);
  bool act = guess.match(brute);
  act = guess.match(input);
  ASSERT_FALSE(act);
}

TEST(GuesserTest, remaining_test)
{
  std::string input = "hello";
  std::string close = "hello1";
  Guesser guess(input);
  int rem = guess.remaining();
  EXPECT_EQ(3,rem);
  bool act = guess.match(close);
  rem = guess.remaining();
  EXPECT_EQ(2,rem);
  act = guess.match(close);
  rem = guess.remaining();
  EXPECT_EQ(1,rem);
  act = guess.match(input);
  rem = guess.remaining();
  ASSERT_EQ(3,rem);
}

TEST(GuesserTest, trunc_test)
{
  //any more than 2 a will brute force lock
  std::string input = "12345678911131517192123252729313aa";
  std::string trunc = "12345678911131517192123252729313";
  Guesser guess(input);
  bool act = guess.match(input);
  EXPECT_FALSE(act);
  act = guess.match(trunc);
  ASSERT_TRUE(act);
}

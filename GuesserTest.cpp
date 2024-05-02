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

TEST(GuesserTest, length_two_dist_check)
{
  std::string input = "12";
  std::string brute = "1111111111111111111111111111";
  Guesser guess(input);
  bool act = guess.match(brute);
  act = guess.match(input);
  //shouldn't shadow lock as max dist length is 2
  ASSERT_TRUE(act);
}

TEST(GuesserTest, empty_secret_test)
{
  std::string input = "";
  std::string close = "h";
  Guesser guess(input);
  bool act = guess.match(close);
  EXPECT_FALSE(act);
  act = guess.match(input);
  ASSERT_TRUE(act);
}

TEST(GuesserTest, empty_input_test)
{
  std::string input = "h";
  std::string close = "";
  Guesser guess(input);
  bool act = guess.match(close);
  EXPECT_FALSE(act);
  act = guess.match(input);
  ASSERT_TRUE(act);
}

TEST(GuesserTest, lock_size_small_check)
{
  //assuming the distance is correct, this should lock due to size problems
  std::string input = "abcde";
  std::string small = "ab";
  Guesser guess(input);
  bool act = guess.match(small);
  act = guess.match(input);
  ASSERT_FALSE(act);
}

TEST(GuesserTest, lock_size_big_check)
{
  //assuming the distance is correct, this should lock due to size problems
  std::string input = "abcde";
  std::string big = "abcdefgh";
  Guesser guess(input);
  bool act = guess.match(big);
  act = guess.match(input);
  ASSERT_FALSE(act);
}

TEST(GuesserTest, smaller_input_check)
{
  std::string input = "abcde";
  std::string small = "abc";
  Guesser guess(input);
  bool act = guess.match(small);
  EXPECT_FALSE(act);
  act = guess.match(input);
  ASSERT_TRUE(act);
}

TEST(GuesserTest, bigger_input_check)
{
  std::string input = "abcde";
  std::string big = "abcdef";
  Guesser guess(input);
  bool act = guess.match(big);
  EXPECT_FALSE(act);
  act = guess.match(input);
  ASSERT_TRUE(act);
}

TEST(GuesserTest, last_input_good)
{
  std::string input = "abcde";
  std::string close = "abcd";
  Guesser guess(input);
  bool act = guess.match(close);
  act = guess.match(close);
  EXPECT_FALSE(act);
  int num = guess.remaining();
  EXPECT_EQ(1,num);
  act = guess.match(input);
  ASSERT_TRUE(act);
  //do it again to check it worked
  act = guess.match(close);
  act = guess.match(close);
  num = guess.remaining();
  EXPECT_EQ(1,num);
  act = guess.match(input);
  ASSERT_TRUE(act);
}

TEST(GuesserTest, a_bit_wrong_input)
{
  std::string input = "abcde";
  std::string close = "abcdf";
  Guesser guess(input);
  bool act = guess.match(close);
  EXPECT_FALSE(act);
  act = guess.match(input);
  ASSERT_TRUE(act);
}

TEST(GuesserTest, a_bit_more_wrong_input)
{
  std::string input = "abcde";
  std::string close = "abcef";
  Guesser guess(input);
  bool act = guess.match(close);
  EXPECT_FALSE(act);
  act = guess.match(input);
  ASSERT_TRUE(act);
}

TEST(GuesserTest, wrong_input)
{
  std::string input = "abcde";
  std::string close = "abysz";
  Guesser guess(input);
  bool act = guess.match(close);
  EXPECT_FALSE(act);
  act = guess.match(input);
  ASSERT_FALSE(act);
}

TEST(GuesserTest, really_wrong_input)
{
  std::string input = "abcde";
  std::string close = "zxywv";
  Guesser guess(input);
  bool act = guess.match(close);
  EXPECT_FALSE(act);
  act = guess.match(input);
  //should now be locked
  ASSERT_FALSE(act);
}

TEST(GuesserTest, extra_input_check)
{
  std::string input = "abcde";
  std::string close = "abcde  ";
  Guesser guess(input);
  bool act = guess.match(close);
  EXPECT_FALSE(act);
  act = guess.match(input);
  ASSERT_TRUE(act);
}

TEST(GuesserTest, one_big_edge_check)
{
  std::string input = "abcde";
  std::string close = "abcee ";
  Guesser guess(input);
  bool act = guess.match(close);
  EXPECT_FALSE(act);
  act = guess.match(input);
  ASSERT_TRUE(act);
}

TEST(GuesserTest, one_small_edge_check)
{
  std::string input = "abcde";
  std::string close = "abce";
  Guesser guess(input);
  bool act = guess.match(close);
  EXPECT_FALSE(act);
  act = guess.match(input);
  ASSERT_TRUE(act);
}

TEST(GuesserTest, over_sized_input)
{
  std::string input = "abcde";
  std::string close = "abcde123";
  Guesser guess(input);
  bool act = guess.match(close);
  EXPECT_FALSE(act);
  act = guess.match(input);
  ASSERT_FALSE(act);
}

TEST(GuesserTest, under_sized_input)
{
  std::string input = "abcde";
  std::string close = "abc";
  Guesser guess(input);
  bool act = guess.match(close);
  EXPECT_FALSE(act);
  act = guess.match(input);
  ASSERT_TRUE(act);
}

TEST(GuesserTest, keep_guesses_after_lock)
{
  std::string input = "abcde";
  std::string close = "abcefefiwhefoiw";
  Guesser guess(input);
  bool act = guess.match(close);
  int rem = guess.remaining();
  EXPECT_EQ(2,rem);
  act = guess.match(input);
  rem = guess.remaining();
  ASSERT_EQ(1,rem);
}

TEST(GuesserTest, zero_guesses)
{
  std::string input = "abcde";
  std::string close = "abcd";
  Guesser guess(input);
  bool act = guess.match(close);
  act = guess.match(close);
  act = guess.match(close);
  int rem = guess.remaining();
  EXPECT_EQ(0,rem);
  act = guess.match(close);
  rem = guess.remaining();
  EXPECT_EQ(0,rem);
  act = guess.match(input);
  ASSERT_EQ(0,rem);
}

#include <gtest/gtest.h>

#include "stack.h"

TEST(StackLTest, AddCheckPopElement) {
  st::StackL stack;
  ASSERT_TRUE(stack.isEmpty());
  stack.push(10);
  ASSERT_FALSE(stack.isEmpty());
  ASSERT_EQ(10, stack.top());
  stack.pop();
  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackLTest, AddElements) {
  st::StackL stack;
  for (int i = 0; i < 100; i++) {
    stack.push(i);
  }

  ASSERT_FALSE(stack.isEmpty());

  for (int i = 99; i >= 0; i--) {
    ASSERT_EQ(i, stack.top());
    stack.pop();
  }

  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackLTest, PopElement) {
  st::StackL stack;
  ASSERT_TRUE(stack.isEmpty());
  stack.pop();
  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackLTest, TopEmpty) {
  st::StackL stack;
  bool er = false;
  ASSERT_TRUE(stack.isEmpty());
  try {
    stack.top();
  } catch (std::out_of_range ex) {
    er = true;
  }
  ASSERT_TRUE(er);
  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackLTest, CopyStack) {
  st::StackL stack;
  for (int i = 0; i < 100; i++) {
    stack.push(i);
  }

  // stack = stack;

  st::StackL stack2(stack);

  // stack2 = stack2;

  for (int i = 99; i >= 0; i--) {
    ASSERT_EQ(i, stack.top());
    stack.pop();
  }
  ASSERT_TRUE(stack.isEmpty());

  for (int i = 99; i >= 0; i--) {
    ASSERT_EQ(i, stack2.top());
    stack2.pop();
  }
  ASSERT_TRUE(stack2.isEmpty());
}

////

TEST(StackVTest, AddCheckPopElement) {
  st::StackV stack;
  ASSERT_TRUE(stack.isEmpty());
  stack.push(10);
  ASSERT_FALSE(stack.isEmpty());
  ASSERT_EQ(10, stack.top());
  stack.pop();
  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackVTest, AddElements) {
  st::StackV stack;
  for (int i = 0; i < 100; i++) {
    stack.push(i);
  }

  ASSERT_FALSE(stack.isEmpty());

  for (int i = 99; i >= 0; i--) {
    ASSERT_EQ(i, stack.top());
    stack.pop();
  }

  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackVTest, PopElement) {
  st::StackV stack;
  ASSERT_TRUE(stack.isEmpty());
  stack.pop();
  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackVTest, TopEmpty) {
  st::StackV stack;
  bool er = false;
  ASSERT_TRUE(stack.isEmpty());
  try {
    stack.top();
  } catch (std::out_of_range ex) {
    er = true;
  }
  ASSERT_TRUE(er);
  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackVTest, CopyStack) {
  st::StackV stack;
  for (int i = 0; i < 100; i++) {
    stack.push(i);
  }

  stack = stack;

  st::StackV stack2(stack);

  stack2 = stack2;

  for (int i = 99; i >= 0; i--) {
    ASSERT_EQ(i, stack.top());
    stack.pop();
  }
  ASSERT_TRUE(stack.isEmpty());

  for (int i = 99; i >= 0; i--) {
    ASSERT_EQ(i, stack2.top());
    stack2.pop();
  }
  ASSERT_TRUE(stack2.isEmpty());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#include <gtest/gtest.h>
#include "stack.h"

TEST(StackLTest, AddCheckPopElement) {
  StackL stack;
  ASSERT_TRUE(stack.isEmpty());
  stack.push(10);
  ASSERT_FALSE(stack.isEmpty());
  ASSERT_EQ(10, stack.top());
  stack.pop();
  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackLTest, AddElements) {
  StackL stack;
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
  StackL stack;
  ASSERT_TRUE(stack.isEmpty());
  stack.pop();
  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackLTest, TopEmpty) {
  StackL stack;
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
  StackL stack;
  for (int i = 0; i < 100; i++) {
    stack.push(i);
  }

  stack = stack;

  StackL stack2(stack);

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

////

TEST(StackVTest, AddCheckPopElement) {
  StackV stack;
  ASSERT_TRUE(stack.isEmpty());
  stack.push(10);
  ASSERT_FALSE(stack.isEmpty());
  ASSERT_EQ(10, stack.top());
  stack.pop();
  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackVTest, AddElements) {
  StackV stack;
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
  StackV stack;
  ASSERT_TRUE(stack.isEmpty());
  stack.pop();
  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackVTest, TopEmpty) {
  StackV stack;
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
  StackV stack;
  for (int i = 0; i < 100; i++) {
    stack.push(i);
  }

  stack = stack;

  StackV stack2(stack);

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

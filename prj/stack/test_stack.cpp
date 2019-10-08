#include <gtest/gtest.h>
#include "stack.h"

TEST(StackTest, AddCheckPopElement)
{
  StackL stack;
  ASSERT_TRUE(stack.isEmpty());
  stack.push(10);
  ASSERT_FALSE(stack.isEmpty());
  ASSERT_EQ(10, stack.top());
  stack.pop();
  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackTest, AddElements)
{
  StackV stack;
  for (int i = 0; i < 100; i++){
    stack.push(i);
  }

  ASSERT_FALSE(stack.isEmpty());

  for (int i = 99; i >= 0; i--){
    ASSERT_EQ(i, stack.top());
    stack.pop();
  }

  ASSERT_TRUE(stack.isEmpty());
}

TEST(StackTest, PopElement){
    StackV stack;
    ASSERT_TRUE(stack.isEmpty());
    stack.pop();
    ASSERT_TRUE(stack.isEmpty());
}

TEST(StackTest, TopEmpty){
    StackV stack;
    bool er = false;
    ASSERT_TRUE(stack.isEmpty());
    try{
        stack.top();
    }
    catch(std::out_of_range ex){
        er = true;
    }
    ASSERT_TRUE(er);
    ASSERT_TRUE(stack.isEmpty());
}

TEST(StackTest, CopyStack){
    StackV stack;
    for (int i = 0; i < 100; i++){
      stack.push(i);
    }

    StackV stack2(stack);

    for (int i = 99; i >= 0; i--){
      ASSERT_EQ(i, stack.top());
      stack.pop();
    }
    ASSERT_TRUE(stack.isEmpty());

    for (int i = 99; i >= 0; i--){
      ASSERT_EQ(i, stack2.top());
      stack2.pop();
    }
    ASSERT_TRUE(stack2.isEmpty());
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

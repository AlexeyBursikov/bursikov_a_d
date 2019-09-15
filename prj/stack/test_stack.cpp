#include <gtest/gtest.h>
#include "stack.h"

TEST(StackTest, AddCheckPopElement)
{
  Stack stack;
  stack.push(10);
  ASSERT_EQ(10, stack.top());
  stack.pop();
}

TEST(StackTest, AddElements)
{
  Stack stack;
  for (int i = 0; i < 100; i++){
    stack.push(i);
  }

  for (int i = 99; i > 0; i--){
    ASSERT_EQ(i, stack.top());
    stack.pop();
  }
}

TEST(StackTest, PopElements){
    Stack stack;
    ASSERT_TRUE(stack.isEmpty());
    stack.pop();
    ASSERT_TRUE(stack.isEmpty());
}

TEST(StackTest, TopEmpty){
    Stack stack;
    ASSERT_TRUE(stack.isEmpty());
    try{
        stack.top();
    }
    catch(std::exception ex){
        ASSERT_FALSE(dynamic_cast<std::out_of_range*>(&ex));
    }
    ASSERT_TRUE(stack.isEmpty());
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

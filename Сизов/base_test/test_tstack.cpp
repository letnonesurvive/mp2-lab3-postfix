#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, can_not_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> st(-5));
}
TEST(TStack, can_not_create_stack_with_too_large_length)
{
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize+1));
}
TEST(TStack, can_return_last_elem_of_stack)
{
	TStack<int> st(5);
	for (int i = 0; i < 5; i++)
	{
		st.Put(i);
	}
	EXPECT_EQ(4, st.Back());
}
TEST(TStack, can_put_elem_in_stack)
{
	TStack<int> st(1);
	ASSERT_NO_THROW(st.Put(10));
}
TEST(TStack, can_get_elem_of_stack)
{
	TStack<int> st(1);
	st.Put(10);
	EXPECT_EQ(10, st.Get());
}
TEST(TStack, method_get_delete_elem_of_stack)
{
	TStack<int> st(5);
	st.Put(5);
	st.Get();
	EXPECT_NE(5, st.Back());
}
TEST(TStack, can_check_stack_for_empty)
{
	TStack<int> st(1);
	EXPECT_TRUE(st.IsEmpty());
}
TEST(TStack, can_check_stack_for_full)
{
	TStack<int> st(5);
	while (!st.IsFull())
		st.Put(5);
	EXPECT_TRUE(st.IsFull());
}
TEST(TStack, can_create_copied_stack)
{
	TStack<int> st1(5);
	st1.Put(5);
	TStack<int> st2(st1);
	EXPECT_EQ(st1,st2);//ASSERT_NO_THROW(TStack<int>st1(st));
}
TEST(TStack, can_compare_two_stacks)
{
	TStack<int> st1(5);
	st1.Put(5);
	TStack<int> st2(st1);
	EXPECT_TRUE(st1==st2);
}
TEST(TStack, two_stacks_are_not_equal)
{
	TStack<int> st1(5),st2(5);
	st1.Put(5);
	EXPECT_NE(st1, st2);
}
TEST(TStack, can_assign_stack)
{
	TStack<int> st1(1),st2(1);
	st1.Put(5);
	ASSERT_NO_THROW(st2 = st1);//st2 = st1;
}
TEST(TStack, assign_operator_change_stack_size)
{
	TStack<int> st1(5), st2(10);
	st1 = st2;
	EXPECT_NE(5, st1.Size());
}
TEST(TStack, assign_operator_change_stack_top)//sorry for my english 
{
	TStack<int> st1(5), st2(10);
	while (!st1.IsFull())
	{
		st1.Put(5);
	}
	st2 = st1;
	EXPECT_NE(-1, st2.Top());
}
TEST(TStack, two_different_stacks_have_different_memories)
{
	TStack<int> st1(2), st2(3);
	EXPECT_NE(&st1, &st2);
}





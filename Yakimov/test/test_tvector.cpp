// ASSERT_NO_THROW - не должен выбрасывать исключение (на создании обьектов и тд)
// ASSERT_ANY_THROW - должен выбрасывать исключение любого типа(на создании обьектов и тд)
// EXPECT_EQ - проверка на равенство объектов
// EXPECT_NQ - проверка на неравенство объектов
// ASSERT_EQ(условие , true/false) - проверка логического выражения

#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> a(5);
	for (int i = 0; i < v.size(); i++)
	{
		v[i] = i;
	}
	a = v;
	ASSERT_EQ(v == a, true);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> a(5);
	for (int i = 0; i < v.size(); i++)
	{
		v[i] = i;
	}
	a = v;
	ASSERT_EQ(v[0] == a[0], true);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v[-1] = 0);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v[MAX_VECTOR_SIZE + 1] = 0);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> w(4);
	for (size_t i = 0; i < 4; i++)
	{
		v[i] = i;
		w[i] = i + 1;
	}
	ASSERT_NO_THROW(v = w);
	ASSERT_EQ(v == w, true);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> w(5);
	ASSERT_NO_THROW(v = w);
	ASSERT_EQ(v.size() == 5, true);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(4);
	TDynamicVector<int> w(5);
	for (size_t i = 0; i < 4; i++)
	{
		v[i] = i;
		w[i] = i + 1;
	}
	ASSERT_NO_THROW(v = w);
	ASSERT_EQ(v == w, true);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(6);
	TDynamicVector<int> w(6);
	for (size_t i = 0; i < 6; i++)
	{
		v[i] = i;
		w[i] = i;
	}
	ASSERT_EQ(v == w, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(6);
	for (size_t i = 0; i < 6; i++)
		v[i] = i;
	ASSERT_EQ(v != v, false);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(6);
	TDynamicVector<int> w(7);
	for (size_t i = 0; i < 6; i++)
	{
		v[i] = i;
		w[i] = i;
	}
	ASSERT_EQ(v == w, false);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> w(5);
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = 1;
		w[i] = 7;
	}
	int c = 6;
	ASSERT_NO_THROW(v + c);
	ASSERT_EQ(v + c == w, true);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> w(5);
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = 1;
		w[i] = -5;
	}
	int c = 6;
	ASSERT_NO_THROW(v - c);
	ASSERT_EQ(v - c == w, true);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> w(5);
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = 2;
		w[i] = 12;
	}
	int c = 6;
	ASSERT_NO_THROW(v * c);
	ASSERT_EQ(v * c == w, true);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> w(5);
	TDynamicVector<int> k(5);
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = 1;
		w[i] = 3;
		k[i] = 4;
	}
	ASSERT_NO_THROW(v + w);
	ASSERT_NO_THROW(v + w, k);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> w(6);
	ASSERT_ANY_THROW(v + w);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> w(5);
	TDynamicVector<int> k(5);
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = 1;
		w[i] = 3;
		k[i] = -2;
	}
	ASSERT_NO_THROW(v - w);
	ASSERT_NO_THROW(v - w, k);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> w(6);
	ASSERT_ANY_THROW(v - w);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> w(5);
	int k = 30;
	for (size_t i = 0; i < 5; i++)
	{
		v[i] = 2;
		w[i] = 3;
	}
	ASSERT_NO_THROW(v * w);
	ASSERT_NO_THROW(v * w, k);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> w(6);
	ASSERT_ANY_THROW(v * w);
}
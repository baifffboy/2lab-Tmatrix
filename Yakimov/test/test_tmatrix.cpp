// ASSERT_NO_THROW - не должен выбрасывать исключение (на создании обьектов и тд)
// ASSERT_ANY_THROW - должен выбрасывать исключение любого типа(на создании обьектов и тд)
// EXPECT_EQ - проверка на равенство объектов
// EXPECT_NQ - проверка на неравенство объектов
// ASSERT_EQ(условие , true/false) - проверка логического выражения

#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++)
			m[i][j] = i;
	TDynamicMatrix<int>n(m);
	ASSERT_EQ(n == m, true);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int>n(m);
	m[0][0] = 1;
	ASSERT_EQ(m[0][0] != n[0][0], true);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(m[0][0] = 5);
	EXPECT_EQ(5, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m[-1][-1] = 2);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m[MAX_MATRIX_SIZE + 1][MAX_MATRIX_SIZE + 1] = 2);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> n(5);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++)
		{
			m[i][j] = i;
			n[j][i] = i;
		}
	ASSERT_NO_THROW(m = n);
	ASSERT_EQ(n == m, true);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(7);
	TDynamicMatrix<int> n(5);
	m = n;
	EXPECT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(7);
	TDynamicMatrix<int> n(5);
	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++)
		{
			n[j][i] = i;
		}
	for (size_t i = 0; i < 7; i++)
		for (size_t j = 0; j < 7; j++)
		{
			m[j][i] = i;
		}
	ASSERT_NO_THROW(m = n);
	ASSERT_EQ(n == m, true);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> n(2);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
		{
			n[j][i] = i;
			m[j][i] = i;
		}
	ASSERT_EQ(n == m, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);
	ASSERT_EQ(m == m, true);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> n(3);
	ASSERT_EQ(m == n, false);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> n(2);
	TDynamicMatrix<int> k(2);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			if ((i + j == 0) || (i + j == 2))
			{
				n[i][j] = 1;
				m[i][j] = 0;
				k[i][j] = 1;
			}
			else
			{
				n[i][j] = 0;
				m[i][j] = 1;
				k[i][j] = 1;
			}
	ASSERT_NO_THROW(m + n);
	ASSERT_EQ((m + n) == k, true);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> n(3);
	ASSERT_ANY_THROW(m + n);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> n(2);
	TDynamicMatrix<int> k(2);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			if ((i + j == 0) || (i + j == 2))
			{
				n[i][j] = 1;
				m[i][j] = 1;
				k[i][j] = 0;
			}
			else
			{
				n[i][j] = 1;
				m[i][j] = 1;
				k[i][j] = 0;
			}
	ASSERT_NO_THROW(m - n);
	ASSERT_EQ((m - n) == k, true);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> n(3);
	ASSERT_ANY_THROW(m - n);
}
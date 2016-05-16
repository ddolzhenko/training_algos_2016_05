// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int linear_sort(int A[], int size, int key)
{
	for (int i = 0; i < size; ++i)
	{
		if (A[i] == key)
			return i;
	}
	return -1;
}


int linear_sort_optimized(int A[], int size, int key)
{
	A[size] = key;
	int i = 0;

	while (A[i] != key)
	{
		++i;
	}

	if (i == size)
		return -1;

	return i;
}

int linear_sort_tricky(int A[], int size, int key)
{
	int back = size - 1;

	if (A[back] == key)
		return back;

	int lastElement = A[back];
	A[back] = key;

	int i = 0;

	while (A[i] != key)
	{
		++i;
	}

	A[back] = lastElement;

	if (i == back)
		return -1;

	return i;
}

int main()
{
    return 0;
}


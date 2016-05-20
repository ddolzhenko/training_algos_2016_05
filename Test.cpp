// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <assert.h>
#include <functional>
#include <vector>
#include <string>

using namespace std;

typedef std::function<int(int*, int, int)> SearchFunc;

int linear_search(int* A, int size, int key)
{
	assert(size >= 0);
	for (int i = 0; i < size; ++i)
	{
		if (A[i] == key)
			return i;
	}
	return -1;
}


int linear_search_optimized(int* A, int size, int key)
{
	assert(size >= 0);
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

int linear_search_tricky(int* A, int size, int key)
{
	assert(size >= 0);

	if (size == 0)
		return -1;

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

/*
// длина полуоткрытого интервала равна разности end - begin
// единственным невалидным елементом, который можно вернуть - это конец полуоткрытого интервала
// можно указать пустой интервал
// полуоткрытый интервал можно всегда поделить пополам на 2 полуоткрытых интервала

// исправить алгоритм
def bin_search(A, k):
	assert is.sorted(A)
	b, e = 0, len(A)
	if e == 0:
		return e
	if e == 1:
		return 0 if A[0] == k else e
	assert b < e ''' assert b > e
	m = (b + e) / 2 ''' = b + ( e - b ) / 2
	if k < A[m]:
		return binary_search(A[b:m), k)
	else:
		return binary_search(A[m:e), k)
	''' [b, m) [m, e)
*/

int binary_search(int* A, int size, int key)
{
	int first = 0;
	int last = size;

	if (key < A[first])
		return -1;
	if (key > A[last - 1])
		return -1;

	while (first < last)
	{
		int mid = first + (last - first) / 2;
		if (key <= mid)
		{
			last = mid;
		}
		else
		{
			first = mid;
		}
	}

	if (A[last] == key)
		return last;

	return -1;
}

bool checkSearch( SearchFunc search, int A[], int size, int targetIndex )
{
	return (targetIndex == search(A, size, 1));
}

struct TestData
{
	int input[10];
	int size;
	int answer;
	std::string description;
};

struct FunctionWrapper
{
	SearchFunc func;
	std::string description;
};

int main()
{
	std::vector<FunctionWrapper> functions =
	{ 
		{ linear_search, "linear_search"}, 
		{ linear_search_optimized, "linear_search_optimized" },
		{ linear_search_tricky, "linear_search_tricky" }
	};

	std::vector<TestData> testData = {
		{
			{}, 0, -1, "Trivial empty"
		},
		{
			{2}, 1, -1, "Trivial one element, no key"
		},
		{
			{1}, 1, 0, "Trivial one element, key exists"
		},
		{
			{1, 2}, 2, 0, "Two elements, has key"
		},
		{
			{ 3, 4 }, 2, -1, "Two elements, no key"
		},
		{
			{ 3, 8, 1, 10 }, 4, 2, "Four elements, has key"
		},
		{
			{ 3, 8, 2, 10 }, 4, -1, "Four elements, has key"
		}
	};

	for (TestData test : testData)
	{
		cout << "------- Test: " << test.description << " ----------" << endl;
		for (FunctionWrapper wrapper : functions)
		{
			const char* result = checkSearch(wrapper.func, test.input, test.size, test.answer) ? "OK" : "FAILED";
			cout << wrapper.description << ": " << result << endl;
		}
	}

	system("pause");
    return 0;
}
// метод мат. индукции
// => inference
// <=> 
// less wrong ru 
// множества чисел
// доказать свойства логарифмов
// Monte Carlo algo
// RANSAC
// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <assert.h>
#include <functional>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
typedef vector<int> IntArray;
typedef vector<int>::iterator IntArrayIter

typedef std::function<int(IntArrayIter&, IntArrayIter&, int)> SearchFunc;

int linear_search(IntArrayIter& begin, IntArrayIter& end, int key)
{
	assert((end - begin) >= 0);
    IntArrayIter it = begin;
	for (it; it!=end; ++it)
	{
		if (*it == key)
			break;
	}
	return (it - begin);
}

int binary_search(IntArrayIter& begin, IntArrayIter& end, int key)
{
    assert( std::is_sorted(begin, end) );
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
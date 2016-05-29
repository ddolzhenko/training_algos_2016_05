// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <cassert>
#include <functional>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;
typedef vector<int> IntArray;
typedef vector<int>::iterator IntArrayIter;

typedef std::function<int(IntArrayIter&, IntArrayIter&, int)> SearchFunc;

int linear_search(IntArrayIter& begin, IntArrayIter& end, int key)
{
	if ((end - begin) < 0)
		throw std::exception("Invalid iterators");

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
	if (!is_sorted(begin, end))
		throw std::exception("Not sorted");

	int len = end - begin;

	if (len == 0)
		return len;

	if (*begin == key)
		return 0;
	else
		return len;

	assert(begin < end);

	IntArrayIter mid = begin + (end - begin) / 2;

	if (key < *mid)
		return binary_search(begin, mid, key);
	else
		return binary_search(mid, end, key);
}

/*template <class T, class TFunct, class P1, class P2>
T test(T expected, TFunct func, P1 p1, P2 p2)
{
	return 
}*/
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


template <class TIter, class T>
TIter binary_search_1(TIter begin, TIter end, T key)
{
	assert(std::is_sorted(begin, end));
	size_t size = end - begin;
	if (size == 0)
		return end;
	if (size == 1)
		return (*begin) == key ? begin : end;
	auto m = begin + (end - begin) / 2;
	if (key < *m)
	{
		auto r = binary_search_1(begin, m, key);
		return m == r ? end : r;
	}
	else
		return binary_search_1(m, end, key);
}

template <class TIter, class T>
TIter binary_search_2(TIter begin, TIter end, T key)
{
	assert(std::is_sorted(begin, end));
	size_t size = end - begin;
	if (size == 0)
		return end;

	assert(size > 0);

	auto m = begin + (end - begin) / 2;

	//[begin, m) [m] (m end )

	//if (*m == key)
	//	return m;
	if (key < *m) // [begin, m)
	{
		auto r = binary_search_2(begin, m, key);
		return m == r ? end : r;
	}
	else if (*m < key)
		return binary_search_2(m+1, end, key);
	else
		return m;
}

template <class TIter, class T>
TIter upper_bound(TIter begin, TIter end, T key)
{
	assert(std::is_sorted(begin, end));
	while ( begin < end )
	{
		auto m = begin + (end - begin) / 2;
		if (key < *m) 
		{
			end = m; // [begin, m)
		}
		else
		{
			begin = m + 1; // [m+1, end)
		}
	}
	return begin;
}

// doesn't compile
template <class TIter, class T>
TIter binary_search_3(TIter begin, TIter end, T key)
{
	auto res = upper_bound<TIter, T>(begin, end, key);
	if (res == end)
		return end;
	else
	{
		return *res == key ? res : end;
	}
}

// implement lower-bound
// implement tests for upper / lower bound

ostream& operator<<( ostream& o, const vector<int>& v )
{
	o << "{";
	for (auto x : v)
	{
		o << x << ", ";
	}
	o << "}";
	return o;
}

template<class T, class TFunc, class P1, class P2>
void test(T expected, TFunc f, P1 p1, P2 p2)
{
	auto result = f(p1, p2);
	cout << "---------------------------------------------------------------------" << endl;
	cout << "f(" << p1 << ", " << p2 << ") = " << result << endl;

	if (expected != result)
	{
		cout << "Expected: " << expected << "; Result: " << result << endl;
		system("pause");
	}
	else
	{
		cout << "OK!" << endl;
	}
}

typedef vector<int> Vec;

template<class TFunc>
void test_binary_search(TFunc bin_search)
{
	
	int key = 42;
	auto adaptor = [bin_search](Vec& v, int key)
	{
		auto result = bin_search(v.begin(), v.end(), key);
		return (result == v.end()) ? -1 : (result - v.begin());
	};

	test(-1, adaptor, Vec({}), key);
	test(0, adaptor, Vec({ 42 }), key);
	test(-1, adaptor, Vec({ 43 }), key);
	test(0, adaptor, Vec({ 42, 43 }), key);
	test(1, adaptor, Vec({ 41, 42 }), key);
	test(-1, adaptor, Vec({ 41, 43 }), key);
	test(-1, adaptor, Vec({1,2,3,4}), key);

	test(3, adaptor, Vec({ 1, 2, 5, 42 }), key);
	test(2, adaptor, Vec({ 3, 5, 42, 45, 67 }), key);
	test(3, adaptor, Vec({ 3, 5, 41, 42, 45, 67 }), key);
	test(3, adaptor, Vec({ 3, 5, 41, 42 }), key);
	test(3, adaptor, Vec({ 3, 5, 41, 42, 43, 44, 45 }), key);

	// more than one key
	test(1, adaptor, Vec({ key, key }), key);
	//test(3, adaptor, Vec({ 1,2,key, key }), key);
	test(1, adaptor, Vec({ key, key, key+1, key+10 }), key);
	test(4, adaptor, Vec({ 1,2,3, key, key }), key);
}

int main()
{
	//test_binary_search(binary_search_1<Vec::iterator, int>);
	test_binary_search(binary_search_3<Vec::iterator, int>);
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


/*bool checkSearch( SearchFunc search, IntArray& A, int targetIndex )
{
return (targetIndex == search(A.begin(), A.end(), 42));
}

struct TestData
{
IntArray input;
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
{ binary_search, "binary_search" }
};

std::vector<TestData> testData = {
{
{}, 0, "{}"
},
{
{2}, 1, "{2}"
},
{
{42}, 0, "{42}"
},
{
{1, 2, 4}, 3, "{1, 2, 4}"
},
{
{ 42, 43 }, 0, "{ 42, 43 }"
},
{
{ 3, 4 }, 2, "{ 3, 4 }"
},
{
{ 1, 2, 3, 5, 41 }, 5, "{ 1, 2, 3, 5, 41 }"
},
{
{ 43, 45, 67, 100 }, 4, "{ 43, 45, 67, 100 }"
},
{
{ 3, 5,41,43,45,67 }, 6, "{ 3, 5,41,43,45,67 }"
},
{
{ 1, 2, 5, 42 }, 3, "{ 1, 2, 5, 42 }"
},
{
{ 42, 45, 67, 100 }, 0, "{ 42, 45, 67, 100 }"
},
{
{ 3, 5, 41, 42 }, 3, "{ 3, 5, 41, 42 }"
},
{
{ 3, 5, 41, 42, 45, 67 }, 3, "{ 3, 5, 41, 42, 45, 67 }"
},
{
{ 3, 5, 42, 45, 67 }, 2, "{ 3, 5, 42, 45, 67 }"
}
};

for (TestData test : testData)
{
cout << "------- Test: " << test.description << " ----------" << endl;
for (FunctionWrapper wrapper : functions)
{
//const char* result = "EXCEPTION";
bool result = checkSearch(wrapper.func, test.input, test.answer);
cout << "Test " << wrapper.description << ": " << ((result) ? "OK" : "FAILED") << endl;
if (!result)
{
cout << "Expected: " << test.answer << ";" << "Given: " << wrapper.func(test.input.begin(), test.input.end(), 42) << endl;
goto end;
}
}
}
end:*/
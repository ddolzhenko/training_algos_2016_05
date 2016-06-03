#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;
using std::vector;
typedef vector<int> IntVector;

namespace {
int tests = 0;
int failed = 0;

ostream& operator<<(ostream& o, const IntVector& v) {
    o << "{";
    for (const auto& x : v) {
        o << x << ",";
    }
    o << "}";
    return o;
}

void print_test_result(bool cond) {
    ++tests;
    if (!cond) ++failed;
    std::cout << (cond ? "OK\n" : "ERROR\n");
}

bool TEST(int (* func)(IntVector& vec, const int key), IntVector input_vector, const int key,  const int expected) {
    const int result = func(input_vector, key);
//    std::cout << "TEST : find {"  << key << "} in " << input_vector << "\n";
//    std::cout << "find on : " << result << " vs expexted: " << expected << " is ";

    std::cout << "test : " << expected << " == f(" << input_vector << ") == " << result << "; ";
    print_test_result(result == expected);
    return result == expected;
}

}

int linear_search_1(IntVector& Array, const int key) {
	for (int i = 0; i < Array.size(); ++i) {
		if (Array[i] == key) { 
			return i;
		}
	}
	return -1;
}

int linear_search_2(IntVector& Array, const int key) {
	int i = 0;
	while (i < Array.size()) {
		if (Array[i] == key) {
			return i;
		}
		++i;
	}
	return -1;
}

int linear_search_3(IntVector& Array, const int key) {
	const int array_size = Array.size();
    const int added_elem_pos = array_size;

    if (!array_size) return -1;

    Array[added_elem_pos] = key;

	int i = 0;
	while (Array[i] != key) { 
		++i; 
	}
    if (i != added_elem_pos) {
        return i;
	}

	return -1;
}

int linear_search_4(IntVector& Array, const int key) {
	const int array_size = Array.size();
    if (!array_size) return -1;
	
    int end = array_size;
	if (Array[end] == key) {
		return end;
	}

	int last = Array[end];
	
	Array[end] = key;

	int i = 0;
	while (Array[i] != key) {
		++i;
	}

	Array[end] = last;

	if (i != array_size) {
		return i;
	}

	return -1;
}

IntVector::iterator binary_search_1(IntVector::iterator begin_itt, IntVector::iterator end_itt,  const int key) {
//    assert(std::is_sorted(begin_itt, end_itt);
    size_t size = end_itt - begin_itt;
    if (0 == size) {
        return end_itt;
    }
    if(1 == size) {
        return (*begin_itt) == key ? begin_itt : end_itt;
    }

    IntVector::iterator m = begin_itt + (end_itt - begin_itt) / 2;
    if (key < *m) {
        IntVector::iterator r = binary_search_1(begin_itt, m, key);
        return m == r ? end_itt : r;
    } else {
        return binary_search_1(m, end_itt, key);
    }
}

IntVector::iterator binary_search_2(IntVector::iterator begin_itt, IntVector::iterator end_itt,  const int key) {
//    assert(std::is_sorted(begin_itt, end_itt);
    size_t size = end_itt - begin_itt;
    if (0 == size) {
        return end_itt;
    }

    IntVector::iterator m = begin_itt + (end_itt - begin_itt) / 2;

    if (key < *m) { // (begin, m)
        IntVector::iterator r = binary_search_2(begin_itt, m, key);
        return m == r ? end_itt : r;
    } else if (*m < key){ // [m+1,end]
        return binary_search_2(m, end_itt, key);
    } else { // key == *m
        return m;
    }
}

IntVector::iterator upper_bound(IntVector::iterator begin_itt, IntVector::iterator end_itt,  const int key) {
//    assert(std::is_sorted(begin_itt, end_itt);

    while (begin_itt < end_itt) {
        IntVector::iterator m = begin_itt + (end_itt - begin_itt) / 2;

        if (key < *m) { // (begin, m)
            end_itt = m;
        } else {
            begin_itt = m + 1;
        }
    }
}

IntVector::iterator lower_bound(IntVector::iterator begin_itt, IntVector::iterator end_itt,  const int key) {
//    assert(std::is_sorted(begin_itt, end_itt);

    while (begin_itt < end_itt) {
        IntVector::iterator m = begin_itt + (end_itt - begin_itt) / 2;

        if (*m < key) { // (begin, m)
            begin_itt = m + 1;
        } else {
            end_itt = m;
        }
    }
}

IntVector::iterator binary_search_3(IntVector::iterator begin_itt, IntVector::iterator end_itt,  const int key) {
//    assert(std::is_sorted(begin_itt, end_itt);
    IntVector::iterator res = upper_bound(begin_itt, end_itt, key);
    if(res == end_itt) {
        return end_itt;
    }
    return *res == key ? res : end_itt;
}

int adaptor(IntVector& vec, const int find_key) {
    IntVector::iterator result = binary_search_1(vec.begin(), vec.end(), find_key);
    return (vec.end() == result) ? -1 : result - vec.begin();
}

// Test Section

void test_linear_search(int (* func)(IntVector&, int key)) {
    const int find_key = 1;
    IntVector empty;
    IntVector one_element_not_exists = {2};
    IntVector one_element_exists = {1};
    IntVector several_elements_not_exists = {2,3,4,5,6};
    IntVector several_elements_exists_start = {1,3,4,5};
    IntVector several_elements_exists_middle = {2,1,4,5,6};
    IntVector several_elements_exists_end = {0,2,3,4,1};

    TEST(func, empty, find_key, -1);
    TEST(func, one_element_not_exists, find_key, -1);
    TEST(func, one_element_exists, find_key, 0);
    TEST(func, several_elements_not_exists, find_key, -1);
    TEST(func, several_elements_exists_start, find_key, 0);
    TEST(func, several_elements_exists_middle, find_key, 1);
    TEST(func, several_elements_exists_end, find_key, 4);
}

void test_binary_search_templ(int (* search_impl)(IntVector& vec, const int key)) {
    const int find_key = 42;
    IntVector v1;
    IntVector v2 = {1};
    IntVector v3 = {42};
    IntVector v4 = {1,2};
    IntVector v5 = {1, 42};
    IntVector v6 = {42, 100};
    IntVector v7 = {1,2,3,5,41};
    IntVector v8 = {43,45,67,100};
    IntVector v9 = {3,5,41,43,45,67};
    IntVector v10 = {1,2,5,42};
    IntVector v11 = {42,45,67,100};
    IntVector v12 = {3,5,41,42,45,67};
    IntVector v13 = {3,5,42,45,67};
    IntVector v14 = {42,42};
    IntVector v15 = {1,2,find_key,find_key};
    IntVector v16 = {find_key,find_key, 43, 45};


    TEST(search_impl, v1, find_key, -1);
    TEST(search_impl, v2, find_key, -1);
    TEST(search_impl, v3, find_key, 0);
    TEST(search_impl, v4, find_key, -1);
    TEST(search_impl, v5, find_key, 1);
    TEST(search_impl, v6, find_key, 0);
    TEST(search_impl, v7, find_key, -1);
    TEST(search_impl, v8, find_key, -1);
    TEST(search_impl, v9, find_key, -1);
    TEST(search_impl, v10, find_key, 3);
    TEST(search_impl, v11, find_key, 0);
    TEST(search_impl, v12, find_key, 3);
    TEST(search_impl, v13, find_key, 2);
    TEST(search_impl, v14, find_key, 1);
    TEST(search_impl, v15, find_key, 3);
    TEST(search_impl, v16, find_key, 1);
}


int main()
{
//    std::cout << "L_1_test\n";
//    test_linear_search(&linear_search_1);
//    std::cout << "L_2_test\n";
//    test_linear_search(&linear_search_2);
//    std::cout << "L_3_test\n";
//    test_linear_search(&linear_search_3);
//    std::cout << "L_4_test\n";
//    test_linear_search(&linear_search_4);


//    std::cout << "B_1_test\n";
//    test_binary_search_templ(adaptor);


    double n = 1;
    while (n < 50) {
        std::cout << pow(2,n) << " : " << pow(n, 8 ) << " _ " << n <<  std::endl;
        ++n;
    }
    std::cout << pow(2,n) << " : " << pow(n, 8 ) << " _ " << n <<  std::endl;

    if (failed != tests) {
        std::cout << std::endl << "TESTS FINISHED : " << failed << " of " << tests << " FAILED!" << std::endl;
    } else {
        std::cout << std::endl << "TESTS FINISHED CORECTLY " << std::endl;
    }
    return 0;
}


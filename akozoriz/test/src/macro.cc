#include <iostream>

#include "helpers.h"
#include "macro.h"

namespace test {

bool TEST(int (*func)(IntVector& vec, const int key),
          IntVector input_vector,
          const int key,
          const int expected) {
  const int result = func(input_vector, key);

  std::cout << "test : " << expected << " == f(" << input_vector
            << ") == " << result << "; ";
  helpers::print_test_result(result == expected);
  return result == expected;
}

void test_linear_search(int (*func)(IntVector&, int key)) {
  const int find_key = 1;
  IntVector empty;
  IntVector one_element_not_exists = {2};
  IntVector one_element_exists = {1};
  IntVector several_elements_not_exists = {2, 3, 4, 5, 6};
  IntVector several_elements_exists_start = {1, 3, 4, 5};
  IntVector several_elements_exists_middle = {2, 1, 4, 5, 6};
  IntVector several_elements_exists_end = {0, 2, 3, 4, 1};

  TEST(func, empty, find_key, -1);
  TEST(func, one_element_not_exists, find_key, -1);
  TEST(func, one_element_exists, find_key, 0);
  TEST(func, several_elements_not_exists, find_key, -1);
  TEST(func, several_elements_exists_start, find_key, 0);
  TEST(func, several_elements_exists_middle, find_key, 1);
  TEST(func, several_elements_exists_end, find_key, 4);
}

void test_binary_search_templ(int (*search_impl)(IntVector& vec,
                                                 const int key)) {
  const int find_key = 42;
  IntVector v1;
  IntVector v2 = {1};
  IntVector v3 = {42};
  IntVector v4 = {1, 2};
  IntVector v5 = {1, 42};
  IntVector v6 = {42, 100};
  IntVector v7 = {1, 2, 3, 5, 41};
  IntVector v8 = {43, 45, 67, 100};
  IntVector v9 = {3, 5, 41, 43, 45, 67};
  IntVector v10 = {1, 2, 5, 42};
  IntVector v11 = {42, 45, 67, 100};
  IntVector v12 = {3, 5, 41, 42, 45, 67};
  IntVector v13 = {3, 5, 42, 45, 67};
  IntVector v14 = {42, 42};
  IntVector v15 = {1, 2, find_key, find_key};
  IntVector v16 = {find_key, find_key, 43, 45};

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

}  // namespace test

//#include <vector>
#include <iostream>
//#include <algorithm>
//#include <math.h>

#include "test/include/helpers.h"
#include "test/include/macro.h"
#include "components/include/search.h"
#include "components/include/sort.h"

using namespace std;
using std::vector;
typedef vector<int> IntVector;

namespace {
int tests = 0;
int failed = 0;
}

int main() {
  IntVector arr = {2, 3, 4, 8, 6, 4, 1, 23, 4, 5, 684, 12, 5, 4, 86};

  //    sort_naive(arr.begin(), arr.end());
  //    sort_buble(arr.begin(), arr.end());

  std::cout << arr << std::endl;
  //    std::cout << "L_1_test\n";
  //    test::test_linear_search(&components::search::linear::linear_search_1);
  //    std::cout << "L_2_test\n";
  //    test::test_linear_search(&components::search::linear::linear_search_2);
  //    std::cout << "L_3_test\n";
  //    test::test_linear_search(&components::search::linear::linear_search_3);
  //    std::cout << "L_4_test\n";
  //    test::test_linear_search(&components::search::linear::linear_search_4);

  //    std::cout << "B_1_test\n";
  //    test::test_binary_search_templ(&components::search::binary::binary_to_linear_adaptor);

  return 0;
}

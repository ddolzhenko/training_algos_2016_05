#include <vector>

namespace test {
typedef std::vector<int> IntVector;

bool TEST(int (*func)(IntVector& vec, const int key),
          IntVector input_vector,
          const int key,
          const int expected);

void test_linear_search(int (*func)(IntVector&, int key));

void test_binary_search_templ(int (*search_impl)(IntVector& vec,
                                                 const int key));
}

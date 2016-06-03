#include <iostream>
#include <vector>

typedef std::vector<int> IntVector;

std::ostream& operator<<(std::ostream& o, const IntVector& v);

namespace test {
namespace helpers {

void print_test_result(bool cond);

}  // namespace helpers
}  // namespace test

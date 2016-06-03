#include "helpers.h"

std::ostream& operator<<(std::ostream& o, const IntVector& v) {
  o << "{";
  for (const auto& x : v) {
    o << x << ",";
  }
  o << "}";
  return o;
}

namespace test {
namespace helpers {

namespace {
int tests = 0;
int failed = 0;
}

void print_test_result(bool cond) {
  ++tests;
  if (!cond)
    ++failed;
  std::cout << (cond ? "OK\n" : "ERROR\n");
}

}  // namespace helpers
}  // namespace test

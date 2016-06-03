#include <vector>

typedef std::vector<int> IntVector;

namespace components {
namespace search {
namespace linear {
int linear_search_1(IntVector& Array, const int key);
int linear_search_2(IntVector& Array, const int key);
int linear_search_3(IntVector& Array, const int key);
int linear_search_4(IntVector& Array, const int key);
}  // namespace linear

namespace binary {
IntVector::iterator binary_search_1(IntVector::iterator begin_itt,
                                    IntVector::iterator end_itt,
                                    const int key);
IntVector::iterator binary_search_2(IntVector::iterator begin_itt,
                                    IntVector::iterator end_itt,
                                    const int key);
IntVector::iterator binary_search_3(IntVector::iterator begin_itt,
                                    IntVector::iterator end_itt,
                                    const int key);

IntVector::iterator upper_bound(IntVector::iterator begin_itt,
                                IntVector::iterator end_itt,
                                const int key);
IntVector::iterator lower_bound(IntVector::iterator begin_itt,
                                IntVector::iterator end_itt,
                                const int key);

int binary_to_linear_adaptor(IntVector& vec, const int find_key);

}  // namespace binary
}  // namespace search
}  // namespace components

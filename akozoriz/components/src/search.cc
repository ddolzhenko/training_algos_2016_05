#include <cstdlib>

#include "search.h"

namespace components {
namespace search {
namespace linear {

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

  if (!array_size)
    return -1;

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
  if (!array_size)
    return -1;

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

}  // namespace linear

namespace binary {

IntVector::iterator binary_search_1(IntVector::iterator begin_itt,
                                    IntVector::iterator end_itt,
                                    const int key) {
  //    assert(std::is_sorted(begin_itt, end_itt);
  size_t size = end_itt - begin_itt;
  if (0 == size) {
    return end_itt;
  }
  if (1 == size) {
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

IntVector::iterator binary_search_2(IntVector::iterator begin_itt,
                                    IntVector::iterator end_itt,
                                    const int key) {
  //    assert(std::is_sorted(begin_itt, end_itt);
  size_t size = end_itt - begin_itt;
  if (0 == size) {
    return end_itt;
  }

  IntVector::iterator m = begin_itt + (end_itt - begin_itt) / 2;

  if (key < *m) {  // (begin, m)
    IntVector::iterator r = binary_search_2(begin_itt, m, key);
    return m == r ? end_itt : r;
  } else if (*m < key) {  // [m+1,end]
    return binary_search_2(m, end_itt, key);
  } else {  // key == *m
    return m;
  }
}

IntVector::iterator upper_bound(IntVector::iterator begin_itt,
                                IntVector::iterator end_itt,
                                const int key) {
  //    assert(std::is_sorted(begin_itt, end_itt);

  while (begin_itt < end_itt) {
    IntVector::iterator m = begin_itt + (end_itt - begin_itt) / 2;

    if (key < *m) {  // (begin, m)
      end_itt = m;
    } else {
      begin_itt = m + 1;
    }
  }
}

IntVector::iterator lower_bound(IntVector::iterator begin_itt,
                                IntVector::iterator end_itt,
                                const int key) {
  //    assert(std::is_sorted(begin_itt, end_itt);

  while (begin_itt < end_itt) {
    IntVector::iterator m = begin_itt + (end_itt - begin_itt) / 2;

    if (*m < key) {  // (begin, m)
      begin_itt = m + 1;
    } else {
      end_itt = m;
    }
  }
}

IntVector::iterator binary_search_3(IntVector::iterator begin_itt,
                                    IntVector::iterator end_itt,
                                    const int key) {
  //    assert(std::is_sorted(begin_itt, end_itt);
  IntVector::iterator res = upper_bound(begin_itt, end_itt, key);
  if (res == end_itt) {
    return end_itt;
  }
  return *res == key ? res : end_itt;
}

int binary_to_linear_adaptor(IntVector& vec, const int find_key) {
  IntVector::iterator result =
      binary_search_1(vec.begin(), vec.end(), find_key);
  return (vec.end() == result) ? -1 : result - vec.begin();
}

}  // namespace binary
}  // namespace search
}  // namespace components

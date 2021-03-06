
#include <iostream>

template <class T>
void swap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

template <class TIter>
TIter min_element(TIter b, TIter e) {
  TIter result = b;
  while (b < e) {
    if (*b < *result) {
      result = b;
    }
    ++b;
  }
  return result;
}

/// SORTS

template <class TIter>
void sort_naive(const TIter b, const TIter e) {
  // [b, e) = [sorted) [unsorted)
  // [b, e) = [b, pivot) [pivot, e)
  for (TIter i = b; i < e; ++i) {
    for (TIter j = i + 1; j < e; ++j) {
      if (*j < *i) {
        swap(*i, *j);
      }
    }
  }
}

template <class TIter>
void sort_selection(TIter b, TIter e) {
  // [b, e) = [sorted) [unsorted)
  // [b, e) = [b, pivot) [pivot, e)
  for (TIter pivot = b; pivot < e; ++pivot) {
    auto m = min_element(pivot, e);
    if (pivot != m) {
      swap(*pivot, *m);
    }
  }
}

template <class TIter>
void sort_selection_fun(TIter b, TIter e) {
  // [b, e) = [sorted) [unsorted)
  // [b, e) = [b, pivot) [pivot, e)
  for (TIter pivot = b; pivot < e; ++pivot) {
    swap(*pivot, *min_element(pivot, e));
  }
}

template <class TIter>
void sort_buble(TIter b, TIter e) {
  // [b, e) = [sorted) [unsorted)
  // [b, e) = [b, pivot) [pivot, e)
  for (TIter pivot = e - 1; pivot != b; --pivot) {
    // assert(std::is_sorted(pivot,e))
    for (TIter j = b; j < pivot; ++j) {
      TIter j_next = j + 1;
      // assert(i == min_element(b, j_next))
      if (*j > *(j_next)) {
        swap(*j, *(j_next));
      }
      // assert(i == min_element(b, j_next))
    }
  }
}

template <class TIter>
void sort(TIter b, TIter e) {
  // [b, e) = [sorted) [unsorted)
  // [b, e) = [b, pivot) [pivot, e)
  for (TIter pivot = b; pivot < e; ++pivot) {
    // assert(is_sorted(b,pivot))
    // insert *pivot to [b,pivot)
    for (TIter i = pivot; i != b; --i) {
      TIter next_i = i + 1;
      if (*next_i < *i)
        swap(*i, *next_i);
    }
    // assert(is_sorted(b,pivot))
  }
}

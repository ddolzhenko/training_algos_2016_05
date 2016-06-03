//#include "sort.h"

// template <class T>
// void swap(T& a, T& b) {
//    T tmp = a;
//    a = b;
//    b = tmp;
//}

// template<class TIter>
// TIter min_element(TIter b, TIter e) {
//    TIter result = b;
//    while(b < e) {
//        if(*b < *result) {
//            result = b;
//        }
//    ++b;
//    }
//    return result;
//}

///// SORTS

// template <class TIter>
// void sort_naive(const TIter b, const TIter e) {
//    // [b, e) = [sorted) [unsorted)
//    // [b, e) = [b, pivot) [pivot, e)
//    for(TIter i = b; i < e; ++i) {
//        for(TIter j = i+1; j < e; ++j) {
//            if(*j < *i) {
//                swap(*i, *j);
//            }
//        }
//    }
//}

// template <class TIter>
// void sort_selection(TIter b, TIter e) {
//    // [b, e) = [sorted) [unsorted)
//    // [b, e) = [b, pivot) [pivot, e)
//    for(TIter pivot = b; pivot < e; ++pivot) {
//        auto m = min_element(pivot,e);
//        if(pivot != m) {
//            swap(*pivot, *m);
//        }
//    }
//}

// template <class TIter>
// void sort_selection_fun(TIter b, TIter e) {
//    for(TIter pivot = b; pivot < e; ++pivot) {
//        swap(*pivot, *min_element(pivot, e));
//    }
//}

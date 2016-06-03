template <class T>
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <class TIter>
void sort_naive(TIter b, TIter e)
{
    // [b, e) = [sorted) [unsorted)
    // [b, e) = [b, pivot) [pivot, e)
    for(TIter i = b; i < e; ++i)
    {
        for(TIter j = i+1; j < e; ++j)
        {
            if(*j < *i)
                swap(*i, *j);
        }
    }
}


template <class TIter>
TIter min_element(TIter b, TIter e)
{
    TIter result = b;
    while(b < e)
    {
        if(*b < *result)
            result = b;
        ++b;
    }
    return result;
}


template <class TIter>
void sort_selection(TIter b, TIter e)
{
    // [b, e) = [sorted) [unsorted)
    // [b, e) = [b, pivot) [pivot, e)
    for(TIter pivot = b; pivot < e; ++pivot)
    {
        assert(std::is_sorted(b, pivot));
        auto m = min_element(pivot, e);
        if(pivot != m)
            swap(*pivot, *m);
    }
}

template <class TIter>
void sort_selection_fun(TIter b, TIter e)
{
    for(TIter pivot = b; pivot < e; ++pivot)
        swap(*pivot, *min_element(pivot, e));
}




void sort(b, e)
{
    // [b, e) = [sorted) [unsorted)
    // [b, e) = [b, pivot) [pivot, e)
    for()
    {
        assert(is_sorted(b, pivot)); 

        // insert *pivot to [b, pivot)
        // [b, pivot)[*pivot] = [b, pivot)[v]
        // [b, pivot)[v] = [b, i) [v] (i, pivot]
        // [b, pivot)[v] = [b, i) [i] [i+1, pivot]
        for(TIter i = pivot; i != b; --i)
        {
            assert(is_sorted(b, i) && is_sorted(i, pivot+1));

            auto next_i = i+1;
            if(*next_i < *i)
                swap(*i, *next_i);
            else
                break;
            
            assert(is_sorted(b, i) && is_sorted(i, pivot+1));
        }

        assert(is_sorted(b, pivot)); 
    }
}






















// http://collabedit.com/jvumw

template <class TIter>
void sort_bubble(TIter b, TIter e)
{
    // [b, e) = [unsorted) [sorted)
    // [b, e) = [b, pivot) [pivot, e)
    for(TIter pivot = e; pivot != b; --pivot)
    {
        assert(std::is_sorted(pivot, e));
        // [b, pivot) = [b, i) [i, pivot)
        for(TIter next_i = b+1; next_i < pivot; ++next_i)
        {
            auto i = next_i-1;
            assert(i == min_element(b, next_i));   // [b, i]

            if(*next_i < *i)
                swap(*i, *next_i);

            assert(i == min_element(b, next_i));
        }

        assert(std::is_sorted(pivot, e));
    }
}



























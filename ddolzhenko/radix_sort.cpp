#include <ctypes>

template <class T>
void counting_sort(vector<T>& v) {

    const size_t freq_size = sizeof(T) << CHAR_BITS;
    vector<size_t> freq(freq_size);
    for(auto x : v) {
        freq[x]++;
    }


    size_t pos = 0;
    for(size_t x = 0; x < freq_size; ++x) 
    {
        auto x_count = freq[x];
        for(size_t i = 0; i < x_count; ++i) 
        {
            v[pos] = x;
            pos++;
        }
    }
}


template <class T>
uint8_t get_radix(T x, size_t radix) {
    return x >> (radix*CHAR_BITS);
    // return x / pow(256, radix);
}

template <class T> 
vector<size_t> compute_frequencies(vector<T>& v, size_t radix) {
    const size_t freq_size = sizeof(T) << CHAR_BITS;
    vector<size_t> freq(freq_size);
    for(auto x : v) {
        auto index = get_radix(x, radix);
        freq[index]++;
    }   
    return freq;
}


vector<size_t> cumulative_sums(vector<size_t>& v) {
    vector<size_t> begins(v.size(), 0);
    copy(v.begin(), v.end()-1, begins.begin()+1);
    for(size_t i = 1; i < begins.size(); ++i) {
        begins[i] += begins[i-1];
    }

    // begins[0] = 0;
    // for(size_t i = 1; i < begins.size(); ++i) {
    //     begins[i] += begins[i-1] + v[i];
    // }


    return begins;
}

template <class T> void radix_sort(vector<T>& v) {
    const size_t radix_count = sizeof(T);

    vector<T> buffer(v.size());

    for(size_t radix = 0; radix < radix_count; ++radix) {
        auto freq = compute_frequencies(v, radix);  // O(n)
        auto begins = cumulative_sums(freq);        // O(1)

        for(auto x : v) {
            auto index_begin = get_radix(x, radix);
            auto index = begins[index_begin];
            buffer[index] = x;
            begins[index_begin]++;
        }

        v.swap(buffer);
    }
}

vector<size_t> compute_frequencies(TIter b, TIter e, size_t radix) {
    vector<size_t> freq(256);
    for(auto it = b; it != e; ++it)
        freq[it-b]++;
    return freq;
}


template <class T> 
void radix_sort_upsidedown1(TIter b, TIter e, int radix, TIter buff) {
    if(radix < 0) return;
    if(e-b < 2)   return;

    auto freq = compute_frequencies(b, e, radix);
    auto begins = cumulative_sums(freq);
    auto old_begins = begins;

    for(auto x : v) {
        auto index = begins[get_radix(x, radix)]++;
        *(buff + index) = x;
    }

    for(size_t i = 0; i < old_begins.size(); ++i) {
        auto begin  = buff + old_begins[i];
        auto end    = buff + begins[i];
        vector<typename TIter::value_type> buff2;
        radix_sort_upsidedown(begin, end, radix-1, buff2.begin());
        copy(begin,end, b+old_begins[i]);
    }
 }

 template <class T> 
void radix_sort_upsidedown2(TIter b, TIter e, int radix) {
    if(radix < 0) return;
    if(e-b < 2)   return;

    auto freq = compute_frequencies(b, e, radix);
    auto ends = cumulative_sums(freq);
    auto begins = ends;

    size_t pos = 0;
    auto x = *(b);
    for(size_t i = 0; i < e-b; ++i) { // check invariants
        auto bucket_pos = b+ends[get_radix(x, radix)]++;
        swap(x, *bucket_pos);
    }

    for(size_t i = 0; i < old_begins.size(); ++i) {
        radix_sort_upsidedown2(b+begins[i], b+ends[i], radix-1);
    }
 }

template <class TIter> 
void radix_sort2(TIter b, TIter e) {
    typedef typename TIter::value_type T;
    vector<T> buffer(e-b);
    const size_t radix_count = sizeof(T);
    radix_sort_upsidedown(b, e, radix_count, buffer.begin());
}























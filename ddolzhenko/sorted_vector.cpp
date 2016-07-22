

template <class T> class SortedVector {
public: // types
    // static_assert(traits<T>::is_comparable::value);
    typedef std::vector<T> impl_type;
    typedef typename impl_type::size_type   size_type;
    typedef typename impl_type::value_type  value_type;
    typedef typename impl_type::reference   reference;
    typedef typename impl_type::iterator    iterator;
    typedef typename impl_type::const_reference const_reference;
    typedef typename impl_type::const_iterator  const_iterator;
public: // ctors    
    SortedVector() = default;
    SortedVector(const SortedVector&) = default;
    SortedVector(const SortedVector&&) = default;
    const SortedVector& operator=(const SortedVector&) = default;
    const SortedVector& operator=(const SortedVector&&) = default;
    ~SortedVector() = default;

    template <class TIter>
    SortedVector(TIter first, TIter last) { this->assign(first, last); }

    void swap(SortedVector& rhs)        { m_data.swap(rhs.m_data); }
    
    void reserve(size_type new_size)    { m_data.reserve(new_size) ; }

public:
    const_iterator begin() const        { return m_data.begin(); }
    const_iterator end() const          { return m_data.end(); }

    const_iterator median() const       { return begin() + (end() - begin())/2; }

    const_iterator lower_bound(const_reference x) const   { 
        return std::lower_bound(begin(), end(), x); 
    }
    const_iterator upper_bound(const_reference x) const   { 
        return std::upper_bound(begin(), end(), x); 
    }

    bool has(const_reference x) const {
        return std::binary_search(begin(), end(), x);
    }

public: // element access

    const_reference peek_min() const    { return m_data.front(); }
    const_reference peek_max() const    { return m_data.back(); }

    const_reference peek_median() const { return *median(); }

public: // modifiers
    template <class TIter>
    void assign(TIter first, TIter last) {
        m_data.assign(first, last);
        std::sort(m_data.begin(), m_data.end());      

        assert(valid_invariant());             
    }

    void push(const_reference x) {
        assert(valid_invariant());
        
        m_data.push_back(x);
        iterator it = m_data.end()-1;
        iterator prev = it-1;
        while(it > m_data.begin()) {
            assert(std::is_sorted(m_data.begin(), prev));
            assert(std::is_sorted(it, m_data.end()));

            if(*it < *prev)
                std::iter_swap(it, prev);
            else
                break;
            it--;
            prev--;

            assert(std::is_sorted(m_data.begin(), prev));
            assert(std::is_sorted(it, m_data.end()));
        }

        assert(valid_invariant());
    }


    void pop_min()                      { m_data.pop_front(); }
    void pop_max()                      { m_data.pop_back(); }

    const_iterator remove(const_iterator it) {
        assert(valid_invariant());
        return m_data.remove(it);
    }
    
    const_iterator remove(const_reference x) {
        assert(valid_invariant());
        
        const_iterator  it = this->lower_bound(x);
        it = m_data.remove(it);
        assert(valid_invariant());
        return it;
    }

public: // capacity
    bool        empty() const           { return m_data.empty(); }
    size_type   size() const            { return m_data.size(); }
    size_type   capacity() const        { return m_data.capacity(); }

private:

    bool valid_invariant() const { 
        return std::is_sorted(m_data.begin(), m_data.end()); 
    }

private:
    impl_type m_data;
};
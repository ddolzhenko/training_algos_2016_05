#include <deque>



template <class TKey, class TValue, class THasher = std::hash<TKey> >
class hash_map {
public:

    typedef TKey key_type;
    typedef std::pair<key_type, TValue> value_type;
    
    typedef std::deque<value_type> bucket_type;

    typedef bucket_type::size_type size_type;
    typedef bucket_type::reference reference;
    typedef bucket_type::const_reference const_reference;

    typedef THasher hasher_type;

    typedef std::vector<bucket_type> storage_type;

    typedef hash_map<TKey, TValue, THasher> self_type;

    class iterator {
    public:
        typedef storage_type::iterator storage_iterator;
        typedef bucket_type::iterator bucket_iterator;

        iterator(storage_iterator b, storage_iterator e)
        : m_bucket(b)
        , m_bucket_end(e)
        {
            if(b != e)
                m_pos = b->begin();

            fix_pos();
        }

        bool operator==(const iterator& rhs) const {
            assert(m_bucket_end == rhs.m_bucket_end);

            if (m_bucket != rhs.m_bucket)
                return false;
            if (m_bucket == m_bucket_end)
                return true;
            return m_pos == rhs.m_pos;
        }

        iterator operator++() {
            ++m_pos;
            fix_pos();
            return *this;
        }

        void fix_pos() {
            if(m_pos == m_bucket->end()) {
                m_bucket = find_if(m_bucket, m_bucket_end, 
                    [](const bucket_type& bucket) { 
                        return !bucket.empty(); } );
                if (m_bucket != m_bucket_end)
                    m_pos = m_bucket.begin();
            }
        }

        reference operator*() { return *m_pos;  }
        pointer operator->() { return &(*m_pos); }
        
        storage_iterator        m_bucket;
        bucket_iterator         m_pos;
    };


    typedef const iterator const_iterator;
public:
    hash_map(
        size_type bucket_count=64,
        hasher_type hasher = hasher_type())
    : m_buckets(bucket_count, bucket_type())
    , m_hasher(hasher)
    {}

    ~hash_map() = default;
    hash_map(const self_type&) = default;
    hash_map(self_type&&) = default;
    self_type& operator=(const self_type&) = default;
    self_type& operator=(self_type&&) = default;

public:

    TValue& operator[](const key_type& key) {
        auto it  = find(key);
        if (it == end())
            it = insert(make_pair(key, TValue()));
        return it->second;
    }

    size_type hash(const key_type& key) const {
        return m_hasher(key) % m_buckets.size();
    }

    iterator find(const key& key) {
        auto& bucket = find_bucket(x.first);
        auto elem = find_element(bucket, x.first);
        
        auto it = 
        it.m_pos - elem;
        return it;
    }

    reference insert(const value_type& x) {
        auto& bucket = find_bucket(x.first);
        bucket.push_front(x);
        return bucket.front();
    }

    void delete(const key_type& key) {
        iterator it = find(key);
        it.m_bucket.erase(it.m_pos);
    }

public: // iterators
    
    iterator begin() {
        return iterator(m_buckets.begin(), m_buckets.end());
    }

    iterator end() {
        return iterator(m_buckets.end(), m_buckets.end());
    }

    
private:

    bucket_type& find_bucket(const key_type& key) {
        size_type bucket_number = hash(key);
        assert(bucket_number < m_buckets.size());
        return m_buckets[bucket_number];
    }

    bucket_type::iterator find_element(
        bucket_type& bucket, const key_type& key) {
        return std::find_if(bucket.begin(), bucket.end(), 
            [&key](const value_type& val) { return val.first == key; } )
    }

    storage_type    m_buckets;
    hasher_type     m_hasher;
};


int main(int argc, char const *argv[])
{
    hash_map<uint64_t, string> M;
    vector<string> V(256);


    M[15] = 'fifteen';
    V[15] = 'fifteen';

    return 0;
}
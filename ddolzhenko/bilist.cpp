

namespace BiList {

    template <T> struct Node {
        Node<T>* prev;
        Node<T>* next;
    };


    template <T> 
    struct RealNode : public Node<T> {
        RealNode(   const T& data_, 
                Node<T>* prev_ = 0,
                Node<T>* next_ = 0) 
        : data(data_)
        , prev(prev_)
        , next(next_)
        {}
        T data;
    };

    template <T> 
    struct DummyNode : public Node<T> {
        DummyNode()
        : prev(this)
        , next(this)
        {}

        DummyNode(Node<T>* prev_, Node<T>* next_) 
        : prev(prev_)
        , next(next_)
        {}
    };

    template <class T>
    void insert_after(Node<T>* node, Node<T>* what) {
        assert(where != nullptr);
        assert(where->prev != nullptr);
        assert(what != nullptr);

        what->prev = where->prev;
        what->next = where;

        where->prev->next = what;
        where->prev = what;
    }

    template <class T>
    void insert_before(Node<T>* where, Node<T>* what) {
        assert(where != nullptr);
        assert(where->next != nullptr);
        assert(what != nullptr);

        what->prev = where;
        what->next = where->next;

        where->next->prev = what;
        where->next = what;
    }

    template <class T>
    Node<T>* cut_out(Node<T>* what) {
        assert(what != nullptr);
        auto next = what->next;
        what->prev->next = what->next;
        what->next->prev = what->prev;
        return next;
    }


    template <class T>
    struct iterator : std::iterator<T, std::bidirectional_iterator_tag>
    {
        typedef size_t  size_type;
        typedef T  value_type;
        typedef T&   reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef std::difference_type difference_type;

    public: // ctors
        iterator(const iterator<T>& rhs) = default;
        iterator(const iterator<T>&& rhs) = default;
        const iterator<T>& operator=(const iterator<T>& rhs) = default;
        const iterator<T>& operator=(const iterator<T>&& rhs) = default;

    public:

        bool operator==(const iterator<T>& rhs) const  { 
            return m_node == rhs.m_node; 
        }
        
        bool operator!=(const iterator<T>& rhs) const { 
            return !(*this == ths); 
        }

        pointer operator->() { 
            assert(validate_invariant());
            return &(this->operator*());
        }

        reference operator*() { 
            assert(validate_invariant());
            return static_cast<RealNode<T>*>(m_node)->data;
        }


        iterator& operator++() {
            return m_node = m_node->next;
        }

        iterator operator++(int) {
            auto node = m_node;
            m_node = m_node->next;
            return node;
        }  

        iterator& operator--() {
            return m_node = m_node->prev;
        }

        iterator operator--(int) {
            auto node = m_node;
            m_node = m_node->prev;
            return node;
        }

       
    private:

        bool validate_invariant() const {
            return dynamic_cast<RealNode<T>*>(m_node) != nullptr;
        }

        friend class List<T>;
        iterator(Node<T>* node) : m_node(node) {};

        Node<T>* m_node; 
    };


} // namespace

template <class T>
class List {
public:
    typedef size_t  size_type;
    typedef T  value_type;
    typedef T&   reference;
    typedef const T& const_reference;
    typedef BiList::iterator<T>   iterator;
    typedef const BiList::iterator<T> const_iterator;
    
public:
    List()
    : m_pivot()
    , m_size(0)
    { }

    List(const List& rhs)
    : List()
    {
        for(const auto& x : rhs) {
            this->push_back(x);
        }
    }

    ~List() {
        auto it = begin();
        while(!empty()) {
            it = erase(it);
        }
    }

    const List<T>& operator=(const List<T>& rhs) {
        if(this != &rhs)
            this->swap(List<T>(rhs));
        return *this;
    }

    void swap(List<T>& rhs) {
        std::swap(this->m_pivot, rhs.m_pivot);
        std::swap(this->m_size, rhs.m_size);
    }

public:
    size_type size() const  { return m_size; }
    bool empty() const      { return size() == 0; }

public: // iterators
    iterator begin()    { return iterator(m_pivot->next); }
    iterator end()      { return iterator(m_pivot); }

    reference front()   { return *begin(); }
    reference back()    { return *(--end()); }

public:

    void push_front(const_reference data) {
        assert(validate_invariant());

        auto node = new RealNode<T>(data);
        insert_after(&m_pivot, node);
        m_size++;

        assert(validate_invariant());
    }

    void push_back(const_reference data) {
        assert(validate_invariant());

        auto node = new RealNode<T>(data);
        insert_before(&m_pivot, node);
        m_size++;

        assert(validate_invariant());
    }

    iterator insert(iterator it, const_reference data) {
        auto node = new RealNode<T>(data);
        insert_before(it.m_node, node);
        m_size++;

        assert(validate_invariant());
        return iterator(node);
    }

    iterator erase(iterator it) {
        assert(it != end());

        auto node = it.m_node;
        auto next = BiList::cut_out(node);
        delete static_cast<RealNode<T>*>(node);
        m_size--;

        assert(validate_invariant());

        return iterator(next);
    }

public:

    void reverse();
    void sort();
    void merge();
    void unique(); // on sorted
    

private:

    bool valid_head() const {
        return m_head == nullptr || m_head->prev == nullptr;
    }

    bool valid_tail() const {
        return m_tail == nullptr || m_tail->next == nullptr;
    }

    size_type compute_size() const {
        auto node = m_head;
        size_type result = 0;
        while(node)
        {
            node = node->next;
            result++;
        }
        return result;
    }

    bool validate_invariant() const {
        return 
            valid_head() &&
            valid_tail() &&
            compute_size(m_head) == m_size;
    }

    BiList::DummyNode<T>    m_pivot;
    size_type               m_size;
};


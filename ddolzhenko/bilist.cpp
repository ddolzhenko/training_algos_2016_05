

namespace BiList {

    template <T> struct Node {
        Node(   const T& data_, 
                Node<T>* prev_ = 0,
                Node<T>* next_ = 0) 
        : data(data_)
        , prev(prev_)
        , next(next_)
        {}
        T data;
        Node<T>* prev;
        Node<T>* next;
    };


    template <class T>
    void insert_after(Node<T>* node, const T& data) {
        assert(node != nullptr);
        auto new_node = new Node<T>(data, node, node->next);
        if(node->next) {
            node->next->prev = new_node;
        }
        node->next = new_node;

        assert(node->next == new_node);
        assert(node == new_node->prev);
    }

    template <class T>
    void insert_before(Node<T>* node, const T& data) {
        assert(node != nullptr);
        auto new_node = new Node<T>(data, node->prev, node);
        if(node->prev) {
            node->prev->next = new_node;
        }
        node->prev = new_node;

        assert(node->prev == new_node);
        assert(node == new_node->next);
    }

} // namespace

template <class T>
class List {
public:
    typedef size_t  size_type;
    typedef T  value_type;
    typedef T&   reference;
    typedef const T& const_reference;
    typedef BiList::iterator   iterator;
    typedef const BiList::iterator const_iterator;
    
public:
    List()
    : m_head(nullptr)
    , m_tail(nullptr)
    , m_size(0)
    { }

    List(const List& rhs) {  /*...*/  }
    ~List() {}

    const List<T>& operator=(const List<T>& rhs) {
        if(this != &rhs)
            this->swap(List<T>(rhs));
        return *this;
    }

    void swap(List<T>& rhs) {
        std::swap(this->m_head, rhs.m_head);
        std::swap(this->m_tail, rhs.m_tail);
        std::swap(this->m_size, rhs.m_size);
    }

public:
    size_type size() const  { return m_size; }
    bool empty() const      { return size() == 0; }

public: // iterators
    iterator begin()    { return iterator(m_head); }
    iterator end()      { return ++iterator(m_tail); }

public:

    void push_front(const_reference data) {
        assert(validate_invariant());

        if(!empty()) {
            BiList::insert_before(m_head, data);
            m_head = m_head.prev;
            m_size++;
        } else {
            m_head = m_tail = new Node<value_type>(data);
            m_size = 1;
        }

        assert(validate_invariant());
    }

    void push_back(const_reference data) {
        assert(validate_invariant());

        if(!empty()) {
            BiList::insert_after(m_tail, data);
            m_tail = m_tail.next;
            m_size++;
        } else {
            m_head = m_tail = new Node<value_type>(data);
            m_size = 1;
        }

        assert(validate_invariant());
    }

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

    BiList::Node<T>*    m_head;
    BiList::Node<T>*    m_tail;
    size_type           m_size;
};


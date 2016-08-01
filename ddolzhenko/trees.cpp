

template <class T>
class Tree {
public:
    Tree( )

    size_t height() const {
        Tree* tree = this;
        // ...
    }

private:
    T data;
    Tree* left;
    Tree* right;
};


static_cast<Tree*>(0)->height();
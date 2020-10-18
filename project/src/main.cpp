#include <iostream>
template<class T>
struct DefComparator {
    bool operator() (const T& l, const T& r) const {
        return l < r;
    }
};

template <class T, class Compare = DefComparator<T>>
class Heap {
public:
    Heap(Compare comp = Compare());
    Heap(Heap&&);

    bool operator= (const Heap&);
    bool operator= (Heap&&);
    ~Heap();
    const T& top() const;

    void pop();
    void push(const T&);
    void push(T&&);

    bool is_empty() const;
    size_t  size;
private:
    T* buf;
    size_t buf_size;
    size_t capacity;
    Compare comp;
};
int main() {


    return 0;
};
#include <iostream>
#include <vector>
#include <cassert>

struct fruit {
    size_t mass = 0;
    int timer = -1;
};

bool operator>(const fruit& l, const fruit& r) {
    return (l.mass > r.mass || (l.mass == r.mass && l.timer < r.timer));
}

bool operator==(const fruit& l, const fruit& r) {
    if (l.mass == r.mass && l.timer < r.timer)
        return true;
    return false;
}
template<class T>
struct DefComparator {
    bool operator() (const T& l, const T& r) const {
        return l > r;
    }
};

template <class T, class Compare = DefComparator<T>>
class Heap {
public:
    explicit Heap(Compare comp = Compare());
    explicit Heap(const std::vector<T> &arr, Compare &comp = Compare());
    //Heap(Heap&&);

    bool operator= (const Heap &rhs);
    //bool operator= (Heap&&);
    ~Heap() = default;
    const T& top() const;

    T pop();
    void push(const T &data);
    //void push(T&&);

    bool is_empty() const;

    std::vector<T> buf;
    size_t &get_size();
    void sift_up(Compare comp = Compare(), size_t i = get_size());
    void sift_down(Compare comp = Compare(), size_t i = 0);
private:
    size_t size = 0;
    Compare comp;
};


template<class T, class Compare>
Heap<T, Compare>::Heap(const std::vector<T> &arr, Compare &comp) {
    for(size_t i = 0; i < arr.size(); i++) {
        this->buf.push_back(arr[i]);
        this->sift_up(comp, buf.size());
    }
    this->size = buf.size();
}

template<class T, class Compare>
void Heap<T, Compare>::sift_up(const Compare, size_t i) {
    assert(!is_empty());
    i--;
    while( i > 0 ) {
        size_t parent = (i-1) / 2;
        if(comp(buf[i], buf[parent])) {
            std::swap(buf[i], buf[parent]);
            i = parent;
        } else
            return;
    }
}



template<class T, class Compare>
T Heap<T, Compare>::pop() {
    assert(!is_empty());
    T result;
    if (buf.size() > 1) {
        result = buf[0];
        std::swap(buf[0], buf[buf.size() - 1]);
        buf.pop_back();
        sift_down(Compare(),0);
        return result;
    } else {
        result = buf[0];
        buf.pop_back();
    }
    return result;
}

template<class T, class Compare>
void Heap<T, Compare>::push(const T &data) {
    this->buf.push_back(data);
    this->sift_up(comp, buf.size());
}

template<class T, class Compare>
void Heap<T, Compare>::sift_down(const Compare, size_t i) {
    if (buf.size() < 2) {
        return;
    }

    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;
    size_t largest = i;
    while (largest < buf.size()) {
// Ищем большего сына, если такой есть.

        if (left < buf.size() && comp(buf[left], buf[i]))
            largest = left;
        if (right < buf.size() && comp(buf[right], buf[largest]))
            largest = right;
// Если больший сын есть, то проталкиваем корень в него.
        if (largest != i) {
            std::swap(buf[i], buf[largest]);
            i = largest;
            left = 2 * i + 1;
            right = 2 * i + 2;
        } else
            break;
    }
}

template<class T, class Compare>
bool Heap<T, Compare>::is_empty() const {
    if (buf.empty())
        return true;
    return false;
}

template<class T, class Compare>
const T &Heap<T, Compare>::top() const {
    return buf[0];
}


template<class T, class Compare>
size_t &Heap<T, Compare>::get_size() {
    return buf.size();
}

template<class T, class Compare>
bool Heap<T, Compare>::operator=(const Heap &rhs) {
    for (size_t i = 0; i < rhs.buf.size(); i++) {
        this->buf.push_back(rhs.buf[i]);
    }
    return true;
}


template<class T, class Compare>
size_t eating(Heap<T,Compare> &heap, size_t &strength) {
    int result = 0;
    while (!heap.is_empty()) {
        int buf = strength;
        if (heap.top().mass > strength)
            return 0;
        fruit res;
        while (buf > 0 && !heap.is_empty()) {
            if (buf >= (int) heap.top().mass && heap.buf[0].timer != result) {
                buf -= (int) heap.top().mass;
                res = heap.pop();
                if (res.mass == 1) {
                    continue;
                }
                res.mass = res.mass/2;
                res.timer = result;       // чтобы не поднимать один и тот же фрукт за 1 итерацию
                heap.push(res);

                if (buf == 0) {
                    break;
                }
            } else {
                break;
            }
        }
        result++;
    }
    return result;
}
/*void test() {
    size_t res;
    DefComparator<fruit> comp;
    size_t strength;
    fruit val;


    val = {5};
    std::vector<fruit> a;
    a.reserve(5);
    for (size_t i = 0; i < 5; i++) {
        a.push_back(val);
    }
    Heap<fruit> heap1(a, comp);
    strength = 24;
    res = eating(heap1, strength);
    assert(res == 4);
    std::cout << "OK\n";

    std::vector<fruit> b;
    b.reserve(1);
    b.push_back({2});
    Heap<fruit> heap2(b, comp);
    strength = 100;
    res = eating(heap2, strength);
    assert(res == 2);
    std::cout << "OK\n";

    std::vector<fruit> c;
    c.reserve(1);
    c.push_back({11});
    Heap<fruit> heap3(c, comp);
    strength = 11;
    res = eating(heap3, strength);
    assert(res == 4);
    std::cout << "OK\n";

    val = { 5};
    std::vector<fruit> d;
    for (size_t i = 0; i < 5; i++) {
        d.push_back(val);
        val.mass--;
    }
    Heap<fruit> heap4(d, comp);
    strength = 5;
    res = eating(heap4, strength);
    assert(res == 5);
    std::cout << "OK\n";


    val = {0,1};
    std::vector<fruit> f;
    f.reserve(10);
    f.push_back({1});
    f.push_back({ 9});
    f.push_back({ 7});
    f.push_back({ 6});
    f.push_back({ 5});
    f.push_back({ 3});
    f.push_back({ 3});
    f.push_back({ 4});
    f.push_back({2});
    f.push_back({ 8});
    Heap<fruit> heap5(f, comp);
    strength = 9;
    res = eating(heap5, strength);
    assert(res == 10);
    std::cout << "OK\n";

    std::vector<fruit> g;
    g.reserve(10);
    g.push_back({1});
    g.push_back({ 10});
    g.push_back({ 2});
    g.push_back({ 9});
    g.push_back({ 3});
    g.push_back({ 8});
    g.push_back({4});
    g.push_back({ 7});
    g.push_back({ 5});
    g.push_back({ 6});
    Heap<fruit> heap6(g, comp);
    strength = 10;
    res = eating(heap6, strength);
    assert(res == 11);
    std::cout << "OK\n";



}*/

int main() {
    //test();
    size_t n;
    std::cin >> n;
    std::vector<fruit> fruits;
    fruit val;
    for (size_t i = 0; i < n; i++) {
        std::cin >> val.mass;
        fruits.push_back(val);
    }
    size_t strength;
    std::cin >> strength;
    DefComparator<fruit> comp;
    Heap<fruit> heap(fruits, comp);
    size_t result = eating(heap, strength);
    std::cout << result;

    return 0;
}

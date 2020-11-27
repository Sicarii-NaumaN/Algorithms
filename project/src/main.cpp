#include <iostream>
#include <vector>
#include <cassert>

template<class T>
struct DefComparator {
    bool operator() (const T& l, const T& r) const {
        return l < r;
    }
};

template <class T, class Compare = DefComparator<T>>
int partition(T* arr, int l, int r, Compare comp = Compare()) {
    int start = l, end = r - 1, middle = l + (r-l)/2;
    int pivot_index = 0;
    T pivot = 0;
    int buf1, buf2;
    if (comp(arr[start], arr[middle])) {
        buf1 = middle;
        buf2 = start;
    } else {
        buf1 = start;
        buf2 = middle;
    }
    if (comp(arr[buf1], arr[end])) {
        pivot_index = buf1;
    } else if (comp(arr[end], arr[buf2])){
        pivot_index = buf2;
    } else
        pivot_index = end;
    pivot = arr[pivot_index];
    int i = l;
    int j = l-1;

    std::swap(arr[pivot_index], arr[r-1]);

    while (true) {
        while (!comp(arr[++j], pivot) && j != r-1);

        if (j == r-1 || i == r -1)
            break;
        std::swap(arr[i], arr[j]);
        i++;
    }
    std::swap(arr[i], arr[r - 1]);
    return i;
}

template <class T, class Compare = DefComparator<T>>
void kth_elem(T* arr, int size, int index, Compare comp = Compare()) {
    int l = 0;
    int r = size;

    while(true) {
        int result = partition(arr, l, r, comp);
        if (result == index) {
            return;
        } else if (result < index) {
            l = result + 1;
        } else {
            r = result;
        }
    }
}
void test(){
    int key;

    int c[10] = {1, 3, 5, 7, 2, 4, 6, 1, 2, 3};
    key = 2;
    kth_elem(c, 10, key);
    assert(c[key] == 2);
    std::cout << "OK\n";

    int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    key = 4;
    kth_elem(b, 10, key);
    assert(b[key] == 5);
    std::cout << "OK\n";

    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    key = 9;
    kth_elem(a, 10, key);
    assert(a[key] == 10);
    std::cout << "OK\n";

}

int main() {
    //test();
    std::cout << "Эмин пидр!!!!!!!!!";
    int n;
    std::cin >> n;

    int key;
    std::cin >> key;
    int *arr = new int [n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    kth_elem(arr, n, key);
    std::cout << arr[key];

    delete [] arr;

    return 0;
}

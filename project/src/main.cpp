#include <iostream>
#include <cassert>
#include <cmath>

int binary(int end, int start, int *A, int &value) {
    int middle;
    middle = 0;
    if (end - start == 1) {           // если массив состоит из 1 элемента, то просто
        return middle;                // возвращаем 0-й индекс
    }
    const int end_ = end;
    while (true) {
        middle = (start + end) / 2;
        if (value == A[middle]) {
            return middle;
        }
        if (start == end) {             // Если сошлись начальный и конечный индекс массивов,
            if (middle == 0) {          // то возвращаем текущий индекс - 1 (в случае 0-го текущего
                return middle;          // индекса не отнимаем единицу)
            }
            return middle - 1;
        }
        if (middle > 0) {
            if (A[middle] > value && A[middle - 1] < value) {
                if (std::abs(value - A[middle - 1]) > std::abs(value - A[middle])) {
                    return middle;
                }
                return (middle - 1);
            }
        }
        if (middle < end_) {
            if (A[middle] < value && A[middle + 1] > value) {
                if (std::abs(value - A[middle]) > std::abs(value - A[middle + 1])) {
                    return middle + 1;
                }
                return middle;
            }
        }

        if (A[middle] > value) {
            end = middle;
        }
        else {
            start = middle + 1;
        }
    }
}
void test() {
    int counter = 0;

    int Zz[10] = {15, 32, 37, 41, 45, 56, 64, 65, 72, 93};
    int Tt[10] = {57, 7, 97, 80, 21, 10, 75, 46, 62, 52};
    int tt[10] = {5, 0, 9, 8, 0, 0, 8, 4, 6, 5};
    for (size_t i = 0; i < 10; ++i) {
        counter = binary(10, 0, Zz, Tt[i]);
        assert(counter == tt[i]);
    }
    std::cout << "OK\n";
    int Z[10] = {15, 32, 37, 41, 45, 56, 64, 65, 72, 93};
    int T[10] = {53, 7, 97, 80, 21, 10, 75, 46, 62, 52};
    int t[10] = {5, 0, 9, 8, 0, 0, 8, 4, 6, 5};
    for (size_t i = 0; i < 10; ++i) {
        counter = binary(10, 0, Z, T[i]);
        assert(counter == t[i]);
    }
    std::cout << "OK\n";
    int A[4] = {-4, 0, 3, 18};
    int B[5] = {-2, 5, 4, 7, 12};
    int b[5] = {0, 2, 2, 2, 3};
    for (size_t i = 0; i < 5; ++i) {
        counter = binary(4, 0, A, B[i]);
        assert(counter == b[i]);
    }

    std::cout << "OK\n";

    int C[4] = {1, 2, 3, 5};
    int D[4] = {-3, -1, 0, 1};
    int d[4] = {0, 0, 0, 0};
    for (size_t i = 0; i < 4; ++i) {
        counter = binary(4, 0, C, D[i]);
        assert(counter == d[i]);
    }
    std::cout << "OK\n";

    int E[2] = {0, 10};
    int F[6] = {-3, 17, 3, 5, 0, 1};
    int f[6] = {0, 1, 0, 0, 0, 0};
    for (size_t i = 0; i < 6; ++i) {
        counter = binary(2, 0, E, F[i]);
        assert(counter == f[i]);
    }
    std::cout << "OK\n";

    int G[5] = {1, 2, 10, 12, 23};
    int J[2] = {10, -1};
    int j[2] = {2, 0};
    for (size_t i = 0; i < 2; ++i) {
        counter = binary(5, 0, G, J[i]);
        assert(counter == j[i]);
    }
    std::cout << "OK\n";

    int H[3] = {0, 4, 5};
    int P[7] = {-3, 0, 1, 2, 5, 7, 10};
    int p[7] = {0, 0, 0, 0, 2, 2, 2};
    for (size_t i = 0; i < 7; ++i) {
        counter = binary(3, 0, H, P[i]);
        assert(counter == p[i]);
    }
    std::cout << "OK\n";

    int X[11] = {-5, -2, 0, 3, 5, 8, 9, 10, 11, 14, 35};
    int Y[10] = {-13, -2, 0, 1, 245, 6, 8, 10, 11, 13};
    int y[10] = {0, 1, 2, 2, 10, 4, 5, 7, 8, 9};
    for (size_t i = 0; i < 10; ++i) {
        counter = binary(11, 0, X, Y[i]);
        assert(counter == y[i]);
    }
    std::cout << "OK\n";

    int O[1] = {-5};
    int K[4] = {0, 1, 12, -100};
    int k[4] = {0, 0, 0, 0};
    for (size_t i = 0; i < 4; ++i) {
        counter = binary(1, 0, O, K[i]);
        assert(counter == k[i]);
    }
    std::cout << "OK\n";

    int L[3] = {-25, 5, 9};
    int N[7] = {-9, 1, -10, 6, 7, 10, -30};
    int n[7] = {1, 1, 0, 1, 1, 2, 0};
    for (size_t i = 0; i < 7; ++i) {
        counter = binary(3, 0, L, N[i]);
        assert(counter == n[i]);
    }
    std::cout << "OK\n";

    int V[5] = {-25, 0, 5, 10, 13};
    int M[8] = {2, 3, 4, 5, 6, 7, 8, 12};
    int m[8] = {1, 2, 2, 2, 2, 2, 3, 4};
    for (size_t i = 0; i < 8; ++i) {
        counter = binary(5, 0, V, M[i]);
        assert(counter == m[i]);
    }
    std::cout << "OK\n";

    int Q[5] = {-25, 0, 5, 10, 13};
    int S[7] = {-13000, 1, 1, 110000, -15, -15, -30000};
    int s[7] = {0, 1, 1, 4, 0, 0, 0};
    for (size_t i = 0; i < 7; ++i) {
        counter = binary(5, 0, Q, S[i]);
        assert(counter == s[i]);
    }
    std::cout << "OK\n";
}

int main() {
    //test();
    size_t n = 0;
    std::cin >> n;
    int *A = new int[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    size_t m = 0;
    std::cin >> m;
    int *B = new int[m];
    for (size_t i = 0; i < m; i++) {
        std::cin >> B[i];
    }
    size_t start = 0;
    for (size_t i = 0; i < m; i++) {
        B[i] = binary(n, start, A, B[i]);
    }
    for (size_t i = 0; i < m; i++) {
        std::cout << B[i] << " ";
    }
    delete[]A;
    delete[]B;
    return 0;
}

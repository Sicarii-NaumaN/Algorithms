#include <iostream>
#include <cassert>
#include <cmath>


int binary(int *A, int &value, int start, int end) {
    int middle;
    int result = -1;
    middle = 0;
    const int end_ = end;

    while (true) {   // Начало цикла
        middle = (start + end) / 2;

        if (start == end) {             // Если сошлись начальный и конечный индекс массивов,
            if (middle == 0) {          // то возвращаем текущий индекс - 1 (в случае 0-го текущего
                result = middle;          // индекса не отнимаем единицу)
                break;
            }
            result = middle - 1;
            break;
        }
        if (A[middle] > value) {
            end = middle;
        }
        else {
            start = middle + 1;
        }
    }                  // Конец цикла

    if (result > 0) {
            if (A[result] > value && A[result - 1] < value) {
                if (std::abs(value - A[result - 1]) > std::abs(value - A[result])) {
                    return result;
                }
                return (result - 1);
            }
        }
        if (result < end_) {
            if (A[result] < value && A[result + 1] > value) {
                if (std::abs(value - A[result]) > std::abs(value - A[result + 1])) {
                    return result + 1;
                }
                return result;
            }
        }
    return result;
}

int exponential_search(int arr[], int size, int &key) {
    if (size == 0) {
        return EXIT_FAILURE;
    }

    int bound = 1;
    while (bound < size && arr[bound] < key) {
        bound *= 2;
    }

    return binary(arr, key, bound / 2, std::min(bound + 1, size));
}

void test() {
    int counter = 0;

    int Zz[10] = {15, 32, 37, 41, 45, 56, 64, 65, 72, 93};
    int Tt[10] = {57, 7, 97, 80, 21, 10, 75, 46, 62, 52};
    int tt[10] = {5, 0, 9, 8, 0, 0, 8, 4, 6, 5};
    for (size_t i = 0; i < 10; ++i) {
        counter = exponential_search(Zz,10, Tt[i]);
        assert(counter == tt[i]);
    }
    std::cout << "OK\n";
    int Z[10] = {15, 32, 37, 41, 45, 56, 64, 65, 72, 93};
    int T[10] = {53, 7, 97, 80, 21, 10, 75, 46, 62, 52};
    int t[10] = {5, 0, 9, 8, 0, 0, 8, 4, 6, 5};
    for (size_t i = 0; i < 10; ++i) {
        counter = exponential_search(Z,10, T[i]);
        assert(counter == t[i]);
    }
    std::cout << "OK\n";
    int A[4] = {-4, 0, 3, 18};
    int B[5] = {-2, 5, 4, 7, 12};
    int b[5] = {0, 2, 2, 2, 3};
    for (size_t i = 0; i < 5; ++i) {
        counter = exponential_search(A,4, B[i]);
        assert(counter == b[i]);
    }

    std::cout << "OK\n";

    int C[4] = {1, 2, 3, 5};
    int D[4] = {-3, -1, 0, 1};
    int d[4] = {0, 0, 0, 0};
    for (size_t i = 0; i < 4; ++i) {
        counter = exponential_search(C,4,  D[i]);
        assert(counter == d[i]);
    }
    std::cout << "OK\n";

    int E[2] = {0, 10};
    int F[6] = {-3, 17, 3, 5, 0, 1};
    int f[6] = {0, 1, 0, 0, 0, 0};
    for (size_t i = 0; i < 6; ++i) {
        counter = exponential_search(E,2, F[i]);
        assert(counter == f[i]);
    }
    std::cout << "OK\n";

    int G[5] = {1, 2, 10, 12, 23};
    int J[2] = {10, -1};
    int j[2] = {2, 0};
    for (size_t i = 0; i < 2; ++i) {
        counter = exponential_search(G,5, J[i]);
        assert(counter == j[i]);
    }
    std::cout << "OK\n";

    int H[3] = {0, 4, 5};
    int P[7] = {-3, 0, 1, 2, 5, 7, 10};
    int p[7] = {0, 0, 0, 0, 2, 2, 2};
    for (size_t i = 0; i < 7; ++i) {
        counter = exponential_search( H,3,  P[i]);
        assert(counter == p[i]);
    }
    std::cout << "OK\n";

    int X[11] = {-5, -2, 0, 3, 5, 8, 9, 10, 11, 14, 35};
    int Y[10] = {-13, -2, 0, 1, 245, 6, 8, 10, 11, 13};
    int y[10] = {0, 1, 2, 2, 10, 4, 5, 7, 8, 9};
    for (size_t i = 0; i < 10; ++i) {
        counter = exponential_search( X,11,  Y[i]);
        assert(counter == y[i]);
    }
    std::cout << "OK\n";

    int O[1] = {-5};
    int K[4] = {0, 1, 12, -100};
    int k[4] = {0, 0, 0, 0};
    for (size_t i = 0; i < 4; ++i) {
        counter = exponential_search( O,1,  K[i]);
        assert(counter == k[i]);
    }
    std::cout << "OK\n";

    int L[3] = {-25, 5, 9};
    int N[7] = {-9, 1, -10, 6, 7, 10, -30};
    int n[7] = {1, 1, 0, 1, 1, 2, 0};
    for (size_t i = 0; i < 7; ++i) {
        counter = exponential_search(L,3, N[i]);
        assert(counter == n[i]);
    }
    std::cout << "OK\n";

    int V[5] = {-25, 0, 5, 10, 13};
    int M[8] = {2, 3, 4, 5, 6, 7, 8, 12};
    int m[8] = {1, 2, 2, 2, 2, 2, 3, 4};
    for (size_t i = 0; i < 8; ++i) {
        counter = exponential_search(V,5 , M[i]);
        assert(counter == m[i]);
    }
    std::cout << "OK\n";

    int Q[5] = {-25, 0, 5, 10, 13};
    int S[7] = {-13000, 1, 1, 110000, -15, -15, -30000};
    int s[7] = {0, 1, 1, 4, 0, 0, 0};
    for (size_t i = 0; i < 7; ++i) {
        counter = exponential_search(Q, 5, S[i]);
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
    for (size_t i = 0; i < m; i++) {
        B[i] = exponential_search(A,n , B[i]);
    }
    for (size_t i = 0; i < m; i++) {
        std::cout << B[i] << " ";
    }
    delete[]A;
    delete[]B;
    return 0;
}

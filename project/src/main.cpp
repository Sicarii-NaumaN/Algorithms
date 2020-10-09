#include <iostream>
#include <cassert>

int logic (const int* A, const int* B,const size_t &n,const size_t &m,const int &k) {
    size_t counter = 0;
    long int i = 0;
    long int j = m - 1;
    while (i < (long int)n && j >= 0) {
        if (A[i] + B[j] == k) {
            counter++;
            i++;
            j--;
        } else {
            if (n == m) {
                if (A[i] + B[j] < k) {
                    if (A[i + 1] + B[j] <= k) {
                        i++;
                        continue;
                    }
                }
                j--;
                continue;
            }

            if (n > m) {
                if (A[i] + B[j] < k) {
                    i++;
                    continue;
                }
                j--;
            } else {
                if (A[i] + B[j] < k) {
                    i++;
                    continue;
                }
                j--;
            }
        }
    }
    return counter;
};
void test() {
    int counter = 0;

    int A[4] = {-5, 0, 3, 18};        // first test
    int B[5] = {-10, -2, 4, 7, 12};
    counter = logic(A, B, 4, 5, 7);
    assert(counter == 3);
    std::cout << "OK\n";

    int C[4] = {1, 2, 3, 5};          // equal size arrays
    int D[4] = {-3, -1, 0, 1};
    counter = logic(C, D, 4, 4, 2);
    assert(counter == 4);
    std::cout << "OK\n";

    int E[4] = {0, 2, 3, 13};          // equal size arrays
    int F[4] = {-3, -1, 0, 1};
    counter = logic(E, F, 4, 4, 2);
    assert(counter == 2);
    std::cout << "OK\n";

    int G[5] = {1, 2, 10, 12};
    int J[2] = {-3, -1};
    counter = logic(G, J, 5, 2, 9);
    assert(counter == 2);
    std::cout << "OK\n";

    int H[3] = {0, 3, 5};
    int P[7] = {-3, 0, 1, 2, 5, 7, 10};
    counter = logic(H, P, 3, 7, 5);
    assert(counter == 3);
    std::cout << "OK\n";

    int U[7] = {-2, 0, 3, 5 ,8, 9, 10};
    int R[10] = {-3, 0, 1, 2, 6, 8, 10, 11, 12, 13};
    counter = logic(U, R, 7, 10, 11);
    assert(counter == 6);
    std::cout << "OK\n";

    int X[11] = {-5, -2, 0, 3, 5, 8, 9, 10, 11, 14};
    int Y[10] = {-3, -2, 0, 1, 2, 6, 8, 10, 11, 13};
    counter = logic(X, Y, 11, 10, 11);
    assert(counter == 8);
    std::cout << "OK\n";

}
int main() {
    test();

    /*size_t n = 0;
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
    int k = 0;
    std::cin >> k;

    size_t counter = logic(A, B, n, m, k);
    std::cout << counter << std::endl;

    delete[] A;
    delete[] B;*/

    return 0;
}
//
// Created by tanknee on 3/3/2021.
//

#include <iostream>

using namespace std;

int merge(int A[], int B[], int C[], int n, int m) {
    int i = 0, j = 0, idx = 0;
    while (i < n && j < m) {
        if (A[i] < B[i]) {
            C[idx++] = A[i++];
        } else {
            C[idx++] = B[j++];
        }
    }
    while (i < n) C[idx++] = A[i++];
    while (j < m) C[idx++] = B[j++];
    return idx;
}

int main() {

}
//
// Created by tanknee on 2/24/2021.
//

#include <iostream>
#include <string.h>
using namespace std;
int main() {
    char c[81], u[30][30];
    memset(u, ' ', sizeof(u));
    scanf("%s", c);
    int n = strlen(c) + 2;
    int n1 = n / 3, n2 = n / 3 + n % 3, index = 0;
    for(int i = 0; i < n1; i++) u[i][0] = c[index++];
    for(int i = 1; i <= n2 - 2; i++) u[n1-1][i] = c[index++];
    for(int i = n1 - 1; i >= 0; i--) u[i][n2-1] = c[index++];
    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < n2; j++)
            printf("%c", u[i][j]);
        printf("\n");
    }
    return 0;
}

/**
#include <bits/stdc++.h>
#include <cstring>
using namespace std;

int main() {
    string word;
    cin >> word;
    int length = word.length() + 2, index = 0;
    int n2 = length / 3 + length % 3;
    int n = length / 3;
    vector<vector<int>> matrix(n, vector<int>(n2, 0));
    for (int i = 0; i < n; ++i) {
        matrix[i][0] = word[index++];
    }
    for (int i = 1; i < n2 - 1; ++i) {
        matrix[n - 1][i] = word[index++];
    }
    for (int i = n - 1; i >= 0; --i) {
        matrix[i][n2 - 1] = word[index++];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n2; ++j) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
 **/
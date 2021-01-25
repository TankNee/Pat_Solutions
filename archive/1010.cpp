//
// Created by tanknee on 2021/1/25.
//

#include <iostream>
#include <algorithm>
#include <cctype>
#include <cmath>

using namespace std;

long long int to_decimal(string num, long long int radix) {
    long long int sum = 0, index = 0, tmp;
    for (long long int i = num.length() - 1; i >= 0; --i) {
        tmp = isalpha(num[i]) ? (num[i] - 'a' + 10) : (num[i] - '0');
        sum += tmp * pow(radix, index++);
    }
    return sum;
}

long long find_radix(long long int num, string N2) {
    char it = *max_element(N2.begin(), N2.end());
    long long low = (isdigit(it) ? it - '0' : it - 'a' + 10) + 1;
    long long high = max(num, low);
    while (low <= high) {
        long long mid = (low + high) / 2;
        long long t = to_decimal(N2, mid);
        if (t < 0 || t > num) high = mid - 1;
        else if (t == num) return mid;
        else low = mid + 1;
    }
    return -1;
}

int main() {
    string N1, N2, tmp;
    long long int flag, radix;
    cin >> N1 >> N2 >> flag >> radix;
    // 交换N1与N2
    if (flag == 2)
        swap(N1, N2);

    long long int result = find_radix(to_decimal(N1, radix), N2);
    if (result > 0)
        cout << result;
    else
        cout << "Impossible";
    return 0;
}
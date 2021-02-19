//
// Created by tanknee on 2/19/2021.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

string get_standard(const string &number, int N) {
    string res = "0.";
    int exponent = 0;
    int pos = number.find('.');
    if (pos < 0) {
        int not_zero_index = 0;
        while (not_zero_index < number.length() && number[not_zero_index] == '0') {
            not_zero_index++;
        }
        if (number.length() - not_zero_index >= N) {
            res.append(number.substr(not_zero_index, N));
        } else {
            res.append(number.substr(not_zero_index, N));
            for (int i = 0; i < N - (number.length() - not_zero_index); ++i) {
                res.append("0");
            }
        }
        exponent = number.length() - not_zero_index;
        if (number.length() == 1 && number[0] == '0') exponent = 0;
    } else {
        if (pos > N) {
            res.append(number.substr(0, N));
            exponent = pos;
        } else {
            int not_zero_index = 2;
            if (pos == 1 && number[0] == '0') {
                while (not_zero_index < number.length() && number[not_zero_index] == '0') {
                    not_zero_index++;
                }
                if (not_zero_index != number.length()) {
                    if (number.length() - not_zero_index >= N) {
                        res.append(number.substr(not_zero_index, N));
                    } else {
                        res.append(number.substr(not_zero_index, number.length() - not_zero_index));
                        for (int i = 0; i < N - (number.length() - not_zero_index); ++i) {
                            res.append("0");
                        }
                    }
                    exponent = -(not_zero_index - pos - 1);
                } else {
                    res.append(number.substr(0, pos)).append(number.substr(pos + 1, number.length() - pos));
                    for (int i = 0; i < N - number.length() + 1; ++i) {
                        res.append("0");
                    }
                    exponent = 0;
                }
            } else {
                if (number.length() - 1 >= N) {
                    res.append(number.substr(0, pos)).append(number.substr(pos + 1, N - pos));
                } else {
                    res.append(number.substr(0, pos)).append(number.substr(pos + 1, number.length() - pos));
                    for (int i = 0; i < N - number.length() + 1; ++i) {
                        res.append("0");
                    }
                }
                exponent = pos;
            }
        }
    }
    res.append("*10^");
    res.append(to_string(exponent));
    return res;
}

int main() {
    int N, flag = 0;
    cin >> N;
    string number1, number2;
    cin >> number1 >> number2;
    string s1 = get_standard(number1, N);
    string s2 = get_standard(number2, N);
    if (s1 == s2) {
        cout << "YES " << s1;
    } else {
        cout << "NO " << s1 << " " << s2;
    }
    return 0;
}
//
// Created by tanknee on 2/17/2021.
//

#include <iostream>

using namespace std;

bool check_palindromic(string num) {
    for (int i = 0; i < (num.length() / 2) + 1; ++i) {
        if (num[i] != num[num.length() - 1 - i]) return false;
    }
    return true;
}

string add(string num1, string num2) {
    int flag = 0;
    string new_num;
    new_num.resize(num1.length());
    for (int i = num1.length() - 1; i >= 0; --i) {
        int tmp = num1[i] - '0' + num2[i] - '0' + flag;
        if (tmp >= 10) {
            tmp -= 10;
            flag = 1;
        } else flag = 0;
        new_num[i] = tmp + '0';
    }
    if (flag) {
        string tmp_num;
        tmp_num.resize(new_num.length() + 1);
        tmp_num[0] = '1';
        for (int i = 1; i < new_num.length() + 1; ++i) {
            tmp_num[i] = new_num[i - 1];
        }
        return tmp_num;
    }
    return new_num;
}

string reverse(string num) {
    string res;
    res.resize(num.length());
    for (int i = num.length() - 1; i >= 0; --i) {
        res[num.length() - 1 - i] = num[i];
    }
    return res;
}

int main() {
    string num, tmp;
    int max_step;
    cin >> num >> max_step;
    tmp.resize(num.length());
    for (int i = 0; i < num.length(); ++i) {
        tmp[num.length() - i - 1] = num[i];
    }
    int step = 0;
    while (step < max_step) {
        if (check_palindromic(num)) {
            cout << num << endl;
            cout << step;
            break;
        }
        num = add(num, tmp);
        tmp = reverse(num);
        step++;
    }
    if (step >= max_step) {
        cout << num << endl;
        cout << max_step;
    }
    return 0;
}
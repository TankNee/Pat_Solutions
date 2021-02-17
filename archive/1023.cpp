//
// Created by tanknee on 2/17/2021.
//

#include <iostream>

using namespace std;

int main() {
    string num;
    cin >> num;
    string new_num;
    new_num.resize(num.length());
    int flag = 0, cur = 0;
    for (int i = num.length() - 1; i >= 0; --i) {
        cur = num[i] - '0';
        cur = cur * 2 + flag;
        if (cur >= 10) {
            cur -= 10;
            flag = 1;
        } else flag = 0;
        new_num[i] = cur + '0';
    }
    if (flag) {
        cout << "No" << endl;
        cout << "1" << new_num;
        return 0;
    }
    int tmp[num.length()];
    fill(tmp, tmp + num.length(), 0);
    for (char &j : num) {
        tmp[j - '0']++;
    }
    for (int i = 0; i < new_num.length(); ++i) {
        if (tmp[new_num[i] - '0'] <= 0) {
            cout << "No" << endl;
            cout << new_num;
            return 0;
        } else {
            tmp[new_num[i] - '0']--;
        }
    }
    cout << "Yes" << endl;
    cout << new_num;
    return 0;
}
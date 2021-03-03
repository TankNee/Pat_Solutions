//
// Created by tanknee on 3/3/2021.
//
#include <iostream>

using namespace std;

struct big_integer {
    int d[1000];
    int length;

    big_integer() {
        length = 0;
    }

    big_integer(string str) {
        length = str.length();
        for (int i = 0; i < length; ++i) {
            d[i] = str[length - i - 1] - '0';
        }
    }

    int compare_to(big_integer bi) {
        if (length > bi.length) return 1;
        else if (length < bi.length) return -1;
        else {
            for (int i = length - 1; i >= 0; --i) {
                if (d[i] > bi.d[i]) return 1;
                else if (d[i] < bi.d[i]) return -1;
            }
            return 0;
        }
    }

    big_integer operator+(const big_integer &bi) const {
        big_integer res;
        int flag = 0;
        for (int i = 0; i < length || i < bi.length; ++i) { // 以较大的为界限
            int tmp = d[i] + bi.d[i] + flag;
            flag = 0;
            if (tmp >= 10) {
                tmp -= 10;
                flag = 1;
            }
            res.d[res.length++] = tmp;
        }
        if (flag) {
            res[res.length++] = 1;
        }
        return res;
    }
    // 这里的这种减法没有考虑负数的情况！所以最好应该先比较，如果被减数较小就交换被减数和减数，并在最后的结果上加上负号！
    big_integer operator-(const big_integer &bi) const {
        big_integer res;
        for (int i = 0; i < length || i < bi.length; ++i) { // 以较大的数为边界
            if (d[i] < bi.d[i]) {   // 如果不够减，那么就从下一位借一位。因为我们的高精度整数的位数是从低到高排列的，所以下一位就是更高位！
                d[i + 1]--;
                d[i] += 10;
            }
            res.d[res.length++] = d[i] - bi.d[i];
        }
        while (res.length - 1 >= 1 && res.d[res.length - 1] == 0) { // 把最高位上多余的0去掉
            res.length--;
        }
        return res;
    }
};

int main() {
    big_integer a("2132512345213452345");
    big_integer b("23345923048520345");
    big_integer c = a + b;
}
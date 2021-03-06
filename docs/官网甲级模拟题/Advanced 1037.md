# 题目

## 1037 Magic Coupon (25 分)

The magic shop in Mars is offering some magic coupons. Each coupon has an integer *N* printed on it, meaning that when you use this coupon with a product, you may get *N* times the value of that product back! What is more, the shop also offers some bonus product for free. However, if you apply a coupon with a positive *N* to this bonus product, you will have to pay the shop *N* times the value of the bonus product... but hey, magically, they have some coupons with negative *N*'s!

For example, given a set of coupons { 1 2 4 −1 }, and a set of product values { 7 6 −2 −3 } (in Mars dollars M) where a negative value corresponds to a bonus product. You can apply coupon 3 (with *N* being 4) to product 1 (with value M ​7) to get M ​28 back; coupon 2 to product 2 to get M 12 back; and coupon 4 to product 4 to get M3 back. On the other hand, if you apply coupon 3 to product 4, you will have to pay M​ 12 to the shop.

Each coupon and each product may be selected at most once. Your task is to get as much money back as possible.

### Input Specification:

Each input file contains one test case. For each case, the first line contains the number of coupons *N**C*, followed by a line with *N**C* coupon integers. Then the next line contains the number of products *N**P*, followed by a line with *N**P* product values. Here 1≤$N_C$,$N_P$≤105, and it is guaranteed that all the numbers will not exceed 230.

### Output Specification:

For each test case, simply print in a line the maximum amount of money you can get back.

### Sample Input:

```in
4
1 2 4 -1
4
7 6 -2 -3
```

### Sample Output:

```out
43
```

# 理解与算法

用优惠券从商家那里拿到最多的钱，排序之后从左到右，再从右到左。大的数跟大的数相乘才能拿到最大收益！

```cpp
//
// Created by tanknee on 2021/3/1.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    int Nc, Np;
    cin >> Nc;
    vector<long long> coupons(Nc);
    for (int i = 0; i < Nc; ++i) {
        cin >> coupons[i];
    }
    sort(coupons.begin(), coupons.end());
    cin >> Np;
    vector<long long> products(Np);
    for (int i = 0; i < Np; ++i) {
        cin >> products[i];
    }
    sort(products.begin(), products.end());

    long long sum = 0;
    int j = 0, i = 0, l = products.size() - 1;
    for (; i < coupons.size() && coupons[i] < 0 && products[j] < 0; ++i, ++j) {
        sum += coupons[i] * products[j];
    }
    for (int k = coupons.size() - 1; k >= 0 && l >= 0 && coupons[k] > 0 && products[l] > 0; k--, l--) {
        sum += coupons[k] * products[l];
    }
    cout << sum;
    return 0;
}
```
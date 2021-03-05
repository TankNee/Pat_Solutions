#include <iostream>

using namespace std;

int main() {
    int n, left = 0, right = 0, a = 1, now = 1, ans = 0;
    scanf("%d", &n);
    while (n / a) {
        // left是当前选取的数位左边的那串数字，now是当前选取的数位，right是当前选取数位右边的那串数字
        left = n / (a * 10), now = n / a % 10, right = n % a;
        // 而且，由于我们是从右到左计算，且每次都只计算当前数位为1的可能的个数！
        // now==0说明now位只有在left从0~left-1的时候会产生1，所以会产生left次，但是又因为右边会重复从0~999…出现a次
        // 例如120，当now==0时，只有01，11，21...111才会让这一位成为1且小于n
        if (now == 0) ans += left * a;
            // 如果当前位是1，left可以取0-left，所以相比上一步，我们要加一个当now为1的时候右边出现0~right个数导致的now为1的次数
            // 例如113，选中中间的1，那么就可取，010，011，一直到019，再从019一直到113。因为left * a这个式子已经包含了重复的right，所以只需要考虑left最大的时候那个有限的right
        else if (now == 1) ans += left * a + right + 1;
            // 当now>=1时，例如123，选中3，那么可以取01，11，一直到121，那就是(12 + 1) * 1种。
        else ans += (left + 1) * a;
        a = a * 10;
    }
    printf("%d", ans);
    return 0;
}
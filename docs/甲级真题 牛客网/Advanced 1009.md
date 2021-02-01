# 题目

## Insertion or Heap Sort (25)

### **题目描述**

According to Wikipedia:
Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. Each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until no input elements remain.
Heap sort divides its input into a sorted and an unsorted region, and it iteratively shrinks the unsorted region by extracting the largest element and moving that to the sorted region. it involves the use of a heap data structure rather than a linear-time search to find the maximum.
Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can you tell which sorting method we are using?

### **输入描述:**

Each input file contains one test case.  For each case, the first line gives a positive integer N (<=100).  Then in the next line, N integers are given as the initial sequence.  The last line contains the partially sorted sequence of the N numbers.  It is assumed that the target sequence is always ascending.  All the numbers in a line are separated by a space.

### **输出描述:**

For each test case, print in the first line either "Insertion Sort" or "Heap Sort" to indicate the method used to obtain the partial result.  Then run this method for one more iteration and output in the second line the resuling sequence.  It is guaranteed that the answer is unique for each test case.  All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

### **输入例子:**

```
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
```

### **输出例子:**

```
Insertion Sort
1 2 3 5 7 8 9 4 6 0
```

# 理解与算法

其实不算很难，只要能够一步步实现插入排序算法和堆排序算法就可以很快完成。

插入排序：

- 确保排过的部分是确定有序的。
- 每个元素都是从后向前比较，只要符合条件就将元素往后移一格，知道遇到不符合条件的元素。

```c
/**
 * 插入排序是保证已经排过序的部分是绝对有序的！所以插入排序是从后向前排序，每次只排序一个元素
 * 排序的时候从后向前扫描，找到比排序元素大的就将其放到它原来的后一位，找到比排序元素小的就将排序元素放在访问元素的后一位！
 * [1,2,6,7,4] etc.
 * 此时假设要排序的数字是4，那就将4(index=4)，和7(index=3)进行比较，因为7>4所以用7覆盖4的位置，变成了[1,2,6,7,7],而4已经存在临时变量中，不用担心丢失数据。
 * 然后将访问元素向前推进，将4和6进行比较，还是小于所以就用6覆盖原来index=3的位置，于是就变成了[1,2,6,6,7]。
 * 最后与2进行比较，4>2所以停止扫描，将4放在2的后面得到排序完成的数组。
 * 可以覆盖的理由是后面的数字必定已经往后移了一位！
 * @param arr
 * @return
 */
vector<int> insert_sort(vector<int> arr, vector<int> p_result) {
    int temp;
    bool flag = false;
    for (int i = 1; i < arr.size(); ++i) {
        temp = arr[i];
        for (int j = i; j > 0; j--) {
            if (temp < arr[j - 1]) {
                arr[j] = arr[j - 1];
            } else {
                arr[j] = temp;
                break;
            }
            if (j == 1) {
                arr[0] = temp;
            }
        }
        if (flag) break;
        i_flag = cmp(arr, p_result);
        if (i_flag) {
            flag = true;
        }
    }
    return arr;
}
```

堆排序：

- 将原数组构建成一个最大堆，然后将堆顶的元素放到数组的末尾
- 将除了最后一位的数组进行大顶堆构造，重复上述过程

```c
vector<int> heap_sort(vector<int> arr, vector<int> p_result) {
    make_heap(arr.begin(), arr.end());
    int temp;
    bool flag = false;
    for (int i = arr.size() - 1, j = 1; i > 0; --i, j++) {
        if (flag) break;
        h_flag = cmp(arr, p_result);
        if (h_flag) {
            flag = true;
        }
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        make_heap(arr.begin(), arr.end() - j);
    }
    return arr;
}
```

这里用C++的`make_heap`方法就能很方便的将数组改造成堆，这个方法在algorithm文件中，记得引用。

## 代码与实现

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
bool i_flag = false, h_flag = false;

bool cmp(vector<int> a1, vector<int> a2);

/**
 * 插入排序是保证已经排过序的部分是绝对有序的！所以插入排序是从后向前排序，每次只排序一个元素
 * 排序的时候从后向前扫描，找到比排序元素大的就将其放到它原来的后一位，找到比排序元素小的就将排序元素放在访问元素的后一位！
 * [1,2,6,7,4] etc.
 * 此时假设要排序的数字是4，那就将4(index=4)，和7(index=3)进行比较，因为7>4所以用7覆盖4的位置，变成了[1,2,6,7,7],而4已经存在临时变量中，不用担心丢失数据。
 * 然后将访问元素向前推进，将4和6进行比较，还是小于所以就用6覆盖原来index=3的位置，于是就变成了[1,2,6,6,7]。
 * 最后与2进行比较，4>2所以停止扫描，将4放在2的后面得到排序完成的数组。
 * 可以覆盖的理由是后面的数字必定已经往后移了一位！
 * @param arr
 * @return
 */
vector<int> insert_sort(vector<int> arr, vector<int> p_result) {
    int temp;
    bool flag = false;
    for (int i = 1; i < arr.size(); ++i) {
        temp = arr[i];
        for (int j = i; j > 0; j--) {
            if (temp < arr[j - 1]) {
                arr[j] = arr[j - 1];
            } else {
                arr[j] = temp;
                break;
            }
            if (j == 1) {
                arr[0] = temp;
            }
        }
        if (flag) break;
        i_flag = cmp(arr, p_result);
        if (i_flag) {
            flag = true;
        }
    }
    return arr;
}

vector<int> heap_sort(vector<int> arr, vector<int> p_result) {
    make_heap(arr.begin(), arr.end());
    int temp;
    bool flag = false;
    for (int i = arr.size() - 1, j = 1; i > 0; --i, j++) {
        if (flag) break;
        h_flag = cmp(arr, p_result);
        if (h_flag) {
            flag = true;
        }
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        make_heap(arr.begin(), arr.end() - j);
    }
    return arr;
}

bool cmp(vector<int> a1, vector<int> a2) {
    for (int i = 0; i < a1.size(); ++i) {
        if (a1[i] != a2[i]) return false;
    }
    return true;
}

int main() {
//    vector<int> t = {3 1 2 8 7 5 9 4 6 0}
    int N, tmp;
    cin >> N;
    vector<int> arr1, arr2, p_result, n_result;
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        arr1.push_back(tmp);
        arr2.push_back(tmp);
    }
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        p_result.push_back(tmp);
    }
    arr1 = insert_sort(arr1, p_result);
    arr2 = heap_sort(arr2, p_result);
    if (i_flag) {
        cout << "Insertion Sort" << endl;
        cout << arr1[0];
        for (int i = 1; i < arr1.size(); ++i) {
            cout << " " << arr1[i];
        }
    } else if (h_flag) {
        cout << "Heap Sort" << endl;
        cout << arr2[0];
        for (int i = 1; i < arr2.size(); ++i) {
            cout << " " << arr2[i];
        }
    }
    return 0;
}
```


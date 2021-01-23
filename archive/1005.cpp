//
// Created by tanknee on 2021/1/23.
//

#include <iostream>
#include <vector>

using namespace std;

string english_numbers[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main() {
    string number;
    cin >> number;
    int count = 0;
    for (char i : number) {
        count += i - '0';
    }
    string number_string = to_string(count);
    cout << english_numbers[number_string[0] - '0'];
    for (int i = 1; i < number_string.size(); ++i) {
        cout << " " << english_numbers[number_string[i] - '0'];
    }
    return 0;
}
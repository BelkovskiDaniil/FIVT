/*Строка называется палиндромом, если она одинаково читается как слева направо, так и справа налево. Например, «abba» – палиндром, а «roman» – нет.

Для заданной строки s длины n (1 ≤ n ≤ 105) требуется подсчитать число пар (i, j), 1 ≤ i < j ≤ n, таких что подстрока s[i..j] является палиндромом.

 https://contest.yandex.ru/contest/49263/run-report/87774962/*/

#include <iostream>
#include <string>
#include <vector>

std::vector<int64_t> find_even(const std::string &string, int64_t left, int64_t right) {
    std::vector<int64_t> res(string.size());
    for (int i = 0; i < string.size(); ++i) {
        int64_t temp = i > right ? 0 : std::min(res[left + right - i + 1], right - i + 1);
        while (i + temp < string.size() && i - temp - 1 >= 0 && string[i + temp] == string[i - temp - 1]) ++temp;
        res[i] = temp;
        if (i + temp - 1 > right) left = i - temp, right = i + temp - 1;
    }
    return res;
}


std::vector<int64_t> find_odd(const std::string &string, int64_t left, int64_t right) {
    std::vector<int64_t> res(string.size());
    for (int i = 0; i < string.size(); ++i) {
        int64_t temp = i > right ? 1 : std::min(res[left + right - i], right - i + 1);
        while (i + temp < string.size() && i - temp >= 0 && string[i + temp] == string[i - temp]) ++temp;
        res[i] = temp;
        if (i + temp - 1 > right) left = i - temp + 1, right = i + temp - 1;
    }
    return res;
}

int64_t find_substr(const std::string &string) {
    int64_t left = 0;
    int64_t right = -1;
    std::vector<int64_t> res1(std::move(find_odd(string, left, right)));
    std::vector<int64_t> res2(std::move(find_even(string, left, right)));
    int64_t result = 0;
    for (int i = 0; i < string.size(); ++i) result += res1[i] + res2[i];
    return result - string.size();
}

int main() {
    std::string s;
    std::cin >> s;
    std::cout << find_substr(s) << std::endl;
    return 0;
}

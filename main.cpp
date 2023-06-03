/*Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки – n. Время O(n + p), доп. память – O(p).
Вариант 1. С помощью префикс-функции

https://contest.yandex.ru/contest/49263/run-report/87921477/*/

#include <iostream>
#include <vector>
#include <string>

std::vector<int> prefix_function(const std::string& s) {
    int n = s.size();
    std::vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

std::vector<int> kmp(const std::string& pattern, const std::string& s) {
    std::vector<int> pi = prefix_function(pattern);
    int n = s.size();
    int m = pattern.size();
    std::vector<int> matches;
    if (m == 0) {
        matches.push_back(0);
        return matches;
    }

    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && s[i] != pattern[j]) {
            j = pi[j-1];
        }
        if (s[i] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            matches.push_back(i - m + 1);
            j = pi[j-1];
        }
    }
    return matches;
}

int main() {
    std::string pattern;
    std::string s;
    std::cin >> pattern >> s;

    auto matches = kmp(pattern, s);

    for (auto match : matches) {
        std::cout << match << " ";
    }

    std::cout << std::endl;

    return 0;
}

/*Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки ­– n. Время O(n + p), доп. память – O(p).
Вариант 1. С помощью префикс-функции

 https://contest.yandex.ru/contest/49263/run-report/87770377/*/

#include <iostream>
#include <vector>
#include <string>

std::vector<int> prefix_function(std::string& s) {
    size_t n = s.size();
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

std::vector<int> kmp(std::string pattern, std::string s) {
    std::string str = pattern + "#" + s;
    int p_size = pattern.size();
    std::vector<int> pi = prefix_function(str);

    std::vector<int> matches;
    for (int i = p_size + 1; i < str.size(); ++i) {
        if (pi[i] == p_size) {
            matches.push_back(i - 2 * p_size);
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

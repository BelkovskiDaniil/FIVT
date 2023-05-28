/*Дана строка длины n. Найти количество ее различных подстрок. Используйте суффиксный массив.

Построение суффиксного массива выполняйте за O(n log n). Вычисление количества различных подстрок выполняйте за O(n).

 https://contest.yandex.ru/contest/49263/run-report/87772055/*/

#include <iostream>
#include <vector>
#include <algorithm>

// Структура для хранения информации о суффиксе
struct Suffix {
    int index;
    int rank[2];
};

// Функция для сравнения суффиксов при сортировке
bool suffixComparator(const Suffix& a, const Suffix& b) {
    return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1]) : (a.rank[0] < b.rank[0]);
}

// Функция для построения суффиксного массива
std::vector<int> buildSuffixArray(const std::string& str) {
    int n = str.length();
    std::vector<Suffix> suffixes(n);

    for (int i = 0; i < n; ++i) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = str[i] - 'a';
        suffixes[i].rank[1] = (i + 1 < n) ? (str[i + 1] - 'a') : -1;
    }

    std::sort(suffixes.begin(), suffixes.end(), suffixComparator);

    std::vector<int> indexes(n);

    for (int k = 4; k < 2 * n; k *= 2) {
        int rank = 0;
        int prevRank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        indexes[suffixes[0].index] = 0;

        for (int i = 1; i < n; ++i) {
            if (suffixes[i].rank[0] == prevRank && suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
                prevRank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else {
                prevRank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            indexes[suffixes[i].index] = i;
        }

        for (int i = 0; i < n; ++i) {
            int nextIndex = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = (nextIndex < n) ? suffixes[indexes[nextIndex]].rank[0] : -1;
        }

        std::sort(suffixes.begin(), suffixes.end(), suffixComparator);
    }

    std::vector<int> suffixArray(n);
    for (int i = 0; i < n; ++i) {
        suffixArray[i] = suffixes[i].index;
    }

    return suffixArray;
}

// Функция для вычисления количества различных подстрок
int countDistinctSubstrings(const std::string& str) {
    int n = str.length();
    std::vector<int> suffixArray = buildSuffixArray(str);

    int count = n - suffixArray[0];
    for (int i = 1; i < n; ++i) {
        int commonPrefix = 0;
        while (str[suffixArray[i] + commonPrefix] == str[suffixArray[i - 1] + commonPrefix]) {
            ++commonPrefix;
        }
        count += (n - suffixArray[i]) - commonPrefix;
    }

    return count;
}

int main() {
    std::string str;
    std::cin >> str;

    int distinctSubstrings = countDistinctSubstrings(str);
    std::cout << distinctSubstrings << std::endl;

    return 0;
}

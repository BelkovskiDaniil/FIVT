/*Даны два "длинных" неотрицательных числа. Требуется найти результат их сложения.
 *
 *https://contest.yandex.ru/contest/46386/run-report/83845057/
 */

#include <iostream>
#include <string>

int main() {
    std::string biggest, smallest, str, first_number, second_number, answer = "";
    int size_biggest, size_smallest, number_biggest, number_smallest, zero = 0;
    std::cin >> first_number;
    std::cin >> second_number;

    //Находим наибольшее число
    if (first_number.size() >= second_number.size()) {
        biggest = first_number;
        smallest = second_number;
    }
    else {
        biggest = second_number;
        smallest = first_number;
    }

    size_biggest = biggest.size() - 1;
    size_smallest = smallest.size() - 1;

    //Производим сложение
    for(int i = 0; i <= size_biggest; i++){
        number_biggest = i <= size_biggest ? biggest[size_biggest - i] - '0': 0;
        number_smallest = i <= size_smallest ? smallest[size_smallest - i] - '0': 0;
        answer = char((number_biggest + number_smallest + zero) % 10 + '0') + answer;
        zero = (number_biggest + number_smallest + zero) / 10;

    }

    if(zero) answer = char(zero + '0') + answer;

    std::cout << answer << "\n";
    return 0;
}

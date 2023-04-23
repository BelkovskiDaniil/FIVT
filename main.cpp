/*Требуется отыскать самый короткий маршрут между городами.
 * Из города может выходить дорога, которая возвращается в этот же город.

Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.

 https://contest.yandex.ru/contest/47820/run-report/86293915/
 */

#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <limits>

//Класс графа, строящегося по условию задачи
class city_map {
public:
    explicit city_map(int size);
    void set_road(int start, int end, int weight);
    void get_vert(int vertex, std::vector<std::pair<int, int>> &vert) const;
    int get_size() const;
    std::vector<std::list<std::pair<int, int>>> vertices;
};

city_map::city_map(int size) : vertices(size, std::list<std::pair<int, int>>()) {}

//Добавляем дорогу (ребро) в граф
void city_map::set_road(int start, int end, int weight) {
    vertices[start].emplace_back(end, weight);
    vertices[end].emplace_back(start, weight);
}

int city_map::get_size() const {
    return vertices.size();
}

void city_map::get_vert(int vertex, std::vector<std::pair<int, int>> &vert) const {
    vert.clear();
    for (const std::pair<int, int> &elem : vertices[vertex]) vert.push_back(elem);
}

//Используем алгоритм Дейкстры
int algo_dij(const city_map &city_map, int start, int end) {
    std::vector<bool> visited(city_map.get_size(), false);
    std::vector<int> path(city_map.get_size(), std::numeric_limits<int>::max());
    path[start] = 0;
    std::set<std::pair<int, int>> queue;
    queue.emplace(std::make_pair(0, start));
    while (!queue.empty()) {
        std::vector<std::pair<int, int>> paths;
        int number = (queue.begin())->second;
        queue.erase(queue.begin());
        visited[number] = true;
        city_map.get_vert(number, paths);
        for (std::pair<int, int> elem : paths) {
            if (path[elem.first] > path[number] + elem.second) {
                if (path[elem.first] != std::numeric_limits<int>::max())
                    queue.erase(std::make_pair(path[elem.first], elem.first));
                path[elem.first] = path[number] + elem.second;
                queue.emplace(std::make_pair(path[elem.first], elem.first));
            }
        }
    }
    return path[end];
}

int main() {
    int n = 0, m = 0, start = 0, end = 0, weight = 0;
    std::cin >> n >> m;
    city_map city_map(n);
    for (int i = 0; i < m; i++) {
        std::cin >> start >> end >> weight;
        city_map.set_road(start, end, weight);
    }
    std::cin >> start >> end;
    std::cout << algo_dij(city_map, start, end) << "\n";
    return 0;
}

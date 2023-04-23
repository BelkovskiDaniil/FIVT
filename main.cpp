/*Дан невзвешенный неориентированный граф.
 *В графе может быть несколько кратчайших путей между какими-то вершинами.
 *Найдите количество различных кратчайших путей между заданными вершинами.
 *Требуемая сложность O(V+E).
 *
 * https://contest.yandex.ru/contest/47820/run-report/86291458/
 * */

#include <vector>
#include <queue>
#include <iostream>

//Параметры графа
struct characteristics_of_graph {
    int uniq_ways = 0;
    int parent = -1;
    bool visited = false;
    int distance = 0;
};

//Граф, создаваемый по входным данным
class unoriented_graph {
public:

    explicit unoriented_graph(int data) :
            quantity_vertexes(data),
            vertexes(data),
            bfc_local(data)
    { }

    void set_way(int data_start, int data_end) {
        vertexes[data_start].push_back(data_end);
        vertexes[data_end].push_back(data_start);
    }

    //Находим ближайшие вершины
    void get_vertexes_near(int data, std::vector<int>& dataVector) const {
        if (dataVector.empty() != 1) { dataVector.clear(); }
        dataVector = vertexes[data];
    }

    //Запускаем обход в ширину, в процессе которого ищем уникальные пути и выводим их в конце алгоритма
    void bfs(int start, int end) {
        int min_len = -1;
        std::queue<int> queue_local;
        std::vector<int> vector_of_vertexes;
        bfc_local[start].uniq_ways = 1;

        queue_local.push(start);
        while (queue_local.empty() == 0) {
            int temporaryVert = queue_local.front();
            queue_local.pop();
            get_vertexes_near(temporaryVert, vector_of_vertexes);

            //В данном цикле ищем кратчайшие пути
            for (unsigned int i = 0; i < vector_of_vertexes.size(); i++) {
                // Если вершина не родительская, то смотрим, бывали ли мы в ней, если нет, то обновляем расстояние до нее и отмечаем как посещенную
                if (vector_of_vertexes[i] != bfc_local[temporaryVert].parent) {
                    if (!bfc_local[vector_of_vertexes[i]].visited) {
                        queue_local.push(vector_of_vertexes[i]);
                        bfc_local[vector_of_vertexes[i]].parent = temporaryVert;
                        bfc_local[vector_of_vertexes[i]].distance = bfc_local[temporaryVert].distance + 1;
                        bfc_local[vector_of_vertexes[i]].visited = true;
                    }
                    
                    // Смотрим, пришли ли в конечную, если пришли, смотрим на min_len, если больше, то заканчиваем bfs, иначе - обновляем минимальное расстояние и добавляем путь
                    if ((vector_of_vertexes[i] == end) && (min_len == -1)) min_len = bfc_local[end].distance;
                    if ((min_len != -1)&&(bfc_local[vector_of_vertexes[i]].distance > min_len)) break;
                    if (bfc_local[temporaryVert].distance==bfc_local[vector_of_vertexes[i]].distance-1) bfc_local[vector_of_vertexes[i]].uniq_ways += bfc_local[temporaryVert].uniq_ways;
                }
            }
        }
        std::cout << bfc_local[end].uniq_ways;
        return;
    }

// Количество вершин и списки смежности
private:
    int quantity_vertexes;
    std::vector<std::vector<int>> vertexes;
    std::vector<characteristics_of_graph> bfc_local;

};

int main() {
    int V, N, start, end, data_start, data_end;
    std::cin >> V;
    std::cin >> N;
    unoriented_graph graph(V);
    for (int i = 0; i < N; i++) {
        std::cin >> data_start;
        std::cin >> data_end;
        graph.set_way(data_start, data_end);
    }
    std::cin >> start;
    std::cin >> end;
    graph.bfs(start, end);
    return 0;
}
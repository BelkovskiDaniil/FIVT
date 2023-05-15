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
    int bfs(int start, int end) {
        int min_len = -1;
        std::queue<int> queue_local;
        bfc_local[start].uniq_ways = 1;

        queue_local.push(start);
        while (queue_local.empty() == 0) {
            int temporaryVert = queue_local.front();
            queue_local.pop();
            if (vector_of_vertexes.empty() != 1) { vector_of_vertexes.clear(); }
            std::vector<int> vector_of_vertexes = vertexes[temporaryVert];

            //В данном цикле ищем кратчайшие пути
            for (int vertex : vector_of_vertexes) {
                // Если вершина не родительская, то смотрим, бывали ли мы в ней, если нет, то обновляем расстояние до нее и отмечаем как посещенную
                if (vertex != bfc_local[temporaryVert].parent) {
                    if (!bfc_local[vertex].visited) {
                        queue_local.push(vertex);
                        bfc_local[vertex].parent = temporaryVert;
                        bfc_local[vertex].distance = bfc_local[temporaryVert].distance + 1;
                        bfc_local[vertex].visited = true;
                    }
                    
                    // Смотрим, пришли ли в конечную, если пришли, смотрим на min_len, если больше, то заканчиваем bfs, иначе - обновляем минимальное расстояние и добавляем путь
                    if ((vertex == end) && (min_len == -1)) min_len = bfc_local[end].distance;
                    if ((min_len != -1)&&(bfc_local[vertex].distance > min_len)) break;
                    if (bfc_local[temporaryVert].distance==bfc_local[vertex].distance-1) bfc_local[vertex].uniq_ways += bfc_local[temporaryVert].uniq_ways;
                }
            }
        }
        return bfc_local[end].uniq_ways;
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
    std::cout << graph.bfs(start, end) << "\n";
    return 0;
}

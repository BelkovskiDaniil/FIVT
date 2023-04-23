/*Необходимо написать торгового советника для поиска арбитража.
Арбитраж - это торговля по цепочке различных валют в надежде заработать на небольших различиях в коэффициентах. Например, есть следующие курсы валют:
GBP/USD: 0.67
RUB/GBP: 78.66
USD/RUB: 0.02
Имея 1$ и совершив цикл USD->GBP->RUB->USD, получим 1.054$. Таким образом заработав 5.4

https://contest.yandex.ru/contest/47820/run-report/86282080
 */


#include <iostream>
#include <vector>
#include <limits>

//Класс графа с помощью которого входная таблица превращается в граф
class arbitrage_graph {
public:
    explicit arbitrage_graph();
    void initialize_graph(int count);
    virtual void set_edge(int start, int end, double weight) ;
    double get_weight(int start, int end);
    virtual int quantity_of_vertices_virtual() const  { return quantity_of_vertices; }

private:
    int quantity_of_vertices;
    std::vector<std::vector<double>> edges;
};

double arbitrage_graph::get_weight(int start, int end) {
    return edges[start][end];
}

arbitrage_graph::arbitrage_graph() :
        quantity_of_vertices(-1),
        edges(0)
{}

void arbitrage_graph::initialize_graph(int count) {
    quantity_of_vertices = count;
    edges.resize(count);
    for (int i = 0; i < quantity_of_vertices; ++i) edges[i].resize(count);
}

void arbitrage_graph::set_edge(int start, int end, double weight) {
    edges[start][end] = weight;
}

//Используем алгоритм Беллмана-Форда
void algo(arbitrage_graph *graph) {
    double min_rate = std::numeric_limits<double>::min();
    int quantity_of_curr = graph->quantity_of_vertices_virtual();
    // Здесь храним информацию по арбитражному циклу (данному)
    std::vector<double> rate(0);

    //Здесь создаем вектор с данным арбитражем (если он нас удовлетворяет, то сразу выводим ответ)
    for (int currency = 0; currency < quantity_of_curr; ++currency) {
        rate.clear();
        rate.resize(quantity_of_curr);
        for (int i = 0; i < quantity_of_curr; ++i) rate[i] = min_rate;
        rate[currency] = 1.0;

        for (int k = 0; k <= quantity_of_curr; ++k) {
            for(int i = 0; i < quantity_of_curr; ++i) {
                for (int j = 0; j < quantity_of_curr; ++j) {
                    if (rate[j] < rate[i] * graph->get_weight(i, j)) {
                        if (k == quantity_of_curr) {
                            std::cout << "\n" << "YES" << "\n";
                            return;
                        }
                        rate[j] = rate[i] * graph->get_weight(i, j);
                    }
                }
            }
        }
    }

    std::cout << "\n" << "NO" << "\n";
    return;
}

//Создаем граф, считываем таблицу и запускаем алгоритм
int main() {
    arbitrage_graph	graph;
    int n = 0;
    std::cin >> n;
    graph.initialize_graph(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
                graph.set_edge(i, j, 1);
            else
            {
                double temp;
                std::cin >> temp;
                if (temp == -1)
                    continue;
                graph.set_edge(i, j, temp);
            }
        }
    }
    algo(&graph);
    return 0;
}

/*Найти в связном графе остовное дерево минимального веса.
 *https://contest.yandex.ru/contest/47820/run-report/86275544/*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Структура ребра
struct rib {
    int u, v, weight;
};

//Сравнения ребер графа
bool compareribs(const rib& a, const rib& b) {
    return a.weight < b.weight;
}

int find(int x, vector<int>& parent) {
    if (parent[x] != x) {
        parent[x] = find(parent[x], parent);
    }
    return parent[x];
}

//Объединяем множества, содержащие x и y
void unite(int x, int y, vector<int>& parent, vector<int>& rank) {
    int rootX = find(x, parent);
    int rootY = find(y, parent);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootX] = rootY;
            if (rank[rootX] == rank[rootY]) {
                rank[rootY]++;
            }
        }
    }
}

//Алгоритм Крускала
int algorithm_k(vector<rib>& ribs, int n) {
    sort(ribs.begin(), ribs.end(), compareribs);

    vector<int> parent(n + 1);
    vector<int> rank(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    int minWeight = 0;
    for (const rib& rib : ribs) {
        if (find(rib.u, parent) != find(rib.v, parent)) {
            unite(rib.u, rib.v, parent, rank);
            minWeight += rib.weight;
        }
    }

    return minWeight;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<rib> ribs(m);
    for (int i = 0; i < m; i++) {
        cin >> ribs[i].u >> ribs[i].v >> ribs[i].weight;
    }

    int minWeight = algorithm_k(ribs, n);
    cout << minWeight << "\n";

    return 0;
}

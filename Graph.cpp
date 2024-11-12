//Фукнціонал для взаємодії з графом, (введення/виведення)
// та знаходження і виведення Ейлерового шляху
#include "Graph.h"
using namespace std;


// Функція для виведення графа
void Graph::printGraph(const vector<vector<int>>& e, int n) {
    cout << "Дані графу.\n";
    cout << "Кількість вершин: " << n << endl;
    cout << "Кількість ребер: " << e.size()<< endl;
    cout << "Ребра:\n";
    for (const auto& edge : e) {
        cout << "Вершина " << edge[0] << " - Вершина "
            << edge[1] << ": вага " << edge[2] << endl;
    }
}

//Функція для запису маршруту до файлу CPP_output.txt
void Graph::writePathToFile(const vector<vector<int>>& edges, const vector<pair<int, int>>& eulerPath) {
    ofstream outFile("CPP_output.txt");
    if (outFile.is_open()) {
        outFile << "Кількість вершин: " << V << "\n";
        outFile << "Кількість ребер: " << edges.size() << "\n";

        // Запис ребер
        outFile << "Ребра:\n";
        for (const auto& edge : edges) {
            outFile << edge[0] << " " << edge[1] << " " << edge[2] << "\n";
        }

        // Запис маршруту
        outFile << "Маршрут:\n";
        for (const auto& edge : eulerPath) {
            outFile << edge.first+1 << " " << edge.second+1 << "\n";
        }

        outFile.close();
    }
}

// Запис оновленого шлязу в CPP_extend.txt
void Graph::writeExtendedPathToFile(const vector<vector<int>>& edges,
    const vector<pair<int, int>>& newPath,
    const vector<pair<int, int>>& additionalEdges) {
    std::ofstream outFile("CPP_extend.txt");
    if (outFile.is_open()) {
        outFile << "Кількість вершин: " << V << "\n";
        outFile << "Кількість ребер: " << edges.size() << "\n";

        // Write edges in structured format
        outFile << "Ребра:\n";
        for (const auto& edge : edges) {
            outFile << edge[0] << " " << edge[1] << " " << edge[2] << "\n";
        }

        // Write additional edges that complete the Eulerian path
        outFile << "Повторне проходження ребер:\n";
        for (const auto& edge : additionalEdges) {
            outFile << edge.first << " " << edge.second << "\n";
        }

        // Write the new Eulerian path in structured format
        outFile << "Оновлений шлях:\n";
        for (const auto& edge : newPath) {
            outFile << edge.first << " " << edge.second << "\n";
        }

        outFile.close();
    }
}

// Метод getEulerPath створює Ейлерів шлях для графа.
vector<pair<int, int>> Graph::getEulerPath(const vector<pair<int, int>>& additionalEdges) {
    // Додаємо додаткові ребра в граф
    for (const auto& edge : additionalEdges) {
        addEdge(edge.first, edge.second);
    }

    // Знаходимо вершину з непарною степенем, якщо така є
    int u = 0;
    for (int i = 0; i < V; i++) {
        if (adj[i].size() & 1) {
            u = i;
            break;
        }
    }

    vector<pair<int, int>> eulerPath;
    getEulerPathUtil(u, eulerPath);  // Викликаємо допоміжну функцію для отримання шляху
    
    // Повертаємо Ейлеровий шлях
    return eulerPath;

}

// Допоміжний метод getEulerPathUtil для побудови Ейлерового шляху.
void Graph::getEulerPathUtil(int u, vector<pair<int, int>>& eulerPath) {
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;
        if (v != -1 && isValidNextEdge(u, v)) {
            eulerPath.push_back({ u, v });  // Додаємо пару (u, v) до шляху
            rmvEdge(u, v);
            getEulerPathUtil(v, eulerPath);  // Рекурсивно викликаємо для наступної вершини
        }
    }
}

// Метод printEulerTour виводить Ейлерів маршрут на екран.
void Graph::printEulerTour(const vector<pair<int, int>>& previousPath) {
    cout << "Оптимальний маршрут :\n";
    for (const auto& edge : previousPath) {
        cout << edge.first + 1 << "-" << edge.second + 1 << " ";  // Виводимо шлях, щоб перевірити, чи він зберігся
    }
    cout << endl;
}

// Метод printEulerExtend виводить оновлений Ейлерів шлях на екран.
void Graph::printEulerExtend(const vector<pair<int, int>>& previousPath,
    const vector<pair<int, int>>& additionalEdges,
    const vector<pair<int, int>>& newPath) {

    // Виведення попереднього шляху
    cout << "Попередній шлях:\n";
    for (const auto& edge : previousPath) {
        cout << edge.first + 1 << "-" << edge.second + 1 << " ";
    }
    cout << endl;

    // Виведення додаткових ребер
    cout << "Повторне проходження ребер:\n";
    for (const auto& edge : additionalEdges) {
        cout << edge.first + 1 << "-" << edge.second + 1 << " ";
    }
    cout << endl;

    // Виведення оновленого шляху
    cout << "Оновлений шлях:\n";
    for (const auto& edge : newPath) {
        cout << edge.first + 1 << "-" << edge.second + 1 << " ";
    }
    cout << endl;

    //треба записати результат у файл CPP_extend.txt
}

// Метод для обрахування загальної ваги ребер
int Graph::getTotalWeight(const vector<vector<int>>& edges) {
    int totalWeight = 0;
    for (const auto& edge : edges) {
        totalWeight += edge[2]; // The weight is the third element
    }
    return totalWeight;
}

// Функція для перевірки наявності ребра в графі
bool Graph::edgeExists(int u, int v) {
    for (auto& neighbor : adj[u]) {
        if (neighbor == v) return true;
    }
    return false;
}

// Функція для перевірки, чи можна вважати ребро u-v наступним ребром в Ейлеровому турі
bool Graph::isValidNextEdge(int u, int v)
{
    // Ребро u-v є допустимим у одному з наступних випадків:

    // 1) Якщо v є єдиною суміжною вершиною для u
    int count = 0; // Для зберігання кількості суміжних вершин
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
        if (*i != -1) // Перевіряємо, що вершина не була видалена (-1)
            count++;
    if (count == 1)
        return true;

    // 2) Якщо є кілька суміжних вершин, тоді u-v не є мостом
    // Виконаємо наступні кроки для перевірки, чи є u-v мостом:

    // 2.a) Рахуємо кількість вершин, досяжних від u
    bool* visited = new bool[V];
    memset(visited, false, V * sizeof(bool));
    int count1 = DFSCount(u, visited);

    // 2.b) Видаляємо ребро (u, v) та після цього рахуємо
    // кількість вершин, досяжних від u
    rmvEdge(u, v);
    memset(visited, false, V * sizeof(bool));
    int count2 = DFSCount(u, visited);

    // 2.c) Додаємо ребро назад до графа
    addEdge(u, v);

    delete[] visited;

    // 2.d) Якщо count1 більше, ніж count2, тоді ребро (u, v) є мостом
    return (count1 > count2) ? false : true;
}

//Функція для додавання ребер
void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// Функція для видалення ребра u-v з графа. Видаляє ребро шляхом заміни значення суміжної вершини на -1.
void Graph::rmvEdge(int u, int v)
{
    // Знаходимо v у списку суміжності u та замінюємо його на -1
    list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
    *iv = -1;

    // Знаходимо u у списку суміжності v та замінюємо його на -1
    list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
    *iu = -1;
}

// Функція на основі DFS для підрахунку кількості досяжних вершин з v
int Graph::DFSCount(int v, bool visited[])
{
    // Відмічаємо поточну вершину як відвідану
    visited[v] = true;
    int count = 1;

    // Рекурсивно обходимо всі вершини, суміжні з цією вершиною
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (*i != -1 && !visited[*i]) // Перевірка, що вершина існує та не відвідана
            count += DFSCount(*i, visited);

    return count;
}

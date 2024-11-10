//Фукнціонал для взаємодії з графом, (введення/виведення)
// та знаходження і виведення Ейлерового шляху
#include "Graph.h"
using namespace std;

// Функція для перетворення числових індексів у символи
char indexToChar(int index) {
    return 'A' + index; // Перетворює 0 в 'A', 1 в 'B', і т.д.
}

// Функція для зчитування графа від користувача
vector<vector<int>> inputGraph(int& n) {
    cout << "Введіть кількість вершин: ";
    cin >> n;
    int edges;
    cout << "Введіть кількість ребер: ";
    cin >> edges;

    vector<vector<int>> e;
    cout << "Введіть ребра у форматі 'початок кінець вага':\n";
    for (int i = 0; i < edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e.push_back({ u, v, w });
    }
    return e;
}

// Функція для виведення графа
void printGraph(const vector<vector<int>>& e, int n) {
    cout << "Дані графу.\n";
    cout << "Кількість вершин: " << n << endl;
    cout << "Ребра:\n";
    for (const auto& edge : e) {
        cout << "Вершина " << indexToChar(edge[0] - 1) << " - Вершина "
            << indexToChar(edge[1] - 1) << ": вага " << edge[2] << endl;
    }
}


// Функція для використання шаблонних даних 1
vector<vector<int>> getTemplateData1(int& n) {
    n = 5; // Кількість точок
    return {
        {1, 2, 100}, // A - B: 100
        {1, 3, 150}, // A - C: 150
        {2, 3, 120}, // B - C: 120
        {2, 4, 200}, // B - D: 200
        {3, 4, 180}, // C - D: 180
        {3, 5, 160}, // C - E: 160
        {4, 5, 140}  // D - E: 140
    };
}

// Функція для використання шаблонних даних 2
vector<vector<int>> getTemplateData2(int& n) {
    n = 13; // Кількість точок
    return {
        {1, 2, 1300}, // A - B: 1300
        {1, 10, 550}, // A - J: 550
        {2, 3, 350},  // B - C: 350
        {3, 4, 150},  // C - D: 150
        {3, 11, 500}, // C - K: 500
        {4, 5, 500},  // D - E: 500
        {4, 12, 350}, // D - L: 350
        {5, 6, 350},  // E - F: 350
        {6, 7, 350},  // F - G: 350
        {6, 13, 240}, // F - M: 240
        {7, 8, 260},  // G - H: 260
        {8, 9, 490},  // H - I: 490
        {8, 13, 350}, // H - M: 350
        {9, 10, 260}, // I - J: 260
        {9, 11, 350}, // I - K: 350
        {11, 12, 150},// K - L: 150
        {12, 13, 210} // L - M: 210
    };
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
    cout << "Ейлеровий маршрут :\n";
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
    cout << "Додаткові ребра для доповнення:\n";
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

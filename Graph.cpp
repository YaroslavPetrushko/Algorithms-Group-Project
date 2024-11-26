//Функціонал для взаємодії з графом, (введення/виведення)
// та знаходження і виведення Ейлерового шляху
#include "Graph.h"
using namespace std;

vector<vector<int>> Graph::renumberGraph(const vector<vector<int>>& edges) {
    vertexMapping.clear();
    reverseVertexMapping.clear();

    // Перевірка, чи є послідовність вершин цільною
    set<int> uniqueVertices;
    for (const auto& edge : edges) {
        uniqueVertices.insert(edge[0]);
        uniqueVertices.insert(edge[1]);
    }

    int minVertex = *uniqueVertices.begin();
    int maxVertex = *uniqueVertices.rbegin();

    // Якщо послідовність не має розривів, нічого не змінюємо
    if (uniqueVertices.size() == (maxVertex - minVertex + 1) && minVertex == 0) {
        this->V = maxVertex + 1;
        return edges; // Повертаємо вихідні ребра без змін
    }

    // Інакше виконуємо перенумерацію
    int currentIndex = 1;
    for (int vertex : uniqueVertices) {
        vertexMapping[vertex] = currentIndex;
        reverseVertexMapping[currentIndex] = vertex;
        currentIndex++;
    }

    // Створення нового списку ребер із перенумерованими вершинами
    vector<vector<int>> renumberedEdges;
    for (const auto& edge : edges) {
        if (vertexMapping.find(edge[0]) == vertexMapping.end() ||
            vertexMapping.find(edge[1]) == vertexMapping.end()) {
            throw std::runtime_error("Invalid edge: vertex not found in mapping");
        }

        renumberedEdges.push_back({
            vertexMapping[edge[0]],
            vertexMapping[edge[1]],
            edge[2] // Вага ребра залишається незмінною
            });
    }

    // Оновлення кількості вершин у графі
    this->V = currentIndex-1;

    return renumberedEdges;
}

// Функція для конвертації Ейлерового шляху відповідно до введених даних
vector<pair<int, int>> Graph::revertEulerPath(const vector<pair<int, int>>& eulerPath) {
    vector<pair<int, int>> revertedPath;

    for (const auto& edge : eulerPath) {
        revertedPath.push_back({
            reverseVertexMapping[edge.first+1],  // Повертаємо до оригінальних вершин
            reverseVertexMapping[edge.second+1]  // Повертаємо до оригінальних вершин
            });
    }

    return revertedPath;
}

//// Функція для ручного введення графу
//pair<int, vector<vector<int>>> Graph::inputGraph(int& n) {
//    cout << "Введіть кількість точок: ";
//    cin >> n;
//    int edges;
//    cout << "Введіть кількість вулиць: ";
//    cin >> edges;
//    vector<vector<int>> e;
//    cout << "Введіть дані графу у форматі \"Вершина1 Вершина2 Вага_ребра\":\n";
//    for (int i = 0; i < edges; ++i) {
//        int u, v, w;
//        cin >> u >> v >> w;
//
//        if ( u < 0 || v < 0) {
//            throw std::invalid_argument("Введено недійсну вершину.");
//        }
//
//        e.push_back({ u, v, w });
//    }
//    return { n,e };
//}

// Функція для виведення графа
void Graph::printGraph(const vector<vector<int>>& e, int n) {
    cout << "Дані графу.\nПроходження поштоматів Нової Пошти в місті Суми\n";
    cout << "Кількість відділень: " << n << endl;
    cout << "Кількість вулиць: " << e.size()<< endl;
    cout << "Вулиці для проходження:\n";

    //Вирівнювання тексту
    cout << left;  
    cout << setw(20) << "Відділення №"
        << setw(20) << "Відділення №"
        << "Довжина" << endl;

    for (const auto& edge : e) {
        cout << setw(20) << edge[0]
            << setw(20) << edge[1]
            << edge[2] << endl;
    }
}

//Функція для запису маршруту до файлу CPP_output.txt
void Graph::writePathToFile(const vector<vector<int>>& edges, const vector<pair<int, int>>& eulerPath, string filename) {
    
    // Перевірка наявності ".txt" на кінці імені файлу
    if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".txt") {
        filename = filename.substr(0, filename.size() - 4);  // Видалення ".txt"
    }

    // Додавання префіксу "_output" і розширення ".txt"
    filename += "_output.txt";

    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "Кількість відділень: " << V << "\n";
        outFile << "Кількість вулиць: " << edges.size() << "\n";

        // Запис ребер
        outFile << "Вулиці для проходження:\n";
        for (const auto& edge : edges) {
            outFile << edge[0] << " " << edge[1] << " " << edge[2] << "\n";
        }

        // Запис маршруту
        outFile << "Оптимальний маршрут:\n";
        for (const auto& edge : eulerPath) {
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
void Graph::printEulerTour(const vector<pair<int, int>>& path) {
    cout << "Оптимальний маршрут між відділеннями :\n";
    for (const auto& edge : path) {
        cout << edge.first << "-" << edge.second << " ";  // Виводимо шлях, щоб перевірити, чи він зберігся
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

Graph::Graph(int V)
{
        this->V = V;
        adj = new list<int>[V];
}

Graph::~Graph()
{
    delete[] adj;
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
    // Знаходимо v у списку суміжності u
    list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
    if (iv != adj[u].end()) *iv = -1; // Якщо знайдено, видаляємо

    // Знаходимо u у списку суміжності v
    list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
    if (iu != adj[v].end()) *iu = -1; // Якщо знайдено, видаляємо
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

//Функціонал для взаємодії з графом
// та знаходження і виведення Ейлерового шляху
#include "Graph.h"
using namespace std;

//Функція для перенумерації вершин графу, (тобто з "1,3,24" в "1,2,3")
pair<int, vector<vector<int>>> Graph::renumberGraph(const vector<vector<int>>& edges, int startPoint) {
    //Очищення мапи перед зміною вершин
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

        return { startPoint, edges }; // Повертаємо вихідні дані без змін
    }

    // Інакше виконуємо перенумерацію
    int currentIndex = 1;
    for (int vertex : uniqueVertices) {
        vertexMapping[vertex] = currentIndex;
        reverseVertexMapping[currentIndex] = vertex;
        currentIndex++;
    }

    // Перенумеровуємо стартову точку
    int renumberedStartPoint = vertexMapping[startPoint];

    // Створення нового списку ребер із перенумерованими вершинами
    vector<vector<int>> renumberedEdges;
    for (const auto& edge : edges) {
        if (vertexMapping.find(edge[0]) == vertexMapping.end() ||
            vertexMapping.find(edge[1]) == vertexMapping.end()) {
            cerr << "Помилка: Невірне ребро, вершина не знайдена у відображенні.\n";
            return {};  // Повертаємо порожній граф
        }

        if (edge.size() < 3 || edge[2] < 0) {
            cerr << "Помилка: Невірна вага ребра.\n";
            return {};  // Повертаємо порожній граф
        }

        renumberedEdges.push_back({
            vertexMapping[edge[0]],
            vertexMapping[edge[1]],
            edge[2] // Вага ребра залишається незмінною
            });
    }

    // Оновлення кількості вершин у графі
    this->V = currentIndex - 1;

    return { renumberedStartPoint, renumberedEdges };
}

// Функція для конвертації Ейлерового шляху відповідно до введених даних
vector<pair<int, int>> Graph::revertEulerPath(const vector<pair<int, int>>& eulerPath) {
    vector<pair<int, int>> revertedPath;

    for (const auto& edge : eulerPath) {
        revertedPath.push_back({
            reverseVertexMapping[edge.first],  // Повертаємо до оригінальних вершин
            reverseVertexMapping[edge.second]  // Повертаємо до оригінальних вершин
            });
    }

    return revertedPath;
}

// Функція для виведення графа в консоль
void Graph::printGraph(const vector<vector<int>>& e, int n, int startPoint) {
    cout << "Дані графу.\nПроходження поштоматів Нової Пошти в місті Суми.\n";
    cout << "Кількість відділень: " << n << endl;
    cout << "Кількість вулиць: " << e.size()<< endl;
    cout << "Початкова точка: " << startPoint << endl;
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

//Функція для запису результатів до текстового файлу
void Graph::writePathToFile(const vector<vector<int>>& edges, const vector<pair<int, int>>& eulerPath,int weight,int startPoint, string filename) {
    
    // Перевірка наявності ".txt" на кінці імені файлу
    if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".txt") {
        filename = filename.substr(0, filename.size() - 4);  // Видалення ".txt"
    }

    // Додавання закінчення "_output.txt" до назви файлу
    filename += "_output.txt";

    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "Кількість відділень: " << V << "\n";
        outFile << "Кількість вулиць: " << edges.size() << "\n";
        outFile << "Початкова точка: " << startPoint << endl;

        // Запис ребер
        outFile << "Вулиці для проходження:\n";
        for (const auto& edge : edges) {
            outFile << edge[0] << " " << edge[1] << " " << edge[2] << "\n";
        }

        outFile << "Найменша довжина маршруту: " <<weight<< "\n";

        // Запис маршруту
        outFile << "Оптимальний маршрут:\n";
        for (const auto& edge : eulerPath) {
            outFile << edge.first << " " << edge.second << "\n";
        }

        outFile.close();
    }
}

// Метод, що створює Ейлерів шлях для графа
vector<pair<int, int>> Graph::getEulerPath(const vector<pair<int, int>>& additionalEdges, int startPoint) {
    // Додаємо додаткові ребра в граф
    for (const auto& edge : additionalEdges) {
        addEdge(edge.first, edge.second);
    }

    // Перевірка на існування стартової точки
    if (startPoint-1 < 0 || startPoint >= V) {
        cerr << "Помилка: Стартова точка " << startPoint << " не існує у графі." << endl;
        return {};  // Повертаємо порожній шлях, щоб уникнути завершення
    }

    if (adj[startPoint].empty()) {
        cerr << "Помилка: Стартова точка " << startPoint << " не має вихідних ребер." << endl;
        return {};  // Повертаємо порожній шлях
    }

    // Додаємо ребра до результатуючого шляху
    vector<pair<int, int>> eulerPath;

    getEulerPathUtil(startPoint, eulerPath);  // Викликаємо допоміжну функцію для отримання шляху

    // Якщо знайдений шлях не починається з startPoint, змінюємо порядок
    if (!eulerPath.empty() && eulerPath.front().first != startPoint) {
        // Знаходимо перше ребро, яке починається з startPoint
        auto it = find_if(eulerPath.begin(), eulerPath.end(), [&](const pair<int, int>& edge) {
            return edge.first == startPoint;
        });

        if (it != eulerPath.end()) {
            // Переміщаємо знайдене ребро в початок шляху
            rotate(eulerPath.begin(), it, eulerPath.end());
        }
    }

    // Перевіряємо, чи шлях завершується на startPoint
    if (!eulerPath.empty() && eulerPath.back().second != startPoint) {
        // Якщо останнє ребро не завершується на startPoint, додаємо його
        eulerPath.push_back({ eulerPath.back().second, startPoint });
    }

    // Якщо шлях пустий, повертаємо порожній список
    if (eulerPath.empty()) {
        cerr << "Помилка: Ейлерів шлях не знайдено." << endl;
    }

    return eulerPath;
}

// Допоміжний метод getEulerPathUtil для побудови Ейлерового шляху.
void Graph::getEulerPathUtil(int u, vector<pair<int, int>>& eulerPath) {
    //Перевірка чи входить вершина в список вершин графу
    if (u < 0 || u >= V) {
        cerr << "Індекс вершини " << u + 1 << " виходить за межі графа." << endl;
        return;
    }

    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i;
        if (v != -1 && isValidNextEdge(u, v)) {
            eulerPath.push_back({ u + 1, v + 1 });  // Додаємо пару (u, v), збільшуючи індекси на 1
            rmvEdge(u, v);
            getEulerPathUtil(v, eulerPath);  // Рекурсивно викликаємо для наступної вершини
        }
    }
}

// Функція що виводить Ейлерів маршрут на екран
void Graph::printEulerTour(const vector<pair<int, int>>& path) {
    cout << "Оптимальний маршрут:\n";
    for (const auto& edge : path) {
        cout << edge.first << "-" << edge.second << " ";  // Виводимо шлях, щоб перевірити, чи він зберігся
    }
    cout << endl;
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

//Конструктор графу
Graph::Graph(int V)
{
        this->V = V;
        adj = new list<int>[V];
}

//Деконструктор графу
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

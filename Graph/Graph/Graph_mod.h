//Бусыгина Татьяна, ИВТ-22

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

/// <summary>
/// Шаблонный ласс взвешенного неориентированного графа
/// </summary>
template <typename Type>
class Graph {
private:
    vector<Type> vertices; //список вершин
    vector<vector<int>> adjacency_matrix; //матрица смежности


    /// <summary>
    /// Обход графа в глубину (DFS)
    /// Сложность O(1) - лучший, O(n + m) - средний и худший, где n - кол-во вершин, m - кол-во ребер
    /// </summary>
    /// <param name="startVertex">Вершина, с которой мы начинаем обход</param>
    // Обход в глубину (DFS)
    void DFS(int start, vector<bool>& visited) {
        visited[start] = true;
        cout << vertices[start] << " ";
        for (int i = 0; i < vertices.size(); ++i) {
            if (adjacency_matrix[start][i] != 0 && !visited[i]) {
                DFS(i, visited);
            }
        }
    }

public:

    //Конструктор
    Graph() {}

    /// <summary>
    /// Добавление вершины
    /// Бросается исключение, если вершина существует
    /// Сложность O(1) - лучший, O(n^2) - худший и средний
    /// </summary>
    /// <param name="vertex"></param>
    void insertVertex(const Type& v) {
        if (findVertex(v) != -1) {
            throw out_of_range("Вершина уже существует в графе.");
        }

        vertices.push_back(v);
        int size = vertices.size() + 1;
        cout << "Вершина " << v << " добавлена." << endl;

        if (adjacency_matrix.empty()) {
            adjacency_matrix.resize(size, vector<int>(size, 0));
        }
        else {
            for (auto& row : adjacency_matrix) {
                row.resize(size, 0);
            }
            adjacency_matrix.resize(size, vector<int>(size, 0));
        }
    }

    /// <summary>
    /// Поиск вершины. Сложность O(1) - лучший, O(n) - средний и худший
    /// </summary>
    /// <param name="vertex">значение вершины, которую нужно найти</param>
    /// <returns>Индекс необходимой вершины, -1 в случае если вершина не найдена</returns>
    int findVertex(const Type& vertex) {
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i] == vertex) {
                return i;
            }
        }
        return -1;
    }

    /// <summary>
    /// Добавление ребра и его веса
    /// Бросается исключение, если вершины не существует 
    /// Сложность О(1) - средний, лучший, худший
    /// </summary>
    /// <param name="v1">Первая вершина</param>
    /// <param name="v2">Вторая вершина</param>
    /// <param name="weight">Вес ребра</param>
    void insertEdge(const Type& v1, const Type& v2, int weight) {
        int position1 = findVertex(v1);
        int position2 = findVertex(v2);

        if (position1 != -1 || position2 != -1) {
            adjacency_matrix[position1][position2] = weight;
            adjacency_matrix[position2][position1] = weight;
            cout << "Ребро между " << vertices[position1] << " и " << vertices[position2] << " добавлено с весом " << weight << "." << endl;
        }
        else {
            throw out_of_range("Такой вершины не существует");
        }
    }

    
    /// <summary>
    /// Удаление вершины
    /// Сложность О(n) - лучший, O(n^2) - худший и средний
    /// Бросается исключение, если такой вершины не существует
    /// </summary>
    /// <param name="v">Вершина, которую нужно удалить</param>
    void deleteVertex(const Type& v) {
        int position = findVertex(v);
        if (position != -1) {
            vertices.erase(vertices.begin() + position); //Функция erase() предназначена для удаления символов из строки. Она принимает начальный индекс удаления и количество удаляемых символов.
            adjacency_matrix.erase(adjacency_matrix.begin() + position);
            for (auto& row : adjacency_matrix) {
                row.erase(row.begin() + position);
            }
            cout << "Вершина удалена" << endl;
        }
        else {
            throw out_of_range("Такой вершины не существует");
        }
    }

    /// <summary>
    /// Удаление ребра
    /// Сложность O(n) - лучший, средний и худший
    /// Бросается исключение, если такой вершины не существует
    /// </summary>
    /// <param name="v1">Первая вершина</param>
    /// <param name="v2">Вторая вершина</param>
    void deleteEdge(const Type& v1, const Type& v2) {
        int position1 = findVertex(v1);
        int position2 = findVertex(v2);
        if (position1 != -1 || position2 != -1) {
            adjacency_matrix[v1][v2] = 0;
            adjacency_matrix[v2][v1] = 0;
            cout << "Ребро между " << vertices[v1] << " и " << vertices[v2] << " удалено." << endl;
        }
        else {
            throw out_of_range("Такой вершины не существует");
        }
    }

    /// <summary>
    /// Получение смежных вершин
    /// Сложность O(n) - лучший, средний и худший
    /// Бросается исключение, если такой вершины не существует
    /// </summary>
    /// <param name="v">Вершина, соседей которой мы хотим найти</param>
    /// <returns>Вектор с вершинами-соседями</returns>
    vector<Type> getNeighbors(const Type& v) {
        int position = findVertex(v);
        if (position != -1) {
            vector<Type> neighbors;
            for (int i = 0; i < vertices.size(); ++i) {
                if (adjacency_matrix[position][i] != 0) {
                    neighbors.push_back(vertices[i]);
                }
            }
        }
        else {
             throw out_of_range("Такой вершины не существует");
        }
    }

    /// <summary>
    /// Получение веса ребра между соседними вершинами
    /// Сложность O(n) - лучший, средний и худший
    /// Бросается исключение, если такой вершины не существует
    /// </summary>
    /// <param name="v1">Первая вершина</param>
    /// <param name="v2">Вторая вершина</param>
    /// <returns>Вес ребра между двумя заданными вершинами</returns>
    int getWeight(const Type& v1, const Type& v2) {
        int position1 = findVertex(v1);
        int position2 = findVertex(v2);
        if (position1 != -1 || position2 != -1) {
            return adjacency_matrix[v1][v2];
        }
        else {
            throw out_of_range("Такой вершины не существует");
            return 0;
        }  
    }

    /// <summary>
    /// Запуск обхода в глубину
    /// Бросается исключение, если такой вершины не существует
    /// </summary>
    /// <param name="start">Вершина, с коротой начинаем обход</param>
    void depthFirstSearch(const Type& value) {
        int start = findVertex(value);
        if (start == -1) {
            throw out_of_range("Такой вершины не существует");
        }
        vector<bool> visited(vertices.size(), false);
        cout << "DFS обход: ";
        DFS(start, visited);
        cout << endl;
    }


    /// <summary>
    /// Обход в ширину 
    /// Сложность О(1) - лучший, O(m + n) - средний, худший. Где n - кол-во вершин, m - кол-во ребер
    /// </summary>
    /// <param name="start">Вершина, с коротой начинаем обход</param>
    void BFS(const Type& start) {
        int position = findVertex(start);
        vector<bool> visited(vertices.size(), false);
        queue<int> q;
        visited[position] = true;
        q.push(position);

        cout << "BFS обход: ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << vertices[v] << " ";

            for (int i = 0; i < vertices.size(); ++i) {
                //Если существует ребро между текущей вершиной v и соседней вершиной i и эта соседняя вершина ещё не была посещена
                if (adjacency_matrix[v][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    /// <summary>
    /// Алгоритм Дейкстры для поиска кратчайшего пути
    /// Сложность О(1) - лучший, O(n^2 + n) - средний и худший, где n - кол-во ребер
    /// </summary>
    /// <param name="start">Начальная вершина</param>
    void dijkstra(const Type& start) {
        int position = findVertex(start);

        //инициализируем вектор расстояний до всех вершин бесконечностью
        vector<int> dist(vertices.size(), numeric_limits<int>::max()); //это функция, которая возвращает максимальное значение, 
        //которое может принимать переменная типа int (2147483647)

        vector<bool> visited(vertices.size(), false);
 
        dist[position] = 0; //расстояние до стартовой вершины

        for (int i = 0; i < vertices.size() - 1; ++i) {
            int minDist = numeric_limits<int>::max(); //минимальное расстояние
            int u = -1; //индекс текущей минимальной вершины

            //поиск ближайшей непосещенной вершины
            for (int j = 0; j < vertices.size(); ++j) {
                if (!visited[j] && dist[j] <= minDist) {
                    minDist = dist[j]; //обновляем минимальное расстояние
                    u = j; //запоминаем индекс вершины
                }
            }

            visited[u] = true;

            //обновление расстояний до соседних вершин
            //После нахождения текущей вершины u, мы обновляем расстояния до всех соседних вершин v, если найденный путь через u 
            //короче, чем ранее известное расстояние до v
            for (int v = 0; v < vertices.size(); ++v) {
                //gроверяем, что v не посещена и есть ребро между u и v
                if (!visited[v] && adjacency_matrix[u][v] != 0 && dist[u] != numeric_limits<int>::max() &&
                    dist[u] + adjacency_matrix[u][v] < dist[v]) {
                    //обновляем кратчайшее расстояние до v
                    dist[v] = dist[u] + adjacency_matrix[u][v];
                }
            }
        }

        cout << "Кратчайшие расстояния от вершины " << vertices[position] << ":" << endl;
        for (int i = 0; i < vertices.size(); ++i) {
            cout << vertices[i] << ": " << dist[i] << endl;
        }
    }

};
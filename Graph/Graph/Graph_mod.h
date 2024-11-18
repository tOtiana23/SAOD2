//�������� �������, ���-22

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>

using namespace std;

/// <summary>
/// ��������� ���� ����������� ������������������ �����
/// </summary>
template <typename Type>
class Graph {
private:
    vector<Type> vertices; //������ ������
    vector<vector<int>> adjacency_matrix; //������� ���������


    /// <summary>
    /// ����� ����� � ������� (DFS)
    /// ��������� O(1) - ������, O(n + m) - ������� � ������, ��� n - ���-�� ������, m - ���-�� �����
    /// </summary>
    /// <param name="startVertex">�������, � ������� �� �������� �����</param>
    // ����� � ������� (DFS)
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

    //�����������
    Graph() {}

    /// <summary>
    /// ���������� �������
    /// ��������� ����������, ���� ������� ����������
    /// ��������� O(1) - ������, O(n^2) - ������ � �������
    /// </summary>
    /// <param name="vertex"></param>
    void insertVertex(const Type& v) {
        if (findVertex(v) != -1) {
            throw out_of_range("������� ��� ���������� � �����.");
        }

        vertices.push_back(v);
        int size = vertices.size() + 1;
        cout << "������� " << v << " ���������." << endl;

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
    /// ����� �������. ��������� O(1) - ������, O(n) - ������� � ������
    /// </summary>
    /// <param name="vertex">�������� �������, ������� ����� �����</param>
    /// <returns>������ ����������� �������, -1 � ������ ���� ������� �� �������</returns>
    int findVertex(const Type& vertex) {
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i] == vertex) {
                return i;
            }
        }
        return -1;
    }

    /// <summary>
    /// ���������� ����� � ��� ����
    /// ��������� ����������, ���� ������� �� ���������� 
    /// ��������� �(1) - �������, ������, ������
    /// </summary>
    /// <param name="v1">������ �������</param>
    /// <param name="v2">������ �������</param>
    /// <param name="weight">��� �����</param>
    void insertEdge(const Type& v1, const Type& v2, int weight) {
        int position1 = findVertex(v1);
        int position2 = findVertex(v2);

        if (position1 != -1 || position2 != -1) {
            adjacency_matrix[position1][position2] = weight;
            adjacency_matrix[position2][position1] = weight;
            cout << "����� ����� " << vertices[position1] << " � " << vertices[position2] << " ��������� � ����� " << weight << "." << endl;
        }
        else {
            throw out_of_range("����� ������� �� ����������");
        }
    }

    
    /// <summary>
    /// �������� �������
    /// ��������� �(n) - ������, O(n^2) - ������ � �������
    /// ��������� ����������, ���� ����� ������� �� ����������
    /// </summary>
    /// <param name="v">�������, ������� ����� �������</param>
    void deleteVertex(const Type& v) {
        int position = findVertex(v);
        if (position != -1) {
            vertices.erase(vertices.begin() + position); //������� erase() ������������� ��� �������� �������� �� ������. ��� ��������� ��������� ������ �������� � ���������� ��������� ��������.
            adjacency_matrix.erase(adjacency_matrix.begin() + position);
            for (auto& row : adjacency_matrix) {
                row.erase(row.begin() + position);
            }
            cout << "������� �������" << endl;
        }
        else {
            throw out_of_range("����� ������� �� ����������");
        }
    }

    /// <summary>
    /// �������� �����
    /// ��������� O(n) - ������, ������� � ������
    /// ��������� ����������, ���� ����� ������� �� ����������
    /// </summary>
    /// <param name="v1">������ �������</param>
    /// <param name="v2">������ �������</param>
    void deleteEdge(const Type& v1, const Type& v2) {
        int position1 = findVertex(v1);
        int position2 = findVertex(v2);
        if (position1 != -1 || position2 != -1) {
            adjacency_matrix[v1][v2] = 0;
            adjacency_matrix[v2][v1] = 0;
            cout << "����� ����� " << vertices[v1] << " � " << vertices[v2] << " �������." << endl;
        }
        else {
            throw out_of_range("����� ������� �� ����������");
        }
    }

    /// <summary>
    /// ��������� ������� ������
    /// ��������� O(n) - ������, ������� � ������
    /// ��������� ����������, ���� ����� ������� �� ����������
    /// </summary>
    /// <param name="v">�������, ������� ������� �� ����� �����</param>
    /// <returns>������ � ���������-��������</returns>
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
             throw out_of_range("����� ������� �� ����������");
        }
    }

    /// <summary>
    /// ��������� ���� ����� ����� ��������� ���������
    /// ��������� O(n) - ������, ������� � ������
    /// ��������� ����������, ���� ����� ������� �� ����������
    /// </summary>
    /// <param name="v1">������ �������</param>
    /// <param name="v2">������ �������</param>
    /// <returns>��� ����� ����� ����� ��������� ���������</returns>
    int getWeight(const Type& v1, const Type& v2) {
        int position1 = findVertex(v1);
        int position2 = findVertex(v2);
        if (position1 != -1 || position2 != -1) {
            return adjacency_matrix[v1][v2];
        }
        else {
            throw out_of_range("����� ������� �� ����������");
            return 0;
        }  
    }

    /// <summary>
    /// ������ ������ � �������
    /// ��������� ����������, ���� ����� ������� �� ����������
    /// </summary>
    /// <param name="start">�������, � ������� �������� �����</param>
    void depthFirstSearch(const Type& value) {
        int start = findVertex(value);
        if (start == -1) {
            throw out_of_range("����� ������� �� ����������");
        }
        vector<bool> visited(vertices.size(), false);
        cout << "DFS �����: ";
        DFS(start, visited);
        cout << endl;
    }


    /// <summary>
    /// ����� � ������ 
    /// ��������� �(1) - ������, O(m + n) - �������, ������. ��� n - ���-�� ������, m - ���-�� �����
    /// </summary>
    /// <param name="start">�������, � ������� �������� �����</param>
    void BFS(const Type& start) {
        int position = findVertex(start);
        vector<bool> visited(vertices.size(), false);
        queue<int> q;
        visited[position] = true;
        q.push(position);

        cout << "BFS �����: ";
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << vertices[v] << " ";

            for (int i = 0; i < vertices.size(); ++i) {
                //���� ���������� ����� ����� ������� �������� v � �������� �������� i � ��� �������� ������� ��� �� ���� ��������
                if (adjacency_matrix[v][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        cout << endl;
    }

    /// <summary>
    /// �������� �������� ��� ������ ����������� ����
    /// ��������� �(1) - ������, O(n^2 + n) - ������� � ������, ��� n - ���-�� �����
    /// </summary>
    /// <param name="start">��������� �������</param>
    void dijkstra(const Type& start) {
        int position = findVertex(start);

        //�������������� ������ ���������� �� ���� ������ ��������������
        vector<int> dist(vertices.size(), numeric_limits<int>::max()); //��� �������, ������� ���������� ������������ ��������, 
        //������� ����� ��������� ���������� ���� int (2147483647)

        vector<bool> visited(vertices.size(), false);
 
        dist[position] = 0; //���������� �� ��������� �������

        for (int i = 0; i < vertices.size() - 1; ++i) {
            int minDist = numeric_limits<int>::max(); //����������� ����������
            int u = -1; //������ ������� ����������� �������

            //����� ��������� ������������ �������
            for (int j = 0; j < vertices.size(); ++j) {
                if (!visited[j] && dist[j] <= minDist) {
                    minDist = dist[j]; //��������� ����������� ����������
                    u = j; //���������� ������ �������
                }
            }

            visited[u] = true;

            //���������� ���������� �� �������� ������
            //����� ���������� ������� ������� u, �� ��������� ���������� �� ���� �������� ������ v, ���� ��������� ���� ����� u 
            //������, ��� ����� ��������� ���������� �� v
            for (int v = 0; v < vertices.size(); ++v) {
                //g��������, ��� v �� �������� � ���� ����� ����� u � v
                if (!visited[v] && adjacency_matrix[u][v] != 0 && dist[u] != numeric_limits<int>::max() &&
                    dist[u] + adjacency_matrix[u][v] < dist[v]) {
                    //��������� ���������� ���������� �� v
                    dist[v] = dist[u] + adjacency_matrix[u][v];
                }
            }
        }

        cout << "���������� ���������� �� ������� " << vertices[position] << ":" << endl;
        for (int i = 0; i < vertices.size(); ++i) {
            cout << vertices[i] << ": " << dist[i] << endl;
        }
    }

};
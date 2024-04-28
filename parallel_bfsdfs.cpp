#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

void parallelBFS(int start, const vector<vector<int>>& graph) {
    auto start_time = high_resolution_clock::now(); // Start timing

    int n = graph.size();  // Number of vertices
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
	cout<<u<<" ";
	#pragma omp critical
        q.pop();

        #pragma omp parallel for
        for (int j = 0; j < graph[u].size(); ++j) {
            int v = graph[u][j];
            if (!visited[v]) {
                #pragma omp critical
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    auto end_time = high_resolution_clock::now(); // End timing
    auto duration = duration_cast<microseconds>(end_time - start_time).count(); // Calculate duration in microseconds
    cout << "Parallel BFS Time: " << duration << " microseconds" << endl; // Output duration
}


void parallelDFS(int start, const vector<vector<int>>& graph) {
    auto start_time = high_resolution_clock::now(); // Start timing

    int n = graph.size();  // Number of vertices
    vector<bool> visited(n, false);
    stack<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.top();
	cout<<u<<" ";
	#pragma omp critical
        q.pop();

        #pragma omp parallel for
        for (int j = 0; j < graph[u].size(); ++j) {
            int v = graph[u][j];
            if (!visited[v]) {
                #pragma omp critical
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    auto end_time = high_resolution_clock::now(); // End timing
    auto duration = duration_cast<microseconds>(end_time - start_time).count(); // Calculate duration in microseconds
    cout << "Parallel DFS Time: " << duration << " microseconds" << endl; // Output duration
}

void sequentialBFS(int start, const vector<vector<int>>& graph) {
    auto start_time = high_resolution_clock::now(); // Start timing

    int n = graph.size();  // Number of vertices
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u<<" ";

        for (int j = 0; j < graph[u].size(); ++j) {
            int v = graph[u][j];
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    auto end_time = high_resolution_clock::now(); // End timing
    auto duration = duration_cast<microseconds>(end_time - start_time).count(); // Calculate duration in microseconds
    cout << "Sequential BFS Time: " << duration << " microseconds" << endl; // Output duration
}

void sequentialDFS(int start, const vector<vector<int>>& graph) {
    auto start_time = high_resolution_clock::now(); // Start timing

    int n = graph.size();  // Number of vertices
    vector<bool> visited(n, false);
    stack<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.top();
        q.pop();
        cout << u<<" ";

        for (int j = 0; j < graph[u].size(); ++j) {
            int v = graph[u][j];
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    auto end_time = high_resolution_clock::now(); // End timing
    auto duration = duration_cast<microseconds>(end_time - start_time).count(); // Calculate duration in microseconds
    cout << "Sequential DFS Time: " << duration << " microseconds" << endl; // Output duration
}

int main() {
    vector<vector<int>> graph = {
        {1, 2},   // Adjacency list of vertex 0
        {0, 3},   // Adjacency list of vertex 1
        {0, 4},   // Adjacency list of vertex 2
        {1},      // Adjacency list of vertex 3
        {2}       // Adjacency list of vertex 4
    };

    cout << "Running Parallel BFS:" << endl;
    parallelBFS(0, graph);

    cout << "\nRunning Parallel DFS:" << endl;
    parallelDFS(0, graph);

    cout << "\nRunning Sequential BFS:" << endl;
    sequentialBFS(0, graph);

    cout << "\nRunning Sequential DFS:" << endl;
    sequentialDFS(0, graph);

    return 0;
}

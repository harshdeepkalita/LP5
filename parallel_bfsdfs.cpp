#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

void parallelBFS(int start, const vector<vector<int>>& graph) {
    int n = graph.size();  // Number of vertices
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << "Visited " << u << " in BFS" << endl;

        #pragma omp parallel for
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                #pragma omp critical
                q.push(v);
            }
        }
    }
}

void parallelDFS(int start, const vector<vector<int>>& graph) {
    int n = graph.size();  // Number of vertices
    vector<bool> visited(n, false);
    stack<int> st;

    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (!visited[u]) {
            visited[u] = true;
            cout << "Visited " << u << " in DFS" << endl;

            #pragma omp parallel for
            for (int v : graph[u]) {
                if (!visited[v]) {
                    #pragma omp critical
                    st.push(v);
                }
            }
        }
    }
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

    return 0;
}

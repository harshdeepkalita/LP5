#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<omp.h>
using namespace std;


class UndirectonalGraph {
    int V;    // No. of vertices
    vector<vector<int>> adj;    // Adjacency Matrix
    public:
    
    UndirectonalGraph(int V) {
        this->V = V;
        for(int i=0;i<V;i++) {
            vector<int> row;
            for(int j=0;j<V;j++) {
                row.push_back(0);
            }
            adj.push_back(row);
        }
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    // Serial BFS traversal of the graph
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << "Visited " << u << " in BFS" << endl;

            for (int v = 0; v < V; v++) {
                if (adj[u][v] && !visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    // Parallel BFS traversal of the graph
    void BFS_parallel(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << "Visited " << u << " in BFS" << endl;

            #pragma omp parallel for
            for (int v = 0; v < V; v++) {
                if (adj[u][v] && !visited[v]) {
                    visited[v] = true;
                    #pragma omp critical
                    q.push(v);
                }
            }
        }
    }

    // Serial DFS traversal of the graph
    void DFS(int start) {
        vector<bool> visited(V, false);
        stack<int> st;

        st.push(start);

        while (!st.empty()) {
            int u = st.top();
            st.pop();

            if (!visited[u]) {
                visited[u] = true;
                cout << "Visited " << u << " in DFS" << endl;

                for (int v = 0; v < V; v++) {
                    if (adj[u][v] && !visited[v]) {
                        st.push(v);
                    }
                }
            }
        }
    }

    // Parallel DFS traversal of the graph
    void DFS_parallel(int start) {
        vector<bool> visited(V, false);
        stack<int> st;

        st.push(start);

        while (!st.empty()) {
            int u = st.top();
            st.pop();

            if (!visited[u]) {
                visited[u] = true;
                cout << "Visited " << u << " in DFS" << endl;

                #pragma omp parallel for
                for (int v = 0; v < V; v++) {
                    if (adj[u][v] && !visited[v]) {
                        #pragma omp critical
                        st.push(v);
                    }
                }
            }
        }
    }
};

int main()
{
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;
    
    UndirectonalGraph g(V);
    
    int u, v;
    cout << "Enter the edges (u v), if (u,v) is entered there is not need to enter (v,u) Enter -1 -1 to stop:" << endl;
    while (true) {
        cin >> u >> v;
        if (u == -1 && v == -1) {
            break;
        }
        g.addEdge(u, v);
    }
    cout<<"Enter the starting vertex: ";
    int starting_vertex;
    cin>>starting_vertex;
    
    double start, end;

    // Serial BFS
    start = omp_get_wtime();
    g.BFS(starting_vertex);
    end = omp_get_wtime();
    cout << "Serial BFS Execution Time: " << end - start << " seconds" << endl;

    // Parallel BFS
    start = omp_get_wtime();
    g.BFS_parallel(starting_vertex);
    end = omp_get_wtime();
    cout << "Parallel BFS Execution Time: " << end - start << " seconds" << endl;

    // Serial DFS
    start = omp_get_wtime();
    g.DFS(starting_vertex);
    end = omp_get_wtime();
    cout << "Serial DFS Execution Time: " << end - start << " seconds" << endl;

    // Parallel DFS
    start = omp_get_wtime();
    g.DFS_parallel(starting_vertex);
    end = omp_get_wtime();
    cout << "Parallel DFS Execution Time: " << end - start << " seconds" << endl;

    // Serial BFS - Clock Cycles
    start = clock();
    g.BFS(starting_vertex);
    end = clock();
    double serial_bfs_clock_cycles = double(end - start) / CLOCKS_PER_SEC;
    cout << "Serial BFS Execution Time (Clock Cycles): " << serial_bfs_clock_cycles << " seconds" << endl;

    // Parallel BFS - Clock Cycles
    start = clock();
    g.BFS_parallel(starting_vertex);
    end = clock();
    double parallel_bfs_clock_cycles = double(end - start) / CLOCKS_PER_SEC;
    cout << "Parallel BFS Execution Time (Clock Cycles): " << parallel_bfs_clock_cycles << " seconds" << endl;

    // Serial DFS - Clock Cycles
    start = clock();
    g.DFS(starting_vertex);
    end = clock();
    double serial_dfs_clock_cycles = double(end - start) / CLOCKS_PER_SEC;
    cout << "Serial DFS Execution Time (Clock Cycles): " << serial_dfs_clock_cycles << " seconds" << endl;

    // Parallel DFS - Clock Cycles
    start = clock();
    g.DFS_parallel(starting_vertex);
    end = clock();
    double parallel_dfs_clock_cycles = double(end - start) / CLOCKS_PER_SEC;
    cout << "Parallel DFS Execution Time (Clock Cycles): " << parallel_dfs_clock_cycles << " seconds" << endl;
    
    return 0;
}
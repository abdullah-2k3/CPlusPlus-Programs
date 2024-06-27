#include <iostream>
#include <queue>

using namespace std;

class Graph {
    int V; // No. of vertices
    int **adj; // adjacency matrix
    bool isDirected; // 0 for undirected, 1 for directed
    bool* visited;
public:
    Graph(int n) {
        V = n;
        adj = new int*[V];
        visited = new bool[V];

        for (int i = 0; i < V; i++) {
            adj[i] = new int[V];
            visited[i] = 0;
        }

    }

    void TakeInput(int v, int w) {  // add an edge to the graph
        if (v == w)
            return;

        adj[v][w] = 1;
        adj[w][v] = 1;
    }
    void DFS(int start) {   // print the paths from start to every other vertex as generated by the DFS method

        visited[start] = true;
        int *row = adj[start];

        cout << start << " ";

        for (int i = 0; i < V; i++) {
            if (adj[start][i] != 0 && !visited[i])
                DFS(i);
        }

    }

    void BFS(int start) {   // print the paths from start to every other vertex using BFS method.
        queue<int> bfs_queue;
        for (int i = 0; i < V; i++) {
            visited[i] = false;
        }
        visited[start] = true;
        bfs_queue.push(start);

        while (!bfs_queue.empty()) {
            int val = bfs_queue.front();
            cout << val << " ";
            bfs_queue.pop();

            for (int i = 0; i < V; i++) {
                if (adj[start][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    bfs_queue.push(i);
                }
            }
        }


    }

    bool Is_Connected(int n) {  // returns true if graph is connected using DFS and BFS both


        return true;
    }

    bool isReachable(int u, int v) {    // Check and returns true if there is a path between any two given vertices.
        if (adj[u][v] == 1 || adj[v][u] == 1)
            return true;

        return false;
    }

    bool is_SC() {  //A directed graph is said to be strongly connected if every vertex is reachable from every other
                    //vertex. Returns true if it is strongly connected otherwise false?

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i == j)
                    continue;

                if (adj[i][j] != 1)
                    return false;
            }
        }

        return true;
    }

    bool isCylic() {

        for (int i = 0; i < V-1; i++) {
            if (adj[i][i+1] != 1)
            return false;
        }
        if (adj[V-1][0] != 1)
            return false;

        return true;
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {
            delete[] adj[i];
        }
        delete[] adj;
        adj = nullptr;
    }
};


int main () {


    Graph graph(4);

    graph.TakeInput(0, 1);
    graph.TakeInput(1, 3);
    graph.TakeInput(0, 2);
    graph.TakeInput(0, 7);
    graph.TakeInput(0, 5);

    cout << "Is Cyclic: "<< graph.isCylic() << endl;


    cout << "Depth First Search: ";
    graph.DFS(0);
    cout << "\n----------------------------\n";
    cout << "Breadth First Search: ";
    graph.BFS(0);

    return 0;
}

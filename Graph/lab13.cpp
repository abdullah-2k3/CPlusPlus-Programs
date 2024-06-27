#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <vector>

using namespace std;

struct Node {
	int destination;
	Node* next;
};

struct AdjList {
   Node *head;
   AdjList() {
        head = nullptr;
   }
};

struct NodeDistance {
    int shortest_node;
    int src_dist;
    int dst_dist;
};

class Graph {
	int v; // No. of nodes in the graph
	AdjList* array; //adjacency List array
    bool* visited;
public:
	Graph (int v) {
        this->v = v;
        array = new AdjList[v];
        visited = new bool[v];
        for (int i = 0; i < v; i++) {
            array[i].head = newAdjListNode(i);
            visited[i] = false;
        }
    }

	Node* newAdjListNode(int dest) {
	    Node* node = new Node();
	    node->destination = dest;
        node->next = nullptr;
        return node;
	}

    void addEdge(int src, int dest) {
        Node* newNode = newAdjListNode(dest);
        newNode->next = array[src].head->next;
        array[src].head->next = newNode;
    }

	void TakeInput(string file) {
        ifstream fin(file);
        string line;
        getline(fin, line); // discard the first line
        for (int i = 0; i < v; i++) {
            getline(fin, line);
            for (size_t j = 3; j < line.size(); j++) {
                int src, dest;
                if (line[j] == '1') {
                    src = (j - 3)/3;
                    dest = i;
                    addEdge(src, dest);

                }
            }

       }

	}


	void ExploreFunction(int start) {

        visited[start] = true;

        cout << start << " ";

        Node *curr = array[start].head;

        while (curr) {
            if (!visited[curr->destination])
                ExploreFunction(curr->destination);

            curr = curr->next;
        }

	}

    void display_graph() {

        for (int i = 0; i < v; i++) {
            Node* curr = array[i].head;
            while (curr) {
                cout << curr->destination<< "->";
                curr = curr->next;
            }
            cout << "\b\b   "<< endl;
        }

    }

	bool hasCycle() {
	    bool found;
	    for (int i = 0; i < v; i++) {
            Node* curr = array[i].head;
            found = false;
            while (curr) {
                if (i < v-1) {
                    if (curr->destination == i+1) {
                        found = true;
                        break;
                    }
                }
                else if (i == v-1) {
                    if (curr->destination == 0) {
                        found = true;
                        break;
                    }
                }
                curr = curr->next;
            }
            if (!found)
                return false;
	    }

        return true;
	}

	void BFS(int src) {

        for (int i = 0; i < v; i++)
            visited[i] = false;


        visited[src] = true;

        queue<int> q1;
        q1.push(src);

        while (!q1.empty()) {
            int curr = q1.front();
            q1.pop();

            cout << curr << " ";

            Node* tmp = array[curr].head;
            while (tmp) {
                if (!visited[tmp->destination]) {
                    visited[tmp->destination] = true;
                    q1.push(tmp->destination);
                }
                tmp = tmp->next;
            }
        }
        cout << endl;
	}

	int DFS_path(int src, int dst) {
        static bool found = false;
        static int path = -1;

        visited[src] = true;

        path++;

        if (src == dst) {
            found = true;
           return path;
        }

        Node *curr = array[src].head;

        while (curr && !found) {
            if (!visited[curr->destination])
                DFS_path(curr->destination, dst);

            curr = curr->next;
        }

        return path;
	}


	void DFS(int src) {

        for (int i = 0; i < v; i++)
            visited[i] = false;


        visited[src] = true;

        stack<int> s1;
        s1.push(src);

        while (!s1.empty()) {
            int curr = s1.top();
            s1.pop();

            cout << curr << " ";

            Node* tmp = array[curr].head;
            while (tmp) {
                if (!visited[tmp->destination]) {
                    visited[tmp->destination] = true;
                    s1.push(tmp->destination);
                }
                tmp = tmp->next;
            }
        }
        cout << endl;
	}


	int BFS_path(int src, int dst) {
        int path = -1;

        for (int i = 0; i < v; i++)
            visited[i] = false;


        visited[src] = true;

        queue<int> q1;
        q1.push(src);

        while (!q1.empty()) {

            path++;
            int curr;
            while (!q1.empty()) {
                curr = q1.front();
                q1.pop();

                if (curr == dst)
                    return path;
            }


            Node* tmp = array[curr].head;

            while (tmp) {
                if (!visited[tmp->destination]) {
                    visited[tmp->destination] = true;
                    q1.push(tmp->destination);
                }

                tmp = tmp->next;
            }
        }

        return -1;
	}

	NodeDistance shortest_path(int src, int dst) {

        vector<int> src_dist;
        vector<int> dst_dist;

        for (int i = 0; i < v; i++) {
            src_dist.push_back(BFS_path(src, i));
            dst_dist.push_back(BFS_path(dst, i));
        }

        vector<int> sum_dist;
        for (int i = 0; i < v; i++) {
            sum_dist.push_back(src_dist[i] + dst_dist[i]);
        }

        cout << "Sum distances: ";
        for (int i = 0; i < v; i++) {
            cout << i << "," << sum_dist[i] << "  ";
        }

        int min_path = sum_dist[0];
        cout << endl;
        for (int i = 0; i < v; i++) {
            if (sum_dist[i] < min_path)
                min_path = sum_dist[i];
        }

        int i;
        for (i = 0; i < v; i++) {
            if (sum_dist[i] == min_path)
                break;
        }

        NodeDistance node;

        node.shortest_node = i;
        node.src_dist = src_dist[i];
        node.dst_dist = dst_dist[i];

        return node;
	}

	~Graph() {
        delete[] array;
        array = nullptr;
	}
};



int main()
{
	Graph g(9); // Total 9 vertices in graph
	g.TakeInput("AdjacencyList.txt");




//	cout << "Explore Traversal\n";
//	g.ExploreFunction(0);
//	cout << endl << endl;
//
//	cout << "Depth First Traversal\n";
//	g.DFS(0);
//	cout << endl << endl;
//
//
//
//	cout << "Breadth First Traversal\n";
//	g.BFS(0);
//	cout << endl << endl;
//
//
//    int src = 1;
//    int dst = 5;
//
//	cout << "Path BFS: ";
//	for (int i = 0; i <= 8; i++)
//        cout << g.BFS_path(8, i) << " ";
//	cout << endl << endl;

    g.ExploreFunction(1);
    cout << "\n\n------------------------------------------\n\n";
    g.DFS(1);
    cout << endl << endl;

    g.display_graph();

    cout << endl << endl;

//    int src, dst;
//
//    cout << "Enter source: ";
//    cin >> src;
//    cout << "Enter Destination: ";
//    cin >> dst;

    //cout << "\n\nNearest Node between 1 and 5: ";
//    NodeDistance node;
//    node =  g.shortest_path(src, dst);
//
//    cout << "Nearest node between " << src << " and " << dst << ": " << node.shortest_node << endl;
//    cout << "Distance from " << src << ": " << node.src_dist << endl;
//    cout << "Distance from " << dst << ": " << node.dst_dist << endl;

	return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Node {
public:
    friend class Maze;
    int data;
    Node* up;
    Node* down;
    Node* left;
    Node* right;
    Node(int d) {
        data = d;
        up = down = left = right = nullptr;
    }

};


class Maze {
    Node* head;
    Node* present;
    int sum = 0;
    int rows = 0, cols = 0;
public:
    Maze() : head(nullptr){}
    vector<Node*> visited_nodes;

    void read (string filename) {
        ifstream fin (filename);

        string str;
        while (getline(fin, str)) {
            rows++;
        }

        for (int i = 0; i < str.length(); i++) {
            if (str[i] == ' ') {
                cols++;
            }
        }

        //cout << rows << " " << cols << endl;
        fin.close();

        fin.open(filename);
        char coma;
        int n;
        fin >> n;
        head = new Node(n);
        Node* curr = head;
        Node* tmp = head;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                fin >> coma;
                fin >> n;
                curr->right = new Node(n);
                curr->right->left = curr;
                curr = curr->right;
            }
            fin.ignore();
            fin >> n;
            tmp->down = new Node(n);
            tmp->down->up = tmp;
            curr = tmp->down;
            tmp = curr;
        }
        visited_nodes.push_back(head);
        fin.close();
    }

    void print() {
        Node* curr = head;
        Node* tmp = head;
        do {
            if (curr) {
                cout << curr->data << " -> ";
                curr = curr->right;
            }
            else {
                cout << "\b\b\b  "<< endl;
                curr = tmp->down;
                tmp = curr;
            }

        } while (tmp->right || tmp->down);
    }

    int sum_digit(int data) {
        int n = data;
        sum = 0;
        while (n != 0) {
            sum += n%10;
            n /= 10;
        }
        return sum;
    }

    int clue_row(int data) {
        return (sum_digit(data)%rows)+1;
    }

    int clue_column(int data) {
        int c = 0;
        int n = data;
        if (n == 0)
            return 1;
        while (n != 0) {
            c++;
            n /= 10;
        }
        return c;
    }

    Node* find_node(Node* &present) {
        int r = clue_row(present->data);
        int c = clue_column(present->data);
        Node* curr = head;
        for (int i = 0; i < r-1; i++) {
            curr = curr->down;
        }
        for (int i = 0; i < c-1; i++) {
            curr = curr->right;
        }
        present = curr;
        return curr;
    }

    bool visited() {
        cout << "\nTraversing Maze: ";
        for (unsigned int i = 0; i < visited_nodes.size()-1; i++) {
            cout << visited_nodes[i]->data << " ";
            if (visited_nodes[i] == visited_nodes.back())
                return true;
        }
        return false;
    }

    void elite_node() {
        do {
            present = visited_nodes.back();
            Node* tmp = present;
            if (find_node(present) == tmp) {
                cout << "\nElite Node found!" << endl << "Value: " << present->data << endl;
                return;
            }
            else {
                visited_nodes.push_back(present);
                //cout << present->data << endl;
            }
        }  while (!visited());
        cout << "\nNo elite node in the maze :(" << endl;
    }

    ~Maze() {
       delete head->right->right;
       delete head->right;
       delete head->down->down;
       delete head->down;
       delete head;

    }

};


int main()
{
    Maze m1;

    m1.read("maze.txt");
    m1.print();
    m1.elite_node();

    cout << endl;

    return 0;
}




/*
    void reshape() {
        Node* curr = head;
        Node* tmp = head;
        vector<Node*> nodes;
        do {
            while (curr->right) {
                if (curr->down) {
                    nodes.push_back(curr->down);
                    //curr->down = nullptr;
                }
                curr = curr->right;
            }
            curr->right = nodes.back();
            nodes.pop_back();
            curr = tmp->down;
            tmp = curr;
        } while (tmp->down);

        do {
            tmp->down = nullptr;
            tmp = tmp->up;
        } while (tmp != head);
    }

    void print_reshape() {
        Node* curr = head;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->right;
        }
    }
*/

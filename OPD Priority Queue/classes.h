#include <iostream>

using namespace std;

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;
    int queueSize;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr), queueSize(0) {}

    ~Queue() {
        while (!empty()) {
            pop();
        }
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        queueSize++;
    }

    void pop() {
        if (!empty()) {
            Node* temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
            if (frontNode == nullptr) {
                rearNode = nullptr;
            }
            queueSize--;
        }
    }

    T front() const {
        if (!empty()) {
            return frontNode->data;
        }
        throw runtime_error("Queue is empty");
    }

    bool empty() const {
        return frontNode == nullptr;
    }

    int size() const {
        return queueSize;
    }
};
template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* topNode;
    int stack_size = 0;
public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (!empty()) {
            pop();
        }
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        stack_size++;
    }

    void pop() {
        if (!empty()) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
        stack_size--;
    }

    T top() const {
        if (!empty()) {
            return topNode->data;
        }
        throw runtime_error("Stack is empty");
    }

    bool empty() const {
        return topNode == nullptr;
    }

    void display() const {
        Node* current = topNode;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    int size() {
        return stack_size;
    }
};

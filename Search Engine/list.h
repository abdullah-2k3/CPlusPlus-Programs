#include <iostream>

using namespace std;



string lower_case(string str) {
    string lower = "";

    for (int i = 0; i < str.length(); i++)
        lower += tolower(str[i]);

    return lower;
}

struct Key {
    string word;
    int frequency = 1;
};

class Node {
public:
    Key data;
    Node* next;

    Node(Key d) {
        data.word = d.word;
        data.frequency = d.frequency;
        this->next = nullptr;
    }
};


class List {
    Node* head;
  public:
    List() {
        head = nullptr;
    }

    void insert (Key d) {
        Node* newNode = new Node(d);

        newNode->next = head;
        head = newNode;

    }


    void delete_value(Key val) {
        Node* curr = head;

        val.word = lower_case(val.word);
        string my_word = lower_case(head->data.word);
        if (my_word == val.word) {
            head = head->next;
            delete curr;
            return;
        }
        // find val and check end of list
        my_word = lower_case(curr->next->data.word);
        while(curr->next && my_word != val.word) {
            curr = curr->next;
            my_word = lower_case(curr->next->data.word);
        }

        Node* tmp = curr->next;
        curr->next = curr->next->next;
        delete tmp;
        tmp = nullptr;

    }

    bool is_empty() {
        if (head == nullptr)
            return true;
        return false;
    }

    void display() {
        Node* curr = head;
        int c = 1;
        while (curr) {
            cout << curr->data.word << "," << curr->data.frequency << " -> ";
            curr = curr->next;
            c++;
            if (c > 7) {
                cout << endl << "   |";
                c = 0;
            }
        }
        if (head)
            cout << "\b\b\b  ";
    }


    bool find(Key val) {
        Node* curr = head;
        string word = lower_case(val.word);
        while (curr) {
            string data = lower_case(curr->data.word);
            if (data == word)
                return true;

            curr = curr->next;
        }
        return false;
    }

    bool is_present(Key val, Node* &node) {
        Node* curr = head;
        string word = lower_case(val.word);
        while (curr) {
            string data = lower_case(curr->data.word);
            if (data == word) {
                node = curr;
                return true;
            }

            curr = curr->next;
        }
        return false;
    }

    Key get_value(Node* &curr, int count) {

        if (count == 0) {
            curr = head;
            return curr->data;
        }

        if (curr->next) {
            curr = curr->next;
            return curr->data;
        }
        else {
            Key dummy;
            dummy.word = "";
            dummy.frequency = -1;
            return dummy;
        }
    }

};

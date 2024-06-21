#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


static int prime_numbers[] = {11, 19, 41, 79, 163, 317, 641, 1279,2557, 5119, 10243, 20479, 40961, 81919, 163841};

struct Key {
    string word;
    int count;


};

struct Node {
    Key data;
    Node* next;


    Node(Key d) {
        data.word = d.word;
        data.count = d.count;
        next = nullptr;
    }
};




class HashTable {
    Node** table;
    int size = 0;
    int capacity;
    int prime_index = 0;

    int get_hash_index(string word) {
        int index = 0;
        for (int i = 0; i < word.length(); i++) {
            index += word[i];
        }
        index %= capacity;

        return index;
    }

    void rehash() {
        prime_index++;

        if (prime_index > 10)
            return;

        int old_capacity = capacity;
        capacity = prime_numbers[prime_index];
        size = 0;
        Node** tmp_table = new Node* [capacity];
        for (int i = 0; i < capacity; i++)
            tmp_table[i] = nullptr;

        Key tmp_key;
        int tmp_index;
        for (int i = 0; i < old_capacity; i++) {

            if (!table[i])
                continue;

            Node* curr = table[i];
            while (curr) {
                tmp_key = curr->data;
                tmp_index = get_hash_index(tmp_key.word);
                Node* tmp = nullptr;
                if (return_search(tmp_table[tmp_index], tmp_key.word, tmp)) {
                    tmp->data.count++;
                }
                else {

                    if (tmp_table[tmp_index] == nullptr)
                        tmp_table[tmp_index] = new Node(tmp_key);
                    else {
                       Node* tmp_curr = tmp_table[tmp_index];
                        while (tmp_curr->next)
                            tmp_curr = tmp_curr->next;
                        tmp_curr->next = new Node(tmp_key);
                    }
                    size++;
                }
                curr = curr->next;
            }
        }
        delete[] table;
        table = tmp_table;
        tmp_table = nullptr;
    }

    void check_load_factor() {
        float load = size;
        load /= capacity;
        if (load > 0.75);
            rehash();
    }

    bool return_search(Node* curr, string word, Node* &tmp) {

        while (curr) {
            if (curr->data.word == word) {
                tmp = curr;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    bool search(Node* curr, string word) {

        while (curr) {
            if (curr->data.word == word)
                return true;
            curr = curr->next;
        }
        return false;
    }

public:

    HashTable() {
        capacity = prime_numbers[prime_index];
        table = new Node* [capacity];
        for (int i = 0; i < capacity; i++)
            table[i] = nullptr;
    }


    void readFile(string name) {
        string words;
        int index;
        ifstream fin(name);

        while (getline(fin, words)) {

            string word = "";
            for (int i = 0; i < words.size(); i++) {
                if (words[i] >= 'a' &&words[i] <= 'z' || words[i] >= 'A' && words[i] <= 'Z') {
                    word += words[i];

                }
                else {
                    if (word != "") {
                        int index = get_hash_index(word);
                        put(word, index);
                    }
                    word = "";
                }
            }
        }
        fin.close();
    }


    void put(string key, int value) {
        Node* tmp = nullptr;
        if (return_search(table[value], key, tmp)) {
            tmp->data.count++;
        }
        else {
            Key my_key;
            my_key.word = key;
            my_key.count = 1;
            if (table[value] == nullptr)
                table[value] = new Node(my_key);
            else {
               Node* curr = table[value];
                while (curr->next)
                    curr = curr->next;
                curr->next = new Node(my_key);
            }
            size++;
        }
        check_load_factor();
    }


    int get_value (string key) {
        if (contains(key))
            return get_hash_index(key);

        return -1;
    }

    int get_frequency(string key) {
        int index = get_hash_index(key);

        Node* curr = table[index];
        while (curr) {
            if (curr->data.word == key)
                return curr->data.count;
        }

        return 0;
    }

    bool contains(string key) {
        int index = get_hash_index(key);
        if (search(table[index], key))
            return true;

        return false;
    }

    void _delete(string key) {
        int index = get_value(key);
        if (index == -1)
            return;

        if (table[index]->data.word == key) {
            Node* tmp = table[index];
            table[index] = table[index]->next;
            delete tmp;
            tmp = nullptr;
            return;
        }


        Node* curr = table[index];
        while (curr->next) {
            if (curr->next->data.word == key) {
                Node* tmp = curr->next;
                curr->next = curr->next->next;
                delete tmp;
                tmp = nullptr;
            }
            curr = curr->next;
        }
    }

    int get_size() {
        return size;
    }


    void print() {
        cout << "\nTotal Distinct Elements: " << size << endl;
        for (int i = 0; i < capacity; i++) {
            if (!table[i])
                continue;

            cout << i << ". ";
            Node* curr = table[i];
            do {
                cout << curr->data.word << "," << curr->data.count << "  ";
                curr = curr->next;
            } while (curr);
            cout << endl;
        }
    }
};



int main()
{
    HashTable h1;

    h1.readFile("countries.txt");
    h1.print();

    return 0;
}


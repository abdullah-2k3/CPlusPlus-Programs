#include <iostream>
#include <fstream>
#include <vector>

#include "list.h"

using namespace std;


int get_index(Key el, int capacity) {
    int index = 0;
    el.word = lower_case(el.word);
    for (int i = 0; i < el.word.length(); i++) {
        index += el.word[i];
    }
    index %= capacity;

    return index;
}


static int prime[] = {11, 19, 41, 79, 163, 317, 641, 1279,2557, 5119, 10243, 20479, 40961, 81919, 163841};
class HashTable {
    List* table;
    int curr_size = 0;
    int p_index = 0;

    void rehash() {
        p_index++;
        if (p_index == 15)
            return;

        int old_cap = capacity;
        capacity = prime[p_index];
        curr_size = 0;
        List* tmp_list = new List [capacity];
        Key tmp_key;
        int new_index;

        for (int i = 0; i < old_cap; i++) {

            if (table[i].is_empty())
                continue;
            int count = 0;
            Node* get_next;
            tmp_key = table[i].get_value(get_next, count++);
            while (tmp_key.frequency != -1) {
                new_index = get_index(tmp_key, capacity);
                Node* freq_node;
                if (tmp_list[new_index].is_present(tmp_key, freq_node)) {
                    freq_node->data.frequency++;
                }
                else {
                    tmp_list[new_index].insert(tmp_key);
                    curr_size++;
                }
                tmp_key = table[i].get_value(get_next, count++);
            }
        }

        delete[] table;
        table = tmp_list;
        tmp_list = nullptr;
    }

    void check_load_factor() {
        float load = curr_size;
        load /= capacity;
        if (load > 0.75)
            rehash();
    }
public:
    int capacity;
    HashTable() {
        capacity = prime[p_index];
        table = new List [capacity];
    }


    void put(Key& key, int value) {
        Node* curr;
        if (table[value].is_present(key, curr)) {
            curr->data.frequency++;
        }
        else {
            table[value].insert(key);
            curr_size++;
        }
        check_load_factor();
    }


    int get_value(Key key) {
        if (contains(key))
            return get_index(key, capacity);

        return -1;
    }

    int get_frequency(Key key) {
        Node* curr;
        int index = get_index(key, capacity);
        if (table[index].is_present(key, curr)) {
            return curr->data.frequency;
        }
        return 0;
    }

    bool contains(Key key) {
        key.word = lower_case(key.word);
        int index = get_index(key, capacity);
        if (table[index].find(key))
            return true;
        return false;
    }

    void remove(Key key) {
        int idx = get_value(key);
        if (idx == -1)
            return;

        table[idx].delete_value(key);
    }

    int size() {
        return curr_size;
    }


    void display() {
        for (int i = 0; i < capacity; i++) {
            if (table[i].is_empty())
                continue;
            if (i > 9)
                cout << i << ". | ";
            else if (i > 99)
                cout << i << ".| ";
            else
                cout << i << ".  | ";
            table[i].display();
            cout << "\n-----------------------------------------------------------------------------------------------------------------------------\n";
        }
        cout << "Current Elements: " << curr_size << endl;
    }
};


int unique_words = 0;
Key key;

bool is_alphabet(char c) {
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' )
        return true;

    return false;
}

vector<string> get_words(string line) {
    vector<string> words;

    for (int i = 0; i < line.size(); i++) {
        string word = "";
        while (is_alphabet(line[i]) ||
               line[i] == '\'' && is_alphabet(line[i-1]) && is_alphabet(line[i+1]) &&
               i < line.size())
        {
            if (line[i] == ' ')
                break;
            word += line[i++];
        }
        if (word != "")
            words.push_back(word);
    }


    return words;
}

void readFile(HashTable& table) {
    string line;
    string word;
    int index;
    ifstream fin("countries.txt");

    while (getline(fin, line)) {
        vector<string> line_words = get_words(line);
        for (int i = 0; i < line_words.size(); i++) {
            string w = line_words[i];
            key.word = w;
            index = get_index(key, table.capacity);
            if (!table.contains(key))
                unique_words++;

            table.put(key, index);
        }
    }
    fin.close();
}



int main()
{
    string word;

    HashTable h1;

    readFile(h1);
    cout << "This text contains " << unique_words << " distinct words." << endl;

    Key input_key;
    while (true) {
        cout << "Enter a word, or hit enter to leave: ";
        getline(cin, word);
        if (word.length() == 0){
            break;
        }
        else {
            if (word[word.size()-1] == '-') {
                string str = "";
                for (int i = 0; i < word.size()-1; i++)
                    str += word[i];
                input_key.word = str;
                h1.remove(input_key);
                cout << input_key.word << " is removed from the table." << endl;
            }
            else {
                input_key.word = word;
                int choice;
                do {
                    cout << "\n1. Get Frequency\n"
                     << "2. Get Index Value in Table\n"
                     << "3. Display Hash Table\n"
                     << "Enter your choice: ";
                    cin >> choice;
                } while (choice < 1 || choice > 3);
                switch (choice) {
                    case 1:
                        cout << "Frequency: "<< h1.get_frequency(input_key) << endl;
                        break;

                    case 2:
                        cout << "Index Value: "<< h1.get_value(input_key) << endl;
                        break;
                    case 3:
                        h1.display();
                        break;
                }
            }
            cin.ignore();
        }
    }

    return 0;
}


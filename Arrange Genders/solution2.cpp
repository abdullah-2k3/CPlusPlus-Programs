#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>
#include <time.h>

using namespace std;

char directions[] = {'L', 'R', 'U', 'D'};


struct Person {
    char gender;
    char direction;
};

unsigned int row, col;
vector<vector<Person>> matrix;
queue<Person> person_queue;
vector<char> gender;
vector<char> direction;
stack<Person> order;


void assign_directions_randomly() {
    srand(time(0));
    for (unsigned int i = 0; i < gender.size(); i++) {
        direction.push_back(directions[rand() % 4]);
    }
}


void fill_person_queue() {
    Person p;
    for (unsigned int i = 0; i < gender.size(); i++) {
        p.gender = gender[i];
        p.direction = direction[i];
        person_queue.push(p);
    }

}

void initialize_matrix() {
    queue<Person> tmp = person_queue;

    for (unsigned int i = 0; i < row; i++) {
        vector<Person> v;
        for (unsigned int j = 0; j < col; j++) {
            v.push_back(tmp.front());
            tmp.pop();
        }
        matrix.push_back(v);
    }

}


char alter_direction(char d) {
    char new_d;

    if (d == 'U')
        new_d = 'R';
    else if (d == 'R')
        new_d = 'D';
    else if (d == 'D')
        new_d = 'L';
    else if (d == 'L')
        new_d = 'U';

    return new_d;
}


bool is_gender_different(int r, int c) {
    if (r > 0 && matrix[r-1][c].gender == matrix[r][c].gender)
        return false;

    if (c > 0 && matrix[r][c-1].gender == matrix[r][c].gender)
        return false;

    return true;
}

bool is_direction_different(int r, int c) {
    if (r > 0 && matrix[r-1][c].direction == matrix[r][c].direction)
        return false;

    if (c > 0 && matrix[r][c-1].direction == matrix[r][c].direction)
        return false;

    return true;
}


bool arrange_matrix(unsigned int r, unsigned int c) {
    static long int attempt = 0;
    static bool res;
    if (r == row && c == col) {
        res = true;
        return res;
    }

    if (c == col) {
        c = 0;
        r++;
    }

    attempt++;
    //cout << attempt << " ";
    if (attempt == 78*78) {
        res = false;
        return res;
    }

    if (person_queue.empty()) {
        res = true;
        return res;
    }

    if (is_gender_different(r, c)) {
        while (!is_direction_different(r, c)) {
            matrix[r][c].direction = alter_direction(matrix[r][c].direction);
        }
        person_queue.pop();
        order.push(matrix[r][c]);
        arrange_matrix(r, c+1);
    }
    else {
        person_queue.push(person_queue.front());
        person_queue.pop();
        matrix[r][c].gender = person_queue.front().gender;
        arrange_matrix(r, c);
    }

    return res;
}


void display_matrix() {
    cout << endl;
    for (unsigned int i = 0; i < row; i++) {
        cout << "\t";
        for (unsigned int j = 0; j < col; j++) {
            cout << matrix[i][j].gender << "," << matrix[i][j].direction << "\t";
        }
        cout << endl;
    }
}


void read_file_into_vector() {

    ifstream fin("people.txt");

    while (!fin.eof()) {
        char p;
        fin >> p;
        gender.push_back(p);
        fin.ignore();
    }
    fin.close();
}


int main()
{
    read_file_into_vector();
    assign_directions_randomly();
    fill_person_queue();

    cout << "People count: " << person_queue.size() << endl;
    do {
        cout << "Enter rows: ";
        cin >> row;
        cout << "Enter cols: ";
        cin >> col;
        if (row * col != person_queue.size()) {
            cout << "Invalid matrix dimension. The product should be " << person_queue.size() << endl;
        }
    } while (row * col != person_queue.size());


    initialize_matrix();

    cout << "\nBefore Arranging: " << endl;
    display_matrix();
    cout << endl;

    // Backtracing in action
    if (!arrange_matrix(0,0)) {
        cout << "No Solutions found." << endl;
        return 0;
    };

    cout << "After arranging: " << endl;
    display_matrix();

    return 0;
}


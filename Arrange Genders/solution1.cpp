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

int row, col;
vector<vector<Person>> matrix;
queue<Person> people;
vector<char> gender;
vector<char> direction;
stack<Person> order;


void set_directions() {
    srand(time(0));
    for (unsigned int i = 0; i < gender.size(); i++) {
        direction.push_back(directions[rand() % 4]);
    }
}


void fill_queue() {
    Person p;
    for (unsigned int i = 0; i < gender.size(); i++) {
        p.gender = gender[i];
        p.direction = direction[i];
        people.push(p);
    }

}

void initialize_matrix() {
    int c = 0;
    queue<Person> tmp = people;

    for (int i = 0; i < row; i++) {
        vector<Person> v;
        for (int j = 0; j < col; j++) {
            v.push_back(tmp.front());
            tmp.pop();
        }
        matrix.push_back(v);
    }

}


char shift(char d) {
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


bool check_gender(int r, int c) {
    if (r > 0 && matrix[r-1][c].gender == matrix[r][c].gender)
        return false;

    if (c > 0 && matrix[r][c-1].gender == matrix[r][c].gender)
        return false;

    return true;
}

bool check_direction(int r, int c) {
    if (r > 0 && matrix[r-1][c].direction == matrix[r][c].direction)
        return false;

    if (c > 0 && matrix[r][c-1].direction == matrix[r][c].direction)
        return false;

    return true;
}


void arrange_matrix(int r, int c) {

    if (r == row && c == col)
        return;

    if (c == col) {
        c = 0;
        r++;
    }

    if (people.empty())
        return;
    if (check_gender(r, c)) {
        while (!check_direction(r, c)) {
            matrix[r][c].direction = shift(matrix[r][c].direction);
        }
        people.pop();
        order.push(matrix[r][c]);
        arrange_matrix(r, c+1);
    }
    else {
        people.push(people.front());
        people.pop();
        matrix[r][c].gender = people.front().gender;
        arrange_matrix(r, c);
    }

}


void display_matrix() {
    cout << endl;
    for (int i = 0; i < row; i++) {
        cout << "\t";
        for (int j = 0; j < col; j++) {
            cout << matrix[i][j].gender << "," << matrix[i][j].direction << "\t";
        }
        cout << endl;
    }
}


void read_file() {
    ifstream fin("people.txt");

    while (!fin.eof()) {
        char p;
        fin >> p;
        gender.push_back(p);
        fin.ignore();
    }
}


int main()
{
    read_file();
    set_directions();
    fill_queue();

    cout << "Total people: " << people.size() << endl;
    do {
        cout << "Enter rows: ";
        cin >> row;
        cout << "Enter cols: ";
        cin >> col;
        if (row * col != people.size()) {
            cout << "Invalid matrix dimension. The product should be " << people.size() << endl;
        }
    } while (row * col != people.size());


    initialize_matrix();
    cout << "\nBefore Arranging: " << endl;
    display_matrix();
    cout << endl;
    arrange_matrix(0,0);
    cout << "After arranging: " << endl;
    display_matrix();

    return 0;
}


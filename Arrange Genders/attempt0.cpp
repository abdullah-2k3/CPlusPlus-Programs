#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <time.h>

using namespace std;

char directions[] = {'L', 'R', 'U', 'D'};
vector<char> gender;
vector<char> side;
int rows = 6, cols = 13;

struct Person {
    char gender;
    char direction;
};


void read_file() {
    ifstream fin("people.txt");

    while (!fin.eof()) {
        char p;
        fin >> p;
        gender.push_back(p);
        fin.ignore();
    }
}

void set_directions() {

    srand(time(0));
    for (unsigned int i = 0; i < gender.size(); i++) {
        side.push_back(directions[rand() % 4]);
    }

}

template <typename T>
void fill_queue(queue<T>& people) {
    Person p;
    for (unsigned int i = 0; i < gender.size(); i++) {
        p.gender = gender[i];
        p.direction = side[i];
        people.push(p);
    }

}

void show_queue(queue<Person> people) {
    for (unsigned int i = 0; i < people.size(); i++) {
        cout << people.front().gender << ", " << people.front().direction << endl;
        people.pop();
    }
}

char shift(char d) {
    char c;

    if (d == 'U')
        c = 'R';
    else if (d == 'R')
        c = 'D';
    else if (d == 'D')
        c = 'L';
    else if (d == 'L')
        c = 'U';

    return c;
}



void create_matrix(queue<Person> people) {
    Person matrix[rows][cols];
    //Populate matrix
    for (int i = 0; i < rows; i++) {
        int c = 0;
        for (int j = 0; j < cols; j++) {
                if (people.front().gender != matrix[i][j - 1].gender &&
                    people.front().gender != matrix[i - 1][j].gender
                ) {
                    if (people.front().direction != matrix[i][j - 1].direction &&
                        people.front().direction != matrix[i - 1][j].direction
                    ) {

                        matrix[i][j] = people.front();
                        people.pop();
                } else  {
                    people.front().direction = shift(people.front().direction);
                    j--;
                    continue;
                }
            } else {

                c++;
                people.push(people.front());
                people.pop();
                if (c == 78) continue;
                j--;
            }
        }
    }


    //DISPLAY MATRIX
    cout << "Displaying Matrix: ";
    cout << endl << endl;
    for (int i = 0; i < rows; i++) {
        cout << "\t\t\t";
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j].gender == 'M' || matrix[i][j].gender == 'F')
                cout << "("<< matrix[i][j].gender << "," << matrix[i][j].direction << ") ";
            else
                cout << "*****" << "  ";
        }
        cout << endl << endl;
    }

}


int main() {
    read_file();
    set_directions();

    queue<Person> people;
    fill_queue(people);

    
    create_matrix(people);


    return 0;
}

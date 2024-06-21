#include <iostream>
#include <windows.h>
#include <stack>
#include <vector>

using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Node {
    friend class Digit;
    Node* up;
    Node* down;
    Node* right;
    Node* left;
public:
    Node() {
        up = nullptr;
        down = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

int x = 5;
int y = 5;
class Digit {
    Node* one;
    Node* two;
    Node* three;
    Node* four;
    Node* five;
    Node* six;

public:
    Digit () {
        one = two = three = four = five = six = nullptr;
    }


    void set_digit(int digit) {
        switch  (digit) {
        case 0:
            one = new Node;
            two = new Node;
            three = new Node;
            four = new Node;
            five = new Node;
            six = new Node;

            one->right = two;
            one->down = three;
            two->down = four;
            four->down = six;
            six->left = five;
            five->up = three;
            three->up = one;
            break;
        case 1:
            one = new Node;
            three = new Node;
            five = new Node;
            two = new Node;
            four = new Node;
            six = new Node;

            one->down = three;
            three->down = five;
            break;

        case 2:
            one = new Node;
            two = new Node;
            three = new Node;
            four = new Node;
            five = new Node;
            six = new Node;

            one->right = two;
            two->down = four;
            four->left = three;
            three->down = five;
            five->right = six;
            break;
        case 3:
            one = new Node;
            two = new Node;
            three = new Node;
            four = new Node;
            five = new Node;
            six = new Node;

            one->right = two;
            two->down = four;
            four->left = three;
            four->down = six;
            six->left = five;
            break;

        case 4:
            one = new Node;
            two = new Node;
            three = new Node;
            four = new Node;
            five = new Node;
            six = new Node;

            one->down = three;
            three->right = four;
            four->up = two;
            two->down = four;
            four->down = six;

            break;
        case 5:
            one = new Node;
            two = new Node;
            three = new Node;
            four = new Node;
            five = new Node;
            six = new Node;

            one->right = two;
            one->down = three;
            three->right = four;
            four->down = six;
            six->left = five;
            break;

        case 6:
            one = new Node;
            two = new Node;
            three = new Node;
            four = new Node;
            five = new Node;
            six = new Node;


            one->right = two;
            one->down = three;
            three->right = four;
            four->down = six;
            six->left = five;
            five->up = three;
            break;

        case 7:
            one = new Node;
            two = new Node;
            four = new Node;
            six = new Node;
            three = new Node;
            five = new Node;

            one->right = two;
            two->down = four;
            four->down = six;
            break;

        case 8:
            one = new Node;
            two = new Node;
            three = new Node;
            four = new Node;
            five = new Node;
            six = new Node;


            one->right = two;
            two->down = four;
            four->down = six;
            four->left = three;
            six->left = five;
            five->up = three;
            three->up = one;
            break;

        case 9:
            one = new Node;
            two = new Node;
            three = new Node;
            four = new Node;
            five = new Node;
            six = new Node;

            one->down = three;
            one->right = two;
            two->down = four;
            four->left = three;
            four->down = six;
            six->left = five;
            break;
        }
    }


    void print() {

        Node* curr = one;

            if (curr->down == three && curr->down->down == five) {
                for (int i = 0; i < 5; i++) {
                        gotoxy(x+5, y+i);
                        cout << "*";
                }
            }

            else if (curr->right == two && curr->right->down == four && curr->right->down->left == three &&
                curr->right->down->left->down == five && curr->right->down->left->down->right == six) {
                gotoxy(x, y);
                cout << "******";
                gotoxy(x+5, y+1);
                cout << "*";
                gotoxy(x, y+2);
                cout << "******";
                gotoxy(x, y+3);
                cout << "*";
                gotoxy(x, y+4);
                cout << "******";
            }

            else if (curr->down == nullptr && curr->right == two && curr->right->down == four &&
                     curr->right->down->left == three && curr->right->down->down == six && six->left == five &&
                     five->up == nullptr) {
                gotoxy(x, y);
                cout << "******";
                gotoxy(x+5, y+1);
                cout << "*";
                gotoxy(x, y+2);
                cout << "******";
                gotoxy(x+5, y+3);
                cout << "*";
                gotoxy(x, y+4);
                cout << "******";
            }

            else if (curr->down == three && curr->down->right == four && curr->down->right->up == two &&
                     curr->down->right->down == six) {
                for (int i = 0; i < 2; i++) {
                    gotoxy(x, y+i);
                    cout << "*";
                }
                gotoxy(x, y+2);
                cout << "******";
                for (int i = 0; i < 5; i++) {
                            gotoxy(x+5, y+i);
                            cout << "*";
                }
            }

            else if (curr->right == two && curr->down == three && curr->down->right == four &&
                     curr->down->right->down == six && curr->down->right->down->left == five &&
                     curr->down->right->down->left->up ==  nullptr) {
                gotoxy(x, y);
                cout << "******";
                gotoxy(x, y+1);
                cout << "*";
                gotoxy(x, y+2);
                cout << "******";
                gotoxy(x+5, y+3);
                cout << "*";
                gotoxy(x, y+4);
                cout << "******";
            }

            else if (curr->right == two && curr->down == three && curr->down->right == four &&
                     curr->down->right->down == six && curr->down->right->down->left == five &&
                     curr->down->right->down->left->up == three) {
                gotoxy(x, y);
                cout << "******";
                gotoxy(x, y+1);
                cout << "*";
                gotoxy(x, y+2);
                cout << "******";
                gotoxy(x, y+3);
                cout << "*";
                gotoxy(x+5, y+3);
                cout << "*";
                gotoxy(x, y+4);
                cout << "******";
            }

            else if (curr->right == two && curr->right->down && curr->right->down->down && !six->left) {
                gotoxy(x, y);
                cout << "******";
                for (int i = 0; i < 5; i++) {
                            gotoxy(x+5, y+i);
                            cout << "*";
                }
            }

            else if (curr->right == two && curr->right->down == four && curr->right->down->down == six &&
                     curr->right->down->left == three && curr->right->down->down->left->up == three) {
                gotoxy(x, y);
                cout << "******";
                gotoxy(x, y+1);
                cout << "*";
                gotoxy(x+5, y+1);
                cout << "*";
                gotoxy(x, y+2);
                cout << "******";
                gotoxy(x, y+3);
                cout << "*";
                gotoxy(x+5, y+3);
                cout << "*";
                gotoxy(x, y+4);
                cout << "******";

            }

            else if (curr->right == two && curr->down == three && curr->right->down == four &&
                     curr->right->down->left == three) {
                gotoxy(x, y);
                cout << "******";
                gotoxy(x, y+1);
                cout << "*";
                gotoxy(x+5, y+1);
                cout << "*";
                gotoxy(x, y+2);
                cout << "******";
                gotoxy(x+5, y+3);
                cout << "*";
                gotoxy(x, y+4);
                cout << "******";
            }
            else if (curr->right == two && two->down == four && four->left == nullptr && four->down == six &&
                six->left == five && five->up == three && three->right == nullptr && three->up == one) {
                gotoxy(x, y);
                cout << "******";
                for (int i = 0; i < 5; i++) {
                    gotoxy(x+5, y+i);
                    cout << "*";
                }
                for (int i = 0; i < 5; i++) {
                    gotoxy(x, y+i);
                    cout << "*";
                }
                gotoxy(x, y+4);
                cout << "******";

            }
    }

    void display() {
        if (one->right) {
            gotoxy(x, y);
            cout << "******";
        }
        if (three->right || four->left) {
            gotoxy(x, y+2);
            cout << "******";
        }
        if (five->right || six->left) {
            gotoxy(x, y+4);
            cout << "******";
        }
        if (one->down || three->up) {
            for (int i = 0; i <= 2; i++) {
                gotoxy(x,y+i);
                cout << "*";
            }
        }
        if (three->down || five->up) {
            for (int i = 0; i < 2; i++) {
                gotoxy(x,y+3+i);
                cout << "*";
            }
        }
        if (two->down) {
            for (int i = 0; i <= 2; i++) {
                gotoxy(x+5,y+i);
                cout << "*";
            }
        }
        if (four->down) {
            for (int i = 0; i <= 2; i++) {
                gotoxy(x+5,y+2+i);
                cout << "*";
            }
        }
    }

    ~Digit() {
        delete one;
        delete two;
        delete three;
        delete four;
        delete five;
        delete six;
    }
};

string add_minutes(string time, int m) {
        int mins = (int)(time[3]-'0');

        mins *= 10;
        mins += (int)(time[4]-'0');
        mins += m;

        int hrs = (int)(time[0]-'0');
        hrs *= 10;
        hrs += (int)(time[1]-'0');

        while (mins > 59) {
            mins -= 60;
            hrs ++;
        }

        while (hrs > 23) {
            hrs -= 24;
        }


        int h1 = hrs%10;
        hrs /= 10;
        int h0 = hrs;

        time[0] = char(h0+'0');
        time[1] = char(h1+'0');

        int m1 = mins%10;
        mins /= 10;
        int m0 = mins;

        time[3] = char(m0+'0');
        time[4] = char(m1+'0');

        return time;
}

string add_hours (string time, int h) {
        int hrs = (int)(time[0]-'0');
        hrs *= 10;
        hrs += (int)(time[1]-'0');

        hrs += h;

        while (hrs > 23) {
            hrs -= 24;
        }

        int h1 = hrs%10;
        hrs /= 10;
        int h0 = hrs;

        time[0] = char(h0+'0');
        time[1] = char(h1+'0');

        return time;
}

string sub_minutes(string time, int m) {
        int mins = (int)(time[3]-'0');

        mins *= 10;
        mins += (int)(time[4]-'0');
        mins -= m;

        int hrs = (int)(time[0]-'0');
        hrs *= 10;
        hrs += (int)(time[1]-'0');

        while (mins < 0) {
            mins += 60;
            hrs--;
            if (hrs < 0)
                hrs += 24;
        }


        int h1 = hrs%10;
        hrs /= 10;
        int h0 = hrs;

        time[0] = char(h0+'0');
        time[1] = char(h1+'0');

        int m1 = mins%10;
        mins /= 10;
        int m0 = mins;

        time[3] = char(m0+'0');
        time[4] = char(m1+'0');

        return time;
}

string sub_hours (string time, int h) {
        int hrs = (int)(time[0]-'0');
        hrs *= 10;
        hrs += (int)(time[1]-'0');

        hrs -= h;

        while (hrs < 0) {
            hrs += 24;
        }

        int h1 = hrs%10;
        hrs /= 10;
        int h0 = hrs;

        time[0] = char(h0+'0');
        time[1] = char(h1+'0');

        return time;
}

bool is_time_valid(string time) {
    bool valid = false;

        if (isdigit(time[0]) && time[0] < '3'&& isdigit(time[1]) && time[2] == ':' && (isdigit(time[3]) &&
            time[3] < '6') && isdigit(time[4])) {
            if (time[0] == '2' && time[1] > '3')
                valid = false;
            else
                valid = true;
        }

    return valid;
}

void display_time(string time) {
    system("cls");
    x = 5, y = 5;
    Digit d1;
    d1.set_digit(int(time[0]-'0'));
    d1.display();

    x+=10;
    Digit d2;
    d1.set_digit(int(time[1]-'0'));
    d1.display();

    x+=10;
    gotoxy(x, y+1);
    cout << "*";
    gotoxy(x, y+3);
    cout << "*";


    x+=5;
    Digit d3;
    d1.set_digit(int(time[3]-'0'));
    d1.display();

    x+=10;
    Digit d4;
    d1.set_digit(int(time[4]-'0'));
    d1.display();

}

int main()
{
    int choice = 0;

    while (true) {
        string time;
        do {
            gotoxy(0,0);
            //system("cls");
            cout << "Enter time in 24h format (00:00): ";
            cin >> time;
        } while (!is_time_valid(time));

        display_time(time);

        do {
            do {
                gotoxy(0, 15);
                cout << "1. Add minutes     2. Add hours     3. Subtract minutes     4. Subtract hours     5. Enter new time    0. Exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
            } while (choice < 0 || choice > 5);

            if (choice == 0) {
                cout << "Are you sure?(1/0): ";
                cin >>  choice;
                if (choice == 1)
                    return 0;
            }

            int n;
            switch (choice) {
            case 1:
                cout << "How many minutes do you want to add: ";
                cin >> n;
                time = add_minutes(time, n);
                display_time(time);
                break;
            case 2:
                cout << "How many hours do you want to add: ";
                cin >> n;
                time = add_hours(time, n);
                display_time(time);
                break;
            case 3:
                cout << "How many minutes do you want to subtract: ";
                cin >> n;
                time = sub_minutes(time, n);
                display_time(time);
                break;
            case 4:
                cout << "How many hours do you want to subtract: ";
                cin >> n;
                time = sub_hours(time, n);
                display_time(time);
                break;
            }
        } while (choice > 0 && choice < 5);

    }
    gotoxy(0, 25);
    return 0;
}

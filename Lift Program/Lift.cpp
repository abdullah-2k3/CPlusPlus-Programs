#include <iostream>
#include <deque>
#include <stack>

using namespace std;

void display(deque<int> lift) {
    
    while (!lift.empty()) {
        cout << lift.front() << " ";
        lift.pop_front();
    }
    cout << endl;
}


void descending_sort(stack<int>& reverse_enrties, int _floor) {
    stack<int> tmp_reverse;
    if (reverse_enrties.empty()) {
        reverse_enrties.push(_floor);
        return;
    }
    
    if (_floor > reverse_enrties.top()) {
        reverse_enrties.push(_floor);
        return;
    }

    while (!reverse_enrties.empty()) {
        if (reverse_enrties.top() > _floor) {
            tmp_reverse.push(reverse_enrties.top());
            reverse_enrties.pop();
        }
        else 
            break;
    }

    reverse_enrties.push(_floor);
        
    while (!tmp_reverse.empty()) {
        reverse_enrties.push(tmp_reverse.top());
        tmp_reverse.pop();
    }
}

void ascending_sort(stack<int>& reverse_enrties, int _floor) {
    stack<int> tmp_reverse;
    if (reverse_enrties.empty()) {
        reverse_enrties.push(_floor);
        return;
    }
    
    if (_floor < reverse_enrties.top()) {
        reverse_enrties.push(_floor);
        return;
    }

    while (!reverse_enrties.empty()) {
        if (reverse_enrties.top() < _floor) {
            tmp_reverse.push(reverse_enrties.top());
            reverse_enrties.pop();
        }
        else 
            break;
    }

    reverse_enrties.push(_floor);
        
    while (!tmp_reverse.empty()) {
        reverse_enrties.push(tmp_reverse.top());
        tmp_reverse.pop();
    }
}

int main()
{
    deque<int> Lift;
    int _floor;
    bool going_up;
    cout << "Enter current floor: ";
    cin >> _floor;
    stack<int> reverse_enrties;
    Lift.push_back(_floor);
    while (true) {
        do {
            cout << "Enter next floor, or -1 to exit: ";
            cin >> _floor;
            if (_floor == -1) 
                break;
            
            if (_floor == Lift.front())
                cout << "Already on floor " << _floor << endl; 
        } while (_floor == Lift.front());
        
        if (_floor == -1) {
            break;
        }
            
        if (Lift.size() == 1) {
            if (_floor > Lift.front())
                going_up = true;   //up
             else 
                going_up = false;  //down
            Lift.push_back(_floor);
        }
        else {
            stack<int> tmp;
            if (going_up) {
                if (_floor < Lift.front()) {
                    descending_sort(reverse_enrties, _floor);
                }
                else {
                    while (_floor < Lift.back()) {
                        tmp.push(Lift.back());      // 12, 17, 18, 19, 13
                        Lift.pop_back();
                    }
                    
                    Lift.push_back(_floor);
                    
                    while (!tmp.empty()) {
                        Lift.push_back(tmp.top());
                        tmp.pop();
                    }
                }
            }
            
            else {
                if (_floor > Lift.front()) {
                    ascending_sort(reverse_enrties, _floor);
                }
                else {
                    while (_floor > Lift.back()) {
                        tmp.push(Lift.back());      // 12, 17, 18, 19, 13
                        Lift.pop_back();
                    }
                    
                    Lift.push_back(_floor);
                    while (!tmp.empty()) {
                        Lift.push_back(tmp.top());
                        tmp.pop();
                    }
                }
            }
        }
    }
    
    while (!reverse_enrties.empty()) {
        Lift.push_back(reverse_enrties.top());
        reverse_enrties.pop();
    }
    
    cout << "Route of the Lift: " << endl;
    display(Lift);
    
    return 0;
}



#include <iostream>
#include <stack>
#include <queue>
#include <windows.h>

using namespace std;

struct Patient {
    string name;
    int age;
    char condition;
    int priority;
    bool reference;
    Patient(string n, int a, char c, bool r) : name(n), age(a), condition(c), reference(r) {


        if (toupper(condition) == 'N')
            if (reference)
                priority = 2;
            else
                priority = 3;
        else if (toupper(condition) == 'C') {
                priority = 2;
        } else if (toupper(condition) == 'I') {
            priority = 1;
        } else {
            throw invalid_argument("Invalid condition");
        }
    }
};


queue<Patient> opdQueue;

void enque_patient() {
    string name;
    char condition;
    int age;
    bool ref;

    cout << "Enter patient's name: ";
    cin >> name;

    cout << "Enter patient's age: ";
    cin >> age;

    do {
    cout << "Enter patient's condition (N)ormal / (C)ritical / (I)ntense: ";
    cin >> condition;
    } while (toupper(condition) != 'N' && toupper(condition) != 'C' && toupper(condition) != 'I');

    cout << "Enter if there is any reference for the patient (0/1): ";
    cin >> ref;

        Patient patient(name, age, condition, ref);

        opdQueue.push(patient);

        cout << "\nPatient " << patient.name << " has been enqueued." << endl;


}

void update_patient_data() {
    string name;
    cout << "Enter the name of the patient to update: ";
    cin >> name;

    queue<Patient> tempQueue;
    bool found = false;

    while (!opdQueue.empty()) {
        Patient patient = opdQueue.front();
        opdQueue.pop();

        if (patient.name == name) {
            found = true;
            char newCondition;

            cout << "Enter the new condition (N)ormal/(C)ritical/(I)ntense: ";
            cin >> newCondition;


            Patient updatedPatient(name, patient.age, newCondition, 0);
            tempQueue.push(updatedPatient);
            cout << "Patient " << name << "'s condition has been updated.\n";

        } else {
            tempQueue.push(patient);
        }
    }

    if (!found) {
        cout << "Patient not found in the queue.\n";
    }

    while (!tempQueue.empty()) {
        opdQueue.push(tempQueue.front());
        tempQueue.pop();
    }

}

void solve_elders(queue<Patient>& priority) {
    queue<Patient> tmp_young;
    queue<Patient> tmp_old;
    while(!priority.empty()) {
        if (priority.front().age < 60) {
            tmp_young.push(priority.front());
        }
        else {
            tmp_old.push(priority.front());
        }
        priority.pop();
    }
    if (opdQueue.front().reference)
        priority.push(opdQueue.front()); // to cater the case of intense patient with reference

    while (!tmp_old.empty()) {
        priority.push(tmp_old.front());
        tmp_old.pop();
    }

    if (!opdQueue.front().reference)
        priority.push(opdQueue.front());

    while (!tmp_young.empty()) {
        priority.push(tmp_young.front());
        tmp_young.pop();
    }
}

void prioritize_patients() {
    queue<Patient> priority1;
    queue<Patient> priority2;
    queue<Patient> priority3;

    while(!opdQueue.empty()) {
        if (opdQueue.front().priority == 1) {
            if (opdQueue.front().age > 60 || opdQueue.front().reference) {
                solve_elders(priority1);
            }
            else {
                priority1.push(opdQueue.front());
            }
        }
        else if (opdQueue.front().priority == 2) {
            if (opdQueue.front().age > 60) {
                solve_elders(priority2);
            }
            else {
                priority2.push(opdQueue.front());
            }
        }
        else if (opdQueue.front().priority == 3) {
            if (opdQueue.front().age > 60) {
                solve_elders(priority3);
            }
            else {
                priority3.push(opdQueue.front());
            }
        }
        opdQueue.pop();
    }

    while (!priority1.empty()) {
        opdQueue.push(priority1.front());
        priority1.pop();
    }
    while (!priority2.empty()) {
        opdQueue.push(priority2.front());
        priority2.pop();
    }
    while (!priority3.empty()) {
        opdQueue.push(priority3.front());
        priority3.pop();
    }
}

void show_priority() {
    if (opdQueue.empty()) {
        cout << "No patients in the queue" << endl;
        return;
    }

    bool is_priority = false;
    queue<Patient> tempQueue = opdQueue;
    while (!tempQueue.empty()) {
        if (tempQueue.front().priority == 1) {
            cout << "Patient " << tempQueue.front().name << " has been prioritized most due to Intense Condition." << endl;
            is_priority = true;
        }
        else if (tempQueue.front().priority == 2) {
            cout << "Patient " << tempQueue.front().name << " has been prioritized due to Severe Condition." << endl;
            is_priority = true;
        }

        tempQueue.pop();
    }

    if (is_priority == false)
        cout << "No patients are in severe condition. The queue remains the same." << endl;
}

void print_queue() {
    cout << "\n------------------------------------------------\n";
    cout << "Current Queue:\n";
    queue<Patient> tempQueue = opdQueue;

    while (!tempQueue.empty()) {
        Patient patient = tempQueue.front();
        tempQueue.pop();
        //Sleep(1000);
        cout << "Name: " << patient.name << ", Age: " << patient.age << ", Condition: ";
        if (toupper(patient.condition) == 'N')
        cout << "Normal" << endl;
        else if (toupper(patient.condition) == 'C')
        cout << "Critical" << endl;
        else if (toupper(patient.condition) == 'I')
        cout << "Intense" << endl;
    }

}

int main() {


    char choice;
    while (true) {
        cout << "1. Enqueue Patients\t 2. Update Information\t 3. View Current Queue\t 4. Prioritize Patients with Special Condition\t 5. Exit\n";

            cout << "\nEnter your choice: ";
            cin >> choice;

        switch (choice) {
            case '1': {
                enque_patient();
                prioritize_patients();
                break;
            }
            case '2': {
                update_patient_data();
                prioritize_patients();
                break;
            }

            case '3': {
                print_queue();
                break;
            }

            case '4': {
                show_priority();
                break;
            }

            case '5': {
                cout << "Exiting the program.\n";
                return 0;
            }

            default: {
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
            }
        }
        cout << endl;
    }

    return 0;
}


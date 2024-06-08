#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>
#include <vector>
#include "queue.cpp"

using namespace std;


string get_random_time() {

    string _time;

    srand(time(0));
    int h1 = rand()%3;

    _time += h1 + '0';

    srand(time(0));
    int h2 = rand()%10;

    _time += h2 + '0';

    _time += ':';

    srand(time(0));
    int m1 = rand()%6;

    _time += m1 + '0';

    srand(time(0));
    int m2 = rand()%10;

    _time += m2 + '0';

    _time += ':';

    srand(time(0));
    int s1 = rand()%6;

    _time += s1 + '0';

    srand(time(0));
    int s2 = rand()%10;

    _time += s2 + '0';

    return _time;
}

string get_departure_time(string arrival_time, int signalTime) {

    string _time = "";


    //Example time: 12:34:02   //converting char in string to int
    int curr_sec = ((arrival_time[6] - '0')*10) + (arrival_time[7] - '0');

    int new_sec = curr_sec + signalTime;

    int min_inc = 0;
    while (new_sec >= 60)  {
        new_sec -= 60;
        min_inc++;
    }

    int curr_min = ((arrival_time[3] - '0')*10) + (arrival_time[4] - '0');

    int new_min = curr_min + min_inc;


    int hour_inc = 0;

    while (new_min >= 60)  {
        new_min -= 60;
        hour_inc++;
    }

    int curr_hour = ((arrival_time[0] - '0')*10) + (arrival_time[1] - '0');

    int new_hour = curr_hour + hour_inc;

    if (new_hour < 10)
        _time += '0';

    _time += to_string(new_hour);
    _time += ':';

    if (new_min < 10)
        _time += '0';

    _time += to_string(new_min);
    _time += ':';

    if (new_sec < 10)
        _time += '0';

    _time += to_string(new_sec);


    return _time;
}

string get_time_diff(string start, string _end) {
    string time;
    //FORMAT --> 00:00:00

    int end_sec = _end[6] - '0';
    end_sec *= 10;
    end_sec += _end[7] - '0';

    int start_sec = start[6] - '0';
    start_sec *= 10;
    start_sec += start[7] - '0';

    int sec_diff = end_sec - start_sec;




    int end_min = _end[3] - '0';
    end_min *= 10;
    end_min += _end[4] - '0';

    int start_min = start[3] - '0';
    start_min *= 10;
    start_min += start[4] - '0';

    int min_diff = end_min - start_min;

    if (sec_diff < 0)
    {
        sec_diff += 60;
        min_diff--;
    }

    if (min_diff < 0)
        min_diff += 60;



    int end_hour = _end[0] - '0';
    end_hour *= 10;
    end_hour += _end[1] - '0';

    int start_hour = start[0] - '0';
    start_hour *= 10;
    start_hour += start[1] - '0';

    int hour_diff = end_hour - start_hour;


    if (hour_diff < 0)
        hour_diff += 24;


    if (hour_diff == 0)
    {
        time += '0';
        time += '0';
    }
    else
    {

        time += '0';
        time += to_string(hour_diff);
    }
    time += ':';

    if (min_diff == 0)
    {
        time += '0';
        time += '0';
    }
    else if (min_diff < 10)
    {
        time += '0';
        time += to_string(min_diff);
    }
    else
        time += to_string(min_diff);

    time += ':';

    if (sec_diff < 10)
        time += '0';

    time += to_string(sec_diff);


    return time;
}

string last_car_departure_time = "";


class Car {
    int ID;
    string arrival_time;
    string departure_time;

    static int globalTime;

public:
    Car () {
        ++globalTime;
    }

    Car(int ID, string a_time) {
        this->ID = ID;
        arrival_time = a_time;
        departure_time = "";
    }

    int get_ID() {
        return this->ID;
    }

    void set_departure_time(string time) {
        departure_time = time;
    }

    string get_departure_time() {
        return departure_time;
    }

    string get_arrival_time() {
        return arrival_time;
    }

    ~Car() {
        ++globalTime;
    }
};


class TrafficSignal {
    Queue<Car> cars;
    string direction;

public:
    TrafficSignal() {
        direction = "";
    }

    TrafficSignal(string direction) {
        this->direction = direction;
    }

    void set_direction(string direction) {
        this->direction = direction;
    }

    Queue<Car> get_car_queue() {
        return cars;
    }

    void addCar(Car car) {
        cars.enqueue(car);

        //cout << "A new car has joined the junction...\n";
    }

    void runSignal(int signalTime) {

        while (signalTime > 0 && !cars.isEmpty()) {
            string arrival_time = cars.front().get_arrival_time();
            last_car_departure_time = get_departure_time(arrival_time, signalTime);

            cout << "\nSignal Direction: " << this->direction << endl;
            cout << "Leaving Car ID: " << cars.front().get_ID() << endl;
            cout << "Arrival Time: " << arrival_time << endl;
            cout << "Departure Time: " << last_car_departure_time << endl;
            cout << "Waiting Time for this Car: " << get_time_diff(arrival_time, last_car_departure_time) << endl << endl;

            //this_thread::sleep_for(chrono::milliseconds(200));

            signalTime -= 5;
            cars.dequeue();

            int id = rand()%10000+1;
            string a_time = last_car_departure_time;
            a_time = get_departure_time(arrival_time, 15);


            Car car(id, a_time);
            addCar(car);
        }
    }


};


class Junction {
    int signalTime;
    TrafficSignal signals[4];
    string directions[4] = {"North", "East", "West", "South"};
public:
    Junction (int signalTime) {
        this->signalTime = signalTime;

        for (int i = 0; i < 4; i++) {
            signals[i].set_direction(directions[i]);
        }
    }

    void addCar (Car car) {

        srand(time(0));
        static int i = rand();
        i = (i+1)%4;

        signals[i].addCar(car);
    }


    float get_signal_time(int index) {
        float time;
        int queue_length[4];

        float total_cars = 0;

        for (int i = 0; i < 4; i++) {
            queue_length[i] = signals[i].get_car_queue().length();
            total_cars += queue_length[i];
        }

        float ratio = queue_length[index] / total_cars;
        time = signalTime * ratio;

        return time;
    }

    void runSimulation() {


        for (int i = 0; i < 4; i++) {
            int length = signals[i].get_car_queue().length();
            float signal_run_time = get_signal_time(i);
            signals[i].runSignal(signal_run_time);

            int avg_wait = (signalTime - signal_run_time)/ length;

            cout << "Total Time for this signal: " << int(signal_run_time) <<  " seconds"<< endl;
            cout << "Average Waiting Time for this signal: " << avg_wait <<  " seconds"<< endl << endl;
            cout << "--------------------------------------------\n\n";

            //this_thread::sleep_for(chrono::seconds(2));

            int id = rand()%100000 + 1;
            string arrival_time = last_car_departure_time;
            arrival_time = get_departure_time(arrival_time, 15);

            Car car(id, arrival_time);
            addCar(car);
        }

    }

};

int main()
{
    int signalTime = 120;
    Junction junction1(signalTime);

    for (int i = 0; i < 20; i++) {
        string a_time = "10:15:";

        srand(time(0));
        int sec = (rand()%40)+i;

        if (sec < 10)
            a_time += '0';

        a_time += to_string(sec);

        int id = rand()%100000 + 1;
        Car car(id, a_time);

        junction1.addCar(car);
    }



    junction1.runSimulation();




    return 0;
}

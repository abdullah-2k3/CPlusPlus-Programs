#include <iostream>
#include <cstdlib>

#include "queue.cpp"
using namespace std;

// Car class representing each car at the junction
class Car {
    public:
        Car(int id, int arrivalTime) {}

    private:
        int id;
        int arrivalTime;
        int departureTime;
        static int globalTime;
};

int Car::globalTime = 0;

// TrafficSignal class representing each side of the junction
class TrafficSignal {
    public:
        TrafficSignal(string direction) : direction(direction) {}

        void addCar(Car car) {}

        void runSignal(int signalTime) {}


    private:
        string direction;
        Queue<Car> queue;
        int totalTime;
};

// Junction class representing the entire traffic signal system
class Junction {
public:
    Junction(int signalTime) {}

    void addCar(Car car) {}

    void runSimulation() {}

private:
    int signalTime;
};

//int main() {
//    // Set the signal time (adjust as needed for part A)
//    int signalTime = 5;
//
//    // Create a junction with the given signal time
//    Junction junction(signalTime);
//
//    // TO DO: Add cars to the junction for simulation
//
//    // Run the simulation
//    junction.runSimulation();
//
//    return 0;
//}

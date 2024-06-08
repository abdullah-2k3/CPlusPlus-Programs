#ifndef __QUEUE_H
#define __QUEUE_H
#include "LinkedList.cpp"


template <class T>
class Queue
{
    LinkedList<T> list;

  public:

    // Constructor
      Queue();

    // Copy Constructor
    Queue(Queue<T>& otherQueue);

    // Destructor
    ~Queue();

    // Required Methods
    void enqueue(T item);
    T front();
    T dequeue();
    int length();
    bool isEmpty();
};

#endif

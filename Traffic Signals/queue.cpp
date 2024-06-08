#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue():list()
{}

template <class T>
Queue<T>::Queue(Queue<T>& otherQueue):list()
{
	if (otherQueue.list.length() > 0)
	{
		shared_ptr<ListItem<T>> tmp = otherQueue.list.getHead();
		while (tmp != NULL)
		{
			enqueue(tmp->value);
			tmp = tmp->next;
		}
	}
	else return;
}

template <class T>
Queue<T>::~Queue()
{
	while (!isEmpty())
		dequeue();
}

template <class T>
void Queue<T>::enqueue(T item)
{
	list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
	return list.getHead()->value;
}

template <class T>
T Queue<T>::dequeue()
{
	T tmp = list.getHead()->value;
	list.deleteHead();
	return tmp;
}

template <class T>
int Queue<T>::length()
{
	return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
	return list.length() == 0;
}


#endif

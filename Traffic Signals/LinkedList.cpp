#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include <memory>
#include "LinkedList.h"
using namespace std;

template <class T>
LinkedList<T>::LinkedList()
{
    head = tail = NULL;
    size = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
	head = tail = NULL;
	size = 0;
	shared_ptr<ListItem<T>> tmp = otherLinkedList.head;
	while (tmp != NULL)
	{
		insertAtTail(tmp->value);
		tmp = tmp->next;
	}
}


template <class T>
void LinkedList<T>::insertAtHead(T item)
{
	shared_ptr<ListItem<T>> newHead = make_shared<ListItem<T>>(item);
	size++;
	if (head == NULL)
	{
		head = newHead;
		tail = newHead;
	}
	else
	{
		newHead->next = head;
		head->prev = newHead;
		head = newHead;
	}
}


template <class T>
void LinkedList<T>::insertAtTail(T item)
{
	shared_ptr<ListItem<T>> newTail = make_shared<ListItem<T>>(item);
	size++;
	if (tail == NULL)
	{
		head = newTail;
		tail = newTail;
	}
	else
	{
		newTail->prev = tail;
		tail->next = newTail;
		tail = newTail;
	}
}


template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
	shared_ptr<ListItem<T>> tmp = head;
	while (tmp != NULL)
	{
		if (tmp->value == afterWhat)
		{
			shared_ptr<ListItem<T>> newItem = make_shared<ListItem<T>>(toInsert);
			newItem->next = tmp->next;
			newItem->prev = tmp;
			size++;
			if (tmp->next != NULL)
				tmp->next->prev = newItem;
			else
				tail = newItem;
			tmp->next = newItem;
			return;
		}
		tmp = tmp->next;
	}
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::getHead()
{
	return head;
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::getTail()
{
	return tail;
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::searchFor(T item)
{
	shared_ptr<ListItem<T>> tmp = head;
	while (tmp != NULL)
	{
		if (tmp->value == item)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}


template <class T>
void LinkedList<T>::deleteElement(T item)
{
	shared_ptr<ListItem<T>> tmp = head;
	while (tmp != NULL)
	{
		if (tmp->value == item)
		{
			if (tmp->prev != NULL)
				tmp->prev->next = tmp->next;
			else
				head = tmp->next;
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			else
				tail = tmp->prev;
			size--;
			return;
		}
		tmp = tmp->next;
	}
}


template <class T>
void LinkedList<T>::deleteHead()
{
	if (head != NULL)
	{
		head = head->next;
		size--;
		if (head != NULL)
			head->prev = NULL;
		else
			tail = NULL;
	}
}

template <class T>
void LinkedList<T>::deleteTail()
{
	if (tail != NULL)
	{
		tail = tail->prev;
		size--;
		if (tail != NULL)
			tail->next = NULL;
		else
			head = NULL;
	}
}

template <class T>
int LinkedList<T>::length()
{
	return size;
}

#endif

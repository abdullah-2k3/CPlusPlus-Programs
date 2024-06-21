#include <iostream>

using namespace std;

template <class T, class U>
struct pair {
  T first;
  U second;
};

class Node {
  friend class LinkedList;

 public:
  int data;
  Node* next;
  Node* nextList;
  Node(int d) {
    this->data = d;
    this->next = nullptr;
    this->nextList = nullptr;
  }
};

class LinkedList {
  int size;
  class Iterator {
    friend class LinkedList;
    Node* curr;

   public:
    Iterator() { curr = nullptr; }

    Iterator(Node* n) { curr = n; }

    Iterator& operator++() {
      if (curr) {
        curr = curr->next;
      }
      return *this;
    }

    bool operator==(Iterator& obj) { return this->curr == obj.curr; }

    bool operator!=(const Iterator& obj) { return this->curr != obj.curr; }
  };

 public:
  Node* head;
  LinkedList() {
    head = nullptr;
    size = 0;
  }

  int get_size() { return size; }

  void insert(int d) {
    Node* newNode = new Node(d);

    if (head == nullptr) {
      head = newNode;
    } else {
      Node* current = head;
      while (current->next != nullptr) {
        current = current->next;
      }
      current->next = newNode;
    }
    size++;
  }

  void delete_from_start() {
    Node* tmp = head->next;
    delete head;
    head = tmp;
  }

  void delete_from_end() {
    if (head == nullptr) return;

    Node* curr = head;
    while (curr->next->next) curr = curr->next;

    delete curr->next;
    curr->next = nullptr;
  }

  void delete_value(Node* val) {
    Node* curr = head;

    if (head == val) {
      head = head->next;
      delete curr;
      return;
    }
    // find val and check end of list
    while (curr->next != val) {
      curr = curr->next;
    }

    Node* tmp = curr->next;
    curr->next = curr->next->next;
    delete tmp;
    tmp = nullptr;
  }

  Iterator begin() { return Iterator(head); }

  Iterator end() { return Iterator(nullptr); }

  void display() {
    for (Iterator i = begin(); i != end(); ++i) {
      cout << i.curr->data << " -> ";
    }
  }

  LinkedList& sum(LinkedList& list) {
    Node* curr = this->head;
    Node* other = list.head;
    while (curr->next) {
      curr->data += other->data;
      curr = curr->next;
      other = other->next;
    }

    return *this;
  }

  bool is_merge(LinkedList& list) {
    Node* curr = head;
    Node* other = list.head;
    while (curr) {
      other = list.head;
      while (other) {
        if (other == curr) return true;
        other = other->next;
      }
      curr = curr->next;
    }

    return false;
  }

  LinkedList* sub_list(int k) {
    int n = size / k;
    if (size % k != 0) n++;

    LinkedList* new_list = new LinkedList[n];
    Node* curr = head;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < k && curr != nullptr; j++) {
        new_list[i].insert(curr->data);
        curr = curr->next;
      }
    }

    return new_list;
  }

  void k_sub_list(int k) {
    int n = size / k;

    Node* curr = head;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < k - 1 && curr != nullptr; j++) {
        curr = curr->next;
      }

      if (!curr) break;

      if (curr->next) {
        curr->nextList = curr->next;
        curr->next = nullptr;
        curr = curr->nextList;
      }
    }
  }

  void print_sublist(LinkedList* list, int k) {
    int n = size / k;

    if (size % k != 0) n++;

    cout << "[ ";
    for (int i = 0; i < n; i++) {
      cout << list[i] << "-> ";
    }
    cout << "\b\b\b ] " << endl;
  }

  void print_sublist() {
    Node* curr = head;
    cout << "[ ";

    while (curr) {
      cout << "[";
      while (curr) {
        cout << curr->data << "->";
        if (curr->next)
          curr = curr->next;
        else
          break;
      }
      cout << "\b\b] -> ";
      curr = curr->nextList;
    }
    cout << "\b\b\b] " << endl;
  }

  void remove_seq() {
    Node* curr = head;
    Node* tmp;
    while (curr) {
      tmp = curr;
      if (curr->next->data == 0) {
        // curr->next = curr->next->next;
        delete_value(curr->next);
      } else
        curr = curr->next;
    }
    delete_value(tmp);
  }

  bool deleteSubList(LinkedList list) {
    bool found = false;
    Node* curr = this->head;
    Node* other;

    while (curr && !found) {
      other = list.head;

      if (curr->data == other->data) {
        found = true;
        Node* tmp = curr;
        do {
          tmp = tmp->next;
          other = other->next;
          if (tmp->data != other->data) {
            found = false;
            break;
          }
        } while (other->next && tmp->next);
        if ((other != nullptr) && (tmp == nullptr)) {
          cout << "Sublist not found";
          return false;
        }
        if (found) {
          other = list.head;
          while (other) {
            Node* tmp = curr;
            curr = curr->next;
            delete_value(tmp);
            other = other->next;
          }
          return true;
        }
      }
      curr = curr->next;
    }

    cout << "Sublist not found" << endl;
    return false;
  }

  friend ostream& operator<<(ostream& out, LinkedList& list) {
    Node* current = list.head;

    if (current == nullptr) return out;

    cout << "[";
    while (current != nullptr) {
      cout << current->data << "->";
      current = current->next;
    }
    cout << "\b\b] ";
    return out;
  }

  friend istream& operator>>(istream& in, LinkedList& list) {
    cout << "Enter the data in linked list: ";

    cin >> list.head->data;

    return in;
  }
};

int main() {
  LinkedList l1;

  for (int i = 0; i < 10; i++) l1.insert(i + 1);

  cout << l1 << endl;

  int k;
  do {
    cout << "Enter the number of elements you want in the sublists: ";
    cin >> k;
    if (k > l1.get_size())
      cout << "Error: Value greater than the actual size of the list..."
           << endl;
  } while (k > l1.get_size());

  l1.k_sub_list(k);

  l1.print_sublist();
  /*
      LinkedList L1, L2;

      L1.head = new Node(4);
      L2.head = new Node(17);

      L1.head->next = new Node(5);
      L1.head->next->next = new Node(6);
      Node* newNode = new Node(7);
      L1.head->next->next->next = newNode;
      L1.head->next->next->next->next = new Node(8);
      L1.head->next->next->next->next->next = new Node(9);
      L1.head->next->next->next->next->next->next = new Node(10);

      L2.head->next = new Node(18);
      L2.head->next->next = new Node(19);
      L2.head->next->next->next = L1.head->next;
      L2.head->next->next->next->next = new Node(13);


      cout << "L1: " << L1 << endl << "L2: " << L2 << endl;
      cout << L1.is_merge(L2) << endl;
  */

  return 0;
}

#include <iostream>

using namespace std;


class Node {
    friend class BST;
    int data;
    Node* left;
    Node* right;
public:
    Node(int d) {
        data = d;
        left = right = nullptr;
    }
};

class BST {
    Node* root;


    Node* insert_helper(Node* curr, int val) {
        if (curr == nullptr) {
            curr = new Node(val);
            return curr;
        }

        if (val == curr->data)
            return curr;

        if (val > curr->data) {
            curr->right = insert_helper(curr->right, val);
        }
        if (val < curr->data) {
            curr->left = insert_helper(curr->left, val);
        }

        return curr;
    }

    void inorder_helper(Node* curr) {
        if (curr == nullptr)
            return;
        inorder_helper(curr->left);
        cout << curr->data << " ";
        inorder_helper(curr->right);
    }

    void preorder_helper(Node* curr) {
        if (curr == nullptr)
            return;
        cout << curr->data << " ";
        inorder_helper(curr->left);
        inorder_helper(curr->right);
    }

    void postorder_helper(Node* curr) {
        if (curr == nullptr)
            return;
        inorder_helper(curr->left);
        inorder_helper(curr->right);
        cout << curr->data << " ";
    }

public:
    BST() {
        root = nullptr;
    }

    void insert (int val) {
        root = insert_helper(root, val);
    }

    void inorder() {
        inorder_helper(root);
    }

    void preorder() {
        preorder_helper(root);
    }

    void postorder() {
        postorder_helper(root);
    }

};

void sorted_arr_to_BST(BST& bst, int* arr, int min, int max) {
    if (min < max) {
        int mid = (max - min) / 2;

        bst.insert(arr[mid]);

        sorted_arr_to_BST(bst, arr, mid + 1, max);
        sorted_arr_to_BST(bst, arr, min, mid - 1);
    }
}


int main()
{
//    BST b1;
//    int size = 10;
//    int arr[] = {1,2,3,4,5,6,7,8,9,10};
//
//    sorted_arr_to_BST(b1, arr, 0, size-1);
//
//    for (int i = 1; i < 10; i++)
//        b1.insert(i);
//
//
//    cout << "Preorder: " << endl;
//    b1.preorder();
//    cout << endl <<     endl;
//
//    cout << "Inorder: " << endl;
//    b1.inorder();
//    cout << endl << endl;
//
//    cout << "Postorder: " << endl;
//    b1.postorder();
//    cout << endl << endl;

    printf("Hello");

//    return 0;
}


#include <iostream>
#include <string>
using namespace std;

class Medicine
{
public:
    string name;
    int medicineID;
    int expiryDate;

    Medicine(string n, int id, int date)
    {
        name = n;
        medicineID = id;
        expiryDate = date;
    }
};

class MinHeap
{
private:
    struct Node
    {
        Medicine data;
        Node* left;
        Node* right;
        Node* parent;

        Node(Medicine m)
            : data(m), left(NULL), right(NULL), parent(NULL)
        {
        }
    };

    Node* root;

    // Heapify Up
    void heapifyUp(Node* temp)
    {
        while(temp->parent != NULL &&
              temp->data.expiryDate < temp->parent->data.expiryDate)
        {
            Medicine swapData = temp->data;
            temp->data = temp->parent->data;
            temp->parent->data = swapData;

            temp = temp->parent;
        }
    }

    // Heapify Down
    void heapifyDown(Node* temp)
    {
        while(temp != NULL)
        {
            Node* smallest = temp;

            if(temp->left != NULL &&
               temp->left->data.expiryDate < smallest->data.expiryDate)
            {
                smallest = temp->left;
            }

            if(temp->right != NULL &&
               temp->right->data.expiryDate < smallest->data.expiryDate)
            {
                smallest = temp->right;
            }

            if(smallest != temp)
            {
                Medicine swapData = temp->data;
                temp->data = smallest->data;
                smallest->data = swapData;

                temp = smallest;
            }
            else
            {
                break;
            }
        }
    }

public:
    MinHeap()
    {
        root = NULL;
    }

    // Insert Medicine
    void insert(Medicine m)
    {
        Node* newNode = new Node(m);

        if(root == NULL)
        {
            root = newNode;
            return;
        }

        Node* q[100];
        int front = 0, rear = 0;

        q[rear++] = root;

        while(front < rear)
        {
            Node* temp = q[front++];

            if(temp->left == NULL)
            {
                temp->left = newNode;
                newNode->parent = temp;
                break;
            }
            else
            {
                q[rear++] = temp->left;
            }

            if(temp->right == NULL)
            {
                temp->right = newNode;
                newNode->parent = temp;
                break;
            }
            else
            {
                q[rear++] = temp->right;
            }
        }

        heapifyUp(newNode);
    }

    // Level Order Traversal
    void display()
    {
        if(root == NULL)
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        Node* q[100];
        int front = 0, rear = 0;

        q[rear++] = root;

        while(front < rear)
        {
            Node* temp = q[front++];

            cout << "Medicine: " << temp->data.name
                 << " | Medicine ID: " << temp->data.medicineID
                 << " | Expiry Date: " << temp->data.expiryDate << endl;

            if(temp->left != NULL)
                q[rear++] = temp->left;

            if(temp->right != NULL)
                q[rear++] = temp->right;
        }
    }

    // Medicine with nearest expiry
    void displayNearestExpiry()
    {
        if(root == NULL)
        {
            cout << "No medicines available!" << endl;
            return;
        }

        cout << "Nearest Expiry Medicine: "
             << root->data.name
             << " | Expiry Date: " << root->data.expiryDate << endl;
    }

    // Delete medicine with nearest expiry
    void deleteRoot()
    {
        if(root == NULL)
            return;

        cout << "Deleted Medicine: "
             << root->data.name << endl;

        if(root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return;
        }

        Node* q[100];
        int front = 0, rear = 0;
        Node* last = root;

        q[rear++] = root;

        while(front < rear)
        {
            last = q[front++];

            if(last->left != NULL)
                q[rear++] = last->left;

            if(last->right != NULL)
                q[rear++] = last->right;
        }

        root->data = last->data;

        Node* parent = last->parent;

        if(parent->left == last)
            parent->left = NULL;
        else
            parent->right = NULL;

        delete last;

        heapifyDown(root);
    }
};

int main()
{
    MinHeap medicines;

    medicines.insert(Medicine("Panadol", 401, 20271215));
    medicines.insert(Medicine("Brufen", 402, 20261120));
    medicines.insert(Medicine("Calpol", 403, 20280110));
    medicines.insert(Medicine("Augmentin", 404, 20261225));
    medicines.insert(Medicine("Disprin", 405, 20271005));
    medicines.insert(Medicine("Arinac", 406, 20260915));

    cout << "===== HOSPITAL MEDICINE EXPIRY SYSTEM =====\n";

    cout << "\nMedicines in Min Heap:\n";
    medicines.display();

    cout << "\n";
    medicines.displayNearestExpiry();

    cout << "\nDeleting Medicine with Nearest Expiry...\n";
    medicines.deleteRoot();

    cout << "\nUpdated Medicine Heap:\n";
    medicines.display();

    return 0;
}


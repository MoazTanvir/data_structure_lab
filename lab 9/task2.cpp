
#include <iostream>
#include <string>
using namespace std;

class Patient
{
public:
    string name;
    int patientID;
    int priority;

    Patient(string n, int id, int p)
    {
        name = n;
        patientID = id;
        priority = p;
    }
};

class MaxHeap
{
private:
    struct Node
    {
        Patient data;
        Node* left;
        Node* right;
        Node* parent;

        Node(Patient p)
            : data(p), left(NULL), right(NULL), parent(NULL)
        {
        }
    };

    Node* root;

    // Heapify Up
    void heapifyUp(Node* temp)
    {
        while(temp->parent != NULL &&
              temp->data.priority > temp->parent->data.priority)
        {
            Patient swapData = temp->data;
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
            Node* largest = temp;

            if(temp->left != NULL &&
               temp->left->data.priority > largest->data.priority)
            {
                largest = temp->left;
            }

            if(temp->right != NULL &&
               temp->right->data.priority > largest->data.priority)
            {
                largest = temp->right;
            }

            if(largest != temp)
            {
                Patient swapData = temp->data;
                temp->data = largest->data;
                largest->data = swapData;

                temp = largest;
            }
            else
            {
                break;
            }
        }
    }

public:
    MaxHeap()
    {
        root = NULL;
    }

    // Insert Patient
    void insert(Patient p)
    {
        Node* newNode = new Node(p);

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

            cout << "Name: " << temp->data.name
                 << " | Patient ID: " << temp->data.patientID
                 << " | Priority: " << temp->data.priority << endl;

            if(temp->left != NULL)
                q[rear++] = temp->left;

            if(temp->right != NULL)
                q[rear++] = temp->right;
        }
    }

    // Highest Priority Patient
    void displayHighest()
    {
        if(root == NULL)
        {
            cout << "No patients available!" << endl;
            return;
        }

        cout << "Highest Priority Patient: "
             << root->data.name
             << " | Priority: " << root->data.priority << endl;
    }

    // Delete Root after treatment
    void deleteRoot()
    {
        if(root == NULL)
            return;

        cout << "Patient treated and removed: "
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
    MaxHeap patients;

    patients.insert(Patient("Ali", 201, 4));
    patients.insert(Patient("Ahmed", 202, 8));
    patients.insert(Patient("Sara", 203, 6));
    patients.insert(Patient("Usman", 204, 10));
    patients.insert(Patient("Ayesha", 205, 3));
    patients.insert(Patient("Moiz", 206, 7));

    cout << "===== HOSPITAL EMERGENCY SYSTEM =====\n";

    cout << "\nAll Patients:\n";
    patients.display();

    cout << "\n";
    patients.displayHighest();

    cout << "\nTreating Highest Priority Patient...\n";
    patients.deleteRoot();

    cout << "\nUpdated Patient Heap:\n";
    patients.display();

    cout << "\nNext Patient for Treatment:\n";
    patients.displayHighest();

    return 0;
}


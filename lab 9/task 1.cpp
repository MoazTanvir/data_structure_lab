
#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
    string name;
    int rollNo;
    int marks;

    Student(string n, int r, int m)
    {
        name = n;
        rollNo = r;
        marks = m;
    }
};

class MaxHeap
{
private:
    struct Node
    {
        Student data;
        Node* left;
        Node* right;
        Node* parent;

        Node(Student s)
            : data(s), left(NULL), right(NULL), parent(NULL)
        {
        }
    };

    Node* root;

    // Move new student upward
    void heapifyUp(Node* temp)
    {
        while(temp->parent != NULL &&
              temp->data.marks > temp->parent->data.marks)
        {
            Student swapData = temp->data;
            temp->data = temp->parent->data;
            temp->parent->data = swapData;

            temp = temp->parent;
        }
    }

    // Restore Max Heap after deletion
    void heapifyDown(Node* temp)
    {
        while(temp != NULL)
        {
            Node* largest = temp;

            if(temp->left != NULL &&
               temp->left->data.marks > largest->data.marks)
            {
                largest = temp->left;
            }

            if(temp->right != NULL &&
               temp->right->data.marks > largest->data.marks)
            {
                largest = temp->right;
            }

            if(largest != temp)
            {
                Student swapData = temp->data;
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

    // Insert student
    void insert(Student s)
    {
        Node* newNode = new Node(s);

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

    // Display using Level Order Traversal
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
                 << " | Roll No: " << temp->data.rollNo
                 << " | Marks: " << temp->data.marks << endl;

            if(temp->left != NULL)
                q[rear++] = temp->left;

            if(temp->right != NULL)
                q[rear++] = temp->right;
        }
    }

    // Display student with highest marks
    void displayHighest()
    {
        if(root == NULL)
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        cout << "Highest Merit Student: "
             << root->data.name
             << " | Marks: " << root->data.marks << endl;
    }

    // Delete student with highest marks
    void deleteRoot()
    {
        if(root == NULL)
            return;

        cout << "Deleted Student: "
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
    MaxHeap students;

    students.insert(Student("Ali", 101, 85));
    students.insert(Student("Ahmed", 102, 92));
    students.insert(Student("Sara", 103, 78));
    students.insert(Student("Moiz", 104, 95));
    students.insert(Student("Ayesha", 105, 88));
    students.insert(Student("Usman", 106, 82));

    cout << "===== STUDENT MAX HEAP =====" << endl;

    cout << "\nStudents in Level Order:\n";
    students.display();

    cout << "\n";
    students.displayHighest();

    cout << "\nDeleting Highest Marks Student...\n";
    students.deleteRoot();

    cout << "\nUpdated Heap:\n";
    students.display();

    return 0;
}


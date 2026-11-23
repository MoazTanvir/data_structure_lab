
#include <iostream>
#include <string>
using namespace std;

class Order
{
public:
    int orderID;
    string customerName;
    int amount;

    Order(int id, string name, int a)
    {
        orderID = id;
        customerName = name;
        amount = a;
    }
};

class MaxHeap
{
private:
    struct Node
    {
        Order data;
        Node* left;
        Node* right;
        Node* parent;

        Node(Order o)
            : data(o), left(NULL), right(NULL), parent(NULL)
        {
        }
    };

    Node* root;

    // Heapify Up
    void heapifyUp(Node* temp)
    {
        while(temp->parent != NULL &&
              temp->data.amount > temp->parent->data.amount)
        {
            Order swapData = temp->data;
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
               temp->left->data.amount > largest->data.amount)
            {
                largest = temp->left;
            }

            if(temp->right != NULL &&
               temp->right->data.amount > largest->data.amount)
            {
                largest = temp->right;
            }

            if(largest != temp)
            {
                Order swapData = temp->data;
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

    // Insert Order
    void insert(Order o)
    {
        Node* newNode = new Node(o);

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

    // Display Orders
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

            cout << "Order ID: " << temp->data.orderID
                 << " | Customer: " << temp->data.customerName
                 << " | Amount: " << temp->data.amount << endl;

            if(temp->left != NULL)
                q[rear++] = temp->left;

            if(temp->right != NULL)
                q[rear++] = temp->right;
        }
    }

    // Delete root and return deleted order
    Order deleteRoot()
    {
        Order deleted = root->data;

        if(root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return deleted;
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

        return deleted;
    }

    bool isEmpty()
    {
        return root == NULL;
    }
};

int main()
{
    MaxHeap orders;

    orders.insert(Order(301, "Ali", 4500));
    orders.insert(Order(302, "Ahmed", 2500));
    orders.insert(Order(303, "Sara", 7000));
    orders.insert(Order(304, "Usman", 1500));
    orders.insert(Order(305, "Ayesha", 9000));
    orders.insert(Order(306, "Moiz", 3500));

    cout << "===== ONLINE SHOPPING ORDERS =====\n";

    cout << "\nOrders in Max Heap:\n";
    orders.display();

    int deletedAmounts[6];

    cout << "\nDeleting Orders using Heap Sort:\n";

    for(int i = 0; i < 6; i++)
    {
        Order deleted = orders.deleteRoot();

        deletedAmounts[i] = deleted.amount;

        cout << deleted.amount << " ";
    }

    cout << "\n\nOrder Amounts in Ascending Order:\n";

    for(int i = 5; i >= 0; i--)
    {
        cout << deletedAmounts[i] << " ";
    }

    cout << endl;

    return 0;
}


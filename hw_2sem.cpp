
#include "iostream"
#include "string"


struct Node
    {
    int data;
    Node *left;
    Node *right;
    Node *previous;

    Node(int value) : data(value), right(nullptr), left(nullptr), previous(nullptr) {}
    };

class BSTree
    {
    Node *root_of_tree;

    void PrintOrd (Node *value)
        {
        if (value)
            {
            PrintOrd (value->left);
            std::cout << value->data << std::endl;
            PrintOrd (value->right);
            }
        }
        
    Node *Find (Node *root, int value)
        {
        if (root == nullptr || root->data == value)
            {
            return root;
            }

        if (root->data < value)
            {
            return Find (root->right, value);
            }

        return Find (root->left, value);
        }
        
    void distructor (Node *value)
        {
        if (value)
            {
            distructor (value->right);
            distructor (value->left);
            distructor (value->previous);
            delete (value);
            }
        }
        
    Node *minData(Node *node)
        {
        Node *current = node;
        while (current && current->left != nullptr)
            {
            current = current->left;
            }
        
        return current;
        }
        
    Node *deleteNode(Node *root, int value)
        {
        if (root == nullptr)
            {
            return root;
            }

        if (value < root->data)
            {
            root->left = deleteNode(root->left, value);
            }
        
        else
            if (value > root->data)
            {
            root->right = deleteNode(root->right, value);
            }
        
        else
            {
            if (root->left == nullptr)
                {
                Node *temp = root->right;
                delete root;
                return temp;
                }
            else
                if (root->right == nullptr)
                    {
                    Node *temp = root->left;
                    delete root;
                    return temp;
                    }
                
            Node *temp = minData(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
            }
        return root;
        }

public:
        
    BSTree() : root_of_tree(nullptr) {}
        
    BSTree(std::initializer_list<int> list) : root_of_tree(nullptr) {
        for (int value: list)
            {
            add_element(value);
            }
        }
        
    bool add_element(int value)
        {
        Node *new_element = new Node(value);
        
        if (!root_of_tree)
            {
            root_of_tree = new_element;
            return true;
            }
        
        Node *previous_value = nullptr;
        Node *current_value = root_of_tree;
        while (current_value)
            {
            previous_value = current_value;
            if (value < current_value->data)
                {
                current_value = current_value->left;
                }
            else
                if (value > current_value->data)
                    {
                    current_value = current_value->right;
                    }
                else
                    {
                    delete new_element;
                    return false;
                    }
            }
        
        new_element->previous = previous_value;
        
        if (value < previous_value->data)
            {
            previous_value->left = new_element;
            }
        else
            {
            previous_value->right = new_element;
            }
        return true;
        }
        
    bool delete_element(int value)
        {
        if (!find_element(value)) return false;
        root_of_tree = deleteNode(root_of_tree, value);
        return true;
        }
        
    bool find_element(int value)
        {
        return Find (root_of_tree, value) != nullptr;
        }
        
    void print()
        {
        PrintOrd (root_of_tree);
        std::cout << std::endl;
        }
        
    ~BSTree()
        {
        distructor (root_of_tree);
        }
    };

int main()
    {
    BSTree tree = {10, 20, 50, 25, 120, 200};
    tree.print();
    
    int i = tree.find_element(11);
    std::cout << i << std::endl;
    
    tree.delete_element(50);
    tree.print();
    
    return 0;
    }


#pragma once

#include "All.h"
using namespace std;

template <typename T>
class RedBlackTree
{
private:
    struct RBNode
    {
        T data;
        int color;
        RBNode* parent;
        RBNode* left;
        RBNode* right;

        RBNode(T value)
        {
            data = value;
            color = 0;
            parent = nullptr;
            left = nullptr;
            right = nullptr;
        }
    };

    RBNode* root;

    void rotateLeft(RBNode*& node)
    {
        RBNode* child = node->right;
        node->right = child->left;

        if (node->right != nullptr)
            node->right->parent = node;


        child->parent = node->parent;

        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;

        child->left = node;
        node->parent = child;
    }

    void rotateRight(RBNode*& node)
    {
        RBNode* child = node->left;
        node->left = child->right;

        if (node->left != nullptr)
            node->left->parent = node;

        child->parent = node->parent;

        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;

        child->right = node;
        node->parent = child;
    }

    void fixInsert(RBNode*& node)
    {
        RBNode* parent = nullptr;
        RBNode* grandparent = nullptr;

        while (node != root && node->color == 0 && node->parent->color == 0)
        {
            parent = node->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left)
                fixInsertLeftCase(node, parent, grandparent);
            else
                fixInsertRightCase(node, parent, grandparent);
        }

        root->color = 1;
    }

    void fixInsertLeftCase(RBNode*& node, RBNode*& parent, RBNode*& grandparent)
    {
        RBNode* uncle = grandparent->right;

        if (uncle != nullptr && uncle->color == 0)
        {
            grandparent->color = 0;
            parent->color = 1;
            uncle->color = 1;
            node = grandparent;
        }
        else
        {
            if (node == parent->right)
            {
                rotateLeft(parent);
                node = parent;
                parent = node->parent;
            }
            rotateRight(grandparent);
            swapColors(parent, grandparent);
            node = parent;
        }
    }

    void fixInsertRightCase(RBNode*& node, RBNode*& parent, RBNode*& grandparent)
    {
        RBNode* uncle = grandparent->left;

        if (uncle != nullptr && uncle->color == 0)
        {
            grandparent->color = 0;
            parent->color = 1;
            uncle->color = 1;
            node = grandparent;
        }
        else
        {
            if (node == parent->left)
            {
                rotateRight(parent);
                node = parent;
                parent = node->parent;
            }
            rotateLeft(grandparent);
            swapColors(parent, grandparent);
            node = parent;
        }
    }

    void swapColors(RBNode* node1, RBNode* node2)
    {
        int temp = node1->color;
        node1->color = node2->color;
        node2->color = temp;
    }

    RBNode* minValueNode(RBNode* node)
    {
        while (node->left != nullptr)
            node = node->left;

        return node;
    }

    void transplant(RBNode* u, RBNode* v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v != nullptr)
            v->parent = u->parent;
    }

    void fixDelete(RBNode*& node)
    {
        while (node != root && node->color == 1)
        {
            if (node == node->parent->left)
                fixDeleteLeftCase(node);
            else
                fixDeleteRightCase(node);
        }

        if (node != nullptr)
            node->color = 1;
    }

    void fixDeleteLeftCase(RBNode*& node)
    {
        RBNode* sibling = node->parent->right;

        if (sibling->color == 0)
        {
            sibling->color = 1;
            node->parent->color = 0;
            rotateLeft(node->parent);
            sibling = node->parent->right;
        }

        if ((sibling->left == nullptr || sibling->left->color == 1) &&
            (sibling->right == nullptr || sibling->right->color == 1))
        {
            sibling->color = 0;
            node = node->parent;
        }
        else
        {
            if (sibling->right == nullptr || sibling->right->color == 1)
            {
                if (sibling->left != nullptr)
                    sibling->left->color = 1;

                sibling->color = 0;
                rotateRight(sibling);
                sibling = node->parent->right;
            }

            sibling->color = node->parent->color;
            node->parent->color = 1;

            if (sibling->right != nullptr)
                sibling->right->color = 1;

            rotateLeft(node->parent);
            node = root;
        }
    }

    void fixDeleteRightCase(RBNode*& node)
    {
        RBNode* sibling = node->parent->left;

        if (sibling->color == 0)
        {
            sibling->color = 1;
            node->parent->color = 0;
            rotateRight(node->parent);
            sibling = node->parent->left;
        }

        if ((sibling->left == nullptr || sibling->left->color == 1) &&
            (sibling->right == nullptr || sibling->right->color == 1))
        {
            sibling->color = 0;
            node = node->parent;
        }
        else
        {
            if (sibling->left == nullptr || sibling->left->color == 1)
            {
                if (sibling->right != nullptr)
                    sibling->right->color = 1;

                sibling->color = 0;
                rotateLeft(sibling);
                sibling = node->parent->left;
            }
            sibling->color = node->parent->color;
            node->parent->color = 1;

            if (sibling->left != nullptr)
                sibling->left->color = 1;

            rotateRight(node->parent);
            node = root;
        }
    }

    void printHelper(RBNode* root, string indent, bool last)
    {
        if (root != nullptr)
        {
            cout << indent;
            if (last)
            {
                cout << "R----";
                indent += "   ";
            }
            else
            {
                cout << "L----";
                indent += "|  ";
            }

            cout << root->data;
            if (root->color == 0)
                cout << "(RED)";
            else
                cout << "(BLACK)";

            cout << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }


public:
    RedBlackTree()
    {
        root = nullptr;
    }

    void insert(T key)
    {
        RBNode* node = new RBNode(key);
        insertNode(node);
    }

    void insertNode(RBNode* node)
    {
        RBNode* parent = nullptr;
        RBNode* current = root;

        while (current != nullptr)
        {
            parent = current;

            if (node->data < current->data)
                current = current->left;
            else
                current = current->right;
        }

        node->parent = parent;

        if (parent == nullptr)
            root = node;
        else if (node->data < parent->data)
            parent->left = node;
        else
            parent->right = node;

        fixInsert(node);
    }

    void remove(T key)
    {
        RBNode* node = root;
        RBNode* z = nullptr;

        do
        {
            if (node->data == key)
                z = node;

            if (key < node->data)
                node = node->left;
            else
                node = node->right;

        } while (node != nullptr);

        if (z == nullptr)
        {
            cout << "Key not found in the tree" << endl;
            return;
        }

        deleteNode(z);
    }

    void deleteNode(RBNode* z)
    {
        RBNode* y = z;
        RBNode* x = nullptr;
        int yOriginalColor = y->color;

        if (z->left == nullptr)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == nullptr)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else
        {
            y = minValueNode(z->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == z)
            {
                if (x != nullptr)
                    x->parent = y;

            }
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (yOriginalColor == 1 && x != nullptr)
            fixDelete(x);

    }

    void print()
    {
        if (root)
            printHelper(root, "", true);

    }

    RBNode* getRoot()
    {
        return root;
    }

    void generateFiles(RBNode* node, const string& parentPath, const string& folderPath, vector<string> lineData, vector<string> fieldData)
    {
        if (node == nullptr)
            return;

        string fileName = folderPath + node->data + ".txt";

        int count = 0;
        while (fileExists(fileName))
        {
            count++;
            fileName = folderPath + node->data + to_string(count) + ".txt";
        }

        ofstream file(fileName);
        if (!file.is_open())
        {
            cout << "Error: Could not open file " << fileName << endl;
            return;
        }
        file << "Parent: " << (parentPath.empty() ? "NULL" : parentPath) << endl;

    }

    bool fileExists(const string& fileName)
    {
        ifstream file(fileName);
        return file.is_open();
    }

    void menu()
    {
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Print" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            T value;
            cout << "Enter the value to insert: ";
            cin >> value;
            insert(value);
            break;
        }
        case 2:
        {
            T value;
            cout << "Enter the value to delete: ";
            cin >> value;
            remove(value);
            break;
        }
        case 3:
            print();
            break;
        }
    }
};

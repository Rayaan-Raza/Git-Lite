#include <iostream>
#include<string>
#include<vector>
#include<stack>

template <typename T>
struct BNode {
    T* keys;
    BNode** children;
    int keyCount;
    bool isLeaf;

    BNode(int order) {
        keys = new T[order - 1];
        children = new BNode<T>*[order];
        keyCount = 0;
        isLeaf = true;
        for (int i = 0; i < order; i++)
            children[i] = nullptr;
    }

    ~BNode() {
        delete[] keys;
        for (int i = 0; i <= keyCount; i++)
            delete children[i];
        delete[] children;
    }
};

template <typename T>
class BTree {
private:
    BNode<T>* root;
    int order;

public:
    BTree(int ord) : root(nullptr), order(ord) {}

    ~BTree() {
        delete root;
    }

    void insert(T value) {
        if (!root) {
            root = new BNode<T>(order);
            root->keys[0] = value;
            root->keyCount = 1;
        }
        else if (root->keyCount == order - 1) {
            BNode<T>* newRoot = new BNode<T>(order);
            newRoot->isLeaf = false;
            newRoot->children[0] = root;
            root = newRoot;
            splitChild(newRoot, 0, newRoot->children[0]);
            insertNonFull(newRoot, value);
        }
        else {
            insertNonFull(root, value);
        }
    }

    void splitChild(BNode<T>* parentNode, int childIndex, BNode<T>* fullChild) {
        BNode<T>* newNode = new BNode<T>(order);
        newNode->isLeaf = fullChild->isLeaf;
        newNode->keyCount = order / 2 - 1;

        for (int i = 0; i < order / 2 - 1; i++)
            newNode->keys[i] = fullChild->keys[i + order / 2];

        if (!fullChild->isLeaf) {
            for (int i = 0; i < order / 2; i++)
                newNode->children[i] = fullChild->children[i + order / 2];
        }

        fullChild->keyCount = order / 2 - 1;

        for (int i = parentNode->keyCount; i >= childIndex + 1; i--)
            parentNode->children[i + 1] = parentNode->children[i];

        parentNode->children[childIndex + 1] = newNode;

        for (int i = parentNode->keyCount - 1; i >= childIndex; i--)
            parentNode->keys[i + 1] = parentNode->keys[i];

        parentNode->keys[childIndex] = fullChild->keys[order / 2 - 1];
        parentNode->keyCount++;
    }

    void insertNonFull(BNode<T>* currentNode, T value) {
        int i = currentNode->keyCount - 1;

        if (currentNode->isLeaf) {
            while (i >= 0 && currentNode->keys[i] > value) {
                currentNode->keys[i + 1] = currentNode->keys[i];
                i--;
            }

            currentNode->keys[i + 1] = value;
            currentNode->keyCount++;
        }
        else {
            while (i >= 0 && currentNode->keys[i] > value)
                i--;

            i++;

            if (currentNode->children[i]->keyCount == order - 1) {
                splitChild(currentNode, i, currentNode->children[i]);

                if (currentNode->keys[i] < value)
                    i++;
            }

            insertNonFull(currentNode->children[i], value);
        }
    }

    BNode<T>* search(T value) {
        return search(root, value);
    }

    BNode<T>* search(BNode<T>* currentNode, T value) {
        int i = 0;

        while (i < currentNode->keyCount && value > currentNode->keys[i])
            i++;

        if (i < currentNode->keyCount && currentNode->keys[i] == value)
            return currentNode;

        if (currentNode->isLeaf)
            return nullptr;

        return search(currentNode->children[i], value);
    }

    void remove(T value) {
        if (!root) {
            std::cout << "The tree is empty.\n";
            return;
        }

        deleteFromNode(root, value);

        if (root->keyCount == 0) {
            BNode<T>* temp = root;
            root = root->isLeaf ? nullptr : root->children[0];
            delete temp;
        }
    }

    void deleteFromNode(BNode<T>* currentNode, T value) {
        int idx = 0;

        while (idx < currentNode->keyCount && currentNode->keys[idx] < value)
            idx++;

        if (idx < currentNode->keyCount && currentNode->keys[idx] == value) {
            if (currentNode->isLeaf) {
                for (int i = idx + 1; i < currentNode->keyCount; i++)
                    currentNode->keys[i - 1] = currentNode->keys[i];
                currentNode->keyCount--;
            }
            else if (currentNode->children[idx]->keyCount >= order / 2) {
                T pred = getPredecessor(currentNode->children[idx]);
                currentNode->keys[idx] = pred;
                deleteFromNode(currentNode->children[idx], pred);
            }
            else if (currentNode->children[idx + 1]->keyCount >= order / 2) {
                T succ = getSuccessor(currentNode->children[idx + 1]);
                currentNode->keys[idx] = succ;
                deleteFromNode(currentNode->children[idx + 1], succ);
            }
            else {
                merge(currentNode, idx);
                deleteFromNode(currentNode->children[idx], value);
            }
        }
        else {
            if (currentNode->isLeaf) {
                std::cout << "The key " << value << " does not exist in the tree.\n";
                return;
            }

            bool isLastChild = (idx == currentNode->keyCount);

            if (currentNode->children[idx]->keyCount < order / 2)
                fill(currentNode, idx);

            if (isLastChild && idx > currentNode->keyCount)
                deleteFromNode(currentNode->children[idx - 1], value);
            else
                deleteFromNode(currentNode->children[idx], value);
        }
    }

    T getPredecessor(BNode<T>* currentNode) {
        while (!currentNode->isLeaf)
            currentNode = currentNode->children[currentNode->keyCount];
        return currentNode->keys[currentNode->keyCount - 1];
    }

    T getSuccessor(BNode<T>* currentNode) {
        while (!currentNode->isLeaf)
            currentNode = currentNode->children[0];
        return currentNode->keys[0];
    }

    void merge(BNode<T>* parentNode, int index) {
        BNode<T>* child = parentNode->children[index];
        BNode<T>* sibling = parentNode->children[index + 1];

        child->keys[order / 2 - 1] = parentNode->keys[index];

        for (int i = 0; i < sibling->keyCount; i++)
            child->keys[i + order / 2] = sibling->keys[i];

        if (!child->isLeaf) {
            for (int i = 0; i <= sibling->keyCount; i++)
                child->children[i + order / 2] = sibling->children[i];
        }

        for (int i = index + 1; i < parentNode->keyCount; i++)
            parentNode->keys[i - 1] = parentNode->keys[i];

        for (int i = index + 2; i <= parentNode->keyCount; i++)
            parentNode->children[i - 1] = parentNode->children[i];

        child->keyCount += sibling->keyCount + 1;
        parentNode->keyCount--;

        delete sibling;
    }

    void fill(BNode<T>* currentNode, int index) {
        if (index != 0 && currentNode->children[index - 1]->keyCount >= order / 2)
            merge(currentNode, index - 1);
        else if (index != currentNode->keyCount && currentNode->children[index + 1]->keyCount >= order / 2)
            merge(currentNode, index);
        else {
            if (index != currentNode->keyCount)
                merge(currentNode, index);
            else
                merge(currentNode, index - 1);
        }
    }



    void printTree(BNode<T>* node = nullptr) 
    {
        if (!node) node = root;

        if (node) 
        {
            // Traverse the keys and children in in-order sequence
            for (int i = 0; i < node->keyCount; i++) {
                // Print left child before the key
                if (!node->isLeaf) {
                    printTree(node->children[i]);
                }
                // Print the key
                std::cout << node->keys[i] << " ";
            }
            // Print the rightmost child
            if (!node->isLeaf) {
                printTree(node->children[node->keyCount]);
            }
        }
    }

    void printLevel(BNode<T>* currentNode, int level) 
    {
        if (currentNode) 
        {
            scout << "Level " << level << ": ";
            for (int i = 0; i < currentNode->keyCount; i++)
                cout << currentNode->keys[i] << " ";

            cout << std::endl;

            if (!currentNode->isLeaf) {
                for (int i = 0; i <= currentNode->keyCount; i++)
                    printLevel(currentNode->children[i], level + 1);
            }
        }
    }


};
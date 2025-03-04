// Group Member 1 : Mahad Malik (23I-0537)
// Group Member 2 : Mohammad Rayaan Raza (23I-0535)
// Group Member 3 : Awais Basheer ( 23I-0506)

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <ctime>
#include <iomanip>
#include <string>


using namespace std;
namespace fs = std::filesystem;

string to_String(int n);

template <typename T>
struct StackNode
{
	T data;
	StackNode* next;
	StackNode() : next(nullptr) {}
	StackNode(T value) : data(value), next(nullptr) {}
};

template <typename T>
class Stack
{
private:
	StackNode<T>* top;

public:
	Stack() : top(nullptr) {}

	~Stack()
	{
		while (!this->isEmpty())
			pop();
	}

	void push(T value)
	{
		StackNode<T>* newNode = new StackNode<T>(value);
		newNode->next = top;
		top = newNode;
	}

	void pop()
	{
		if (this->isEmpty())
			return;

		StackNode<T>* temp = top;
		top = top->next;
		T value = temp->data;
		delete temp;

		//return value;
	}

	T peek()
	{
		if (this->isEmpty())
			return;

		return top->data;
	}

	T Top()
	{
		return top->data;
	}


	void clear()
	{
		while (!isEmpty())
			pop();
	}

	void print()
	{
		StackNode<T>* temp = top;
		while (temp != nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	bool empty()
	{
		return top == nullptr;
	}

	bool isEmpty()
	{
		return top == nullptr;
	}
};

template <typename T>
struct AVLNode
{
    T data;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode() : data(T()), height(0), left(nullptr), right(nullptr) {}

    AVLNode(T data) : data(data), height(0), left(nullptr), right(nullptr) {}
};

template <typename T>
class AVLTree
{
    AVLNode<T>* root;


public:
    AVLTree() : root(nullptr) {}

    int getHeight(AVLNode<T>* root)
    {
        if (root == nullptr)
            return -1;
        return root->height;
    }

    void updateHeight(AVLNode<T>* node)
    {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    void insert(T data)
    {
        root = insertRec(root, data);
    }

    AVLNode<T>* insertRec(AVLNode<T>* node, T data)
    {
        if (node == nullptr)
            return new AVLNode<T>(data);

        if (data < node->data)
            node->left = insertRec(node->left, data);
        else
            node->right = insertRec(node->right, data);

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && data < node->left->data)
            return rightRotate(node);

        if (balance < -1 && data > node->right->data)
            return leftRotate(node);

        if (balance > 1 && data > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && data < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode<T>* rightRotate(AVLNode<T>* root)
    {
        AVLNode<T>* child = root->left;
        AVLNode<T>* rightChild = child->right;

        child->right = root;
        root->left = rightChild;

        updateHeight(root);
        updateHeight(child);

        return child;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* root)
    {
        AVLNode<T>* child = root->right;
        AVLNode<T>* leftChild = child->left;

        child->left = root;
        root->right = leftChild;

        updateHeight(root);
        updateHeight(child);

        return child;
    }

    int getBalance(AVLNode<T>* root)
    {
        if (root == nullptr)
            return 0;
        return getHeight(root->left) - getHeight(root->right);
    }

    void printInOrder(AVLNode<T>* root)
    {
        if (root == nullptr)
            return;

        printInOrder(root->left);
        cout << root->data << " ";
        printInOrder(root->right);
    }

    void printPreOrder(AVLNode<T>* root)
    {
        if (root == nullptr)
            return;

        cout << root->data << " ";
        printPreOrder(root->left);
        printPreOrder(root->right);
    }

    void printPostOrder(AVLNode<T>* root)
    {
        if (root == nullptr)
            return;

        printPostOrder(root->left);
        printPostOrder(root->right);
        cout << root->data << " ";
    }

    void remove(T removeItem)
    {
        root = removeRec(root, removeItem);
    }

    AVLNode<T>* removeRec(AVLNode<T>* root, T removeItem)
    {
        if (root == nullptr)
            return root;

        if (removeItem < root->data)
            root->left = removeRec(root->left, removeItem);
        else if (removeItem > root->data)
            root->right = removeRec(root->right, removeItem);
        else
        {

            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return nullptr;
            }
            else if (root->left == nullptr)
            {
                AVLNode<T>* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                AVLNode<T>* temp = root->left;
                delete root;
                return temp;
            }
            else
            {
                AVLNode<T>* temp = findMin(root->right);

                root->data = temp->data;

                root->right = removeRec(root->right, temp->data);
            }
        }

        updateHeight(root);

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    AVLNode<T>* getRoot()
    {
        return root;
    }

    void generateFiles(AVLNode<T>* node, const string& parentPath, const string& folderPath, vector<string> lineData, vector<string> fieldData)
    {

        if (node == nullptr)
            return;

        string fileName = folderPath + node->data + ".txt";

        int count = 0;

        while (fileExists(fileName))
        {
            count++;
            fileName = folderPath + node->data + to_String(count) + ".txt";
        }

        ofstream file(fileName);

        if (!file.is_open())
        {
            cout << "Error: Could not open file " << fileName << endl;
            return;
        }

        file << "Parent: " << (parentPath.empty() ? "NULL" : parentPath) << endl;


        for (int i = 0; i < lineData.size(); i++)
        {
            if (node->data == fieldData[i])
            {
                file << "Data :" << endl;
                istringstream lineStream(lineData[i]);
                string field;

                while (getline(lineStream, field, ','))
                    file << field << endl;

                lineData.erase(lineData.begin() + i);
                fieldData.erase(fieldData.begin() + i);
                break;
            }
        }

        file << "Left Child: " << (node->left ? (folderPath + node->left->data + ".txt") : "NULL") << endl;
        file << "Right Child: " << (node->right ? (folderPath + node->right->data + ".txt") : "NULL") << endl;

        file.close();

        generateFiles(node->left, fileName, folderPath, lineData, fieldData);
        generateFiles(node->right, fileName, folderPath, lineData, fieldData);
    }

    bool fileExists(const string& fileName)
    {
        ifstream file(fileName);
        return file.is_open();
    }


    vector<T> searchRange(T low, T high) {
        vector<T> result;
        Stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.Top();
            s.pop();

            if (current->data >= low && current->data <= high)
                result.push_back(current->data);

            if (current->data > high)
                break; // No need to explore further

            current = current->right;
        }

        return result;
    }

    void deleteRange(T low, T high) {
        Stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.Top();
            s.pop();

            if (current->data >= low && current->data <= high)
                remove(current->data); // Call iterative remove function

            if (current->data > high)
                break; // No need to explore further

            current = current->right;
        }
    }

    //void remove(T removeItem) {
    //    AVLNode<T>* current = root;
    //    AVLNode<T>* parent = nullptr;

    //    while (current != nullptr && current->data != removeItem) {
    //        parent = current;
    //        if (removeItem < current->data)
    //            current = current->left;
    //        else
    //            current = current->right;
    //    }

    //    if (current == nullptr)
    //        return; // AVLNode not found

    //    if (current->left == nullptr || current->right == nullptr) {
    //        AVLNode<T>* child = (current->left != nullptr) ? current->left : current->right;
    //        if (parent == nullptr)
    //            root = child; // Deleting root node
    //        else if (parent->left == current)
    //            parent->left = child;
    //        else
    //            parent->right = child;
    //        delete current;
    //    }
    //    else {
    //        AVLNode<T>* successorParent = current;
    //        AVLNode<T>* successor = current->right;
    //        while (successor->left != nullptr) {
    //            successorParent = successor;
    //            successor = successor->left;
    //        }

    //        current->data = successor->data;
    //        if (successorParent->left == successor)
    //            successorParent->left = successor->right;
    //        else
    //            successorParent->right = successor->right;

    //        delete successor;
    //    }
    //}


    void updateRange(T low, T high, T newValue) {
        Stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.top();
            s.pop();

            if (current->data >= low && current->data <= high) {
                T oldValue = current->data;
                remove(oldValue);     // Remove old node
                insert(newValue);      // Insert new value
            }

            if (current->data > high)
                break; // No need to explore further

            current = current->right;
        }
    }


    void updateRecordsByField(string fieldName, string fieldValue, string newField, string newValue) {
        Stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.Top();
            s.pop();

            if (current->data == fieldValue) {
                // Update logic (modify the text file for the node)
                string fileName = "C:\\Users\\armuj\\Desktop\\project_test\\src\\" + current->data + ".txt";
                updateFieldInFile(fileName, newField, newValue);
            }

            current = current->right;
        }
    }

    void deleteRecordsByField(string fieldName, string fieldValue) {
        Stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.Top();
            s.pop();

            if (current->data == fieldValue) {
                remove(current->data);
                string fileName = "C:\\Users\\armuj\\Desktop\\project_test\\src\\" + current->data + ".txt";
                removeFile(fileName);
            }

            current = current->right;
        }
    }

    void removeFile(const string& fileName) {
        if (filesystem::exists(fileName))
            filesystem::remove(fileName);
    }


    void deleteFirstRecordByField(string fieldName, string fieldValue) {
        Stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.Top();
            s.pop();

            if (current->data == fieldValue) {
                remove(current->data);
                string fileName = "C:\\Users\\armuj\\Desktop\\project_test\\src\\" + current->data + ".txt";
                removeFile(fileName);
                break; // Stop after deleting first match
            }

            current = current->right;
        }
    }

    void searchByPattern(const string& pattern) {
        Stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.Top();
            s.pop();

            if (matchesPattern(current->data, pattern))
                cout << "Match: " << current->data << endl;

            current = current->right;
        }
    }


    void updateRange(string low, string high, string fieldName, string newValue) {
        Stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.Top();
            s.pop();

            if (current->data >= low && current->data <= high) {
                string fileName = "C:\\Users\\armuj\\Desktop\\project_test\\src\\" + current->data + ".txt";
                updateFieldInFile(fileName, fieldName, newValue);
            }

            if (current->data > high)
                break;

            current = current->right;
        }
    }

    void updateFieldInFile(const string& fileName, const string& fieldName, const string& newValue) {
        if (!fs::exists(fileName))
            return;

        vector<string> fileLines;
        ifstream inFile(fileName);
        string line;

        while (getline(inFile, line))
        {
            if (line.find(fieldName + ":") != string::npos)
                line = fieldName + ": " + newValue;

            fileLines.push_back(line);
        }

        inFile.close();

        ofstream outFile(fileName);

        for (int i = 0; i < fileLines.size(); i++)
        {
            outFile << fileLines[i];
            if (i != fileLines.size() - 1)
                outFile << endl;
        }

        outFile.close();
    }


    void selectByPattern(string pattern)
    {
        Stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr)
        {
            while (current != nullptr)
            {
                s.push(current);
                current = current->left;
            }

            current = s.Top();
            s.pop();

            if (matchesPattern(current->data, pattern))
                displayNode(current);


            current = current->right;
        }
    }

    bool matchesPattern(const string& value, const string& pattern)
    {
        if (pattern.back() == '%')
        {
            string prefix = pattern.substr(0, pattern.size() - 1);
            return value.substr(0, prefix.size()) == prefix;
        }
        return false;
    }

    void displayNode(AVLNode<T>* node)
    {
        if (node == nullptr)
            return;

        string fileName = "C:\\Users\\armuj\\Desktop\\project_test\\src\\" + node->data + ".txt";
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << fileName << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }

    void menu()
    {
        int choice;
        string low, high, fieldName, newValue, pattern;
        cout << "1. Update records by range" << endl;
        cout << "2. Update records by field" << endl;
        cout << "3. Delete records by field" << endl;
        cout << "4. Delete first record by field" << endl;
        cout << "5. Search by pattern" << endl;
        cout << "6. Select by pattern" << endl;
		cout << "7. Inorder Traversal" << endl;
		cout << "8.Preorder Traversal" << endl;
		cout << "9. Postorder Traversal" << endl;
		cout << "10. Visualize Tree" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter low value: ";
            cin >> low;
            cout << "Enter high value: ";
            cin >> high;
            cout << "Enter field name: ";
            cin >> fieldName;
            cout << "Enter new value: ";
            cin >> newValue;
            updateRange(low, high, fieldName, newValue);
            break;
        case 2:
            cout << "Enter field name: ";
            cin >> fieldName;
            cout << "Enter field value: ";
            cin >> newValue;
            cout << "Enter new field name: ";
            cin >> fieldName;
            cout << "Enter new value: ";
            cin >> newValue;
            updateRecordsByField(fieldName, newValue, fieldName, newValue);
            break;
        case 3:
            cout << "Enter field name: ";
            cin >> fieldName;
            cout << "Enter field value: ";
            cin >> newValue;
            deleteRecordsByField(fieldName, newValue);
            break;
        case 4:
            cout << "Enter field name: ";
            cin >> fieldName;
            cout << "Enter field value: ";
            cin >> newValue;
            deleteFirstRecordByField(fieldName, newValue);
            break;
        case 5:
            cout << "Enter pattern: ";
            cin >> pattern;
            searchByPattern(pattern);
            break;
        case 6:
            cout << "Enter pattern: ";
            cin >> pattern;
            selectByPattern(pattern);
            break;
        case 7:
			printInOrder(root);
			break;
        case 8:
			printPreOrder(root);
			break;
		case 9:
			printPostOrder(root);
			break;
        case 10:
			visualizeTree(root);
			break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    AVLNode<T>* findMin(AVLNode<T>* root)
    {
        while (root->left != nullptr)
            root = root->left;
        return root;
    }


    void visualizeTree(AVLNode<T>* root, int space = 0, int height = 10) 
    {
        if (root == nullptr)
            return;

        space += height;

        visualizeTree(root->right, space);

        cout << endl;
        for (int i = height; i < space; i++)
            cout << " ";
        cout << root->data << "(" << root->height << ")" << endl;

        visualizeTree(root->left, space);
    }
};

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

        for (int i = 0; i < lineData.size(); i++)
        {
            if (node->data == fieldData[i])
            {
                file << "Data :" << endl;
                istringstream lineStream(lineData[i]);
                string field;

                while (getline(lineStream, field, ','))
                    file << field << endl;

                lineData.erase(lineData.begin() + i);
                fieldData.erase(fieldData.begin() + i);
                break;
            }
        }

        file << "Left Child: " << (node->left ? (folderPath + node->left->data + ".txt") : "NULL") << endl;
        file << "Right Child: " << (node->right ? (folderPath + node->right->data + ".txt") : "NULL") << endl;

        file.close();

        generateFiles(node->left, fileName, folderPath, lineData, fieldData);
        generateFiles(node->right, fileName, folderPath, lineData, fieldData);

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

int instructorHash(const string& value)
{
    long long hash = 1;

    for (char c : value)
    {
        if (isdigit(c))
            hash *= (c - '0');
        else
            hash *= static_cast<int>(c);

        hash %= 29;
    }

    return static_cast<int>(hash);
}

struct MerkleNode
{
    string data;
    int hash;
    MerkleNode* left;
    MerkleNode* right;

    MerkleNode(const string& value) : data(value), hash(instructorHash(value)), left(nullptr), right(nullptr) {}
};

class MerkleTree
{
private:
    MerkleNode* root;

    MerkleNode* buildTree(vector<MerkleNode*>& leaves)
    {
        if (leaves.size() == 1)
            return leaves[0];


        vector<MerkleNode*> parents;

        for (size_t i = 0; i < leaves.size(); i += 2)
        {
            if (i + 1 < leaves.size())
            {
                string combinedData = to_string(leaves[i]->hash) + to_string(leaves[i + 1]->hash);
                MerkleNode* parent = new MerkleNode(combinedData);
                parent->left = leaves[i];
                parent->right = leaves[i + 1];
                parents.push_back(parent);
            }
            else
            {
                parents.push_back(leaves[i]);
            }
        }

        return buildTree(parents);
    }

public:
    MerkleTree(const vector<string>& data)
    {
        vector<MerkleNode*> leaves;
        for (const string& value : data) {
            leaves.push_back(new MerkleNode(value));
        }

        root = buildTree(leaves);
    }

    int getRootHash() const
    {
        return root->hash;
    }

    void printTree(MerkleNode* node, int depth = 0) const
    {
        if (node == nullptr) return;

        for (int i = 0; i < depth; ++i) cout << "\t";
        cout << "Hash: " << node->hash << " (Data: " << node->data << ")" << endl;

        printTree(node->left, depth + 1);
        printTree(node->right, depth + 1);
    }

    void printTree() const
    {
        printTree(root);
    }

    ~MerkleTree()
    {
        deleteTree(root);
    }

private:
    void deleteTree(MerkleNode* node)
    {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
};

class Branching
{
public:
    string currentBranch;
    Branching() : currentBranch("C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\Initial Branch") {}

    string getCurrentBranch() { return currentBranch; }

    void createBranch()
    {
        string branchName;
        cout << "Enter the name of the new Branch: ";
        cin.ignore();
        getline(cin, branchName);

        string currentFolderPath = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches";
        string branchFolder = currentFolderPath + "\\" + branchName + "\\Node Files\\";

        if (fs::exists(branchFolder))
        {
            cout << "Error: Branch folder already exists!" << endl;
            return;
        }

        fs::create_directories(branchFolder);

        for (const auto& entry : fs::directory_iterator("C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\Initial Branch\\Node Files\\"))
        {
            const string sourceFile = entry.path().string();
            string destinationFile = branchFolder + entry.path().filename().string();

            if (fs::is_regular_file(entry))
                fs::copy(sourceFile, destinationFile, fs::copy_options::overwrite_existing);
        }

        cout << "Branch '" << branchName << "' created successfully." << endl;
        branchFolder = currentFolderPath + "\\" + branchName;
        currentBranch = branchFolder;
    }


    void switchBranch()
    {
        string parentDirectory = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\";
        vector<string> branchesNames;

        for (const auto& entry : fs::directory_iterator(parentDirectory))
        {
            if (fs::is_directory(entry))
                branchesNames.push_back(entry.path().filename().string());
        }

        cout << "Available Branches: " << endl;

        for (int i = 0; i < branchesNames.size(); i++)
            cout << i + 1 << ". " << branchesNames[i] << endl;

        cout << "Enter the number of the branch you want to switch to: ";
        int branchNumber;
        cin >> branchNumber;
        if (branchNumber < 1 || branchNumber > branchesNames.size())
        {
            cout << "Error: Invalid branch number!" << endl;
            return;
        }
        string branchFolder = parentDirectory + branchesNames[branchNumber - 1];
        currentBranch = branchFolder;
        cout << "Switched to branch '" << branchesNames[branchNumber - 1] << "'." << endl;
    }

    void deleteBranch()
    {
        string parentDirectory = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\";
        vector<string> branchesNames;
        for (const auto& entry : fs::directory_iterator(parentDirectory))
        {
            if (fs::is_directory(entry))
                branchesNames.push_back(entry.path().filename().string());
        }
        cout << "Available Branches: " << endl;
        for (int i = 0; i < branchesNames.size(); i++)
            cout << i + 1 << ". " << branchesNames[i] << endl;
        cout << "Enter the number of the branch you want to delete: ";
        int branchNumber;
        cin >> branchNumber;
        if (branchNumber < 1 || branchNumber > branchesNames.size())
        {
            cout << "Error: Invalid branch number!" << endl;
            return;
        }
        string branchFolder = parentDirectory + branchesNames[branchNumber - 1];
        fs::remove_all(branchFolder);
        cout << "Branch '" << branchesNames[branchNumber - 1] << "' deleted successfully." << endl;
    }

    void mergeBranch()
    {
        string parentDirectory = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\";
        vector<string> branchesNames;

        for (const auto& entry : fs::directory_iterator(parentDirectory))
        {
            if (fs::is_directory(entry))
                branchesNames.push_back(entry.path().filename().string());
        }

        cout << "Available Branches: " << endl;
        for (int i = 0; i < branchesNames.size(); i++)
            cout << i + 1 << ". " << branchesNames[i] << endl;

        cout << "Your current branch is: " << currentBranch << endl;
        cout << "Enter the number of the branch you want to merge with the current branch: ";
        int branchNumber;
        cin >> branchNumber;
        if (branchNumber < 1 || branchNumber > branchesNames.size())
        {
            cout << "Error: Invalid branch number!" << endl;
            return;
        }
        string branchFolder = parentDirectory + branchesNames[branchNumber - 1];
        for (const auto& entry : fs::directory_iterator(branchFolder))
        {
            const string& sourceFile = entry.path().string();
            string destinationFile = currentBranch + "\\" + entry.path().filename().string();

            if (fs::is_regular_file(entry))
                fs::copy(sourceFile, destinationFile);
        }
        cout << "Branch '" << branchesNames[branchNumber - 1] << "' merged successfully." << endl;
    }

    void menu()
    {
        int choice;
        cout << "1. Create a new branch" << endl;
        cout << "2. Switch to a branch" << endl;
        cout << "3. Delete a branch" << endl;
        cout << "4. Merge a branch" << endl;
        cout << "5. Display all branches" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            createBranch();
            break;
        case 2:
            switchBranch();
            break;
        case 3:
            deleteBranch();
            break;
        case 4:
            mergeBranch();
            break;
        case 5:
            displayAllBranches();
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    void displayAllBranches()
    {
        string parentDirectory = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\";
        vector<string> branchesNames;

        for (const auto& entry : fs::directory_iterator(parentDirectory))
        {
            if (fs::is_directory(entry))
                branchesNames.push_back(entry.path().filename().string());
        }

        cout << "Available Branches: " << endl;

        for (int i = 0; i < branchesNames.size(); i++)
            cout << i + 1 << ". " << branchesNames[i] << endl;
    }
};

class Commit
{
public:
    string folderPath;
    fstream commitlogFile;
    vector<int> commitNumbers;
    vector<string> commitPaths;

    Commit()
    {
        folderPath = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\Initial Branch";

        if (!fs::exists(folderPath))
            fs::create_directories(folderPath);

        commitPaths.push_back(folderPath);
        commitNumbers.push_back(0);
    }

    void commit(const string& currentBranch)
    {
        int index;
        bool found = false;


        for (int i = 0; i < commitPaths.size(); i++)
        {
            if (currentBranch==commitPaths[i])
            {
                index = i;
                found = true;
                break;
            }
        }

        int commitNumber = 0;

        if (found)
            commitNumber = ++commitNumbers[index];
        else
        {
            commitPaths.push_back(currentBranch);
            commitNumbers.push_back(0);
        }

        string commitFolderPath = currentBranch + "\\commits\\commit" + to_string(commitNumber);
        fs::create_directories(commitFolderPath);
        
        //cout << "Reached Here";
        commitlogFile.open(currentBranch + "\\commits\\commitlog.txt", ios::app);
        if (!commitlogFile.is_open())
        {
            cout << "Error: Could not open the commit log file!" << endl;
            return;
        }

        commitlogFile << "Commit Number: " << commitNumber << endl;
        time_t currentTime = time(nullptr);
        tm localTime;
        localtime_s(&localTime, &currentTime);
        commitlogFile << "Date and Time: " << put_time(&localTime, "%Y-%m-%d %H:%M:%S") << endl;

        string message;
        cin.ignore();
        cout << "Enter your commit message: ";
        getline(cin, message);
        commitlogFile << "Commit Message: " << message << endl;

        cout << "How many files do you want to commit? : ";
        int fileCount;
        cin >> fileCount;

        vector<string> files;
        for (int i = 0; i < fileCount; i++)
        {
            string fileName;
            cout << "Enter the file name with extension : ";
            cin >> fileName;

            if (!fs::exists(currentBranch + "\\Node Files\\" + fileName))
            {
                cout << "Error: File '" << fileName << "' does not exist in Node Files!" << endl;
                return;
            }

            files.push_back(fileName);
        }

        for (int i = 0; i < fileCount; i++)
            fs::copy_file(currentBranch + "\\Node Files\\" + files[i], commitFolderPath + "\\" + files[i], fs::copy_options::overwrite_existing);

        commitlogFile << "Files Committed: " << endl;
        for (int i = 0; i < fileCount; i++)
            commitlogFile << i + 1 << ". " << files[i] << endl;

        commitlogFile << "----------------------------------------------------" << endl;
        commitlogFile.close();
    }

    void displayCommitLog(const string& currentBranch)
    {
        commitlogFile.open(currentBranch + "commitlog.txt", ios::in);
        if (!commitlogFile.is_open())
        {
            cout << "Error: Could not open the commit log file!" << endl;
            return;
        }
        string line;
        while (getline(commitlogFile, line))
            cout << line << endl;
        commitlogFile.close();
    }

    void menu(string branchName)
    {
        cout << "1. Commit" << endl;
        cout << "2. Display Commit Log" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            commit(branchName);
            break;
        case 2:
            displayCommitLog(branchName);
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
};

class String
{
private:
    char* ptr;
    int size;
public:
    String()
    {
        this->ptr = nullptr;
        this->size = 0;
    }

    String(const char* str)
    {
        this->size = 0;
        for (int i = 0; str[i] != '\0'; i++)
            this->size++;

        this->ptr = new char[this->size + 1];

        for (int i = 0; str[i] != '\0'; i++)
            this->ptr[i] = str[i];

        ptr[this->size] = '\0';
    }

    String(const String& copy)
    {
        this->size = copy.size;

        this->ptr = new char[this->size + 1];

        for (int i = 0; copy.ptr[i] != '\0'; i++)
            this->ptr[i] = copy.ptr[i];

        this->ptr[this->size] = '\0';

    }

    String(int x)
    {
        this->size = x;

        this->ptr = new char[this->size + 1];

        for (int i = 0; i < this->size; i++)
            this->ptr[i] = NULL;

        this->ptr[this->size] = '\0';
    }

    char* getdata()
    {
        return this->ptr;
    }

    char* getData() const
    {
        return this->ptr;
    }

    char& operator[](int i) const
    {
        if (i >= 0)
        {
            if (i < this->size)
                return *(this->ptr + i);

        }
        else
        {
            int temp = this->size + i;

            if (temp >= 0 && temp < this->size)
                return *(this->ptr + temp);

        }
    }

    String operator+(const String& str)
    {
        String temp(this->ptr);

        delete[]this->ptr;
        this->ptr = nullptr;

        this->size = temp.size + str.size;
        this->ptr = new char[this->size + 1];
        int tempIndex = 0;

        for (int i = 0; temp.ptr[i] != '\0'; i++)
        {
            this->ptr[i] = temp.ptr[i];
            tempIndex++;
        }

        int j = 0;

        for (int i = tempIndex; i < this->size; i++)
        {
            this->ptr[i] = str.ptr[j];
            j++;
        }

        this->ptr[this->size] = '\0';

        return	*this;
    }

    String operator+(const char& str)
    {
        String temp(this->ptr);

        delete[]this->ptr;
        this->ptr = nullptr;

        this->size = temp.size + 1;
        this->ptr = new char[this->size + 1];

        for (int i = 0; i <= this->size; i++)
            this->ptr[i] = temp.ptr[i];

        this->ptr[this->size - 1] = str;
        this->ptr[this->size] = '\0';

        return *this;
    }

    String operator+(const char* str)
    {
        String temp(this->ptr);

        delete[]this->ptr;
        this->ptr = nullptr;

        int strSize = 0;
        for (int i = 0; str[i] != '\0'; i++)
            strSize++;

        this->size = temp.size + strSize;
        this->ptr = new char[this->size + 1];

        int tempIndex = 0;

        for (int i = 0; temp.ptr[i] != '\0'; i++)
        {
            this->ptr[i] = temp.ptr[i];
            tempIndex++;
        }

        int j = 0;

        for (int i = tempIndex; i < this->size; i++)
        {
            this->ptr[i] = str[j];
            j++;
        }

        this->ptr[this->size] = '\0';

        return	*this;
    }

    String operator-(const String& substr)
    {
        int loopCount = 0;
        for (int i = 0; i < this->size; i++)
        {
            if (this->ptr[i] == substr.ptr[0])
                loopCount++;
        }

        for (int k = 0; k < loopCount; k++)
        {
            int i = 0, j = 0, c = 0, endIndex = 0;

            while (this->ptr[i] != '\0')
            {
                if (this->ptr[i] != substr.ptr[j])
                    i++;
                else if (this->ptr[i] == substr.ptr[j])
                {
                    while (substr.ptr[j] != '\0')
                    {
                        if (this->ptr[i] == substr.ptr[j])
                        {
                            endIndex = i;
                            i++;
                            j++;
                            c++;
                        }
                        else
                        {
                            c = 0;
                            break;
                        }
                    }
                }
            }

            int startIndex = endIndex - (substr.size - 1);

            if (c != 0)
            {
                String temp(this->ptr);
                delete this->ptr;
                this->size = this->size - substr.size;
                this->ptr = new char[this->size + 1];
                int l = 0;
                for (int k = 0; k < temp.size; k++)
                {
                    if (k<startIndex || k>endIndex)
                    {
                        this->ptr[l] = temp.ptr[k];
                        l++;
                    }
                }
                this->ptr[this->size] = '\0';
            }
        }

        return *this;
    }

    String operator-(const char& str)
    {
        int count = 0;
        String temp(this->ptr);
        for (int i = 0; i < this->size; i++)
        {
            if (this->ptr[i] == str)
                count++;
        }

        this->size -= count;

        delete this->ptr;

        this->ptr = new char[this->size + 1];

        int j = 0;

        for (int i = 0; i < temp.size; i++)
        {
            if (temp.ptr[i] != str)
            {
                this->ptr[j] = temp.ptr[i];
                j++;
            }
        }

        this->ptr[this->size] = '\0';

        return *this;
    }

    String operator-(const char* str)
    {

        int strSize = 0;
        for (int i = 0; str[i] != '\0'; i++)
            strSize++;

        int loopCount = 0;
        for (int i = 0; i < this->size; i++)
        {
            if (this->ptr[i] == str[0])
                loopCount++;
        }

        for (int k = 0; k < loopCount; k++)

        {
            int i = 0, j = 0, c = 0, endIndex = 0;

            while (this->ptr[i] != '\0')
            {
                if (this->ptr[i] != str[j])
                    i++;
                else if (this->ptr[i] == str[j])
                {
                    while (str[j] != '\0')
                    {
                        if (this->ptr[i] == str[j])
                        {
                            endIndex = i;
                            i++;
                            j++;
                            c++;
                        }
                        else
                        {
                            c = 0;
                            break;
                        }
                    }
                }
            }

            int startIndex = endIndex - (strSize - 1);

            if (c != 0)
            {
                String temp(this->ptr);
                delete this->ptr;
                this->size = this->size - strSize;
                this->ptr = new char[this->size + 1];
                int l = 0;
                for (int k = 0; k < temp.size; k++)
                {
                    if (k<startIndex || k>endIndex)
                    {
                        this->ptr[l] = temp.ptr[k];
                        l++;
                    }
                }
                this->ptr[this->size] = '\0';
            }
        }

        return *this;
    }

    String& operator=(const String& copy)
    {
        delete[]this->ptr;

        this->size = 0;
        this->size = copy.size;
        this->ptr = new char[this->size + 1];

        for (int i = 0; i < this->size; i++)
            this->ptr[i] = copy.ptr[i];

        this->ptr[this->size] = '\0';

        return *this;
    }

    String& operator=(char* str)
    {

        delete[]this->ptr;
        this->ptr = nullptr;

        int strSize = 0;
        for (int i = 0; str[i] != '\0'; i++)
            strSize++;

        this->size = strSize;
        this->ptr = new char[this->size + 1];

        for (int i = 0; str[i] != '\0'; i++)
            this->ptr[i] = str[i];

        this->ptr[this->size] = '\0';

        return	*this;
    }

    String& operator+=(const char& str)
    {
        String temp(this->ptr);

        delete[]this->ptr;
        this->ptr = nullptr;

        this->size = temp.size + 1;
        this->ptr = new char[this->size + 1];

        for (int i = 0; i <= this->size; i++)
            this->ptr[i] = temp.ptr[i];

        this->ptr[this->size - 1] = str;
        this->ptr[this->size] = '\0';

        return *this;
    }

    bool operator==(const String& copy) const
    {
        bool check = true;

        if (this->size == copy.size)
        {
            for (int i = 0; i < this->size; i++)
            {
                if (this->ptr[i] == copy.ptr[i])
                    check = true;
                else
                    check = false;

                if (check == 0)
                    return false;
            }
        }
        else
            return false;

        if (check)
            return true;
    }

    bool operator==(const char* str) const
    {
        bool check = true;

        int strSize = 0;
        for (int i = 0; str[i] != '\0'; i++)
            strSize++;

        if (this->size == strSize)
        {
            for (int i = 0; i < this->size; i++)
            {
                if (this->ptr[i] == str[i])
                    check = true;
                else
                    check = false;

                if (check == 0)
                    return false;
            }
        }
        else
            return false;

        if (check)
            return true;
    }

    bool operator!()
    {
        if (this->ptr[0] == '\0')
            return true;
        else
            return false;
    }

    int operator()(char c) const
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->ptr[i] == c)
                return i;
        }

        return -1;
    }

    int operator()(const String& substr) const
    {
        int i = 0, j = 0, c = 0, endIndex = 0;

        while (this->ptr[i] != '\0')
        {
            if (this->ptr[i] != substr.ptr[j])
                i++;
            else if (this->ptr[i] == substr.ptr[j])
            {
                while (substr.ptr[j] != '\0')
                {
                    if (this->ptr[i] == substr.ptr[j])
                    {
                        endIndex = i;
                        i++;
                        j++;
                        c++;
                    }
                    else
                    {
                        c = 0;
                        break;
                    }
                }
            }
        }

        int startIndex = endIndex - (substr.size - 1);

        if (c != 0)
            return startIndex;
        else
            return -1;

    }

    int operator()(const char* str) const
    {
        int strSize = 0;
        for (int i = 0; str[i] != '\0'; i++)
            strSize++;

        int i = 0, j = 0, c = 0, endIndex = 0;

        while (this->ptr[i] != '\0')
        {
            if (this->ptr[i] != str[j])
                i++;
            else if (this->ptr[i] == str[j])
            {
                while (str[j] != '\0')
                {
                    if (this->ptr[i] == str[j])
                    {
                        endIndex = i;
                        i++;
                        j++;
                        c++;
                    }
                    else
                    {
                        c = 0;
                        break;
                    }
                }
            }
        }

        int startIndex = endIndex - (strSize - 1);

        if (c != 0)
            return startIndex;
        else
            return -1;

    }

    operator int() const
    {
        int length = 0;
        for (int i = 0; this->ptr[i] != '\0'; i++)
            length++;

        return length;
    }

    bool operator>(const String& str)
    {
        int i = 0;

        while (this->ptr[i] != '\0' && str.ptr[i] != '\0')
        {
            if (this->ptr[i] > str.ptr[i])
                return true;
            else if (this->ptr[i] < str.ptr[i])
                return false;
            i++;
        }

        if (this->ptr[i] == '\0' && str.ptr[i] != '\0')
            return false;
        else
            return true;
    }

    /*bool operator=(const string& str)
    {

    }*/

    ~String()
    {
        delete[] ptr;
    }

};

ostream& operator<<(ostream& output, const String& str)
{
    output << str.getData();
    return output;
}

istream& operator>>(istream& input, String& str)
{
    char temp[1000];
    input >> temp;
    str = temp;
    return input;
}

string to_String(int n)
{
    string str;
    while (n != 0)
    {
        str = (char)(n % 10 + 48) + str;
        n /= 10;
    }
    return str;
}

template <typename T>
class Vector
{
private:
    T* data;
    int capacity;
    int size;
    void resize()
    {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[newCapacity];

        for (int i = 0; i < size; i++)
            newData[i] = data[i];

        delete[] data;

        data = newData;
        capacity = newCapacity;
    }

public:
    Vector() : data(nullptr), capacity(0), size(0) {}

    ~Vector()
    {
        delete[] data;
    }

    void push_back(const T& value)
    {
        if (size == capacity)
            resize();

        data[size++] = value;
    }

    T& operator[](int index)
    {
        return data[index];
    }

    int getSize()
    {
        return size;
    }

    int getCapacity()
    {
        return capacity;
    }

    void erase(int index)
    {
        if (index < 0 || index >= size)
            return;

        for (int i = index; i < size - 1; i++)
            data[i] = data[i + 1];

        size--;
    }
};

string Introduction()
{
	cout << "Welcome to our  GITLite" << endl << "Our very own Version Control System!" << endl;
	cout << endl << endl << "Enter the file name (with Extension) to Initialize the repository: ";
	string fileName;
	getline(cin, fileName);
	return fileName;
}


int main()
{
	RedBlackTree<string> RBtree;
	AVLTree<string> AVLtree;
	ifstream file(Introduction());

	if (!file.is_open())
	{
		cout << "Error: Could not open the file " << endl;
		return 0;
	}

	string line;

	getline(file, line);
	istringstream lineStream(line);
	string field;

	int fieldCount = 1;
	Vector<string> fields;  // Column names

	while (getline(lineStream, field, ','))
	{
		cout << "Field " << fieldCount << ": " << field << endl;
		fields.push_back(field);
		fieldCount++;
	}

	cout << "Enter a field number to choose : ";
	int fieldNumber;
	cin >> fieldNumber;
	string folderPath = "C:\\Users\\HP\\Desktop\\Data Structures Project\\.git\\branches\\Initial Branch\\Node Files\\";
    fs::create_directories(folderPath);

	vector<string> lineDetails;  // Each line of the file
	vector<string> fieldDetails;  //Each selected field data from the file

	int choice = 0;

	cout << "Choose the Tree data structure to store the data: " << endl;
	cout << "1. Red Black Tree" << endl;
	cout << "2. AVL Tree" << endl;
	cin >> choice;

	while (choice != 1 && choice != 2)
	{
		cout << "Invalid choice! Please enter a valid choice: ";
		cin >> choice;
	}


	while (getline(file, line))
	{
		lineDetails.push_back(line);
		istringstream lineStream(line);
		string field;
		int count = 1;

		while (getline(lineStream, field, ','))
		{
			if (count == fieldNumber)
			{
				if (choice == 1)
					RBtree.insert(field);
				else
					AVLtree.insert(field);

				fieldDetails.push_back(field);
			}
				
			count++;
		}
	}

	file.close();

	cout << "Initializing Tree ....." << endl;
	if (choice == 1)
		RBtree.generateFiles(RBtree.getRoot(), "", folderPath, lineDetails, fieldDetails);
	else
		AVLtree.generateFiles(AVLtree.getRoot(), "", folderPath, lineDetails, fieldDetails);

	cout << "Tree Initialized Successfully!" << endl;
	Commit commit;
	//commit.commit();
	Branching branch;

	bool loopvar = true;
	while (loopvar)
	{
		cout << endl << endl << "Choose an option: " << endl;
		cout << "1. Handle Queries on Current Created Files :" << endl;
		cout << "2. Handle Branching :" << endl;
		cout << "3. Commit Changes :" << endl;
		cout << "4. Exit" << endl;

		cout << "Enter your choice: ";
		int schoice;
		cin >> schoice;

		switch (schoice)
		{
		case 1:
			if(choice==1)
				RBtree.menu();
			else
				AVLtree.menu();
		case 2:
			branch.menu();
			break;
		case 3:
			commit.menu(branch.getCurrentBranch());
			break;
		case 4:
			loopvar = false;
			break;
		}
	}

	return 0;
}

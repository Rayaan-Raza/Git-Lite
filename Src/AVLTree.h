#pragma once

#include "All.h"


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
	vector<string> lineData;
	vector<string> fieldData;

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
        stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.top();
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
        stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.top();
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
        stack<AVLNode<T>*> s;
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
        stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.top();
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
        stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.top();
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
        stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.top();
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
        stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.top();
            s.pop();

            if (matchesPattern(current->data, pattern))
                cout << "Match: " << current->data << endl;

            current = current->right;
        }
    }


    void updateRange(string low, string high, string fieldName, string newValue) {
        stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }

            current = s.top();
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
        stack<AVLNode<T>*> s;
        AVLNode<T>* current = root;

        while (!s.empty() || current != nullptr) 
        {
            while (current != nullptr) 
            {
                s.push(current);
                current = current->left;
            }

            current = s.top();
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

};










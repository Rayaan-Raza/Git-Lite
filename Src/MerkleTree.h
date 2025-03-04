#pragma once 

#include "All.h"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

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



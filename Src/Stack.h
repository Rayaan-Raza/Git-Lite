#pragma once

#include "All.h"

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
        while (!isEmpty())
            pop();
    }

    void push(T value)
    {
        StackNode<T>* newNode = new StackNode<T>(value);
        newNode->next = top;
        top = newNode;
    }

    T pop()
    {
        if (isEmpty())
            return;

        StackNode<T>* temp = top;
        top = top->next;
        T value = temp->data;
        delete temp;
        return value;
    }

    T peek()
    {
        if (isEmpty())
            return;

        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
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
};
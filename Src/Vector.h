#pragma once

#include<iostream>
using namespace std;

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

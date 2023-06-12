#include <bits/stdc++.h>
using namespace std;

// my own vector class
template <typename T>
class my_vector
{
    T *arr;
    int capacity;
    int current;

public:
    // initialization my_vector using class constructor
    my_vector()
    {
        arr = new T[1];
        capacity = 1;
        current = 0;
    }

    // destructor for deallocate after going out of scope
    ~my_vector()
    {
        delete[] arr;
    }

    void push_back(T element)
    {
        // dynamically increasing capacity
        if (current == capacity)
        {
            // Use nothrow to avoid exceptions
            T *temp = new T[2 * capacity];

            if (temp == nullptr)
            {
                cout << "Memory allocation failed" << endl;
                return;
            }

            for (int i = 0; i < capacity; i++)
            {
                temp[i] = arr[i];
            }

            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        // data insertion
        arr[current] = element;
        current++;
    }

    void pop()
    {
        current--;
    }

    int size()
    {
        return current;
    }

    int get_capacity()
    {
        return capacity;
    }

    bool empty() { return current == 0; }

    /* ----------------------------------------
                    iterator class start
        -------------------------------------- */
    class iterator
    {
    public:
        T *ptr;

    public:
        explicit iterator(T *p = nullptr) : ptr(p) {}
        // operator overloading
        T &operator*() const { return *ptr; }
        iterator &operator++() // pre increment overloading
        {
            ++ptr;
            return *this;
        }

        iterator operator++(int) // post increment overloading
        {
            iterator tmp(*this);
            ++ptr;
            return tmp;
        }

        iterator operator+(int index) const
        {
            return iterator(ptr + index);
        }
        bool operator==(const iterator &other) const { return ptr == other.ptr; }
        bool operator!=(const iterator &other) const { return ptr != other.ptr; }
    };

    /* ### iterator class ends */

    // declaring begin and end iterator
    iterator begin() { return iterator(arr); }
    iterator end() { return iterator(arr + current); }

    T &operator[](int index)
    {
        if (index >= 0 && index < current)
        {
            return arr[index];
        }
        else
        {
            throw out_of_range("Index out of range");
        }
    }

    void erase(iterator pos)
    {
        if (pos.ptr >= arr && pos.ptr < arr + current)
        {
            for (T *ptr = pos.ptr; ptr < arr + current - 1; ++ptr)
            {
                *ptr = *(ptr + 1);
            }
            current--;
        }
        else
            throw out_of_range("Invalid Iterator");
    }
};
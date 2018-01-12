#pragma once

#include <utility>

template<typename T>
class Vector {
public:
    /*
     * Constructors and destructors
     */

    // Default constructor, that fills all class settings to zero or nullptr
    Vector() : size(0), capacity(0), data(nullptr) {}

    // Constructor, creates container with requested size
    Vector(size_t inputSize) : size(inputSize), capacity(inputSize), data(nullptr) {}

    // Constructor, creates container with requested size and fill it with values
    Vector(size_t inputSize, T const &value) : size(inputSize), capacity(inputSize), data(new T[inputSize]) {
        for (std::size_t i = 0; i < inputSize; i++)
            data[i] = value;
    }
    // Constructor that takes another vector
    Vector(Vector const &otherVector): size(a.size), capacity(a.capacity), data(new T[capacity]){
        for (std::size_t i = 0; i < size; i++)
            data[i] = otherVector.data[i];
    };
    // Simplified move constructor
    Vector(Vector && otherVector): data(nullptr), size(0), capacity(0){
        *this = std::move(otherVector);
    };
    // Default destructor that deletes only data, created by 'New'
    ~Vector() {
        delete[] data;
    };


    /*
     * Getters
     */
    T &operator[](std::size_t i) {
        return data[i];
    };
    T const &operator[](std::size_t i) const {
        return data[i];
    };

    T &at(std::size_t i) {
        // Sorry for this way of error throw
        if (i >= size)
            std::cerr << "out of range\n";
        return data[i];
    };
    T const &at(std::size_t i) const {
        if (i >= size)
            std::cerr << "out of range\n";
        return data[i];
    };


    /*
     * Functions for resizing
     */
    void resize(std::size_t inputSize) {
        if (inputSize > capacity) {
            add_size(inputSize);
        }
        size = inputSize;
    };

    void resize(std::size_t inputSize, T const &n) {
        if (inputSize > capacity) {
            add_size(inputSize);
            for (std::size_t i = size; i < inputSize; i++)
                data[i] = n;
        }
        size = inputSize;
    };

    void reserve(std::size_t inputSize) {
        if (inputSize > capacity) {
            add_size(inputSize);
        }
    };

    /*
     * Operators
     */
    Vector<T> &operator=(Vector const &a) {
        if (this != &a) {
            delete[] data;
            size = a.size;
            capacity = a.capacity;
            data = new T[capacity];
            for (std::size_t i = 0; i < size; i++)
                data[i] = a.data[i];
        }
        return *this;
    };
    // move operator
    Vector &operator=(Vector &&v){
        // Checking this for not destroying our data
        if (this != &v){
            delete[] data;
            data = v.data;
            size = v.size;
            capacity = v.capacity;
        }
        return *this;
    };
    /*
     * Push back's
     */
    void push_back(T const &value) {
        if (size == capacity) reserve(2 * capacity);
        data[size++] = value;
    };

    void push_back(T &&value) {
        if (size == capacity) reserve(2 * capacity);
        data[size++] = std::move(value);
    };
    // And length
    std::size_t length() const {
        return size;
    };

private:

    void add_size(std::size_t inputSize) {
        auto *new_data = new T[inputSize];
        capacity = inputSize;
        for (std::size_t i = 0; i < inputSize; i++)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
    };

    std::size_t capacity, size;
    T *data;

};

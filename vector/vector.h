#pragma once
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    uint64_t _capacity = 10;
    T* vector = nullptr;
    size_t _begin = 0;
    size_t _end = 0;
    int gap_space = 5;

    void allocate() {
        // allocate to left
        if (_begin < gap_space) {
            T* to_delete = vector;
            _capacity *= 2;
            vector = new T[_capacity];
            for (size_t i = _begin; i != _end; ++i) {
                vector[_capacity / 2 + i] = to_delete[i];
            }
            _begin += _capacity / 2;
            _end += _capacity / 2;
            delete[] to_delete;
        }
        // allocate to right
        if (_capacity - _end <= gap_space) {
            T* to_delete = vector;
            _capacity *= 2;
            vector = new T[_capacity];
            for (size_t i = 0; i != _end - _begin; ++i) {
                vector[i] = to_delete[i];
            }
            delete[] to_delete;
        }
    }
public:
    size_t begin() const;
    size_t end() const;
    size_t capacity() const;

    T& operator [] (size_t i) const {
        if (_begin + i >= _end) {
            std::cerr << _begin + i << ' ' << _end << '\n';
            throw std::out_of_range("index error");
        }
        return vector[_begin + i];
    }

    Vector() = default;
    Vector(size_t n);

    bool empty() const;

    Vector& push_front(const T& _value);
    Vector& push_back(const T& _value);

    ~Vector() {
        // recursively delete all vectors included.
        std::cout << "delete this -> " << vector << ' ' << this->begin() << ' ' << this->end() << ' ' << this->capacity() << '\n';
        delete[] vector;
    }
};

template <typename T>
Vector<T>::Vector(size_t n) {
    _capacity = n;
    T* vector = new T[n];
}

template <typename T>
size_t Vector<T>::capacity() const {
    return _capacity;
}

template <typename T>
size_t Vector<T>::begin() const {
    return _begin;
}

template <typename T>
size_t Vector<T>::end() const {
    return _end;
}

template <typename T>
bool Vector<T>::empty() const {
    return _begin == _end;
}

template <typename T>
Vector<T>& Vector<T>::push_front(const T& value) {
    this->allocate();
    vector[--_begin] = value;
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::push_back(const T& value) {
    this->allocate();
    vector[_end++] = value; 
    return *this;
}
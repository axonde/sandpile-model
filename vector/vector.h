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
            for (size_t i = _begin; i != _end; ++i) {
                vector[i] = to_delete[i];
            }
            delete[] to_delete;
        }
    }

public:
    T& operator [] (size_t i) const {
        if (_begin + i >= _end) {
            std::cerr << "log error: " << _begin + i << ' ' << _end << '\n';
            std::cout << "\e[35muse function .at() to check cell's owning to vector\e[0m" << '\n';
            throw std::out_of_range("index error");
        }
        return vector[_begin + i];
    }

    size_t begin() const;
    size_t end() const;
    size_t capacity() const;

    Vector() = default;
    Vector(size_t n);

    Vector& operator = (const Vector& v) {
        _capacity = v.capacity();
        vector = new T[_capacity];
        _begin = v.begin();
        _end = v.end();
        for (size_t i = _begin; i != _end; ++i) {
            vector[i] = v[i - _begin];
        }
        return *this;
    }

    size_t size() const;
    bool empty() const;
    bool at(size_t i) const;

    Vector& push_front(const T& _value);
    Vector& push_back(const T& _value);

    ~Vector() {
        // recursively delete all vectors included.
        delete[] vector;
    }
};

template <typename T>
Vector<T>::Vector(size_t n) {
    _capacity = n;
    vector = new T[n];
    _end = n;
}

template <typename T>
size_t Vector<T>::begin() const {
    return _begin;
}

template <typename T>
size_t Vector<T>::capacity() const {
    return _capacity;
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
bool Vector<T>::at(size_t i) const {
    if (i >= 0 && i < _end - _begin) {
        return true;
    }
    return false;
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

template <typename T>
size_t Vector<T>::size() const {
    return _end - _begin;
}

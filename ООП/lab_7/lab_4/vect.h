#ifndef VECT_H
#define VECT_H

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include "exceptions.h"
#include "iterator_interface.h"
using namespace std;

template <typename T>
class Vect {
private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void check_bounds(size_t index) const {
        if (index >= size) {
            throw VectException("Index out of bounds");
        }
    }

    void increase_capacity() {// добавила увеличение емкости копированием
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* new_data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }

public:
    Vect() = default;

    Vect(std::initializer_list<T> list)
        : size(list.size()), capacity(list.size()) {
        data = new T[capacity];
        size_t i = 0;
        for (const T& elem : list) {
            data[i++] = elem;
        }
    }

    Vect(const Vect& other)
        : size(other.size), capacity(other.capacity) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    Vect& operator=(const Vect& other) {
        if (this == &other) return *this;
        delete[] data;

        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    Vect(Vect&& other) noexcept
        : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    Vect& operator=(Vect&& other) noexcept {
        if (this == &other) return *this;

        delete[] data;
        data = other.data;
        size = other.size;
        capacity = other.capacity;

        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
        return *this;
    }

    ~Vect() {
        delete[] data;
    }

    void push_back(const T& value) {// добавлено
        if (size == capacity) {
            increase_capacity();//для увеличения из прошлой лабы
        }
        data[size++] = value;
    }

    T& operator[](size_t index) {
        check_bounds(index);
        return data[index];
    }

    const T& operator[](size_t index) const {
        check_bounds(index);
        return data[index];
    }

    size_t get_size() const { return size; }

    bool empty() const { return size == 0; }

    void clear() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    // Итератор слева направо
    class ForwardIterator : public IteratorInterface<T> {
    private:
        const Vect<T>& vect;
        size_t current_index = 0;

    public:
        explicit ForwardIterator(const Vect<T>& vect) : vect(vect) {}

        bool has_next() const override {// на пустоту
            return current_index < vect.size;
        }

        T next() override {
            if (!has_next()) {
                throw VectException("No more elements in ForwardIterator");
            }
            return vect.data[current_index++];
        }
    };

    // Итератор справа налево
    class ReverseIterator : public IteratorInterface<T> {
    private:
        const Vect<T>& vect;
        size_t current_index;

    public:
        explicit ReverseIterator(const Vect<T>& vect) : vect(vect), current_index(vect.size) {}

        bool has_next() const override {
            return current_index > 0;
        }

        T next() override {
            if (!has_next()) {
                throw VectException("No more elements in ReverseIterator");
            }
            return vect.data[--current_index];
        }
    };

    ForwardIterator forward_iterator() const {//добавлено
        if (empty()) {
            throw VectException("Cannot create ForwardIterator for an empty collection");
        }
        return ForwardIterator(*this);
    }

    ReverseIterator reverse_iterator() const {
        if (empty()) {
            throw VectException("Cannot create ReverseIterator for an empty collection");
        }
        return ReverseIterator(*this);
    }
};

#endif // VECT_H
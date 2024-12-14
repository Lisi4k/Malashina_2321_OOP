#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include <stdexcept>

template <typename T>
class SmartPointer {
private:
    T* ptr;

public:
    SmartPointer(T* p = nullptr) : ptr(p) {}
    ~SmartPointer() { delete ptr; }

    T& operator*() {
        if (!ptr) throw std::runtime_error("Dereferencing null pointer");
        return *ptr;
    }
    T* operator->() { return ptr; }
    T* get() { return ptr; }
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;
};

#endif // SMART_POINTER_H

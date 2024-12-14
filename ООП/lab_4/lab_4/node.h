#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T value;
    Node* next = nullptr;
    Node* prev = nullptr;

    Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
};

#endif // NODE_H

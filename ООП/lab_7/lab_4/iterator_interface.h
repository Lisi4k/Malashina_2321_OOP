#ifndef ITERATOR_INTERFACE_H
#define ITERATOR_INTERFACE_H

template <typename T>
class IteratorInterface {
public:
    virtual ~IteratorInterface() = default;
    virtual bool has_next() const = 0;
    virtual T next() = 0;
};

#endif // ITERATOR_INTERFACE_H
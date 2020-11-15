#ifndef OOP_EXERCISE_05_STACK_H
#define OOP_EXERCISE_05_STACK_H

#include "Rectangle.h"

template<class T>
struct Node;

template<class T>
void operator++(std::shared_ptr<Node<T>> &curNode) {
    if (curNode) {
        curNode = curNode->prev;
    }
    else {
        throw std::out_of_range("Iterator has already in nullptr");
    }
}

template<class T>
bool operator!=(const Node<T> &lhs, const Node<T> &rhs) {
    return &lhs != &rhs;
}

template<class T>
bool operator==(const Node<T> &lhs, const Node<T> &rhs) {
    return &lhs.data == &rhs.data;
}

template<class T>
std::ostream &operator<<(std::ostream &cout, const Node<T> &node) {
    cout << node.data;
    return cout;
}

template<class T>
struct Node {
    T data;
    std::shared_ptr<Node> prev;


    Node() : prev(nullptr) {
    }

    Node(const T &val) : data(val) {
    }

    friend void operator++<>(std::shared_ptr<Node<T>> &n);

    friend bool operator!=<>(const Node<T> &lhs, const Node<T> &rhs);

    friend bool operator==<>(const Node<T> &lhs, const Node<T> &rhs);

    friend std::ostream &operator<<<>(std::ostream &cout, const Node<T> &obj);
};


template<class T>
class Stack {
private:
    size_t size = 0;
    std::shared_ptr<Node<T>> head;
public:

    class iterator {
    private:
        std::shared_ptr<Node<T>> iter;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        iterator() : iter(nullptr) {
        }

        explicit iterator(const std::shared_ptr<Node<T>> &anotherIter) : iter(anotherIter) {
        }

        bool isNull() {
            return iter == nullptr;
        }

        friend void operator++(iterator &it) {
            ++it.iter;
        }

        friend bool operator!=(const Stack<T>::iterator &lhs, const Stack<T>::iterator &rhs) {
            return lhs.iter != rhs.iter;
        }

        friend std::ostream &operator<<(std::ostream &out, const iterator &it) {
            out << *it.iter;
            return out;
        }

        Node<T> &operator*() {
            return *iter;
        }
    };

    Stack() noexcept: head(nullptr) {
    }

    void pop() {
        if (head) {
            head = head->prev;
            --size;
        }
        else {
            throw std::runtime_error("Stack is empty");
        }
    }

    void push(const T &val) {
        Node<T> *newNode = new Node<T>(val);
        std::shared_ptr<Node<T>> newPtr{newNode};
        newPtr->prev = head;
        head = newPtr;
        ++size;
    }

    T top() {
        if (head) {
            return head->data;
        }
        else {
            throw std::runtime_error("Nullptr in head");
        }
    }

    void insert(Stack<T>::iterator &it, const T &elem) {
        std::unique_ptr<Node<T>> newNode{new Node<T>(elem)};
        std::shared_ptr<Node<T>> newPtr = std::move(newNode);
        std::shared_ptr<Node<T>> prevPtr = head;

        if (prevPtr) {
            if (!it.isNull()) {
                while (*prevPtr->prev != *it) {
                    ++prevPtr;
                }
            }
            else {
                while (prevPtr->prev != nullptr) {
                    ++prevPtr;
                }
            }
            newPtr->prev = prevPtr->prev;
            prevPtr->prev = newPtr;
        }
        else {
            head = newPtr;
        }
        ++size;
    }

    void erase(iterator &it) {
        if (it.isNull()) {
            throw std::runtime_error("Iterator is in nullptr state");
        }
        else {
            if (*it == *head) {
                head = head->prev;
            }
            else {
                std::shared_ptr<Node<T>> prevPtr = head;
                while (*prevPtr->prev != *it) {
                    ++prevPtr;
                }
                prevPtr->prev = prevPtr->prev->prev;
            }
            --size;
        }

    }

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    size_t getSize() {
        return size;
    }
};

#endif //OOP_EXERCISE_05_STACK_H

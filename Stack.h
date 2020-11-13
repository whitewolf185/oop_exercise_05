#ifndef OOP_EXERCISE_05_STACK_H
#define OOP_EXERCISE_05_STACK_H
#include "Rectangle.h"

template<class T>
struct Node {
    T data;
    std::shared_ptr<Node> prev;

    Node() : prev(nullptr) {}
    Node(const T &val) : data(val) {}
    friend void operator++(std::shared_ptr<Node<T>>&);
    friend bool operator!=(const std::shared_ptr<Node<T>>&,const std::shared_ptr<Node<T>>&);
    friend bool operator==(const std::shared_ptr<Node<T>>&, const std::shared_ptr<Node<T>>&);
    friend std::ostream& operator<<(std::ostream&, const Node<T>&);
};

template<class T>
class Stack {
private:

    std::shared_ptr<Node<T>> head;
public:

    class iterator{
    private:
        std::shared_ptr<Node<T>> iter;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T ;
        using pointer = T*;
        using reference = T&;

        iterator():iter(nullptr){}
        iterator(const std::shared_ptr<Node<T>> & anotherIter) : iter(anotherIter) {}

        bool isNull(){
            return iter == nullptr ? true : false;
        }

        friend void operator ++ (iterator & it) {
            ++it.iter;
        }

        friend bool operator != (const iterator & lhs, const iterator & rhs) {
            return lhs.iter != rhs.iter;
        }

        friend std::ostream & operator << (std::ostream & out, const iterator & it) {
            out << *it.iter;
            return out;
        }

        Node<T>& operator * () {
            return *iter;
        }
    };

    Stack() noexcept :head(nullptr){}

    void pop(){
        if(head){
            head = head->prev;
        }
        else{
            throw std::runtime_error("Stack is empty");
        }
    }

    void push(const T& val){
        Node<T>* newNode = new Node<T>(val);
        std::shared_ptr<Node<T>> newPtr{newNode};
        newPtr->prev = head;
        head = newPtr;
    }

    T top(){
        if(head){
            return head->data;
        }
        else{
            throw std::runtime_error("Nullptr in head");
        }
    }

    void insert(iterator& it, const T& elem){
        std::unique_ptr<Node<T>> newNode {new Node<T>(elem)};
        std::shared_ptr<Node<T>> newPtr(newNode);
        std::shared_ptr<Node<T>> prevPtr = head;

        if(prevPtr){
            if(!it.isNull()){
                while(*prevPtr->prev != *it){
                    ++prevPtr;
                }
            }
            else{
                while(*prevPtr->prev != nullptr){
                    ++prevPtr;
                }
            }
            newPtr->prev = prevPtr->prev;
            prevPtr->prev = newPtr;
        }
        else{
            head = newPtr;
        }
    }

    void erase(iterator& it){
        if(it.isNull()){
            throw std::runtime_error("Iterator is in nullptr state");
        }
        else{
            if(*it == *head){
                head = head->prev;
            }
            else{
                std::shared_ptr<Node<T>> prevPtr = head;
                while(*prevPtr->prev != *it){
                    ++prevPtr;
                }
                prevPtr->prev = prevPtr->prev->prev;
            }
        }
    }

    iterator begin(){
        return iterator(head);
    }

    iterator end(){
        return iterator(nullptr);
    }
};

#endif //OOP_EXERCISE_05_STACK_H

#include "Stack.h"

template<class T>
void operator++(std::shared_ptr<Node<T>>& curNode){
    if(curNode){
        curNode = curNode->prev;
    }
    else{
        throw std::out_of_range("Iterator has already in nullptr");
    }
}

template<class T>
bool operator!=(const Node<T>& lhs, const Node<T>& rhs){
    return &lhs != &rhs;
}

template<class T>
bool operator==(const Node<T>& lhs, const Node<T>& rhs){
    return &lhs.data == &rhs.data;
}

template<class T>
std::ostream& operator<<(std::ostream& cout, const Node<T>& node){
    cout << node.data;
    return cout;
}



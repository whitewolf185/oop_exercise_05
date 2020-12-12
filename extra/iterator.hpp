//Будниква Валерия 207
//Фигура - шестиугольник
//Динамический массив 

#include <memory>
#include <iostream>

template<class T>
class iterator{
    public:
        using self_type = iterator<T>;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T ;
        using pointer = T*;
        using reference = T&;
    private:
        std::shared_ptr<T> ptr;
        size_t ind;
        size_t Size;
        bool compatible(self_type const &other) const {
            return ptr == other.ptr;
        }
    public:
        iterator(): ind(0), Size(0) {}
        iterator(std::shared_ptr<T> fig, size_t ind1, size_t s): ptr(fig), ind(ind1), Size(s) {}
        ~iterator(){}
        bool operator==(self_type const &other) const {
            assert(compatible(other));
            return ind == other.ind;
        }

        bool operator!=(self_type const &other) const{
            return !(*this == other);
        }

        self_type &operator++(){
            if (ind >= Size) {
                throw std::out_of_range("Iterator cannot be incremented past the end of range.");
                ind = Size;
                return *this;
            } else {
                ++ind;
                return *this;
            }     
        }

        self_type operator++(int){
            self_type tmp = *this;
            ++*this;
            return tmp;
        }

        reference operator*() const{
            if (ptr == nullptr) {
                throw std::bad_function_call();
            } else {
                return ptr.get()[ind];
            }
        }

        self_type operator+(difference_type offset) {
            if (ind + offset > Size) {
                throw std::out_of_range("Iterator cannot be incremented past the end of range.");
            } else {
                ind += offset;
            }
            return *this;
        }
};
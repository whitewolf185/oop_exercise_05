//Будниква Валерия 207
//Фигура - шестиугольник
//Динамический массив 

#include <memory>
#include <iostream>

template<class T>
struct Hexagon {
    std::pair<T, T> point;
    Hexagon(T x, T y, T side1): point(x, y), side(side1) {}
    Hexagon(): point(0,0), side(0) {}
    T side;
};

template<class T>
std::ostream& operator<<(std::ostream &os, std::pair<T,T> p) {
    os << '(' << p.first << ',' << p.second << ')';
    return os;
}

template<class T>
std::ostream& operator<<(std::ostream &os, Hexagon<T> p) {
    std::pair<T, T> p1 = p.point;
    std::pair<T, T> p2(p.point.first - (double)p.side * sqrt(3) / 2, p.point.second - (double) p.side / 2);
    std::pair<T, T> p3(p.point.first + (double)p.side * sqrt(3) / 2, p.point.second - (double) p.side / 2);
    std::pair<T, T> p4(p.point.first - (double)p.side * sqrt(3) / 2, p.point.second - (double) p.side / 2 - p.side);
    std::pair<T, T> p5(p.point.first + (double)p.side * sqrt(3) / 2, p.point.second - (double) p.side / 2 - p.side);
    std::pair<T, T> p6(p.point.first, p.point.second - 2 * p.side);
    os << p1 << p2 << p3 << std::endl << p4 << p5 << p6;
    return os;
}


template<class T>
class Vect {
    public:
        using Hex = Hexagon<T>;
        Vect(){
            size = 0;
            capacity = 2;
        };
        ~Vect(){};
        void push_back(const Hex fig){
            if (size == capacity) {
                capacity <<= 1;
                std::shared_ptr<Hex> ptr1{new Hex[capacity]};
                for (int i = 0; i < size; ++i) {
                    ptr1.get()[i] = ptr.get()[i];
                }
                ptr1.get()[size] = fig;
                ++size;
                ptr = ptr1;
            } else {
                ptr.get()[size] = fig;
                ++size;
            }
        }
        Hex operator[](int i) {
            return ptr.get()[i];
        }
        iterator<Hex> begin() {
            return iterator(ptr, 0, size);
        }
        iterator<Hex> end() {
            return iterator(ptr, size, size);
        }

        void insert(iterator<Hex> iter, Hex fig) {
            iterator<Hex> iter_tmp = iterator(ptr, 0, size);
            std::shared_ptr<Hex> ptr1{new Hex[capacity + 1]};
            int i = 0;
            while(iter != iter_tmp) {
                ++iter_tmp;
                ptr1.get()[i] = ptr.get()[i];
                ++i;
            }
            ptr1.get()[i] = fig;
            ++i;
            ++size;
            while(i < size) {
                ptr1.get()[i] = ptr.get()[i - 1];
                ++i;
            }
            ptr = ptr1;
        }

        void erase(iterator<Hex> iter) {
            iterator<Hex> iter_tmp = iterator(ptr, 0, size);
            std::shared_ptr<Hex> ptr1{new Hex[capacity]};
            int i = 0;
            while(iter != iter_tmp) {
                ++iter_tmp;
                ptr1.get()[i] = ptr.get()[i];
                ++i;
            }
            ++i;
            while(i < size) {
                ptr1.get()[i - 1] = ptr.get()[i];
                ++i;
            }
            --size;
            ptr = ptr1;
        }

    private:
        std::shared_ptr<Hex> ptr{new Hex[2]};
        int size;
        int capacity;
};

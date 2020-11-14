#ifndef OOP_EXERCISE_05_RECTANGLE_H
#define OOP_EXERCISE_05_RECTANGLE_H

#include <iostream>
#include <memory>
#include <exception>


template<class T>
struct Rectangle{
    using vertex_t = std::pair<T,T>;
    vertex_t point;
    T a;
    T b;

    Rectangle(const vertex_t& _point, const T& _a, const T& _b ):a(_a), point(_point),b(_b){}

    T area() const {
        return a*b;
    }
};

template<class T>
std::ostream& operator << (std::ostream& cout, const std::pair<T,T>& val){
    cout << "(" << val.first << ", " << val.second << ")";
    return cout;
}

template<class T>
std::ostream& operator << (std::ostream& cout, const Rectangle<T>& obj){
    cout << "Coordinates: {"
         << std::pair<T,T>(obj.point.first,obj.point.second)<< "; "
         << std::pair<T,T>(obj.point.first,obj.point.second + obj.a)<< "; "
         << std::pair<T,T>(obj.point.first + obj.b,obj.point.second + obj.a)<< "; "
         << std::pair<T,T>(obj.point.first + obj.b,obj.point.second)<< "}\n ";

    return cout;
}

#endif //OOP_EXERCISE_05_RECTANGLE_H

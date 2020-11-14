/*Волков Мавтей Андреевич
 *
 * Разработать шаблоны классов согласно варианту задания.  Параметром шаблона должен являться скалярный тип данных
 * задающий тип данных для оси координат. Классы должны иметь публичные поля. Фигуры являются фигурами вращения, т.е.
 * равносторонними (кроме трапеции и прямоугольника). Для хранения координат фигур необходимо использовать шаблон
 * std::pair.
Например:
template <class T>
struct Square{
    using vertex_t = std::pair<T,T>;
    vertex_t a,b,c,d;
};

Создать шаблон динамической коллекцию, согласно варианту задания:
1.	Коллекция должна быть реализована с помощью умных указателей (std::shared_ptr, std::weak_ptr). Опционально
 использование std::unique_ptr;
2.	В качестве параметра шаблона коллекция должна принимать тип данных - фигуры;
3.	Реализовать forward_iterator по коллекции;
4.	Коллекция должны возвращать итераторы begin() и  end();
5.	Коллекция должна содержать метод вставки на позицию итератора insert(iterator);
6.	Коллекция должна содержать метод удаления из позиции итератора erase(iterator);
7.	При выполнении недопустимых операций (например выход аз границы коллекции или удаление не существующего элемента)
 необходимо генерировать исключения;
8.	Итератор должен быть совместим со стандартными алгоритмами (например, std::count_if)
9.	Коллекция должна содержать метод доступа:
o	Стек – pop, push, top;
10.	Реализовать программу, которая:
o	Позволяет вводить с клавиатуры фигуры (с типом int в качестве параметра шаблона фигуры) и добавлять в коллекцию;
o	Позволяет удалять элемент из коллекции по номеру элемента;
o	Выводит на экран введенные фигуры c помощью std::for_each;
o	Выводит на экран количество объектов, у которых площадь меньше заданной (с помощью  std::count_if);
 Вариант 3: прямоугольни - стек
*/
#include "Stack.h"
#include <algorithm>

int main() {
    Stack<Rectangle<int>> st;
    int x, y, a,b;
    std::cout << "Input rectangles.\nTo end entering press the EOF button.\n"
                 "First, enter the X and Y - point of vertex\n"
                 "Second, enter the sides of rectangle - A and B" << std::endl;
    while(std::cin >> x >> y >> a >> b){
        st.push(Rectangle<int>(std::pair<int,int> {x,y}, a, b));
    }
    auto printStack = [](const Node<Rectangle<int>>& obj){
        std::cout << obj << std::endl;
    };
    std::cout << "\nThis is all rectangles" << std::endl;
    std::for_each(st.begin(), st.end(), printStack);

    std::cout << "\nEnter your index to insert" << std::endl;
    size_t n;
    std::cin >> n;
    try{
        if(st.getSize() < n){
            throw std::invalid_argument("You entered wrong index");
        }
        else{
            auto it = st.begin();
            while(--n){
                ++it;
            }
            std::cout << "Input rectangle.\n"
                         "First, enter the X and Y - point of vertex\n"
                         "Second, enter the sides of rectangle - A and B" << std::endl;
            std::cin >> x >> y >> a >> b;
            st.insert(it, Rectangle<int>(std::pair<int,int>{x,y},a,b));
        }
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\nThis is all rectangles" << std::endl;
    std::for_each(st.begin(), st.end(), printStack);

    std::cout << "\nEnter your index to erase" << std::endl;
    std::cin >> n;
    try{
        auto it = st.begin();
        while(--n){
            ++it;
        }
        st.erase(it);
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "\nThis is all rectangles" << std::endl;
    std::for_each(st.begin(), st.end(), printStack);

    int minArea;
    std::cout << "\nEnter your minimal area" << std::endl;
    std::cin >> minArea;
    auto checkMinArea = [&minArea](const Node<Rectangle<int>>& rec){
        return rec.data.area() >= minArea;
    };
    std::cout << "Number of rectangles with area greater or equal, than " << minArea << ": "
              << std::count_if(st.begin(), st.end(), checkMinArea) << std::endl;
    return 0;
}

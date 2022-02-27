# Лабораторная работа №3 Итератор

## Структура контейнера

Контейнер реализованный в данной работе представляет собой двусвязанный список, узлом которого является объект класса `Node`, имеющий следующую структуру:
```cpp
template<class Type>
class Node {
    Type data_;
public:
    Node* prev = nullptr;
    Node* next = nullptr;

    Node(Type data) {
        data_ = data;
    }
    ~Node() {}
    Type getData() {
        return data_;
    }
};
```

Узел хранит элемент очереди и ссылки на предыдущий и последующий узлы.

Основной класс `Deque` помимо методов, содержит поля - указатели на первый и последний узлы, количество элементов в очереди.

## Особенности реализации итератора
Класс итератора `Iterator` содержит индекс(номер позиции в очереди, на которую он указывает на данный момент) и указатель на очередь `Deque`.
Класс итератора достаточно маловесный, так что можно привести его целиком:
```cpp
template<class T>
class Iterator {
private:
    Deque<T>* deque_;
    int index;
public:
    Iterator(Deque<T>* deque) : deque_{ deque }, index{ 0 } {};
    Iterator(Deque<T>* deque, int index) : deque_{ deque }, index{ index } {};

    virtual Iterator* begin() {
        index = 0;
        return this;
    }

    virtual Iterator* end() {
        index = deque_->getLength();
        return this;
    }

    virtual Iterator* next() {
        index++;
        return this;
    }

    virtual bool IsDone() const {
        return (index >= deque_->getLength());
    }

    int getIndex() { return index; }

    T getSpecElement(int pos) {
        return deque_->getElement(pos);
    }

    T getElement() {
        return deque_->getElement(index);
    }
};
```
Методы `begin` и `end` устанавливают индекс на позицию начала/конца очереди соответственно и возвращают исходный итератор.
`next`  - прибавляет к индексу итератора единицу.
`IsDone` - возвращает **True** если индекс итератора вышел за границы очереди, **False** если находится еще в пределах очереди.
Также с помощью любого итератора можно получить не только тот элемент, на который он указывет, но и любой элемент очереди.

Интерфейс итертатора унифицирован вне зависимости от типа контейнера deque, vector, set ets., в этом его преимущество. Особенности реализации методов контейнеров, использующих итераторы, скрыты внутри этих контейнеров.

## Методы контейнера
Текущая реализация контейнера `Deque` поддерживает методы реализованные при помощи итераторов и без них.

Следующие методы реализованы без итераторов:  `clear, isEmpty, getFront, getBack, getNode, getElement, getLength, setLength, setBeginNode, setEndNode, addFront, insert, remove, addBack, deleteFront, deleteBack, swap`.

Методы реализованные через итераторы: 
`print, insertIt, erase`(перегрузка для удаления одного элемента или последовательности в диапозоне), `empty`.

### Итератор содержит указатель на контейнер, тип связи - ***агрегация***.

## Код и тесты

В [main](https://github.com/svetlana-mel/Iterator/blob/main/L_iterator.cpp) примеры применения основных методов `Deque`, крайние случаи, выходы за пределы списка, отрицательные индексы и нулевые указатели, обрабатываются черех exeptions с использованием библиотеки:
```cpp
#include <stdexcept>
```
Встречаются ошибки типа:
```cpp 
throw std::out_of_range("Element index out of range");
//========================
throw std::overflow_error("Failed to create class object");
```

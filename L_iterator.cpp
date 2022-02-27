#include <iostream>
#include <string>
#include <stdexcept>
#include "Deque.h"
#include "Complex.h" 

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

int main() {
    try {
        /// Наполнение первого контейнера
        Deque<int> dq1;
        dq1.addFront(4);
        dq1.addBack(6);
        dq1.addFront(2);
        dq1.addBack(8);

        std::cout << "Deque#1 length = " << dq1.getLength() << "\n";
        // метод print выполнен с помощью итератора
        dq1.print();

        // наполнение контейнера, элемент - объект
        Deque<Complex> dq2;
        Complex c1{ 2,4 };
        dq2.addBack(c1);
        Complex c2{ 3,5 };
        dq2.addBack(c2);
        Complex c3{ 1,1 };
        dq2.addBack(c3);
        Complex c4{ 6,-1 };
        dq2.addBack(c4);

        std::cout << "Deque#2 length = " << dq2.getLength() << "\n";
        dq2.print();

        // использование метода insert
        std::cout << "\n\nUsage the insert method: \n";
        std::cout << "\nInsert the (10, 10) in the Deque#1 on third position." << "\n";
        Iterator<Complex>* it_onThreePosition = new Iterator<Complex>(&dq2, 10);
        Complex toInsert{ 10,10 };
        Iterator<Complex> it_new = dq2.insertIt(*it_onThreePosition, toInsert);
        if (it_new.getIndex() != -1) {
            it_new.begin();
            while (!it_new.IsDone()) {
                std::cout << it_new.getElement() << " ";
                it_new.next();
            };
        }
        else {
            throw std::out_of_range("Iterator is out of range");
        }

        // использование метода erase
        std::cout << "\n\nUsage the erase method: \n";
        std::cout << "\nDelete the elements from 1 to 3 position\n";
        Iterator<Complex>* it_onFirstPosition = new Iterator<Complex>(&dq2, 1);
        Iterator<Complex>* it_onThirdPosition = new Iterator<Complex>(&dq2, 3);
        Iterator<Complex> it_new2 = dq2.erase(*it_onFirstPosition, *it_onThirdPosition);
        if (it_new2.getIndex() != -1) {
            it_new2.begin();
            while (!it_new2.IsDone()) {
                std::cout << it_new2.getElement() << " ";
                it_new2.next();
            };
        }
        else {
            throw std::out_of_range("Iterator is out of range");
        }

        // использование метода empty
        std::cout << "\n\nUsage the empty method: \n";
        std::string isEmpty = (dq2.empty()) ? "true" : "false";
        std::cout << "\nThe second deque empty = " << isEmpty;

        // использование метода swap
        std::cout << "\n\nUsage the swap method: \n";
        std::cout << "First deque: \n";
        dq2.print();

        std::cout << "Second deque: \n";
        Deque<Complex> dq3;
        Complex c11{ 11,0 };
        dq3.addBack(c11);
        Complex c22{ 0,11 };
        dq3.addBack(c22);
        std::cout << "Deque#3 length = " << dq3.getLength() << "\n";
        dq3.print();

        std::cout << "\nUse the swap method - dq2.swap(&dq3);\n";
        dq2.swap(&dq3);

        std::cout << "First deque: \n";
        dq2.print();
        std::cout << "Second deque: \n";
        dq3.print();
    }
    catch(std::out_of_range err) {
        std::cerr << err.what();
    }
    catch (std::overflow_error err) {
        std::cerr << err.what();
    };

    return 0;
};


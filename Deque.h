#ifndef DEQUE
#define DEQUE

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

template<class Type>
class Iterator;

template<class Type>
class Deque {
    Node<Type>* begin = nullptr;
    Node<Type>* end = nullptr;
    int length = 0;
public:
    Deque() {};

    ~Deque() {
        this->clear();
    };

    void clear() {
        Node<Type>* current = nullptr;
        Node<Type>* next = begin;
        do {
            current = next;
            next = current->next;
            delete current;
        } while (next);
        this->setLength(0);
    }

    bool isEmpty() {
        return (begin == nullptr) ? true : false;
    }

    Type getFront() { return begin->getData(); }

    Type getBack() { return end->getData(); }

    Node<Type>* getNode(int pos) {
        if (pos >= length || pos < 0) {
            throw std::out_of_range("Element index out of range");
        }
        Node<Type>* temp = begin;
        for (int i = 0; i < length; i++) {
            if (i == pos) {
                return temp;
            };
            temp = temp->next;
        }
        throw std::overflow_error("Failed to create class object");
    }

    Type getElement(int pos) {
        if (pos >= length || pos < 0) {
            throw std::out_of_range("Element index out of range");
        }
        Node<Type>* temp = this->getNode(0);
        for (int i = 0; i < length; i++) {
            if (i == pos) {
                return temp->getData();
            };
            temp = temp->next;
        }
        throw std::overflow_error("Failed to create class object");
    }

    int getLength() { return length; }

    /// ====== setters =========
    void setLength(int l) { length = l; }

    void setBeginNode(Node<Type>* node) { begin = node; }

    void setEndNode(Node<Type>* node) { end = node; }
    // =========================

    void addFront(Type data) {
        Node<Type>* newNode = new Node<Type>(data);
        if (begin == nullptr) {
            begin = newNode;
            end = newNode;
            length++;
        }
        else {
            newNode->next = begin;
            begin->prev = newNode;
            begin = newNode;
            length++;
        }
    }

    void insert(int pos, const Type element) {
        Node<Type>* node = this->getNode(pos);

        Node<Type>* newNode = new Node<Type>(element);

        newNode->next = node;
        newNode->prev = node->prev;
        node->prev->next = newNode;
        node->prev = newNode;

        length++;
    }

    void remove(int pos) {
        Node<Type>* node = this->getNode(pos);

        node->next->prev = node->prev;
        node->prev->next = node->next;
        delete node;
        length--;
    }

    void addBack(Type data) {
        Node<Type>* newNode = new Node<Type>(data);
        if (end == nullptr) {
            begin = newNode;
            end = newNode;
            length++;
        }
        else {
            newNode->prev = end;
            end->next = newNode;
            end = newNode;
            length++;
        }
    }

    void deleteFront() {
        if (begin != nullptr) {
            if (length == 1) {
                this->clear();
                this->setLength(0);
                return;
            }
            Node<Type>* temp = begin;
            begin = temp->next;
            temp->next->prev = nullptr;
            delete temp;
            length--;
        }
    }

    void deleteBack() {
        if (end != nullptr) {
            if (length == 1) {
                this->clear();
                this->setLength(0);
                return;
            }
            Node<Type>* temp = end;
            end = temp->prev;
            temp->prev->next = nullptr;
            delete temp;
            length--;
        }
    }

    void print() {
        Iterator<Type>* it = new Iterator<Type>(this);
        it->begin();
        while (!it->IsDone()) {
            std::cout << it->getElement() << " ";
            it->next();
        }
        std::cout << "\n";
    }

    /**
    * вставляет элемент key в позицию, на которую указывает
    * итератор pos(перед элементом, на который указывает pos)
    * и возвращает итератор, указывающий на вставленный объект
    */
    Iterator<Type> insertIt(Iterator<Type>& it_pointer, const Type element) {
        int index = it_pointer.getIndex();

        if (index >= this->getLength()) {
            throw std::out_of_range("Iterator index is out of range");
        };
        
        this->insert(index, element);

        Iterator<Type>* it = new Iterator<Type>(this, index);
        return *it;
    };

    /**
    * удаляет элемент, на который указывает итератор pos и возвращает
    * итератор, указывающий на следующий за удаленным объект
    */
    Iterator<Type> erase(Iterator<Type> it_pos) {
        int index = it_pos.getIndex();
        if (index >= this->length) {
            throw std::out_of_range("Iterator index is out of range");
        };
        this->remove(index);

        Iterator<Type>* it = new Iterator<Type>(this, index);
        return *it;
    };

    /**
    * удаляет элементы от итератора begin до(не включая) end,
    * возвращает итератор
    */
    Iterator<Type> erase(Iterator<Type> begin, Iterator<Type> end) {
        int length_inBegin = length;
        int start = begin.getIndex();
        start = (start < 0) ? 0 : start;
        int finish = end.getIndex();
        finish = (finish > length) ? length : finish;

        if (start >= length || finish < 0) {
            throw std::out_of_range("Iterator index is out of range");
        }
        else {
            for (int i = start; i < finish; i++) {
                this->remove(i);
            }

            Iterator<Type>* it = new Iterator<Type>(this, (length_inBegin - (finish - start)));
            return *it;
        }
    };
    /**
    * Метод проверки на пустоту, который обращается к итераторам
    */
    bool empty() {
        return (new Iterator<Type>(this))->IsDone();
    };

    /**
    * метод, обменивающий содержимое двух контейнеров
    */
    void swap(Deque<Type>* deq) {
        int tempLength = length;
        Node<Type>* tempBegin = begin;
        Node<Type>* tempEnd = end;

        length = deq->getLength();
        begin = deq->getNode(0);
        end = deq->getNode(length - 1);

        deq->setLength(tempLength);
        deq->setBeginNode(tempBegin);
        deq->setEndNode(tempEnd);
    };
};

#endif

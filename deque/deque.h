#pragma once
#include <iostream>

template <typename T>
struct Node {
    T value;
    Node<T>* next = nullptr;
    Node<T>* prev = nullptr;
};

template <typename T>
class Deque {
    private:
        Node<T>* head = nullptr;
        Node<T>* tail = nullptr;
        size_t size = 0;
    public:
        Deque() = default;
        Deque(const Deque&) {};
        Deque& operator = (const Deque& deq) {
            // глубокое копирование
            Node* node = deq->head;
            // Node* new_node = new Node;
            // while (node != nullptr) {
            //     new_node = 
            //     this->push_back(node->value);
            // }????????????
            return *this;
        }
        Deque(const T& value);

        Node<T>* get_head() const;
        Node<T>* get_tail() const;
        size_t get_size() const;
        bool empty() const;

        void insert(const T& value, Node<T>* prev);
        void push_front(const T& value);
        void push_back(const T& value);
        void pop_head();
        void pop_tail();

        ~Deque();
};



template <typename T>
Deque<T>::Deque(const T& _value) {
    // std::cout << "Generating a new Deque!" << '\n';
    Node<T>* node = new Node<T>;
    node->value = _value;
    head = node;
    tail = node;
    size = 1;
}


template <typename T>
Node<T>* Deque<T>::get_head() const {
    // Warning: return nullptr if deque is empty
    return head;
}

template <typename T>
Node<T>* Deque<T>::get_tail() const {
    // Warning: return nullptr if deque is empty
    return tail;
}

template <typename T>
size_t Deque<T>::get_size() const {
    return size;
}

template <typename T>
bool Deque<T>::empty() const {
    return head == nullptr;
}


template <typename T>
void Deque<T>::insert(const T& _value, Node<T>* _prev) {
    if (_prev == nullptr) {
        this->push_front(_value);
        return;
    }
    if (_prev == tail) {
        this->push_back(_value);
        return;
    }
    Node<T>* node = new Node<T>;
    node->value = _value;
    _prev->next->prev = node;
    node->next = _prev->next;
    _prev->next = node;
    node->prev = _prev;
}

template <typename T>
void Deque<T>::push_front(const T& _value) {
    Node<T>* node = new Node<T>;
    node->value = _value;
    node->next = head;
    if (head == nullptr) {
        tail = node;
    } else {
        head->prev = node;
    }
    head = node;
}

template <typename T>
void Deque<T>::push_back(const T& _value) {
    Node<T>* node = new Node<T>;
    node->value = _value;
    node->prev = tail;
    if (tail == nullptr) {
        head = node;
    } else {
        tail->next = node;
    }
    tail = node;
}

template <typename T>
void Deque<T>::pop_head() {
    if (head == nullptr) {
        return;
    }
    Node<T>* to_delete = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    } else {
        head->prev = nullptr;
    }
    delete to_delete;
}

template <typename T>
void Deque<T>::pop_tail() {
    if (tail == nullptr) {
        return;
    }
    Node<T>* to_delete = tail;
    tail = tail->prev;
    if (tail == nullptr) {
        head = nullptr;
    } else {
        head->next = nullptr;
    }
    delete to_delete;
}


template <typename T>
Deque<T>::~Deque() {
    std::cout << "Run Destructor!" << '\n';
    Node<T>* to_delete;
    while (head != nullptr) {
        to_delete = head;
        std::cout << "\t value: " << head->value << ", next: " << head->next << '\n';
        head = head->next;
        std::cout << "\t :( will delete > \e[31m" << to_delete << "\e[0m\n";
        delete to_delete;
    }
}

template <typename T>
std::ostream& operator << (std::ostream& stream, const Deque<T>& deq) {
    stream << "\e[35m";
    if (deq.empty()) {
        return stream << "empty deque\e[0m";
    }
    Node<T>* node = deq.get_head();
    while (node != nullptr) {
        stream << node->value;
        if (node == deq.get_head()) {
            stream << "\t<-- head";
        }
        if (node == deq.get_tail()) {
            stream << "\t<-- tail";
        }
        node = node->next;
        if (node != nullptr) {
            stream << '\n';
        }
    }
    stream << "\e[0m";
    return stream;
}
template <typename T>
std::ostream& operator << (std::ostream& stream, const Deque<Deque<T>>& deq) {
    Node<Deque<T>>* node = deq.get_head();
    while (node != nullptr) {
        stream << node->value << '\n';
        node = node->next;
    }
    return stream;
}
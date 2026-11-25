
#include "Base.h"

#include <iostream>
#include <stdexcept>
#include <climits>

Base::Base()
    : head_(nullptr), tail_(nullptr), count_(0) {

    std::cout << "[Base] Конструктор без параметров, объект "
              << this << '\n';
}

Base::Base(int number) : Base() {
    enqueue(number);

    std::cout << "[Base] Конструктор с параметром, объект "
              << this << '\n';
}

Base::Base(const Base& other) : Base() {
    *this = other;

    std::cout << "[Base] Конструктор копирования, объект "
              << this << '\n';
}

Base& Base::operator=(const Base& other) {
    if (this == &other)
        return *this;

    Node* newHead = nullptr;
    Node* newTail = nullptr;
    int newCount = 0;

    try {
        for (Node* p = other.head_; p != nullptr; p = p->next) {
            Node* created = new Node(p->value);

            if (newTail)
                newTail->next = created;
            else
                newHead = created;

            newTail = created;
            ++newCount;
        }
    }
    catch (...) {
        while (newHead) {
            Node* next = newHead->next;
            delete newHead;
            newHead = next;
        }

        throw;
    }

    clear();

    head_ = newHead;
    tail_ = newTail;
    count_ = newCount;

    return *this;
}

Base::~Base() {
    clear();

    std::cout << "[Base] Деструктор, объект "
              << this << '\n';
}

void Base::clear() {
    while (head_ != nullptr) {
        Node* next = head_->next;
        delete head_;
        head_ = next;
    }

    tail_ = nullptr;
    count_ = 0;
}

void Base::enqueue(int number) {
    if (count_ == INT_MAX)
        throw std::overflow_error(
            "Очередь достигла максимального размера."
        );

    Node* node = new Node(number);

    if (tail_ != nullptr)
        tail_->next = node;
    else
        head_ = node;

    tail_ = node;
    ++count_;
}

int Base::dequeue() {
    if (empty())
        throw std::underflow_error(
            "Очередь пуста: удалить элемент нельзя."
        );

    Node* old = head_;
    int number = old->value;

    head_ = old->next;

    delete old;
    --count_;

    if (head_ == nullptr)
        tail_ = nullptr;

    return number;
}

int Base::first() const {
    if (empty())
        throw std::underflow_error(
            "Очередь пуста: получить элемент нельзя."
        );

    return head_->value;
}

void Base::rotate() {
    if (count_ < 2)
        return;

    Node* old = head_;

    head_ = old->next;
    old->next = nullptr;

    tail_->next = old;
    tail_ = old;
}

int Base::valueAt(int index) const {
    if (index < 0 || index >= count_)
        throw std::out_of_range(
            "Индекс элемента выходит за границы контейнера."
        );

    Node* current = head_;

    for (int i = 0; i < index; ++i)
        current = current->next;

    return current->value;
}

void Base::replaceAt(int index, int number) {
    if (index < 0 || index >= count_)
        throw std::out_of_range(
            "Нельзя изменить элемент: неверный индекс."
        );

    Node* current = head_;

    for (int i = 0; i < index; ++i)
        current = current->next;

    current->value = number;
}

void Base::printNumbers(std::ostream& out) const {
    out << '[';

    for (Node* node = head_; node != nullptr; node = node->next) {
        out << node->value;

        if (node->next != nullptr)
            out << ", ";
    }

    out << ']';
}

int Base::size() const {
    return count_;
}

bool Base::empty() const {
    return count_ == 0;
}

int Base::get(int index) const {
    return valueAt(index);
}

void Base::set(int index, int number) {
    replaceAt(index, number);
}

void Base::saveNumbers(std::ostream& out) const {
    out << count_;

    for (Node* node = head_; node != nullptr; node = node->next)
        out << ' ' << node->value;

    out << '\n';

    if (!out)
        throw std::runtime_error(
            "Ошибка записи чисел в файл."
        );
}

void Base::loadNumbers(std::istream& in) {
    long long amount;

    if (!(in >> amount) || amount < 0 || amount > INT_MAX)
        throw std::runtime_error(
            "Неверное количество чисел в файле."
        );

    Node* newHead = nullptr;
    Node* newTail = nullptr;
    int newCount = 0;

    try {
        for (long long i = 0; i < amount; ++i) {
            int value;

            if (!(in >> value))
                throw std::runtime_error(
                    "Файл повреждён: отсутствует число "
                    "или неверный формат."
                );

            Node* created = new Node(value);

            if (newTail)
                newTail->next = created;
            else
                newHead = created;

            newTail = created;
            ++newCount;
        }
    }
    catch (...) {
        while (newHead) {
            Node* next = newHead->next;
            delete newHead;
            newHead = next;
        }

        throw;
    }

    clear();

    head_ = newHead;
    tail_ = newTail;
    count_ = newCount;
}

std::ostream& operator<<(std::ostream& out, const Base& object) {
    object.print(out);
    return out;
}

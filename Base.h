
#ifndef BASE_H
#define BASE_H

#include <iosfwd>

class Base {
private:
    struct Node {
        int value;
        Node* next;

        Node(int number)
            : value(number), next(nullptr) {}
    };

    Node* head_;
    Node* tail_;
    int count_;

    void clear();

protected:
    void enqueue(int number);
    int dequeue();
    int first() const;
    void rotate();

    int valueAt(int index) const;
    void replaceAt(int index, int number);

    void printNumbers(std::ostream& out) const;

public:
    Base();
    explicit Base(int number);
    Base(const Base& other);
    Base& operator=(const Base& other);
    virtual ~Base();

    int size() const;
    bool empty() const;

    int get(int index) const;
    void set(int index, int number);

    void saveNumbers(std::ostream& out) const;
    void loadNumbers(std::istream& in);

    virtual int type() const = 0;
    virtual Base* clone() const = 0;
    virtual void print(std::ostream& out) const = 0;
};

std::ostream& operator<<(std::ostream& out, const Base& object);

#endif

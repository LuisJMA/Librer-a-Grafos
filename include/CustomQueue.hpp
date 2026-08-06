#ifndef CUSTOM_QUEUE_HPP
#define CUSTOM_QUEUE_HPP

#include <stdexcept>

namespace SimpleGraph {
    template <typename T>
    class CustomQueue {
    private:
        struct Node {
            T data;
            Node* next;
            Node(T d) : data(d), next(nullptr) {}
        };
        Node* head;
        Node* tail;

    public:
        CustomQueue();
        ~CustomQueue();
        CustomQueue(const CustomQueue& other);            // Constructor de copia
        CustomQueue& operator=(const CustomQueue& other); // Operador de asignacion
        
        void push(const T& data);
        void pop();
        T front() const;
        bool isEmpty() const;
    };
}

#include "../src/CustomQueue.cpp"
#endif
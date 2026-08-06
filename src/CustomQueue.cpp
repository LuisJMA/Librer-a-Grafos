#ifndef CUSTOM_QUEUE_CPP
#define CUSTOM_QUEUE_CPP

#include "../include/CustomQueue.hpp"

namespace SimpleGraph {
    template <typename T>
    CustomQueue<T>::CustomQueue() : head(nullptr), tail(nullptr) {}

    template <typename T>
    CustomQueue<T>::~CustomQueue() { while (!isEmpty()) pop(); }

    template <typename T>
    CustomQueue<T>::CustomQueue(const CustomQueue& other) : head(nullptr), tail(nullptr) {
        Node* temp = other.head;
        while (temp) {
            push(temp->data);
            temp = temp->next;
        }
    }

    template <typename T>
    CustomQueue<T>& CustomQueue<T>::operator=(const CustomQueue& other) {
        if (this != &other) {
            while (!isEmpty()) pop();
            Node* temp = other.head;
            while (temp) {
                push(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

    template <typename T>
    void CustomQueue<T>::push(const T& data) {
        Node* newNode = new Node(data);
        if (isEmpty()) head = tail = newNode;
        else { tail->next = newNode; tail = newNode; }
    }

    template <typename T>
    void CustomQueue<T>::pop() {
        if (isEmpty()) return;
        Node* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
    }

    template <typename T>
    T CustomQueue<T>::front() const {
        if (isEmpty()) throw std::runtime_error("Cola vacia.");
        return head->data;
    }

    template <typename T>
    bool CustomQueue<T>::isEmpty() const { return head == nullptr; }
}
#endif
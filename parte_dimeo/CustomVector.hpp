#ifndef CUSTOM_VECTOR_HPP
#define CUSTOM_VECTOR_HPP

#include <stdexcept>

namespace SimpleGraph {
    template <typename T>
    class CustomVector {
    private:
        T* arr;
        int _capacity;
        int _current;

    public:
        CustomVector();
        ~CustomVector();
        CustomVector(const CustomVector& other);
        CustomVector& operator=(const CustomVector& other);
        
        void push_back(const T& data);
        T& at(int index);
        const T& at(int index) const;
        int size() const;
        void resize(int new_size, T default_val);
    };
}

#include "CustomVector.cpp"
#endif
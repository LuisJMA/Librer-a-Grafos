#ifndef CUSTOM_VECTOR_CPP 
#define CUSTOM_VECTOR_CPP 
 
#include "../parte_dimeo/CustomVector.hpp" 
 
namespace SimpleGraph { 
    template <typename T> 
    CustomVector<T>::CustomVector() : _capacity(2), _current(0), arr(new T[2]) {} 
 
    template <typename T> 
    CustomVector<T>::~CustomVector() { delete[] arr; } 
 
    template <typename T> 
    CustomVector<T>::CustomVector(const CustomVector& other)  
        : _capacity(other._capacity), _current(other._current), arr(new T[other._capacity]) { 
        for (int i = 0; i < _current; i++) arr[i] = other.arr[i]; 
    } 
 
    template <typename T> 
    CustomVector<T>& CustomVector<T>::operator=(const CustomVector& other) { 
        if (this != &other) { 
            delete[] arr; 
            _capacity = other._capacity; 
            _current = other._current; 
            arr = new T[_capacity]; 
            for (int i = 0; i < _current; i++) arr[i] = other.arr[i]; 
        } 
        return *this; 
    } 
 
    template <typename T> 
    void CustomVector<T>::push_back(const T& data) { 
        if (_current == _capacity) { 
            _capacity *= 2; 
            T* temp = new T[_capacity]; 
            for (int i = 0; i < _current; i++) temp[i] = arr[i]; 
            delete[] arr; 
            arr = temp; 
        } 
        arr[_current++] = data; 
    } 
 
    template <typename T> 
    T& CustomVector<T>::at(int index) { 
        if (index < 0 || index >= _current) throw std::out_of_range("Indice fuera de rango (Out of Index)."); 
        return arr[index]; 
    } 
 
    template <typename T> 
    const T& CustomVector<T>::at(int index) const { 
        if (index < 0 || index >= _current) throw std::out_of_range("Indice fuera de rango (Out of Index)."); 
        return arr[index]; 
    } 
 
    template <typename T> 
    int CustomVector<T>::size() const { return _current; } 
 
    template <typename T> 
    void CustomVector<T>::resize(int new_size, T default_val) { 
        while (_current < new_size) push_back(default_val); 
    } 
 
    template <typename T> 
    void CustomVector<T>::removeAt(int index) { 
        if (index < 0 || index >= _current) throw std::out_of_range("Indice fuera de rango."); 
        for (int i = index; i < _current - 1; i++) { 
            arr[i] = arr[i + 1]; 
        } 
        _current--; 
    } 
} 
#endif
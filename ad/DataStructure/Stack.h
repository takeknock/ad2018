#pragma once
#include <memory>

#include "ad/macro.h"

namespace ds {
    template<typename T>
    class Stack {
    public:
        typedef T value_type;
        Stack(const Stack<T>& rhs);
        Stack(const std::size_t max);
        Stack(Stack<T>&& rhs);
        Stack<T>& operator =(const Stack<T>& rhs);
        Stack<T>& operator =(Stack<T>&& rhs);

        T pop();
        void push(T element);
        bool isEmpty();
        bool isFull();

        T* getContainer();

        ~Stack();

    private:
        const std::size_t _max;
        T *_container;
        std::size_t _index;
    };

    template<typename T>
    Stack<T>::Stack(const std::size_t max)
    :_index(0), _max(max), _container(new T[max])
    {
    }

    template<typename T>
    Stack<T>::Stack(const Stack<T>& rhs)
    :_container(rhs.getContainer())
    {
    }

    template<typename T>
    Stack<T>::Stack(Stack<T>&& rhs)
    : _container(rhs.getContainer())
    {
    }

    template<typename T>
    Stack<T>& Stack<T>::operator =(const Stack<T>& rhs)
    {
        _container = rhs.getContainer();
        return *this;
    }

    template<typename T>
    Stack<T>& Stack<T>::operator =(Stack<T>&& rhs)
    {
        _container = rhs.getContainer();
        return *this;
    }

    template<typename T>
    T Stack<T>::pop()
    {
        _index--;
        T ret = _container[_index];
        return ret;
    }

    template<typename T>
    void Stack<T>::push(const T element)
    {
        _container[_index] = element;
        _index++;
    }

    template<typename T>
    bool Stack<T>::isEmpty()
    {
        return _index == 0;
    }

    template<typename T>
    bool Stack<T>::isFull()
    {
        return _index == _max;
    }

    template<typename T>
    T* Stack<T>::getContainer()
    {
        return _container;
    }

    template<typename T>
    Stack<T>::~Stack()
    {
        delete _container;
    }

}// namespace ds {
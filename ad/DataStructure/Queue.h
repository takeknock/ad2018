#pragma once
#include <cstddef>

namespace ds {
    template<typename T>
    class Queue {

    public:
        Queue(const std::size_t size);
        void enqueue(const T element);
        T dequeue();
        bool isEmpty();
        bool isFull();
        ~Queue();

    private:
        T* _container;
        std::size_t _head;
        std::size_t _tail;
        const std::size_t _max;
    };

    template<typename T>
    Queue<T>::Queue(const std::size_t size)
    :_max(size), _head(0), _tail(0), _container(new T[size])
    {
    }

    template<typename T>
    void Queue<T>::enqueue(const T element)
    {
        _container[_tail] = element;
        _tail++;
    }

    template<typename T>
    T Queue<T>::dequeue()
    {
        T ret = _container[_head];
        _head++;
        return ret;
    }

    template<typename T>
    bool Queue<T>::isEmpty()
    {
        return _head == _tail;
    }

    template<typename T>
    bool Queue<T>::isFull()
    {
        return _tail == _max;
    }

    template<typename T>
    Queue<T>::~Queue()
    {
        delete _container;
    }
} // namespace ds {


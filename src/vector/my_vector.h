// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef ADDER_MY_VECTOR_H
#define ADDER_MY_VECTOR_H

#include <initializer_list>
#include <algorithm>
#include <utility>
#include <cmath>

#define CAPACITY_MULTIPLIER 2

template<class T>
class my_vector {
public:
    explicit my_vector();

    explicit my_vector(size_t n);

    explicit my_vector(size_t n, const T &elem);

    my_vector(const my_vector &copy);

    my_vector(my_vector &move);

    my_vector(std::initializer_list<T> list);

    ~my_vector();

    my_vector &operator=(const my_vector &assign) noexcept;

    my_vector &operator=(my_vector &&move) noexcept;

    T operator[](size_t n) const;

    T at(size_t n) const;

    T front();

    T back();

    T *begin();

    T *end();

    const T *cbegin() const;

    const T *cend() const;

    std::reverse_iterator<T *> rbegin();

    std::reverse_iterator<T *> rend();

    const std::reverse_iterator<const T *> crbegin() const;

    const std::reverse_iterator<const T *> crend() const;


    size_t size() const;

    bool is_empty() const;

    size_t capacity() const;


    void clear();

    void reserve(size_t n);

    void shrink_to_fit();

    void resize(size_t n);

    void swap(my_vector &vct);

    T *insert(const T *iter, size_t amount, T &value);

    T *insert(const T *iter, const T *begin, const T *end);

    T *erase(const T *iter);

    T *erase(const T *begin, const T *end);

    void pop_back();

    void push_back(const T &value);

    template<typename ...Args>
    void emplace_back(Args &&... args);

private:
    T *data;
    size_t _size = 0;
    size_t _capacity = 2;

    void realloc();
};

template<class T>
void my_vector<T>::realloc() {
    T *new_data = new T[_capacity];
    for (size_t i = 0; i < _size; i++)
        new_data[i] = data[i];
    delete[] data;
    data = new_data;
}

template<typename T>
my_vector<T>::my_vector() {
    data = new T[_capacity];
}

template<class T>
my_vector<T>::my_vector(size_t n) {
    data = new T[n];
    _capacity = n;
}

template<class T>
my_vector<T>::my_vector(size_t n, const T &elem) {
    _size = n;
    _capacity = n * CAPACITY_MULTIPLIER;
    data = new T[_capacity];
    for (size_t i = 0; i < _size; i++) {
        data[i] = elem;
    }
}

template<class T>
my_vector<T>::my_vector(const my_vector &copy) {
    _size = copy._size;
    _capacity = copy._capacity;
    data = new T[_capacity];
    for (size_t i = 0; i < _size; i++) {
        data[i] = copy[i];
    }
}

template<class T>
my_vector<T>::my_vector(my_vector &move) {
    _size = move._size;
    _capacity = move._capacity;
    data = new T[_capacity];
    for (size_t i = 0; i < _size; i++) {
        data[i] = std::move(move[i]);
    }
}

template<class T>
my_vector<T>::my_vector(std::initializer_list<T> list) {
    _size = list.size();
    _capacity = _size * CAPACITY_MULTIPLIER;
    data = new T[_capacity];

    size_t i = 0;

    for (const T &elem: list) {
        data[i++] = elem;
    }
}

template<class T>
my_vector<T>::~my_vector() {
    delete[] data;
}

template<class T>
my_vector<T> &my_vector<T>::operator=(const my_vector &assign) noexcept {
    if (this == &assign)
        return *this;

    my_vector<T> v{assign};
    swap(*this, v);
    delete[] v.data;

    return *this;
}

template<class T>
my_vector<T> &my_vector<T>::operator=(my_vector &&move) noexcept {
    if (this == &move)
        return *this;

    delete[] data;
    _size = move._size;
    _capacity = move._capacity;

    data = new T[_capacity];

    for (size_t i = 0; i < _size; i++)
        data[i] = std::move(move.data[i]);
    return *this;
}

template<class T>
T my_vector<T>::operator[](size_t n) const {
    return data[n];
}

template<class T>
T my_vector<T>::at(size_t n) const {
    if (n >= _size) throw std::runtime_error("Out of range");
    return data[n];
}

template<class T>
T my_vector<T>::front() {
    return data[0];
}

template<class T>
T my_vector<T>::back() {
    return data[_size - 1];
}

template<class T>
T *my_vector<T>::begin() {
    return data;
}

template<class T>
T *my_vector<T>::end() {
    return data + _size;
}

template<class T>
const T *my_vector<T>::cbegin() const {
    return data;
}

template<class T>
const T *my_vector<T>::cend() const {
    return data + _size;
}

template<class T>
std::reverse_iterator<T *> my_vector<T>::rbegin() {
    return std::reverse_iterator<T *>(data + _size);
}

template<class T>
std::reverse_iterator<T *> my_vector<T>::rend() {
    return std::reverse_iterator<T *>(data);
}

template<class T>
const std::reverse_iterator<const T *> my_vector<T>::crbegin() const {
    return std::reverse_iterator<const T *>(data + _size);
}

template<class T>
const std::reverse_iterator<const T *> my_vector<T>::crend() const {
    return std::reverse_iterator<const T *>(data);
}

template<class T>
size_t my_vector<T>::size() const {
    return _size;
}

template<class T>
bool my_vector<T>::is_empty() const {
    return _size == 0;
}

template<class T>
void my_vector<T>::clear() {
    for (size_t i; i < _size; ++i) {
        data[i].~T();
    }
    _size = 0;
}

template<class T>
void my_vector<T>::reserve(size_t n) {
    if (_capacity >= n)
        return;
    _capacity = n;
    realloc();
}

template<class T>
size_t my_vector<T>::capacity() const {
    return _capacity;
}

template<class T>
void my_vector<T>::shrink_to_fit() {
    _capacity = _size;
    if (_capacity) {
        realloc();
    }
}

template<class T>
void my_vector<T>::resize(size_t n) {
    if (_size == n)
        return;

    _size = n;
    _capacity = _size * CAPACITY_MULTIPLIER;
    realloc();
}

template<class T>
void my_vector<T>::swap(my_vector &vct) {
    std::swap(_size, vct._size);
    std::swap(_capacity, vct._capacity);
    std::swap(data, vct.data);
}

template<class T>
void my_vector<T>::pop_back() {
    data[--_size].~T();
}

template<class T>
void my_vector<T>::push_back(const T &value) {
    if (_size >= _capacity) {
        _capacity = _capacity * CAPACITY_MULTIPLIER;
        realloc();
    }
    data[_size++] = value;
}

template<class T>
template<typename... Args>
void my_vector<T>::emplace_back(Args &&... args) {
    this->push_back(T(std::forward<Args>(args)...));
}

template<class T>
T *my_vector<T>::insert(const T *iter, size_t amount, T &value) {
    size_t pos = iter - data;
    if (pos + amount >= _capacity) {
        _size = pos;
        _capacity = (pos + amount) * CAPACITY_MULTIPLIER;
        realloc();
    }
    for (size_t i = 0; i < amount; i++)
        data[pos + i] = value;

    _size = std::max(pos + amount, _size);
    return data + pos;
}

template<class T>
T *my_vector<T>::insert(const T *iter, const T *begin, const T *end) {
    size_t pos = iter - data;
    size_t amount = end - begin;
    if (pos + amount >= _capacity) {
        _size = pos;
        _capacity = (pos + amount) * CAPACITY_MULTIPLIER;
        realloc();
    }
    for (size_t i = 0; i < amount; i++)
        data[pos + i] = begin[i];

    _size = std::max(pos + amount, _size);
    return data + pos;
}

template<class T>
T *my_vector<T>::erase(const T *iter) {
    size_t index = iter - data;

    data[index].~T();

    for (size_t i = index + 1; i < _size; i++)
        data[i - 1] = data[i];

    _size--;

    return data + index;
}

template<class T>
T *my_vector<T>::erase(const T *begin, const T *end) {
    size_t index = begin - data;
    size_t amount = end - begin;

    for (size_t i = index; i < amount; i++)
        data[i].~T();

    for (size_t i = index + amount; i < _size; i++)
        data[i - amount] = data[i];

    _size -= amount;

    return data + index;
}

template<typename T>
bool operator==(const my_vector<T> &lhs,
                const my_vector<T> &rhs) {
    if (lhs.size() != rhs.size())
        return false;

    for (size_t i = 0; i < lhs.size(); i++)
        if (lhs[i] != rhs[i])
            return false;

    return true;
}

template<typename T>
bool operator!=(const my_vector<T> &lhs,
                const my_vector<T> &rhs) {
    return !(lhs == rhs);
}

template<typename T>
bool operator>(const my_vector<T> &lhs,
               const my_vector<T> &rhs) {
    for (size_t i = 0; i < std::min(lhs.size(), rhs.size()); i++) {
        if (lhs[i] > rhs[i])
            return true;
        if (lhs[i] < rhs[i])
            return false;
    }

    if (lhs.size() < rhs.size())
        return true;
    else
        return false;
}

template<typename T>
bool operator<(const my_vector<T> &lhs,
               const my_vector<T> &rhs) {
    for (size_t i = 0; i < std::min(lhs.size(), rhs.size()); i++) {
        if (lhs[i] < rhs[i])
            return true;
        if (lhs[i] > rhs[i])
            return false;
    }

    if (lhs.size() >= rhs.size())
        return false;
    else
        return true;
}

template<typename T>
bool operator<=(const my_vector<T> &lhs,
                const my_vector<T> &rhs) {
    for (size_t i = 0; i < std::min(lhs.size(), rhs.size()); i++) {
        if (lhs[i] > rhs[i])
            return false;
        if (lhs[i] < rhs[i])
            return true;
    }

    if (lhs.size() <= rhs.size())
        return true;
    else
        return false;
}

template<typename T>
bool operator>=(const my_vector<T> &lhs,
                const my_vector<T> &rhs) {
    for (size_t i = 0; i < std::min(lhs.size(), rhs.size()); i++) {
        if (lhs[i] > rhs[i])
            return false;
        if (lhs[i] < rhs[i])
            return true;
    }

    if (lhs.size() >= rhs.size())
        return true;
    else
        return false;
}

#endif //ADDER_MY_VECTOR_H

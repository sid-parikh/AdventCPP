#pragma once

#include <cstdlib>
#include <utility>
#include <algorithm>
#include <iostream>

namespace structures {

    /**
     * This is just practicing creating a container,
     * in this case, an array-backed queue
     * @tparam T
     */
    template<typename T>
    class queue_it {
    public:

        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::forward_iterator_tag;

        queue_it(T* arr, size_t start, size_t capacity) : arr_{arr}, curr_{start}, capacity_{capacity} {}

        T& operator*() const {
            return arr_[curr_ % capacity_];
        }

        queue_it& operator++() {
            ++curr_;
            return *this;
        }

        queue_it operator++(int)& { //NOLINT(*-dcl21-cpp)
            return queue_it{arr_, curr_ + 1, capacity_};
        }

        queue_it& operator+=(size_t amt) {
            curr_ += amt;
            return *this;
        }

        bool operator==(const queue_it& rhs) const {
            return (arr_ == rhs.arr_) && (curr_ == rhs.curr_) && (capacity_ == rhs.capacity_);
        }

    private:
        T* arr_;
        size_t curr_;
        const size_t capacity_;
    };

    template<typename T>
    class queue_const_it {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::forward_iterator_tag;

        queue_const_it(const T* arr, size_t curr, size_t capacity) : arr_{arr}, curr_{curr}, capacity_{capacity} {}

        const T& operator*() const {
            return arr_[curr_ % capacity_];
        }

        queue_const_it& operator++() {
            ++curr_;
            return *this;
        }

        queue_const_it operator++(int)& { //NOLINT(*-dcl21-cpp)
            return queue_const_it{arr_, curr_ + 1, capacity_};
        }

        queue_const_it& operator+=(size_t amt) {
            curr_ += amt;
            return *this;
        }

        bool operator==(const queue_const_it& rhs) const {
            return (arr_ == rhs.arr_) && (curr_ == rhs.curr_) && (capacity_ == rhs.capacity_);
        }

    private:
        const T* arr_;
        size_t curr_;
        size_t capacity_;
    };

    template<typename T>
    queue_it<T> operator+(const queue_it<T> it, size_t amt) {
        queue_it<T> ret = it;
        ret += amt;
        return ret;
    }

    /**
     * Array Backed Queue
     * @tparam T type. currently must be default constructible
     */
    template<typename T>
    class Queue {
    public:
        Queue() : arr_{new T[default_size]}, size_{0}, capacity_{default_size}, start_{0} {}

        Queue(std::initializer_list<T> list) : arr_{new T[list.size()]}, size_{list.size()}, capacity_{list.size()},
                                               start_{0} {
            std::copy(list.begin(), list.end(), arr_);
        }

        ~Queue() {
            delete[] arr_;
        }

        using iterator = queue_it<T>;
        using const_iterator = queue_const_it<T>;

        Queue(const Queue& other) {
            arr_ = new T[other.capacity_];
            std::copy(other.arr_, other.arr_ + other.capacity_, arr_);
            capacity_ = other.capacity_;
            size_ = other.size_;
            start_ = other.start_;
        }

        Queue(Queue&& other) noexcept {
            arr_ = other.arr_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            start_ = other.start_;

            other.arr_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
            other.start_ = 0;
        }

        Queue& operator=(const Queue& other) {
            if (this == &other) {
                return *this;
            }

            T* new_arr = new T[other.capacity_];
            std::copy(other.arr_, other.arr_ + capacity_, new_arr);

            delete[] arr_;
            arr_ = new_arr;

            capacity_ = other.capacity_;
            size_ = other.size_;
            start_ = other.start_;

            return *this;
        }

        Queue& operator=(Queue&& other) noexcept {
            delete[] arr_;

            arr_ = other.arr_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            start_ = other.start_;

            other.arr_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
            other.start_ = 0;

            return *this;
        }

        T dequeue() {
            T ret = arr_[start_];
            start_ = (start_ + 1) % capacity_;
            --size_;
            return ret;
        }

        void pop() {
            start_ = (start_ + 1) % capacity_;
            --size_;
        }

        void enqueue(T&& elem) {
            if (size_ == capacity_) {
                double_capacity();
            }
            arr_[(start_ + size_) % capacity_] = std::move(elem);
            ++size_;
        }

        void enqueue(const T& elem) {
            if (size_ == capacity_) {
                double_capacity();
            }
            arr_[(start_ + size_) % capacity_] = elem;
            ++size_;
        }

        T& front() {
            return arr_[start_];
        }

        const T& front() const {
            return arr_[start_];
        }

        iterator begin() noexcept {
            return queue_it{arr_, start_, capacity_};
        }

        iterator end() noexcept {
            return queue_it{arr_, start_ + size_, capacity_};
        }

        const_iterator begin() const noexcept {
            return cbegin();
        }

        const_iterator end() const noexcept {
            return cend();
        }

        const_iterator cbegin() const noexcept {
            return queue_const_it{arr_, start_, capacity_};
        }

        const_iterator cend() const noexcept {
            return queue_const_it{arr_, start_ + size_, capacity_};
        }

        [[nodiscard]] size_t size() const noexcept {
            return size_;
        }

        [[nodiscard]] bool empty() const noexcept {
            return size_ == 0;
        }

    private:
        T* arr_;
        size_t size_;
        size_t capacity_;
        size_t start_;
        static constexpr size_t default_size{16};

        void double_capacity() {
            T* new_arr = new T[capacity_ * 2];
            std::copy(cbegin(), cend(), new_arr);

            delete[] arr_;
            arr_ = new_arr;
            capacity_ *= 2;
            start_ = 0;
        }
    };


} // structures
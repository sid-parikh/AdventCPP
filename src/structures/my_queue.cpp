#include "my_queue.hpp"

#include <iostream>

void test_queue() {
    using namespace structures;

    Queue<int> q {};
    q.enqueue(3);

    std::cout << q.front() << std::endl;

}
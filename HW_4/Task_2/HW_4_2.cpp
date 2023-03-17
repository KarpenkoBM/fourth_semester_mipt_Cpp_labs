#include <thread>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <functional>
#include <iterator>
#include<future>
#include <mutex>

std::mutex door;

template<typename Iter, typename Func>

void parallel_for_each( Iter begin, Iter end, Func f)
{

    unsigned long const length = std::distance(begin, end);
    if (length == 0 ) return;
    const int numberOfThreads = std::thread::hardware_concurrency();
    unsigned long const MinElementsPerThread = 50;
    if (length < (2 * MinElementsPerThread))
        {
            door.lock();
            std::for_each(begin, end, f);
            door.unlock();
        }
    else
        {
            Iter  mid_point = begin + length / 2;
            std::future<void> first_half = std::async(&parallel_for_each<Iter,Func>,begin, mid_point, f);
            parallel_for_each(mid_point, end, f);
        }
}

int main()
{
    size_t size = 1000;
    //std::cin >>size;
    std::vector<int>  sequence_1(size);
    for (auto i = 0; i < size; i++) sequence_1[i] = i;
     auto print = [](const int& n) { std::cout << n << ' '; };
    parallel_for_each(sequence_1.begin(),sequence_1.end(), print );
    parallel_for_each(sequence_1.begin(),sequence_1.end(), [](int &n){n *= n;});
    std::cout<<std::endl;
    parallel_for_each(sequence_1.begin(),sequence_1.end(), print );
}

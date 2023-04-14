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

template<typename Iter, typename Func>
int block_for_each(Iter begin, Iter end, Func f) {
    std::for_each(begin, end, f);
}
template<typename Iter, typename Func>
void parallel_for_each (Iter begin, Iter end, Func f)
{
    auto num_threads = std::thread::hardware_concurrency();
    auto block_size = std::distance(begin, end) / num_threads;
    std::vector<std::future<int>> threads;
    for (auto i = 0u; i + 1 < num_threads; i++)
        {
            threads.push_back(std::async(std::launch::async, &block_for_each<Iter, Func>, std::next(begin, i * block_size), std::next(begin, (i + 1) * block_size), f));
        }
    threads.push_back(std::async(std::launch::async, &block_for_each<Iter, Func>, std::next(begin, (num_threads - 1) * block_size), end, f));
    for(auto& it : threads)
    {
        it.wait();
    }
}
int main()
{
    size_t size = 10000;
    //std::cin >>size;
    std::vector<int>  sequence_1(size);
    for (auto i = 0; i < size; i++) sequence_1[i] = i;
     auto print = [](const int& n) { std::cout << n << ' '; };
    parallel_for_each(sequence_1.begin(),sequence_1.end(), print );
    parallel_for_each(sequence_1.begin(),sequence_1.end(), [](int &n){n *= n;});
    std::cout<<std::endl;
    parallel_for_each(sequence_1.begin(),sequence_1.end(), print );
    //std::for_each(sequence_1.begin(),sequence_1.end(), print);
    //std::for_each(sequence_1.begin(),sequence_1.end(), [](int &n){n *= n;});
     //std::for_each(sequence_1.begin(),sequence_1.end(), print);

}

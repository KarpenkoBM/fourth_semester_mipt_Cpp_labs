#include <thread>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <functional>
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>

using namespace nlohmann;


using steady_clock_t = std::chrono::steady_clock;

template <typename T>
class Timer
{
    public:
        Timer(const std::string& message): message(message), begin(steady_clock_t::now()) {}
        double getTime()
        {
            auto end = steady_clock_t::now();
            auto diff = end - begin;
            T passed =  std::chrono::duration_cast<T>(diff);
            return passed.count();
        }


        ~Timer() {
            //std::cout << message << ": " << std::chrono::duration_cast<T>(steady_clock_t::now() - begin).count() << std::endl;
        }
    private:
        steady_clock_t::time_point begin;
        std::string message;
};


template<typename Iter, typename T>
void accumulate_block(Iter begin, Iter end, T init, T& result) {
	result = std::accumulate(begin, end, init);
}

template<typename Iter, typename T>
T parallel_accumulate(Iter begin, Iter end, T init, int n)
 {
	auto num_threads = n;
	std::vector<std::thread> threads;
	std::vector<T> results(num_threads - 1);
	unsigned
	 long long int block_size = std::distance(begin, end) / num_threads;
	for (auto i = 0u; i + 1 < num_threads; i++) {
		threads.push_back(std::thread(
			accumulate_block<Iter, T>,
			std::next(begin, i * block_size),
			std::next(begin, (i + 1) * block_size),
			0,
			std::ref(results[i]))
		);
	}
	T last_result;
	accumulate_block(std::next(begin, (num_threads - 1) * block_size),
			end, init, last_result);
	std::for_each(std::begin(threads), std::end(threads), std::mem_fn(&std::thread::join));
	return std::accumulate(std::begin(results), std::end(results), last_result);
}

int main() {
	auto size = 0ull;
    std::filesystem::create_directory("parallel_accum");
    for(size = 1000; size < 10'000'000'000; size *= 10)
    {
       std::vector<unsigned long long int> numbers(size);
        std::iota(std::begin(numbers), std::end(numbers), 1);
        auto max_threads = std::thread::hardware_concurrency();
        auto time = 0.0 ;
        auto summ = 0ull;
        json object;
        for(int i = 1; i <= max_threads; i++)
        {

                Timer<std::chrono::microseconds> t("Parallel");
                summ = parallel_accumulate(std::begin(numbers), std::end(numbers), 0ull, i);
                time += t.getTime();

            object["number of threads"][i - 1] = i;
            object["time"][i - 1] = (time/10);
            object["summ"][i - 1] = summ;
        }
        std::ofstream file("parallel_accum/sum "+std::to_string(size)+".json");
        file << object;
    }
}


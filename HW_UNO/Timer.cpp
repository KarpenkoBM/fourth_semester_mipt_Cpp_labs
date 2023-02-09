#include <iostream>
#include <chrono>
#include <cmath>

template <typename T>
class Timer
{
public:
	Timer() : begin(std::chrono::steady_clock::now()) {}
	void start()
	{
		begin = std::chrono::steady_clock::now();  
	}

    void stop()
	{
		passed += std::chrono::steady_clock::now() - begin;
	}

	void show()
	{
		std::cout<< std::chrono::duration_cast<T>(passed).count()<<std::endl;  
	}

	void Reset()
	{
		passed =  std::chrono::duration<double>(0);
	}
	~Timer() 
	{
		std::cout <<"My name is uwuvweuweonetenewueouemubemossas"<<std::endl;
	}
private:
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	std::chrono::duration<double> passed;
};

int main() {
	auto count = 0.;
	{
		Timer<std::chrono::microseconds> t;
		t.start();
		for (auto i = 0; i < 1'000'000; i++) {
			count += std::cos(i) + std::sin(i);
		}
        t.stop();
		t.show();
		t. start();
		for (auto i = 0; i < 1'000'000; i++) 
		{
			count += std::cos(i) + std::sin(i);
		}
		 t.stop();
		t.show();

		
	}

}

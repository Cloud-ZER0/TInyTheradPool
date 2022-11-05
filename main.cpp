#include "ThreadPool.h"
void task(std::vector<std::vector<int>>& vec, std::size_t i) {

	for (auto j = 0; j < vec[i].size();++j) {
		vec[i].operator[](j)++;
	}
}

int main() {
	
	auto start = std::chrono::steady_clock::now();

	tp::ThreadPool pool(4);

	int shared_int = 0;

	for (auto i = 0; i < 100'500; ++i) {
		pool.Submit([&shared_int]() {
			++shared_int;
			});
	}
	pool.Wait();
	pool.Stop();

	std::cout << shared_int << '\n';

	auto elapsed = std::chrono::steady_clock::now() - start;

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << "ms" << '\n';

	/*int i = 0;
	while (i < 100'000'000) {
		++i;
	}
	i = 0;
	
	while (i < 100'000'000) {
		++i;
	}
	i = 0;

	while (i < 100'000'000) {
		++i;
	}
	i = 0;*/


	return 0;
}
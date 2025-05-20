#include <vector>
#include <thread>
#include <numeric>
#include <algorithm>
#include <iostream>

int concurrent_vector_sum(const std::vector<int>& vec) 
{
    if (vec.empty()) {
        return 0;
    }

    const size_t num_hardware_threads = std::thread::hardware_concurrency();
    const size_t num_threads = std::min(num_hardware_threads, vec.size());
    const size_t chunk_size = vec.size() / num_threads;

    std::vector<int> partial_sums(num_threads, 0);
    std::vector<std::thread> threads(num_threads);

    for (size_t i = 0; i < num_threads; ++i) {
        const size_t start = i * chunk_size;
        const size_t end = (i == num_threads - 1) ? vec.size() : start + chunk_size;

        threads[i] = std::thread([&vec, start, end, &partial_sums, i] {
            partial_sums[i] = std::accumulate(vec.begin() + start, vec.begin() + end, 0);
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return std::accumulate(partial_sums.begin(), partial_sums.end(), 0);
}

int main()
{
    int max_num = 100;
    std::vector<int> data(max_num);
    for (int i = 0; i < max_num; i++)
    {
        data[i] = i + 1;
    }

    std::cout << concurrent_vector_sum(data) << std::endl;

    return 0;
}
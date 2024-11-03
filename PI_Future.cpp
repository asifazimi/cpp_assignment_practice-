#include <iostream>
#include <thread>
#include <vector>
#include <future>

double calculatePartielPI(int start, int end)
{
    double local_sum = 0.0;
    for (int i = start; i < end; ++i)
    {
        if (i % 2 == 0)
        {
            local_sum += 1.0 / (2.0 * i + 1.0);
        }
        else
        {
            local_sum -= 1.0 / (2.0 * i + 1.0);
        }
    }

    return local_sum;
}

int main()
{
    int num_terms = 1000000;
    int num_threads = 4;

    // static work allocation
    int terms_per_thread = num_terms / num_threads;
    std::vector<std::future<double>> futures;

    // to give the asynce task for every chunk to calculate
    for (int i = 0; i < num_threads; ++i)
    {
        int start = i * terms_per_thread;
        int end = (i == num_threads - 1) ? num_terms : start + terms_per_thread;

        // launch asynce task and store the future
        futures.push_back(std::async(std::launch::async, calculatePartielPI, start, end));
    }

    // aggregate results from all futures
    double pi = 0.0;
    for (auto &fut : futures)
    {
        pi += fut.get(); // Reterieve and accumulate each partial result
    }

    // multiply by 4 to get the final PI value
    pi *= 4.0;
    std::cout << "Calculate PI (Partial with future): " << pi << std::endl;
    return 0;
}

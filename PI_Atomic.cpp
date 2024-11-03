#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

// void atomic_add(std::atomic<double> &shared_value, double value)
// {
//     double current = shared_value.load();
//     while (!shared_value.compare_exchange_weak(current, current + value))
//     {
//         // keep retrying until the operation is successful
//     }
// }

void cacluatePartialPI(int start, int end, std::atomic<double> &pi)
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
    pi = pi + local_sum;
}

int main()
{
    int num_terms = 1000000;
    int num_threads = 4;
    std::atomic<double> pi(0.0); // shared atomic variable

    int terms_per_thread = num_terms / num_threads; // static work allocation

    std::vector<std::thread> threads;

    // Creating threads and assign work to them
    for (int i = 0; i < num_threads; ++i)
    {
        int start = i * terms_per_thread;
        int end = (i == num_threads - 1) ? num_terms : start + terms_per_thread;
        threads.emplace_back(cacluatePartialPI, start, end, std::ref(pi));
    }

    // Wait for all threads to finish
    for (auto &th : threads)
    {
        th.join();
    }

    // pi = pi.load() * 4.0;
    pi = pi * 4.0;
    // std::cout << "Caculate PI (Parallel with Atomic): " << pi.load() << std::endl;
    std::cout << "Caculate PI Succesfully (Parallel with Atomic): " << pi << std::endl;
    return 0;
}
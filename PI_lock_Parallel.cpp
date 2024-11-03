#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mtx;

void calculatePartialPI(int start, int end, double &pi) // we use &(reference variable to only use the original variable not the copies)
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

    std::lock_guard<std::mutex> lock(mtx);
    pi += local_sum;
}

int main()
{

    int num_terms = 1000000;
    int num_threads = 4;

    double pi = 0.0;

    int terms_per_thread = num_terms / num_threads; // static work allocation

    std::vector<std::thread> threads;

    // creating threads and assgin works
    for (int i = 0; i < num_threads; ++i)
    {
        int start = i * terms_per_thread;
        int end = (i == num_threads) ? num_terms : start + terms_per_thread;
        threads.emplace_back(calculatePartialPI, start, end, std::ref(pi));
    }

    // wait for all threads to finish
    for (auto &th : threads)
    {
        th.join();
    }

    // multiply by 4 to get the final value
    pi *= 4.0;
    std::cout << "Pi value is equal to : " << pi << std::endl;
    return 0;
}
#include <iostream>

// based on a formal we calculate the below function

double calculatePI(int num_terms)
{

    double pi = 0.0;

    for (int i = 0; i < num_terms; ++i)
    {
        if (i % 2 == 0)
        {
            pi += 1.0 / (2.0 * i + 1.0);
        }
        else
        {
            pi -= 1.0 / (2.0 * i + 1.0);
        }
    }

    return 4.0 * pi;

    // Return the approximate value of PI
}

int main()
{

    int num_terms = 1000000;
    double pi = calculatePI(num_terms);

    std::cout << "Approximate value of PI: " << pi << std::endl;

    return 0;
}
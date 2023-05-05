#include "PmergeMe.hpp"
#include <iostream>


int main(int ac,char **av)
{
    if(ac < 2)
        return 1;

    int i = 0;
    PmergeMe *sorted;
    sorted = PmergeMe::getMerge(av);
    while (av[++i])
    {
        if(sorted->is_num(av[i]) == false || atoi(av[i]) < 0)
        {
            std::cerr << "error" << std::endl;
            delete sorted;
            exit (1);
        }
    }
    sorted->sort_it();
    delete sorted;
}
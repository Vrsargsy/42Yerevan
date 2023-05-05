#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <set>
#include <chrono>
#include <sys/time.h>

struct ListType
{
	enum List
	{
        list,
        vector,
        deque
	};
};


class PmergeMe
{
    private:
        static PmergeMe *instance;
        std::vector<int>ivector;
        std::deque<int>ideque;
        int limit;

    private:
        class INVALID_INPUT : std::exception
        {
            const char *what()const throw();
        };

    private:
        template <typename T>
        void merge(T& arr, int left, int mid, int right);
        template <typename T>
        void insertSort(T&arr,int left, int right);
        template <typename T>
        void mergeSort(T& arr, int left, int right);
        PmergeMe();
        PmergeMe(char **av);
        double get_time();
    
    public:
        ~PmergeMe();
        bool is_num(std::string const &str);
        void sort_it();
        static PmergeMe *getMerge(char **av);
};






#endif
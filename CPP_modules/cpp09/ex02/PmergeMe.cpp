#include "./PmergeMe.hpp"

PmergeMe *PmergeMe::instance = NULL;

PmergeMe::PmergeMe(char **av)
{
    if(!this->instance)
    {
        instance = this;
        int i = 0;
        while (av[++i])
        {
            ideque.push_back(atoi(av[i]));
            ivector.push_back(atoi(av[i]));
        }
        limit = ivector.size() > 16 ? ivector.size() / 100 : 16;
    }
    else
        this->~PmergeMe();
}

PmergeMe::PmergeMe() { }

PmergeMe::~PmergeMe() { }


template <typename T>
void PmergeMe::merge(T& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    T L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void PmergeMe::insertSort(T&arr,int left, int right)
{
      for (int i = left + 1; i <= right; i++) 
      {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
                    j--;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
void PmergeMe::mergeSort(T& arr, int left, int right) 
{
    if (left < right) {
        if (right - left <= limit) 
            insertSort(arr,left,right);
        else 
        {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
}
void PmergeMe::sort_it() 
{
   
    double start;
    double vec;
    double deq;
    std::deque<int>::iterator itt = ideque.begin();
    std::cout << "before : ";
    while (itt != ideque.end())
    {
        std::cout << *itt << " ";
        ++itt;
    }
    std::cout << std::endl;
    start = get_time();
    mergeSort(ivector, 0, ivector.size() - 1);
    vec = (get_time() - start);
    start = get_time();
    mergeSort(ideque,0,ideque.size() - 1);
    deq = (get_time() - start);
    std::vector<int>::iterator it = ivector.begin();
    std::cout << "after : ";
    while (it != ivector.end())
    {
        std::cout << *it << " ";
        ++it;
    }
    std:: cout << std::endl;
    std:: cout << "Time to proccess the vector merge && insertion sort is : " << vec << " ms\n"
                << "Time to proccess the deque merge && insertion sort is : " << deq << " ms" << std::endl;
    
}



bool PmergeMe::is_num(std::string const &str)
{
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it))
        it++;
    return !str.empty() && it == str.end();
    
}

PmergeMe *PmergeMe::getMerge(char **av)
{
    if(!instance)
        return new PmergeMe(av);
    return instance; 
}

const char *PmergeMe::INVALID_INPUT::what()const throw()
{
    return "error";
}

double PmergeMe::get_time()
{
    struct timeval time;
    gettimeofday(&time,NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

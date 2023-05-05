#ifndef RPN_HPP
 #define RPN_HPP

#include <iostream>
#include <stack>
#include <cmath>
#include <cstring>

class RPN
{
private:
    static RPN *instance;
    std::stack<double>stak;
    std::string input;

    RPN();
    RPN(std::string const &input);
    RPN(const RPN &copy);
    RPN &operator=(const RPN &dcopy);


    class ERROR : public std::exception {
        const char *what() const throw();
    };

    std::string trim(std::string const &str)const;
    double scanNum(char ch);
    bool isOperator(char ch);
    bool isOperand(char ch);
    double operation(double a, double b, char oper);
    bool is_num(std::string const &str);
    int oper_cnt(std::string const &copy);
    int opernd_cnt(std::string const &copy);
    void validate();
public:
   static RPN *getRPN(std::string const &input);
    ~RPN();
    double start();
};


#endif
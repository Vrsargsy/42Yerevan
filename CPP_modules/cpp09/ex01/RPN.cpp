#include "./RPN.hpp"

RPN *RPN::instance = NULL;

RPN::RPN() {}
RPN::~RPN() {}


RPN::RPN(std::string const &input):input(input)
{
   if (!this->instance)
      instance = this;
   else
      this->~RPN();
}



RPN *RPN::getRPN(std::string const &input)
{
   if(!instance)
      instance = new RPN(input);
   return instance;
}

double RPN::scanNum(char ch)
{
   int value;
   value = ch;
   return double(value-'0');
}

bool RPN::isOperator(char ch)
{
   if(ch == '+'|| ch == '-'|| ch == '*'|| ch == '/')
      return true;
   return false;
}
bool RPN::isOperand(char ch)
{
   if(ch >= '0' && ch <= '9')
      return true;
   return false;
}
double RPN::operation(double aint, double bint, char op)
{
   double b = bint * 1.0;  
   double a = aint * 1.0;
   if(op == '+')
      return b+a;
   else if(op == '-')
      return b-a;
   else if(op == '*')
      return b*a;
   else if(op == '/')
   {
      if(a == 0)
         throw ERROR();
      return b/a;
   }
   else
      return INT_MIN;
}

double RPN::start()
{
   double a, b;
   validate();
   std::stack<double> stak;
   std::string::iterator it;
   for(it=input.begin(); it!=input.end(); it++){
      if(isOperator(*it) != false){
         a = stak.top();
         stak.pop();
         b = stak.top();
         stak.pop();
         stak.push(operation(a, b, *it));
      }
      else if(isOperand(*it) > 0){
         stak.push(scanNum(*it));
      }
   }
   return stak.top();
}

bool RPN::is_num(std::string const &str)
{
   std::string::const_iterator it = str.begin();
   while (it != str.end() && std::isdigit(*it))
      ++it;
   return !str.empty() && it == str.end();
    
}

int RPN::oper_cnt(std::string const &cpy)
{
   std::string str = cpy;
   std::string check;
   int res = 0;
   std::string::iterator it = input.begin();
   while (it != input.end())
    {
      if(isOperator(*it))
         res++;
      ++it;
    }
   return res;
}
int RPN::opernd_cnt(std::string const &cpy)
{
   std::string str = cpy;
   std::string check;
   int res = 0;
   std::string::iterator it = str.begin();
	while (it != str.end())
	{
      if(std::isdigit(*it))
         ++res;
      it++;
	}
    return res;
}

std::string RPN::trim(std::string const &str)const 
{
    size_t start_pos = str.find_first_not_of(" \r\n");
    size_t end_pos = str.find_last_not_of(" \t\r\n");

    if (start_pos == std::string::npos || end_pos == std::string::npos) {
        return "";
    }

    return str.substr(start_pos, end_pos - start_pos + 1);
}


const char *RPN::ERROR::what() const throw()
{
    return "ERROR!";
}

void RPN::validate()
{
   if(input.length() < 3)
       throw ERROR();
   std::string::iterator it = input.begin();
   if(!isOperator(trim(input).back()))
     throw ERROR();
   while (it != input.end())
   {
       if(!(std::isdigit(*it) || isOperand(*it) || isOperator(*it) || *it == ' '))
           throw ERROR();
       ++it;
   }
   if(opernd_cnt(input) != (oper_cnt(input) + 1))
       throw ERROR();
}
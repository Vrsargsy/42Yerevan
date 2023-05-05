#include "./RPN.hpp"

int main(int ac,char **av)
{
   if(ac < 2)
   {
      std::cerr << "Invalid arguments\n";
      return 1;
   }
   RPN *calculator = RPN::getRPN(av[1]);
   try
   {
      std::cout << calculator->start() << std::endl;
   }
   catch(const std::exception& e)
   {
      std::cerr << e.what() << '\n';
   }
}
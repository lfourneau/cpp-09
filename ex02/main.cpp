#include "PmergeMe.hpp"

int main(int ac, char **av)
{
   if (ac == 1)
   {
      
      std::cerr << "This program requires at least one argument" << std::endl;
      return (2);
   }

   for (int i = 1; i < ac; i++)
   {
      int j = 0;
      while (av[i][j])
      {
         if (!std::isdigit(av[i][j]))
         {
            std::cerr << "Error" << std::endl;
            return (2);
         }
         j++;
      }
   }

   std::cout << "Before: ";
   for (int i = 1; i < ac; i++)
   {
      if (i < 6)
         std::cout << av[i] << " ";
      if (i == 6)
         std::cout << " [..] ";
   }
   std::cout << "\n";
   std::string vec = "std::vector";
   std::string list = "std::list";
   PmergeMe<std::vector<std::pair<long, long> > >   exercize_vec(av + 1, vec);
   PmergeMe<std::list<std::pair<long, long> > >   exercize_list(av + 1, list);
   return 0;
}
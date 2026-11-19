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
      if (av[i][0] == '\0')
      {
         std::cerr << "Error: empty argument" << std::endl;
         return (2);
      }
      while (av[i][j])
      {
         if (!std::isdigit(av[i][j]))
         {
            std::cerr << "Error: not a positive number: " << av[i] << std::endl;
            return (2);
         }
         j++;
      }
      std::istringstream stream(av[i]);
      long value = 0;
      stream >> value;
      if (stream.fail() || value > std::numeric_limits<int>::max())
      {
         std::cerr << "Error: value is too big: " << av[i] << std::endl;
         return (2);
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
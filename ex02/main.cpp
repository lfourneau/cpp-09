#include "PmergeMe.hpp"

int main(int ac, char **av)
{
   (void)ac;
   std::string vec = "std::vector";
   std::string list = "std::list";
   PmergeMe<std::vector<std::pair<long, long> > >   exercize_vec(++av, vec);
   PmergeMe<std::list<std::pair<long, long> > >   exercize_list(++av, list);
   return 0;
}
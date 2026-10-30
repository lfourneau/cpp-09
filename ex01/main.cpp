#include "RPN.hpp"

int main(int ac , char **av)
{
    if (ac != 2)
    {
        std::cerr << "This program expects one RPN notation argument" \
        << std::endl;
        return (1);
    }
    RPN exercize(av[1]);

    return (0);
}
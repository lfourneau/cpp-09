#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Program requires one argument" << std::endl;
        return (1);
    }
    BitcoinExchange transform_to_map(av + 1);
    return (0);
}
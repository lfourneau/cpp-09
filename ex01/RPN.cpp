#include "RPN.hpp"

RPN::RPN(char *av)
{
    find_solution(av);
}

RPN::RPN(RPN const &other)
{
    digits = other.digits;
}

RPN &RPN::operator=(RPN const &other)
{
    if (this != &other)
    {
        digits = other.digits;
    }
    return (*this);
}

RPN::~RPN()
{
}

void    RPN::find_solution(std::string val)
{
    std::istringstream content(val);
    std::string curr;
    int type;

    while (true)
    {
        if (! (content >> curr))
        {
            if (content.peek() == EOF)
                break;
            throw(RPNErr("too many chars (number)"));
        }
        if (curr.size() != 1)
            throw(RPNErr("too many chars (number)"));
        type = find_type(curr[0]);

        if (type == OTHER)
            throw(RPNErr("invalid sign"));
        if (type == SIGN)
        {
            if (digits.size() < 2)
                throw(RPNErr("too many elements in sign stack"));
            calculate(curr[0]);
            continue;
        }
        if (type == NUMBER)
        {
            digits.push_front(curr[0] - '0');
        }
    }
    if (digits.size() == 0)
        throw(RPNErr("Need a number for it to work obviously"));
    if (digits.size() != 1)
        throw(RPNErr("Too many digits in que"));
    std::cout << digits.front() << std::endl;
}

int RPN::find_type(char &val)
{
    if (std::isdigit(val))
        return (NUMBER);
    else if (val == '+' || val == '-' || val == '*' || val == '/')
        return (SIGN);
    else
        return (OTHER);
}

void RPN::calculate(char const &val)
{
    double top = static_cast<double>(digits.front());
    digits.pop_front();
    double bellow = static_cast<double>(digits.front());
    digits.pop_front();

    switch(val)
    {
        case '+':
            bellow = std::plus<double>()(bellow, top);
            break;
        case '-':
            bellow = std::minus<double>()(bellow, top);
            break;
        case '*':
            bellow = std::multiplies<double>()(bellow, top);
            break;
        case '/':
            if (top == 0)
            {
                throw(RPNErr("division by 0"));
                return ;
            }
            bellow = std::divides<double>()(bellow, top);
            break;
    }
    digits.push_front(bellow);
}
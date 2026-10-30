#include "RPN.hpp"

RPN::RPN(char *av)
{
    try
    {
        find_solution(av);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return ;
    }
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

//double RPN::transform_to_double(std::string &val)
//{
//    std::istringstream content(val);
//    double return_val;
//
//    content >> return_val;
//    return (return_val);
//}
//
//void RPN::parse_input(std::string av)
//{
//    std::stringstream input(av);
//    std::string content_section;
//
//    while (getline(input, content_section, ' '))
//    {
//        check_number(content_section);
//        new_data.num = transform_to_double(content_section);
//        if (first_character == false)
//        {
//            if (getline(input, content_section, ' '))
//            {
//                check_operator(static_cast<char>(content_section[0]));
//            }
//            new_data.sign = static_cast<char>(content_section[0]);
//        }
//        else 
//        {
//            first_character = false;
//            new_data.sign = '+';
//        }
//        this->list.push_back(new_data);
//    }
//}
//
//void    RPN::check_number(std::string test)
//{
//    double result;
//
//    try
//    {
//        isnum(test);
//        result = transform_to_double(test);
//    }
//    catch(const std::exception& e)
//    {
//        throw (IncorrectNumber());
//    }
//
//    if (result > 10)
//        throw(ValueOverTen());
//}
//
//void    RPN::isnum(std::string const &val)
//{
//    std::string::const_iterator it = val.begin();
//
//    for (; it != val.end(); ++it)
//    {
//        if (*it < 48 || *it > 57)
//            throw (IncorrectNumber());
//    }
//}
//
//void    RPN::check_operator(char const &oper)
//{
//    char authorized_characters[] = {'+', '-', '/', '*'};
//
//    for (int i = 0; i < 4; i++)
//    {
//        if (authorized_characters[i] == oper)
//            return ;
//    }
//    throw (IncorrectOperand());
//}
//
//void RPN::calculate_result() 
//{
//    double  result = 0;
//    char    current_operation;
//
//
//    for (std::list<t_rpn>::iterator it = this->list.begin(); it != this->list.end(); it++)
//    {
//        current_operation = (*it).sign;
//        switch (current_operation)
//        {
//        case '+':
//            result = std::plus<double>()(result, (*it).num);
//            break;
//        case '-':
//            result = std::minus<double>()(result, (*it).num);
//            break;
//        case '*':
//            result = std::multiplies<double>()(result, (*it).num);
//            break;
//        case '/':
//            if ((*it).num == 0)
//            {
//                std::cout << "Forbidden division by 0" << std::endl;
//                return ;
//            }
//            result = std::divides<double>()(result, (*it).num);
//            break;
//        }
//    }
//    std::cout << static_cast<int>(result) << std::endl;
//}
#include "RPN.hpp"

RPN::RPN(char **av)
{
    try
    {
        check_one_arg(av);
        parse_input(static_cast<std::string>(av[0]));
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return ;
    }
    calculate_result();

}

RPN::RPN(RPN const &other)
{
    list = other.list;
}

RPN &RPN::operator=(RPN const &other)
{
    list = other.list;
    return (*this);
}

RPN::~RPN()
{
}

Node::Node(double value, char operand) : number(value), sign(operand)
{
}

Node::Node(Node const &other) : number(other.getNumber()), sign(other.getSign())
{

}

Node    &Node::operator=(Node const &other)
{
    this->number = other.getNumber();
    this->sign = other.getSign();
    return (*this);
}

Node::~Node()
{

}

void    RPN::check_one_arg(char **av)
{
    int i = 0;
    
    while (*av != NULL)
    {
        i++;
        av++;
    }
    if (i != 1) 
    {
        throw(NotCorrectArguments());
        return ;
    }
}

void RPN::parse_input(std::string av)
{
    bool first_character = true;
    std::stringstream input(av);
    std::string content_section;
    Node new_node;

    while (getline(input, content_section, ' '))
    {
        check_number(content_section);
        new_node.setNumber(stod(content_section));
        if (first_character == false)
        {
            if (getline(input, content_section, ' '))
            {
                check_operator(static_cast<char>(content_section[0]));
            }
            new_node.setSign(static_cast<char>(content_section[0]));
        }
        else 
        {
            first_character = false;
            new_node.setSign('+');
        }
        this->list.push_back(new_node);
    }
}

void    RPN::check_number(std::string test)
{
    double result;

    try
    {
        result = stod(test);
    }
    catch(const std::exception& e)
    {
        throw (IncorrectNumber());
    }

    if (result > 10)
        throw(ValueOverTen());
}

void    RPN::check_operator(char const &oper)
{
    char authorized_characters[] = {'+', '-', '/', '*'};

    for (int i = 0; i < 4; i++)
    {
        if (authorized_characters[i] == oper)
            return ;
    }
    throw (IncorrectOperand());
}

void    Node::setNumber(double const &val)
{
    this->number = val;
}

void    Node::setSign(char const &val)
{
    this->sign = val;
}

double const &Node::getNumber() const
{
    return this->number;
}

char const &Node::getSign() const
{
    return this->sign;
}

void RPN::calculate_result() 
{
    double  result = 0;
    char    current_operation;


    for (std::list<Node>::iterator it = this->list.begin(); it != this->list.end(); it++)
    {
        current_operation = (*it).getSign();
        switch (current_operation)
        {
        case '+':
            result = std::plus<double>()(result, (*it).getNumber());
            break;
        case '-':
            result = std::minus<double>()(result, (*it).getNumber());
            break;
        case '*':
            result = std::multiplies<double>()(result, (*it).getNumber());
            break;
        case '/':
            if ((*it).getNumber() == 0)
            {
                std::cout << "Forbidden division by 0" << std::endl;
                return ;
            }
            result = std::divides<double>()(result, (*it).getNumber());
            break;
        }
    }
    std::cout << result << std::endl;
}
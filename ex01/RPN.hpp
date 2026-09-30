#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <algorithm>
# include <list>
# include <exception>
# include <sstream>
# include <functional>

class Node
{
    public:
        Node(double value = 0, char operand = '+');
        Node(Node const &other);
        Node &operator=(Node const &other);
        ~Node();
        void    setNumber(double const &val);
        void    setSign(char const &val);
        double const &getNumber() const;
        char const  &getSign() const;
    private:
        double     number;
        char    sign;
};

class RPN
{
    public:
        RPN(char **av);
        RPN(RPN const &other);
        RPN &operator=(RPN const &other);
        ~RPN();
        class NotCorrectArguments : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return "this program only accepts one parameter";
                }
        };
        class ValueOverTen : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return "values can not be over 10";
                }
        };
        class IncorrectOperand : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return "using a non supported opperand";
                }
        };
        class IncorrectNumber : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return "a non number has been used";
                }
        };   
        private:
        RPN(){};
        std::list<Node> list;
        std::string content;
        void    check_one_arg(char **av);
        void    parse_input(std::string av);
        void    check_number(std::string test);
        void    check_operator(char const &oper);
        void    calculate_result();
};

#endif
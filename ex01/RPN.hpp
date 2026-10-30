#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <ostream>
# include <algorithm>
# include <deque>
# include <exception>
# include <sstream>
# include <functional>
# include <cstdio>

enum test
{
    NUMBER,
    SIGN,
    OTHER,
};

class RPN
{
    public:
        RPN(char *av);
        RPN(RPN const &other);
        RPN &operator=(RPN const &other);
        ~RPN();
        class RPNErr : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return reason.c_str();
                }
            RPNErr(std::string const val) : reason(val) {};
            virtual ~RPNErr() throw() {};
            private:
            std::string const reason;
        }; 
    private:
    RPN(){};
    std::deque<double> digits;
    std::string content;
    void    find_solution(std::string val);
    int     find_type(char &val);
    void    calculate(char const &val);
};

#endif
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <iomanip>
# include <map>
# include <exception>
# include <string>
# include <sstream>
# include <fstream>
# include <ctime>
# define BIGGEST_VALUATION 1000
# define DATABASEREFERENCE "data.csv"

class BitcoinExchange 
{
    public:
    BitcoinExchange(char **documents, std::string database = DATABASEREFERENCE); 
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    class  NoFile : public std::exception 
    {
        public:
        virtual const char *what() const throw()
        {
            return "could not open file.";
        }
    };
    class  TooManyFiles : public std::exception 
    {
        public:
        virtual const char *what() const throw()
        {
            return "too many files provided.";
        }
    };
    class  TooLittleNumber : public std::exception 
    {
        public:
        virtual const char *what() const throw()
        {
            return "not a positive number.";
        }
    };   
    class  TooLargeNumber: public std::exception 
    {
        public:
        virtual const char *what() const throw()
        {
            return "too large a number.";
        }
    };
    class  InvalidDateFormat: public std::exception 
    {
        public:
        virtual const char *what() const throw()
        {
           return "bad input.";
        }
    };
    
    private:
    void parse_input(char symbol);
    void check_files(char **av);
    void output_bitcoin_value(std::string const &date, double const &value);
    void check_valid_date(std::string const &date);
    void check_valid_value(double const &value);
    void trim(std::string &line);
    std::map<std::string, double>::iterator check_date_database(std::string date);
    //void find_value_portfolio(std::string const &request);
    std::string _input_file;
    std::string _database;
    std::map<std::string, double> _mapping;
    BitcoinExchange() {};
};

#endif
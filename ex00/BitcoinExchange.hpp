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
# include <algorithm>
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
        private:
        std::string _date;
        public:
        InvalidDateFormat(std::string date) : _date("bad input => " + date) {};
        virtual ~InvalidDateFormat() throw() {};
        virtual const char *what() const throw()
        {
           return (_date.c_str());
        }
    };
    
    private:
    void parse_input(char symbol);
    void check_files(char **av);
    void output_bitcoin_value(double const &date, double const &value);
    void transform_date(std::string date, double &val);
    void check_valid_value(double const &value);
    void trim(std::string &line);
    std::map<double, double>::iterator \
    find_date_database(double date);
    std::string get_date_string(double date);
    //void find_value_portfolio(std::string const &request);
    double transform_to_double(std::string val);
    void open_file_stream(std::ifstream &val, char const *str);
    bool    isvaliddate(int const &year, int const &month, int const &day);
    std::string _input_file;
    std::string _database;
    std::map<double, double> _mapping;
    BitcoinExchange() {};
};

#endif
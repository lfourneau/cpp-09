# include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(char **av, std::string database) : _database(database)
{
    try
    {
        std::cout << std::setprecision(10);
        parse_input(',');
        std::cout << "The database is healthy" << std::endl;
        //revoir pour pas qu'une erreure fasse tout planter
        check_files(av);
        this->_input_file = av[0];
        parse_input('|');
    }
    catch (std::exception &error)
    {
        std::cout << "Error: " << error.what() << std::endl;
        return;
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _input_file(other._input_file), \
_database(other._database)
{ 
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    this->_database = other._database;
    this->_input_file = other._input_file; 
    return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::check_files(char **av)
{
    int i = 0;

    while (*av != NULL)
    {
        i++;
        av++;
    }
    if (i == 0)
    {
        throw (NoFile());
        return ;
    }
    if (i > 1)
    {
        throw(TooManyFiles());
        return ;
    }
}

void BitcoinExchange::parse_input(char symbol)
{
    std::ifstream file;
    if (symbol == ',')
        file = static_cast<std::ifstream>(_database.c_str());
    else 
        file = static_cast<std::ifstream>(_input_file.c_str());

    if (!file.is_open())
        throw (NoFile());

    std::string line;
    std::string date;
    std::string value;
    double value_dob;
    //ignore the first line of the file
    getline(file, line);
    while (getline(file, line))
    {
        std::stringstream current_line(line);
        getline(current_line, date, symbol);
        try
        {
            check_valid_date(date);
            getline(current_line, value, symbol);
            value_dob = stod(value);
            if (symbol == '|')
                check_valid_value(value_dob);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << '\n';
            continue;
        }
        if (symbol == ',')
            this->_mapping.insert({date, value_dob});
        else
        {
            trim(date);
            output_bitcoin_value(date, value_dob);
        }
    }
    file.close();
}

void    BitcoinExchange::output_bitcoin_value(std::string const &date, double const &value)
{
    std::map<std::string, double>::iterator node;

    try
    {
        node = check_date_database(date);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << " => " << date << std::endl;
        return;
    }
    try
    {
        check_valid_value(value);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    std::cout << date << " => " << value << " = " << static_cast<double>(value * node->second) << std::endl; 
}

std::map<std::string, double>::iterator   BitcoinExchange::check_date_database(std::string date)
{
    std::map<std::string, double>::iterator node;
    node = this->_mapping.find(date);
    if (node == this->_mapping.end())
        throw(InvalidDateFormat());
    return (node);
}

void    BitcoinExchange::check_valid_date(std::string const &date)
{
    std::string const date_format = "%Y-%m-%d";
    tm tmStruct;
    std::istringstream ss(date);
    ss >> std::get_time(&tmStruct, date_format.c_str()); 
    
    if (ss.fail())
        throw (InvalidDateFormat());
}

void    BitcoinExchange::check_valid_value(double const &value)
{
    if (value < 0)
    {
        throw (TooLittleNumber());
        return ; 
    }
    if (value > BIGGEST_VALUATION)
    {
        throw (TooLargeNumber());
        return ;
    }
}

void BitcoinExchange::trim(std::string &line)
{
    const char* ws = " \t\r\n";
    std::string::size_type start = line.find_first_not_of(ws);
    if (start == std::string::npos)
    {
        line.clear();          // only whitespace
        return;
    }
    std::string::size_type end = line.find_last_not_of(ws);
    line = line.substr(start, end - start + 1);
}

//void    BitcoinExchange::find_value_portfolio(std::string const &request)
//{
//    std::stringstream   to_analyse(request);
//    std::string         date;
//    std::string         value;
//    std::map<std::string, double> it;
//
//    try
//    {
//        getline(to_analyse, date, ',');
//        check_valid_date(date);
//        getline(to_analyse, value, ',');
//        check_valid_value(stod(value));
//    }
//    catch(const std::exception& e)
//    {
//        std::cerr << e.what() << '\n';
//    }
//
//    if (this->_mapping.find(date) ;
//    
//}
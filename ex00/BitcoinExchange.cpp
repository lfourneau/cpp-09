# include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(char **av, std::string database) : _database(database)
{
    std::cout << std::setprecision(10);
    parse_input(',');
    check_files(av);
    this->_input_file = av[0];
    parse_input('|');
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

void BitcoinExchange::open_file_stream(std::ifstream &val, char const *str)
{
    if (val.is_open())
        val.close();
    val.clear();
    val.open(str);
    if (!val.is_open())
        throw NoFile();
}

void BitcoinExchange::parse_input(char symbol)
{
    std::ifstream file;

    if (symbol == ',')
        open_file_stream(file, _database.c_str());
    else 
        open_file_stream(file, _input_file.c_str());

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

        double date_to_double;
        try
        {
            transform_date(date, date_to_double);
            getline(current_line, value, symbol);
            value_dob = transform_to_double(value);
            if (symbol == '|')
                check_valid_value(value_dob);
            if (symbol == ',')
            {
                this->_mapping[date_to_double] = value_dob;
            }
            else
            {
                trim(date);
                output_bitcoin_value(date_to_double, value_dob);
            }   
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << '\n';
            continue;
        }
    }
    file.close();
}

double BitcoinExchange::transform_to_double(std::string val)
{
    std::istringstream str(val);
    double exit_val;

    str >> exit_val; 
    return (exit_val);
}

std::string BitcoinExchange::get_date_string(double val)
{
    std::stringstream output;

    int year;
    int month;
    int day;

    year = val / (31*12);
    month = (val - year * 31 * 12) / 31;
    day = val - year * 31 * 12 - month * 31;
    output << year << "-" ;
    if (month < 9)
        output << "0";
    output << month << "-" ;
    if (day < 10)
        output << "0";
    output << day;
    return (output.str());
}

void    BitcoinExchange::output_bitcoin_value(double const &date, double const &value)
{
    std::map<double, double>::iterator node;

    node = find_date_database(date);
    check_valid_value(value);
    std::cout << get_date_string(date) << " => " << value << " = " \
    << static_cast<double>(value * node->second) << std::endl; 
}

std::map<double, double>::iterator   BitcoinExchange::find_date_database(double date)
{
    std::map<double, double>::iterator node;
    double save_date = date;

    while (true)
    {
        node = this->_mapping.find(date);
        if (node != this->_mapping.end())
            return (node);
        date--;
        if (date <= 0)
            throw (InvalidDateFormat(get_date_string(save_date)));
    }
}

void    BitcoinExchange::transform_date(std::string date, double &val)
{
    std::string copy_date = date;
    std::replace(date.begin(), date.end(), '-', ' ');
    std::istringstream store(date);
    double year;
    double month;
    double day;
    double test;

    if (!(store >> year >> month >> day && !(store >> test)))
        throw(InvalidDateFormat(copy_date));
    if (isvaliddate(year, month, day))
        throw(InvalidDateFormat(copy_date));
    val = day + month * 31 + year * 31 * 12;

}

bool    BitcoinExchange::isvaliddate(int const &year, int const &month, int const &day)
{
    bool is_leap;

    if (month > 12 || month < 1)
        return (true);
    if (day < 1 || day > 31)
        return (true);
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
        return (true);
    if (month == 2)
    {
        is_leap = (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
        if (day > (is_leap ? 29 : 28))
            return (true);
    }
    return (false);
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
        line.clear();         
        return;
    }
    std::string::size_type end = line.find_last_not_of(ws);
    line = line.substr(start, end - start + 1);
}
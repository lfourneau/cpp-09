#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **av) : odd(false), straggler(0), total_pairs(0)
{
   parse_input(av);
   sort();
   insert_good_order();
   show_pairs();
   sort_deque();
   insert_good_order_deque();
   show_pairs_deque();
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    return *this;
}

PmergeMe::~PmergeMe()
{

}


void    PmergeMe::parse_input(char **av)
{
    unsigned long val1;
    unsigned long val2;
    char        *ignore = NULL;

    try
    {
        while (*av != NULL)
        {
            check_validity_numbers(static_cast<std::string>(*av));
            val1 = std::strtoul(*av, &ignore, 10);
            av++;
            if (*av == NULL)
            {
                this->odd = true;
                this->straggler = val1;
                break;
            }
            check_validity_numbers(static_cast<std::string>(*av));
            val2 = std::strtoul(*av, &ignore, 10);
            add_to_vector(val1, val2);
            add_to_deque(val1, val2);
            this->total_pairs++;
            av++;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void    PmergeMe::add_to_vector(unsigned long &val1, unsigned long &val2)
{
    std::pair<long, long> tab;

    if (val1 >= val2)
    {
        tab.first = val1;
        tab.second = val2;
    }
    else
    {
        tab.first = val2;
        tab.second = val1;
    }
    this->values.push_back(tab);
}

void    PmergeMe::check_validity_numbers(const std::string &val)
{
    std::string::const_iterator it = val.begin();

    while (it != val.end())
    {
        if (! std::isdigit(*it))
        {
            throw(InvalidInputNotNumber(val));
        }
        it++;
    }
}

void    PmergeMe::show_pairs()
{
    std::vector<std::pair<long, long> >::iterator it;
    unsigned int    i = 0;

    for (it = this->values.begin(); it != values.end(); it++)
    {
        std::cout << "Pair: " << i << " | " << (*it).first << " " << (*it).second << std::endl;
        i++;
    }
}

void PmergeMe::merge(unsigned int left, unsigned int middle, unsigned int right)
{
    unsigned int    i, j, k;
    std::vector<std::pair<long, long> > left_vec;
    std::vector<std::pair<long, long> > right_vec;
    unsigned int    total_right = right - middle;
    unsigned int    total_left = middle - left + 1;

    for (i = 0; i < total_left; i++)
        left_vec.push_back(this->values[left + i]);
    for (i = 0; i < total_right; i++)
        right_vec.push_back(this->values[middle + 1 + i]);

    i = j = k = 0;
    while(i < total_left && j < total_right)
    {
        if (left_vec[i].first <= right_vec[j].first)
        {
            this->values[left + k] = left_vec[i];
            i++;
        }
        else 
        {
            this->values[left + k] = right_vec[j];
            j++;
        }
        k++;
    }
    while (i < total_left)
    {
        this->values[left + k] = left_vec[i];
        i++;
        k++;
    }
    while (j < total_right)
    {
        this->values[left + k] = right_vec[j];
        j++;
        k++;
    }
}

void PmergeMe::merge_sort(unsigned int left, unsigned int right)
{
    unsigned int    middle;

    if (left < right)
    {
        middle = left + (right - left) / 2;       
        merge_sort(left, middle);
        merge_sort(middle + 1, right);
        merge(left, middle, right);
    }
}

void PmergeMe::sort()
{
    unsigned int i;

    i = this->values.size();
    if (i < 2)
        return ;
    merge_sort(0, i - 1);
}

std::vector<long> PmergeMe::list_index(unsigned int &current_index, unsigned int &prev, unsigned int &current_jacob_val) const
{
    std::vector<long> output;
    prev = current_jacob_val;
    current_jacob_val = jacobstahl(current_index);
    unsigned int    i;
    
    if (current_jacob_val > total_pairs)
        current_jacob_val = total_pairs;
    i = 0;
    while (current_jacob_val - i != prev)
    {
        output.push_back(current_jacob_val - i);
        i++;
    }
    output.push_back(-1);
    current_index++;
    return (output);
}

unsigned int PmergeMe::jacobstahl(unsigned int current_index) const
{
    return ((pow(2, current_index) - pow(-1, current_index)) / 3);
}

void    PmergeMe::insert_good_order()
{
    unsigned int current_index = 2;
    unsigned int previous = 0;
    unsigned int current_jacob_val = 1;
    std::vector<long> output;
    std::vector<std::pair<long, long> > copy;
    int i;

    if (total_pairs > 0)
    {
        this->values.insert(this->values.begin(), std::make_pair(this->values[0].second, -1L));
        copy = this->values;
        while (current_jacob_val < total_pairs)
        {
            output = list_index(current_index, previous, current_jacob_val);
            i = 0;
            while (output[i] != -1)
            {
                merge_main_chain(copy[output[i]].second, previous + current_jacob_val - 1);
                i++;
            }
        }
    }
    if (odd == true)
        merge_main_chain(straggler, this->values.size());
}

void    PmergeMe::merge_main_chain(long value_to_insert, unsigned int zone)
{
    unsigned int pos = 0;
    unsigned int gap = zone;
    unsigned int half;

    while (gap > 0)
    {
        half = gap / 2;
        if (value_to_insert < this->values[pos + half].first)
            gap = half;
        else
        {
            pos += half + 1;
            gap -= half + 1;
        }
    }
    this->values.insert(this->values.begin() + pos, std::make_pair(value_to_insert, -1L));
}

void    PmergeMe::add_to_deque(unsigned long &val1, unsigned long &val2)
{
    std::pair<long, long> tab;

    if (val1 >= val2)
    {
        tab.first = val1;
        tab.second = val2;
    }
    else
    {
        tab.first = val2;
        tab.second = val1;
    }
    this->values_deque.push_back(tab);
}

void    PmergeMe::show_pairs_deque()
{
    std::deque<std::pair<long, long> >::iterator it;
    unsigned int    i = 0;

    for (it = this->values_deque.begin(); it != values_deque.end(); it++)
    {
        std::cout << "Pair: " << i << " | " << (*it).first << " " << (*it).second << std::endl;
        i++;
    }
}

void PmergeMe::merge_deque(unsigned int left, unsigned int middle, unsigned int right)
{
    unsigned int    i, j, k;
    std::deque<std::pair<long, long> > left_deq;
    std::deque<std::pair<long, long> > right_deq;
    unsigned int    total_right = right - middle;
    unsigned int    total_left = middle - left + 1;

    for (i = 0; i < total_left; i++)
        left_deq.push_back(this->values_deque[left + i]);
    for (i = 0; i < total_right; i++)
        right_deq.push_back(this->values_deque[middle + 1 + i]);

    i = j = k = 0;
    while(i < total_left && j < total_right)
    {
        if (left_deq[i].first <= right_deq[j].first)
        {
            this->values_deque[left + k] = left_deq[i];
            i++;
        }
        else 
        {
            this->values_deque[left + k] = right_deq[j];
            j++;
        }
        k++;
    }
    while (i < total_left)
    {
        this->values_deque[left + k] = left_deq[i];
        i++;
        k++;
    }
    while (j < total_right)
    {
        this->values_deque[left + k] = right_deq[j];
        j++;
        k++;
    }
}

void PmergeMe::merge_sort_deque(unsigned int left, unsigned int right)
{
    unsigned int    middle;

    if (left < right)
    {
        middle = left + (right - left) / 2;       
        merge_sort_deque(left, middle);
        merge_sort_deque(middle + 1, right);
        merge_deque(left, middle, right);
    }
}

void PmergeMe::sort_deque()
{
    unsigned int i;

    i = this->values_deque.size();
    if (i < 2)
        return ;
    merge_sort_deque(0, i - 1);
}

std::deque<long> PmergeMe::list_index_deque(unsigned int &current_index, unsigned int &prev, unsigned int &current_jacob_val) const
{
    std::deque<long> output;
    prev = current_jacob_val;
    current_jacob_val = jacobstahl(current_index);
    unsigned int    i;
    
    if (current_jacob_val > total_pairs)
        current_jacob_val = total_pairs;
    i = 0;
    while (current_jacob_val - i != prev)
    {
        output.push_back(current_jacob_val - i);
        i++;
    }
    output.push_back(-1);
    current_index++;
    return (output);
}

void    PmergeMe::insert_good_order_deque()
{
    unsigned int current_index = 2;
    unsigned int previous = 0;
    unsigned int current_jacob_val = 1;
    std::deque<long> output;
    std::deque<std::pair<long, long> > copy;
    int i;

    if (total_pairs > 0)
    {
        this->values_deque.insert(this->values_deque.begin(), std::make_pair(this->values_deque[0].second, -1L));
        copy = this->values_deque;
        while (current_jacob_val < total_pairs)
        {
            output = list_index_deque(current_index, previous, current_jacob_val);
            i = 0;
            while (output[i] != -1)
            {
                merge_main_chain_deque(copy[output[i]].second, previous + current_jacob_val - 1);
                i++;
            }
        }
    }
    if (odd == true)
        merge_main_chain_deque(straggler, this->values_deque.size());
}

void    PmergeMe::merge_main_chain_deque(long value_to_insert, unsigned int zone)
{
    unsigned int pos = 0;
    unsigned int gap = zone;
    unsigned int half;

    while (gap > 0)
    {
        half = gap / 2;
        if (value_to_insert < this->values_deque[pos + half].first)
            gap = half;
        else
        {
            pos += half + 1;
            gap -= half + 1;
        }
    }
    this->values_deque.insert(this->values_deque.begin() + pos, std::make_pair(value_to_insert, -1L));
}

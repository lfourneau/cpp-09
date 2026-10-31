#include "PmergeMe.hpp"

template <typename T>
PmergeMe<T>::PmergeMe(char **av, std::string const stl) : stl(stl), odd(false), straggler(0), total_pairs(0)
{
    //parsing
    parse_input(av);

    //creation des 2 tests

    add_stl(this->values);
    sort();
    insert_good_order();
    show_sorted(this->values.begin(), this->values.end());
    //show_sorted(this->values_deque.begin(), this->values_deque.end());
}

template <typename T>
PmergeMe<T>::PmergeMe(const PmergeMe &other)
    : stl(other.stl), values(other.values), av_to_nb(other.av_to_nb),
      odd(other.odd), straggler(other.straggler), total_pairs(other.total_pairs)
{
}

template <typename T>
PmergeMe<T> &PmergeMe<T>::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        values = other.values;
        av_to_nb = other.av_to_nb;
        odd = other.odd;
        straggler = other.straggler;
        total_pairs = other.total_pairs;
    }
    return *this;
}

template <typename T>
PmergeMe<T>::~PmergeMe()
{

}

template <typename T>
void    PmergeMe<T>::parse_input(char **av)
{
    long val;
    std::string to_str;

    try
    {
        std::cout << "Before : ";
        while (*av != NULL)
        {
            to_str = *av;
            check_validity_numbers(to_str, val);
            std::cout << val << " ";
            av_to_nb.push_back(val);
            ++av;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    odd = av_to_nb.size() % 2;
    total_pairs = av_to_nb.size() / 2;
    std::cout << std::endl;
}

template <typename T>
void    PmergeMe<T>::add_stl(T &stl)
{
    size_t total = 0;
    long  val1;
    long  val2;

    while (total < av_to_nb.size() - odd)
    {
        val1 = this->av_to_nb[total];
        val2 = this->av_to_nb[total + 1];
        if(val1 < val2)
            swap(val1, val2);
        stl.push_back(std::make_pair(val1, val2));
        total += 2;
    }
    if (odd)
        straggler = av_to_nb.back();
}

template <typename T>
void    PmergeMe<T>::swap(long& one, long& two)
{
    long value;

    value = one;
    one = two;
    two = value;
}

template <typename T>
void    PmergeMe<T>::check_validity_numbers(std::string const &val, long& exp)
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
    std::istringstream export_stream(val.c_str());
    long export_val;

    export_stream >> export_val;
    exp = export_val;
}

template <typename T>
void    PmergeMe<T>::show_sorted(typename T::iterator it, typename T::iterator end)
{
    std::cout << "After : " ;
    for (; it != end; it++)
    {
        std::cout << (*it).first << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void PmergeMe<T>::merge(unsigned int left, unsigned int middle, unsigned int right)
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

template <typename T>
template <typename U>
std::pair<long, long> &PmergeMe<T>::get_list_iterator(U &list, unsigned int node)
{
    typename U::iterator it = list.begin();
    unsigned int i = 0;

    while (i < node)
    {
        if (it == list.end())
            throw(InvalidInputNotNumber("iterator out of range"));
        it++;
        i++;
    }
    return (*it);
}

template <typename T>
void PmergeMe<T>::merge_list(unsigned int left, unsigned int middle, unsigned int right)
{
    unsigned int    i, j, k;
    std::list<std::pair<long, long> > left_list;
    std::list<std::pair<long, long> > right_list;
    unsigned int    total_right = right - middle;
    unsigned int    total_left = middle - left + 1;

    for (i = 0; i < total_left; i++)
        left_list.push_back(get_list_iterator(this->values, left + i));
    for (i = 0; i < total_right; i++)
        right_list.push_back(get_list_iterator(this->values, middle + 1 + i));

    i = j = k = 0;
    while(i < total_left && j < total_right)
    {
        if (get_list_iterator(left_list, i).first <= get_list_iterator(right_list, j).first)
        {
            get_list_iterator(this->values, left + k) = get_list_iterator(left_list, i);
            i++;
        }
        else 
        {
            get_list_iterator(this->values, left + k) = get_list_iterator(right_list, j);
            j++;
        }
        k++;
    }
    while (i < total_left)
    {
        get_list_iterator(this->values, left + k) = get_list_iterator(left_list, i);
        i++;
        k++;
    }
    while (j < total_right)
    {
        get_list_iterator(this->values, left + k)  = get_list_iterator(right_list, j);
        j++;
        k++;
    }
}

template <typename T>
void PmergeMe<T>::merge_sort(unsigned int left, unsigned int right, void (PmergeMe<T>::*func)(unsigned int, unsigned int, unsigned int))
{
    unsigned int    middle;

    if (left < right)
    {
        middle = left + (right - left) / 2;       
        merge_sort(left, middle, func);
        merge_sort(middle + 1, right, func);
        (this->*func)(left, middle, right);
    }
}

template <typename T>
void PmergeMe<T>::sort()
{
    unsigned int i;

    i = this->values.size();
    if (i < 2)
        return ;
    if (stl == "std::vector")
        merge_sort(0, i - 1, &PmergeMe<T>::merge);
    else if (stl == "std::list")
        merge_sort(0, i - 1, &PmergeMe<T>::merge_list);
}

template <typename T>
std::vector<long> PmergeMe<T>::list_index(unsigned int &current_index, unsigned int &prev, unsigned int &current_jacob_val)
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

template <typename T>
unsigned int PmergeMe<T>::jacobstahl(unsigned int current_index) const
{
    return ((pow(2, current_index) - pow(-1, current_index)) / 3);
}

template <typename T>
void    PmergeMe<T>::insert_good_order()
{
    unsigned int current_index = 2;
    unsigned int previous = 0;
    unsigned int current_jacob_val = 1;
    std::vector<long> output;
    std::vector<std::pair<long, long> > copy;
    int i;

    if (total_pairs > 0)
    {
        this->values.insert(this->values.begin(), std::make_pair(this->values[0].second, -1));
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

template <typename T>
void    PmergeMe<T>::merge_main_chain(long value_to_insert, unsigned int zone)
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

template PmergeMe<std::vector<std::pair<long, long> > >::PmergeMe(char **, std::string const);
template PmergeMe<std::vector<std::pair<long, long> > >::~PmergeMe();
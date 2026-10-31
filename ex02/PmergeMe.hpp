#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <sstream>
# include <vector>
# include <list>
# include <exception>
# include <cstdlib>
# include <utility>
# include <string>
# include <cmath>

template <typename T>
class PmergeMe {
    public:
        PmergeMe(char **value, std::string const stl);
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();
        class InvalidInputNotNumber : public std::exception
        {
            public:
                InvalidInputNotNumber(std::string issue)
                {
                    problem = "The input is incorret: " + issue;
                }
                virtual ~InvalidInputNotNumber() throw() {};
                virtual const char *what() const throw()
                {
                    return (problem.c_str());
                }
            private:
                std::string problem;
        };
    private:
        std::string const stl;
        T values;
        std::vector<long> av_to_nb;
        bool odd;
        long straggler;
        unsigned int total_pairs;
        void parse_input(char **av);
        void check_validity_numbers(const std::string &val, long& exp);
        void swap(long& one, long& two);
        void add_stl(T &stl);
        void show_sorted(typename T::iterator it, typename T::iterator end);
        void merge_sort(unsigned int left, unsigned int right, void (PmergeMe<T>::*func)(unsigned int, unsigned int, unsigned int));
        void merge(unsigned int left, unsigned int middle, unsigned int right);
        void sort();
        void insert_good_order();
        std::vector<long> list_index(unsigned int &current_index, unsigned int &previous, unsigned int &jacob);
        unsigned int jacobstahl(unsigned int current_index) const;
        void    merge_main_chain(long value_to_insert, unsigned int zone);
        template <typename U>
        std::pair<long, long> &get_list_iterator(U &list, unsigned int node);
        void    merge_list(unsigned int left, unsigned int middle, unsigned int right);
};

#endif
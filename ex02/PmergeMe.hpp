#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <vector>
# include <deque>
# include <exception>
# include <cstdlib>
# include <utility>
# include <string>
# include <cmath>

class PmergeMe {
    public:
        PmergeMe(char **value);
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
        std::vector<std::pair<long, long> > values;
        std::deque<std::pair<long, long> > values_deque;
        bool odd;
        long straggler;
        unsigned int total_pairs;
        void parse_input(char **av);
        void check_validity_numbers(const std::string &val);
        void add_to_vector(unsigned long &val1, unsigned long &val2);
        void show_pairs();
        void merge_sort(unsigned int left, unsigned int right);
        void merge(unsigned int left, unsigned int middle, unsigned int right);
        void sort();
        void insert_good_order();
        std::vector<long> list_index(unsigned int &current_index, unsigned int &previous, unsigned int &jacob) const;
        unsigned int jacobstahl(unsigned int current_index) const;
        void    merge_main_chain(long value_to_insert, unsigned int zone);
        void add_to_deque(unsigned long &val1, unsigned long &val2);
        void show_pairs_deque();
        void merge_sort_deque(unsigned int left, unsigned int right);
        void merge_deque(unsigned int left, unsigned int middle, unsigned int right);
        void sort_deque();
        void insert_good_order_deque();
        std::deque<long> list_index_deque(unsigned int &current_index, unsigned int &previous, unsigned int &jacob) const;
        void    merge_main_chain_deque(long value_to_insert, unsigned int zone);
};

#endif
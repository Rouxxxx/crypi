#ifndef BFV_TESTS_HH
#define BFV_TESTS_HH

#include <chrono>

#include "../BFV/bfv.hh"

class Tester
{
public:
    Tester(std::ostream& stream, Infos infos);

private:
    int nb_tests;
    int nb_tests_passed;

    void execute_test(bool (Tester::*function_ptr)(), std::string section, std::string test_name);
    void print_good(std::string section, std::string test_name, long double& duration);
    void print_bad(std::string section, std::string test_name, long double& duration);
    void print_green(std::string str);
    void print_red(std::string str);
    void print_bold_red(std::string str);
    void print_bold_green(std::string str);
    std::ostream& stream;
    Infos infos;


    bool basic_test();
    bool simple_test();
    bool real_life_test();
};

#endif
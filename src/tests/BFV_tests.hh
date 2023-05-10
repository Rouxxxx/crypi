#ifndef BFV_TESTS_HH
#define BFV_TESTS_HH

#include "../BFV/bfv.hh"
class Tester
{
public:
    Tester(std::ostream& stream, Infos infos);

private:
    int nb_tests;
    int nb_tests_passed;

    void execute_test(bool (Tester::*function_ptr)(), std::string section, std::string testName);
    void print_good(std::string str);
    void print_bad(std::string str);
    void print_bold_bad(std::string str);
    void print_bold_good(std::string str);
    std::ostream& stream;
    Infos infos;


    bool basic_test();
    bool simple_test();
    bool real_life_test();
};

#endif
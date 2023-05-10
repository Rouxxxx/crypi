#ifndef BFV_TESTS_HH
#define BFV_TESTS_HH

#include <chrono>

#include "../BFV/bfv.hh"


/**
Class to store our tests and execute them.
*/
class Tester
{
public:
    /**
    Constructs the tester using an output stream and an info struct.
    */
    Tester(std::ostream& stream, Infos infos);

private:
    int nb_tests = 0;
    int nb_tests_passed = 0;

    /**
    Executes a test.
    @param[in] function_ptr Tester member function to use
    @param[in] section      Section's name (example : BASIC)
    @param[in] test_name    Example : Test
    */
    void execute_test(bool (Tester::*function_ptr)(), std::string section, std::string test_name);


    /**
    Pretty prints as the test is starting.
    @param[in] section      Section's name (example : BASIC)
    @param[in] test_name    Example : Test
    */
    void print_start(std::string section, std::string test_name);
    /**
    Pretty prints if the test passed (so green).
    @param[in] section      Section's name (example : BASIC)
    @param[in] test_name    Example : Test
    @param[in] duration     Time taken by the test
    */
    void print_good(std::string section, std::string test_name, long double& duration);
    /**
    Pretty prints if the test failed (so red).
    @param[in] section      Section's name (example : BASIC)
    @param[in] test_name    Example : Test
    @param[in] duration     Time taken by the test
    */
    void print_bad(std::string section, std::string test_name, long double& duration);


    /**
    Pretty prints a line in green.
    @param[in] str The string to be printed
    */
    void print_green(std::string str);
    /**
    Pretty prints a line in red.
    @param[in] str The string to be printed
    */
    void print_red(std::string str);
    /**
    Pretty prints a line in yellow.
    @param[in] str The string to be printed
    */
    void print_yellow(std::string str);
    /**
    Pretty prints a line in bold green.
    @param[in] str The string to be printed
    */
    void print_bold_red(std::string str);
    /**
    Pretty prints a line in bold red.
    @param[in] str The string to be printed
    */
    void print_bold_green(std::string str);
    /**
    Pretty prints a line in bold yellow.
    @param[in] str The string to be printed
    */
    void print_bold_yellow(std::string str);


    std::ostream& stream;
    Infos infos;

    /**
    Test to see if our tester works.
    */
    bool basic_test();
    /**
    Test to see if homomorphic operations (+ and *) work.
    */
    bool simple_test();
    /**
    Test to see if a real vote works (with x candidates and y votes).
    */
    bool real_life_test();
};

#endif
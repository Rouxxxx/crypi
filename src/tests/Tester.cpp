#include "BFV_tests.hh"

Tester::Tester(std::ostream& stream, Infos infos)
    : stream(stream), infos(infos)
{
    execute_test(&Tester::basic_test, "BASIC", "Basic test");
    execute_test(&Tester::simple_test, "BFV", "simple example");
    execute_test(&Tester::real_life_test, "BFV", "real life example");
}



void Tester::execute_test(bool (Tester::*function_ptr)(), std::string section, std::string testName)
{
    nb_tests++;
    bool result = (this->*function_ptr)();
    if (result) {
        nb_tests_passed++;
        print_bold_good("[" + section + "] ");
        print_good(testName + " -> ");
        print_bold_good("OK");
    }
    else {
        print_bold_bad("[" + section + "] ");
        print_bad(testName + " -> ");
        print_bold_bad("BAD");
    }
    stream << std::endl;
}

void Tester::print_good(std::string str)
{
    stream << "\033[32m";
    stream << str;
    stream << "\033[0m";;
}
void Tester::print_bold_good(std::string str)
{
    stream << "\033[1;32m";
    stream << str;
    stream << "\033[0m";;
}
void Tester::print_bad(std::string str)
{
    stream << "\033[31m"; 
    stream << str;
    stream << "\033[0m";;
}
void Tester::print_bold_bad(std::string str)
{
    stream << "\033[1;31m"; 
    stream << str;
    stream << "\033[0m";;
}



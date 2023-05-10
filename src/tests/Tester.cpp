#include "Tester.hh"
#include <string>

Tester::Tester(std::ostream& stream, Infos infos)
    : stream(stream), infos(infos)
{
    execute_test(&Tester::basic_test, "BASIC", "Basic test");
    execute_test(&Tester::simple_test, "BFV", "simple example");
    execute_test(&Tester::real_life_test, "BFV", "real life example");

    int accuracy = (nb_tests / nb_tests_passed) * 100;
    stream << std::endl;

    std::string str = "[" + std::to_string(nb_tests_passed) + "/" + std::to_string(nb_tests) + "] (" + std::to_string(accuracy) + "%)\n";

    if (accuracy == 100) {
        print_green("Number of tests passed: ");
        print_bold_green(str);
    }
    else if (accuracy == 0) {
        print_red("Number of tests passed: ");
        print_bold_red(str);
    }
    else {
        print_yellow("Number of tests passed: ");
        print_bold_yellow(str);
    }
}



void Tester::execute_test(bool (Tester::*function_ptr)(), std::string section, std::string test_name)
{
    stream << std::endl;
    print_start(section, test_name);
    stream << std::endl;
    // Start a clock before executing the test
    auto start = std::chrono::high_resolution_clock::now();

    bool result = (this->*function_ptr)();

    // End the clock and calculate the duration in seconds.milliseconds
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    long double duration_m = static_cast<long double>(duration_s) / 1000;

    nb_tests++;
    if (result) {
        nb_tests_passed++;
        print_good(section, test_name, duration_m);
    }
    else
        print_bad(section, test_name, duration_m);
    stream << std::endl;
}

void Tester::print_start(std::string section, std::string test_name)
{
    print_yellow("[" + section + "]");
    stream << " ";
    print_bold_yellow(test_name + "...");
}


void Tester::print_good(std::string section, std::string test_name, long double& duration)
{
    print_bold_green("[" + section + "] ");
    print_green(test_name + " -> ");
    print_bold_green("OK");

    std::string dur_str = cut_double(duration);

    print_green(" (" + dur_str + "s)");
}

void Tester::print_bad(std::string section, std::string test_name, long double& duration)
{
    print_bold_red("[" + section + "] ");
    print_red(test_name + " -> ");
    print_bold_red("ERROR");

    std::string dur_str = cut_double(duration);

    print_red(" (" + dur_str + "s)");
}

void Tester::print_green(std::string str)
{
    stream << "\033[32m";
    stream << str;
    stream << "\033[0m";
}
void Tester::print_bold_green(std::string str)
{
    stream << "\033[1;32m";
    stream << str;
    stream << "\033[0m";
}
void Tester::print_red(std::string str)
{
    stream << "\033[31m"; 
    stream << str;
    stream << "\033[0m";
}
void Tester::print_bold_red(std::string str)
{
    stream << "\033[1;31m"; 
    stream << str;
    stream << "\033[0m";
}


void Tester::print_yellow(std::string str)
{
    stream << "\033[33m";
    stream << str;
    stream << "\033[0m";
}

void Tester::print_bold_yellow(std::string str)
{
    stream << "\033[1;33m";
    stream << str;
    stream << "\033[0m";
}

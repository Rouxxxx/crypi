#include "BFV_tests.hh"

Tester::Tester(std::ostream& stream, Infos infos)
    : stream(stream), infos(infos)
{
    execute_test(&Tester::basic_test, "BASIC", "Basic test");
    execute_test(&Tester::simple_test, "BFV", "simple example");
    execute_test(&Tester::real_life_test, "BFV", "real life example");
}



void Tester::execute_test(bool (Tester::*function_ptr)(), std::string section, std::string test_name)
{
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

std::string cut_double(long double &val)
{
    std::string dur_str = std::to_string(val);
    size_t index = dur_str.find(".");

    if (index != std::string::npos && dur_str.length() > index + 4)
        dur_str = dur_str.substr(0, index + 4);

    return dur_str;
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
    stream << "\033[0m";;
}
void Tester::print_bold_green(std::string str)
{
    stream << "\033[1;32m";
    stream << str;
    stream << "\033[0m";;
}
void Tester::print_red(std::string str)
{
    stream << "\033[31m"; 
    stream << str;
    stream << "\033[0m";;
}
void Tester::print_bold_red(std::string str)
{
    stream << "\033[1;31m"; 
    stream << str;
    stream << "\033[0m";;
}



#include "tools.hh"

// Check if user is 18 or older user social security number.
bool check_social_number(const Wt::WString num_secu)
{
    // Regex for valid social security number
    std::regex regex_secu(
        "^(1|2)\\d{2}(0[1-9]|1[0-2])(0[1-9]|[1-2]\\d|3[0-1])(\\d{3})(\\d{2})$");
    std::smatch match;
    const std::string str = num_secu.toUTF8();

    if (!std::regex_match(str, match, regex_secu))
        return false;

    int birth_year = std::stoi(match[1].str());
    int present_year =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    int minimum_age = present_year - 18;

    return birth_year <= minimum_age;
}

bool check_credentials(const Wt::WString username, const Wt::WString password)
{
    return username == "root" && password == "root";
}

std::vector<std::string> get_candidates(std::string path)
{
    std::fstream file;
    std::vector<std::string> v;
    std::string s;

    file.open(path);
    if (file.is_open())
    {
        while (getline(file, s))
            v.push_back(s);
        file.close();
    }
    return v;
}

void vote(std::string name, std::vector<std::string> candidates)
{
    auto it = find(candidates.begin(), candidates.end(), name);
    if (it != candidates.end())
        std::cout << "vote for " << name << " !" << std::endl;
    else
        std::cout << "Impossible" << std::endl;

    // Call homomorphic function
    // See main function
    // TODO
}

bool has_voted()
{
    // Add data in file to check if user has voted in data/
    // TODO
    return false;
}

bool add_user(const Wt::WString social_security_password, const Wt::WString password)
{
    // TODO
    std::cout << password << social_security_password << std::endl;
    return false;
}

#include "tools.hh"

bool check_credentials(const Wt::WString username, const Wt::WString password)
{
    // Check file from data/credentials.csv
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

void vote(std::string name)
{
    std::cout << "vote for " << name << " !" << std::endl;
}

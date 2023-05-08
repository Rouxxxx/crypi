#include "tools.hh"

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

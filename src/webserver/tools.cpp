#include "tools.hh"

std::string calculate_hash(const std::string username, const std::string password)
{
    // Create single string
    std::string combined_str = username + password;

    // Calculate hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(combined_str.c_str()), combined_str.size(), hash);

    std::stringstream ss;
    // Hex format : FF FF FF FF
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    std::string hex_hash = ss.str();

    return hex_hash;
}

// Check if user is 18 or older user social security number.
bool check_social_number(const Wt::WString num_secu)
{
    // Regex for valid social security number
    std::regex regex_secu(
        "^(1|2)\\d{2}(0[1-9]|1[0-2])\\d{5}\\d{3}\\d{2}$");
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
    // Calculate hash
    std::string hash = calculate_hash(username.toUTF8(), password.toUTF8());

    // Open user file
    std::fstream file;
    std::string line;

    // Check if hash is present in file
    file.open(USER_PATH);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::vector<std::string> output;
            std::stringstream ss(line);
            std::string val;
            const char separator = ';';
            std::getline(ss, val, separator);
            if (hash == val)
            {
                file.close();
                return true;
            }
        }
        file.close();
    }
    return false;

}

std::vector<std::string> get_candidates(std::string path)
{
    std::fstream file;
    std::vector<std::string> v;
    std::string s;

    file.open(path);
    if (file.is_open())
    {
        while (std::getline(file, s))
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

bool has_voted(const Wt::WString social_security_password, const Wt::WString password)
{
    // Calculate hash
    std::string hash = calculate_hash(social_security_password.toUTF8(), password.toUTF8());

    // Open user file
    std::fstream file;
    std::string line;

    // Check if hash is present in file
    file.open(USER_PATH);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::vector<std::string> output;
            std::stringstream ss(line);
            std::string val;
            const char separator = ';';
            std::getline(ss, val, separator);
            if (hash == val)
            {
                std::getline(ss, val, separator);
                if (val == "1")
                {
                    file.close();
                    return true;
                }
                else
                {
                    file.close();
                    return false;
                }
            }
        }
        file.close();
    }
    return false;
}



bool add_user(const Wt::WString social_security_password, const Wt::WString password)
{
    // Calculate hash
    std::string hash = calculate_hash(social_security_password.toUTF8(), password.toUTF8());

    // Open user file
    std::fstream file;
    std::string line;

    // Check if hash is present in file
    file.open(USER_PATH);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::vector<std::string> output;
            std::stringstream ss(line);
            std::string val;
            const char separator = ';';
            std::getline(ss, val, separator);
            if (hash == val)
            {
                file.close();
                return false;
            }
        }
        file.close();
    }

    // Add user in database
    std::ofstream out(USER_PATH, std::ios::app);
    out << hash << ";0" << std::endl;
    return true;
}

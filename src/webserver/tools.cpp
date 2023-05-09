#include "tools.hh"

std::string calculate_hash(const std::string username,
                           const std::string password)
{
    // Create single string
    std::string combined_str = username + password;

    // Calculate hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(combined_str.c_str()),
           combined_str.size(), hash);

    std::stringstream ss;
    // Hex format : FF FF FF FF
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(hash[i]);
    }
    std::string hex_hash = ss.str();

    return hex_hash;
}

// Check if user is 18 or older user social security number.
bool check_social_number(const Wt::WString num_secu)
{
    // Regex for valid social security number
    std::regex regex_secu("^(1|2)\\d{2}(0[1-9]|1[0-2])\\d{5}\\d{3}\\d{2}$");
    std::smatch match;
    const std::string str = num_secu.toUTF8();

    if (!std::regex_match(str, match, regex_secu))
        return false;

    // Extract birth year and month.
    int birth_date = std::stoi(str.substr(1, 4));
    int year = birth_date % 100;
    int month = birth_date / 100;

    // Get current date
    auto now = std::chrono::system_clock::now();
    time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Convert current date to struct tm
    struct tm parts
    {};
    localtime_r(&now_c, &parts);
    int currentYear = parts.tm_year + 1900; // years since 1900
    int currentMonth = parts.tm_mon + 1; // months since January

    // Calculate age
    int age = currentYear - year;
    if (currentMonth < month)
        age--;
    std::cout << age << std::endl;

    return age >= 18;
}

bool check_credentials(const Wt::WString username, const Wt::WString password)
{
    // return true;
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

void vote(std::string name, std::vector<std::string> candidates,
          Container* container, std::string hash)
{
    auto it = find(candidates.begin(), candidates.end(), name);
    if (it != candidates.end())
        std::cout << "vote for " << name << " !" << std::endl;
    else
        std::cout << "Impossible" << std::endl;

    // Ensure user vote only once
    std::ofstream out(VOTED_PATH, std::ios::app);
    out << hash << std::endl;

    // Call homomorphic function
    if (!container)
    {
        std::cout << "No container, can't save Ciphertext." << std::endl;
        return;
    }

    // Encode the nb which will be added to the counter
    Ciphertext votes_count;
    Ciphertext tmp_nb_votes = encrypt_number(container, 1);

    if (container->test_if_vote_count_exists())
    {
        votes_count = container->load_vote_count();
        votes_count = container->sum(votes_count, tmp_nb_votes);
    }
    else
        votes_count = tmp_nb_votes;

    // Encode the vote and add it to the current vector
    int vote_id = it - candidates.begin();
    std::vector<uint64_t> votes_vector(candidates.size());
    votes_vector[vote_id] = 1;

    // Encrypt then encode the vector (vector -> plaintext -> encrypted
    // plaintext)
    Ciphertext votes;
    Plaintext votes_vector_txt = container->encode_vector(votes_vector);
    Ciphertext votes_vector_cipher = container->encrypt(votes_vector_txt);

    if (container->test_if_votes_exists())
    {
        votes = container->load_votes();
        votes = container->sum(votes, votes_vector_cipher);
    }
    else
        votes = votes_vector_cipher;

    container->save_vote_count(votes_count);
    container->save_votes(votes);
}

bool has_voted(const Wt::WString social_security_password,
               const Wt::WString password)
{
    // Calculate hash
    std::string hash =
        calculate_hash(social_security_password.toUTF8(), password.toUTF8());

    // Open user file
    std::fstream file;
    std::string line;

    // Check if hash is present in file
    file.open(VOTED_PATH);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (hash == line)
                return true;
        }
        file.close();
    }
    return false;
}

bool check_login(std::string user)
{
    // Create single string
    std::string combined_str = user;

    // Calculate hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(combined_str.c_str()),
           combined_str.size(), hash);

    std::stringstream ss;
    // Hex format : FF FF FF FF
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(hash[i]);
    }
    std::string hex_hash = ss.str();

    // Open account file
    std::fstream file;
    std::string line;

    // Check if hash is present in file
    file.open(ACCOUNT_PATH);
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (hex_hash == line)
            {
                file.close();
                return false;
            }
        }
        file.close();
    }

    std::ofstream out(ACCOUNT_PATH, std::ios::app);
    out << hex_hash << std::endl;
    return true;
}

bool add_user(const Wt::WString social_security_password,
              const Wt::WString password)
{
    // Check if login has been used.
    if (!check_login(social_security_password.toUTF8()))
        return false;

    // Calculate hash
    std::string hash =
        calculate_hash(social_security_password.toUTF8(), password.toUTF8());

    // Add user in database
    std::ofstream out(USER_PATH, std::ios::app);
    out << hash << std::endl;
    return true;
}

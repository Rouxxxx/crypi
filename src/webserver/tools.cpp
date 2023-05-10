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

    // Extract birth year
    int birth_year = std::stoi(str.substr(1, 2));
    int birth_month = std::stoi(str.substr(3, 2));
    if (birth_year >= 0 && birth_year <= 99)
        birth_year += (birth_year < 30) ? 2000 : 1900;

    // Current year
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    std::tm* current_time_tm = std::localtime(&current_time);
    int current_year = current_time_tm->tm_year + 1900;
    int current_month = current_time_tm->tm_mon + 1;

    // Calculate age
    int age = current_year - birth_year;
    if (birth_month > current_month)
        age -= 1;
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

void vote(int vote_id, int nb_candidates,
          Container* container, std::string hash)
{
    // Ensure user votes only once
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
    std::vector<uint64_t> votes_vector(nb_candidates);
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

bool has_voted(const Wt::WString username,
               const Wt::WString password)
{
    // return false;
    // Calculate hash
    std::string hash =
        calculate_hash(username.toUTF8(), password.toUTF8());

    // Open user file
    std::fstream file;
    std::string line;

    file.open(VOTED_PATH);

    // If the file doesn't exist, no user has voted created yet
    if (!file.is_open())
        return false;

    // Check if hash is present in file
    while (std::getline(file, line))
        if (hash == line)
            return true;

    file.close();
    return false;
}

bool check_login(std::string username)
{
    // Create single string
    std::string combined_str = username;



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



    // If the file doesn't exist, no user has been created yet
    file.open(ACCOUNT_PATH);
    if (!file.is_open())
        return false;

    // Check if hash is present in file
    while (std::getline(file, line)) {
        if (hex_hash == line) {
            file.close();
            return false;
        }
    }
    file.close();
    //std::ofstream out(ACCOUNT_PATH, std::ios::app);
    //out << hex_hash << std::endl;
    return true;
}

bool add_user(const Wt::WString username,
              const Wt::WString password)
{
    // Check if login has been used.
    if (!check_login(username.toUTF8()))
        return false;

    // Calculate hash
    std::string hash =
        calculate_hash(username.toUTF8(), password.toUTF8());

    // Add user in database
    std::ofstream out(USER_PATH, std::ios::app);
    out << hash << std::endl;
    return true;
}

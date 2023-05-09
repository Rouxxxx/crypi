#ifndef TOOLS_HH
#define TOOLS_HH

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <openssl/sha.h>
#include <regex>
#include <sstream>
#include <vector>

#include "../BFV/bfv.hh"
#include "Wt/WString.h"

#define USER_PATH "./data/users.txt"
#define CANDIDATE_PATH "./data/candidates.txt"
#define CSS_PATH "./data/style.css"
#define ACCOUNT_PATH "./data/accounts.txt"
#define VOTED_PATH "./data/voted.txt"

bool check_social_number(const Wt::WString num_secu);
bool check_credentials(const Wt::WString username, const Wt::WString password);
std::vector<std::string> get_candidates(std::string path);
void vote(std::string name, std::vector<std::string> candidates,
          Container* container, std::string hash);
bool has_voted(const Wt::WString social_security_password,
               const Wt::WString password);
bool add_user(const Wt::WString social_security_password,
              const Wt::WString password);
std::string calculate_hash(const std::string username,
                           const std::string password);
bool check_login(std::string user);

#endif /* ! TOOLS_HH */

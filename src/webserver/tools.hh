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

#include "Wt/WString.h"

#include "../utils/utils.hh"

#include "../BFV/bfv.hh"
#include "evote.hh"


#define USER_PATH "./data/users.txt"
#define CANDIDATE_PATH "./data/candidates.txt"
#define CSS_PATH "./data/style.css"
#define ACCOUNT_PATH "./data/accounts.txt"
#define VOTED_PATH "./data/voted.txt"

/**
Check if a social number is valid.
@param[in] num_secu The number to be tested
@return True if the number is valid, False otherwise
*/
bool check_social_number(const Wt::WString num_secu);

/**
Check if the users credentials match our database.
@param[in] username The user's social security number
@param[in] password The user's password
@return True if the credentials match, False otherwise
*/
bool check_credentials(const Wt::WString username, const Wt::WString password);

/**
Builds the list of candidates used by the app, picking a random name and image for each.
@param[in] path The candidates names' file
@param[in] nb_candidates The number of candidates we want in our vote
@return The list of generated candidates
*/
std::vector<Candidate> get_candidates(std::string path, int nb_candidates);

/**
Uses the container to add the vote to the ciphertexts.
@param[in] id The ID of the candidate the user voted for
@param[in] nb_candidates The current number of candidates (to encrypt a vector with an appropriate size)
@param[in] container The app's BFV container
@param[in] hash The current user's hash (to register their vote in the logs so they don't do it multiple times)
*/
void vote(int id, int nb_candidates,
          Container* container, std::string hash);
/**
Check if the user has already voted or not.
@param[in] username The user's social security number
@param[in] password The user's password
@return True if they already voted, False otherwise
*/
bool has_voted(const Wt::WString username,
               const Wt::WString password);

/**
Add an user to the database.
@param[in] username The user's social security number
@param[in] password The user's password
@return True if the user is already in use, False otherwise (if it's added to the db)
*/
bool add_user(const Wt::WString username,
              const Wt::WString password);

/**
Calculates a hash with the user's username + password.
@param[in] username The user's social security number
@param[in] password The user's password
@return The computed hash
*/
std::string calculate_hash(const std::string username,
                           const std::string password);

/**
Check if a login is already in use.
@param[in] username The user's social security number
@return True if the user is already in use, False otherwise
*/
bool check_login(std::string username);

#endif /* ! TOOLS_HH */

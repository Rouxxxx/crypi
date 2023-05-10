#ifndef BASICS_HH
#define BASICS_HH

#include <cstdint>
#include <fstream>
#include <stddef.h>
#include <string>
#include <vector>
#include <sstream>

#include "jsonLib.hh"

/**
    Converts a hex string to an int
    @param[in] hexString The hex string to be converted
*/
inline int hex_to_int(std::string hexString)
{
    int intValue;
    std::stringstream ss;
    ss << std::hex << hexString;
    ss >> intValue;

    return intValue;
}

/**
    Finds the id in a vector, corresponding to its max value
    @param[in] table The vector where to find the max 
*/
inline int find_max(std::vector<uint64_t> table)
{
    if (table.size() == 0)
        return -1;

    uint64_t max = table[0];
    int id_max = 0;

    for (size_t id = 1; id < table.size(); id++)
    {
        if (table[id] > max)
        {
            max = table[id];
            id_max = id;
        }
    }
    return id_max;
}


/**
Cut a double to 3 digits.
@param[in] val The double value
@return The cut string
*/
inline std::string cut_double(long double &val)
{
    std::string dur_str = std::to_string(val);
    size_t index = dur_str.find(".");

    if (index != std::string::npos && dur_str.length() > index + 4)
        dur_str = dur_str.substr(0, index + 4);

    return dur_str;
}


class Infos
{
public:
    /**
    Class to store our programs basic infos (paths, modulus_degress).
    @see JsonLib to know how the JSON file is read
    */
    size_t poly_modulus_degree;
    int nb_candidates;
    std::string data_folder;
    std::string secret_key_file;
    std::string vote_count_file;
    std::string votes_file;
    bool skip_social_verif;

    /**
    Sets the variables.
    @param[in] path The path of the JSON file
    */
    void build_static_info(std::string path)
    {
        JsonLib json(path);

        json.readInt("nb_candidates", nb_candidates);
        json.readUint64("poly_modulus_degree", poly_modulus_degree);

        json.readString("data_folder", data_folder);
        json.readString("secret_key_file", secret_key_file);

        json.readString("vote_count_file", vote_count_file);
        json.readString("votes_file", votes_file);

        skip_social_verif = false;
    }
};

#endif
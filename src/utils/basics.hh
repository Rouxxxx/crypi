#ifndef BASICS_HH
#define BASICS_HH

#include <cstdint>
#include <fstream>
#include <stddef.h>
#include <string>
#include <vector>
#include <sstream>

#include "jsonLib.hh"

inline int hex_to_int(std::string hexString)
{
    int intValue;
    std::stringstream ss;
    ss << std::hex << hexString;
    ss >> intValue;

    return intValue;
}

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

#include <iostream>

class Infos
{
public:
    size_t poly_modulus_degree;
    int nb_candidates;
    std::string data_folder;
    std::string secret_key_file;
    std::string vote_count_file;
    std::string votes_file;
    void build_static_info(std::string path)
    {
        JsonLib json(path);

        json.readInt("nb_candidates", nb_candidates);
        json.readUint64("poly_modulus_degree", poly_modulus_degree);

        json.readString("data_folder", data_folder);
        json.readString("secret_key_file", secret_key_file);

        json.readString("vote_count_file", vote_count_file);
        json.readString("votes_file", votes_file);
    }
};

#endif
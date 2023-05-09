#include <random>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "utils.hh"

#define MAX_CANDIDATES 30

std::vector<std::string> shuffle_names(std::vector<std::string> names)
{
    int size = names.size();
    std::vector<std::string> firstVec(names.begin(), names.begin() + size / 2);
    std::vector<std::string> secondVec(names.begin() + names.size() / 2, names.end());

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(firstVec.begin(), firstVec.end(), g);
    std::shuffle(secondVec.begin(), secondVec.end(), g);

    firstVec.insert(firstVec.end(), secondVec.begin(), secondVec.end());

    return firstVec;
}

std::vector<Candidate> get_candidates(std::string path, int nb_candidates)
{
    srand(time(nullptr));

    std::fstream file;
    std::vector<std::string> names;
    std::string s;

    file.open(path);
    if (file.is_open())
    {
        while (std::getline(file, s))
            names.push_back(s);
        file.close();
    }

    names = shuffle_names(names);

    nb_candidates = (nb_candidates > MAX_CANDIDATES) ? MAX_CANDIDATES : nb_candidates;
    int middle = nb_candidates / 2;
    int middle_max = MAX_CANDIDATES / 2;


    std::vector<int> ids_men;
    std::vector<int> ids_women;

    std::vector<Candidate> men;
    std::vector<Candidate> women;

    for (int id = 1; id <= middle_max; id++) {
        ids_men.push_back(id);
        ids_women.push_back(id + middle_max);
    }

    // take random values 
    for (int id = 0; id < middle; id++) {

        int men_size = ids_men.size();
        int women_size = ids_women.size();

        int randMen = rand() % men_size;
        int randWomen = rand() % women_size;

        int idMen = ids_men[randMen];
        int idWomen = ids_women[randWomen];
        
        men.push_back(Candidate(idMen, names[idMen - 1]));
        women.push_back(Candidate(idWomen, names[idWomen - 1]));

        auto it = std::find(ids_men.begin(), ids_men.end(), idMen);
        if (it != ids_men.end())
            ids_men.erase(it);

        it = std::find(ids_women.begin(), ids_women.end(), idWomen);
        if (it != ids_women.end())
            ids_women.erase(it);
    }

    // merge the two vectors
    men.insert(men.end(), women.begin(), women.end());
    
    // shuffle the merged vector
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(men.begin(), men.end(), g);
    return men;
}
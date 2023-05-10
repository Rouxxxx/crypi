#ifndef UTILS_HH
#define UTILS_HH

#include "basics.hh"
#include "file.hh"

/**
Website's candidate
*/
class Candidate {
public:
    /**
    @param[in] image The image ID in the folder data/images
    @param[in] name The candidate name
    */
    Candidate(int image, std::string name)
      : image(image), name(name) {}
    int image;
    std::string name;
};

std::vector<Candidate> get_candidates(std::string path, int nb_candidates);

#endif
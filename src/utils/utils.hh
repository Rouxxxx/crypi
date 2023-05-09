#ifndef UTILS_HH
#define UTILS_HH

#include "basics.hh"
#include "file.hh"

class Candidate
{
  public:
    Candidate(int image, std::string name)
      : image(image), name(name) {}
    int image;
    std::string name;
};

std::vector<Candidate> get_candidates(std::string path, int nb_candidates);

#endif
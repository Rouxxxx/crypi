#ifndef TOOLS_HH
#define TOOLS_HH

#include <fstream>
#include <iostream>
#include <vector>
#include "Wt/WString.h"

bool check_credentials(const Wt::WString username, const Wt::WString password);
std::vector<std::string> get_candidates(std::string path);
void vote(std::string name);

#endif /* ! TOOLS_HH */

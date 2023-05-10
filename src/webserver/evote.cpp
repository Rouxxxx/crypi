#include "evote.hh"
#include "tools.hh"

#include "home_page.hh"
#include "vote_page.hh"

bool EvoteApplication::skip_social_verif() {
    return container->infos_struct.skip_social_verif;
}




/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#              Home page
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/

EvoteApplication::EvoteApplication(const Wt::WEnvironment& env,
                                   Container* container, std::vector<Candidate> candidates)
    : Wt::WApplication(env)
    , candidates(candidates)
    , container(container)
{
    // Imports the CSS
    this->useStyleSheet(CSS_PATH);
    this->useStyleSheet("data/fontawesome.css");

    home_page();
}
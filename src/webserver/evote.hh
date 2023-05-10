#ifndef EVOTE_HH
#define EVOTE_HH

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WGlobal.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WVBoxLayout.h>
#include <vector>

#include "../BFV/bfv.hh"
#include "tools.hh"

/**
The application's website.
@see Wt's Application class
*/
class EvoteApplication : public Wt::WApplication
{
public:
    /**
    Constructs the website object, to keep track of the important files. Loads the home page for the user.
    @param[in] container The container that will execute all homomorphic operations
    @param[in] candidates The vote's candidates
    */
    EvoteApplication(const Wt::WEnvironment& env, Container* container, std::vector<Candidate> candidates);

    /**
    Loads the voting page.
    @param[in] socialNumber The social number entered by the user
    @param[in] password The password entered by the user
    @param[in] idPage The vote page to load (default=0)
    */
    void VotePage(Wt::WString socialNumber, Wt::WString password, int idPage = 0);
    
    /**
    Sends the vote to the container, and logs the user's vote (so they can't do it multiple times).
    @param[in] id The candidate ID the user voted for
    @param[in] socialNumber The social number entered by the user
    @param[in] password The password entered by the user
    */
    void call_vote(int id, Wt::WString socialNumber, Wt::WString password);

    /**
    Check if the container info struct skip_social_verif's value.
    @return True if skip_social_verif is true, False otherwise
    */
    bool skip_social_verif();

    /**
    Loads the home page
    */
    void home_page();

    std::vector<Candidate> candidates;
private:
    Container* container;
};

#endif /* ! EVOTE_HH */

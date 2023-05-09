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

class EvoteApplication : public Wt::WApplication
{
public:
    EvoteApplication(const Wt::WEnvironment& env, Container* container, std::vector<Candidate> candidates);
    void add_newlines(size_t n);
    void VotePage(Wt::WString socialNumber, Wt::WString password, int idPage);
    std::vector<Candidate> candidates;
private:
    void call_vote(int id, Wt::WString socialNumber, Wt::WString password);
    Container* container;
};

#endif /* ! EVOTE_HH */

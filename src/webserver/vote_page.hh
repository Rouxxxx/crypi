#ifndef VOTE_PAGE_HH
#define VOTE_PAGE_HH

#include "evote.hh"

class CandidatesPanel : public Wt::WContainerWidget {
public:
  CandidatesPanel(EvoteApplication *app, int idPage, Wt::WString socialNumber, Wt::WString password);

private:
    Wt::WVBoxLayout* layout;
    std::vector<Wt::WPushButton*> button;
    std::vector<Wt::WText*> texts;
    Wt::WText* errorLabel;
    EvoteApplication *app;
};

#endif
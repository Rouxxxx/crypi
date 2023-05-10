#ifndef VOTE_PAGE_HH
#define VOTE_PAGE_HH

#include "evote.hh"

/**
Home page's candidates panel
*/
class CandidatesPanel : public Wt::WContainerWidget {
public:
    /**
    Constructs the candidates panel.
    @param[in] app The main app (to call its members when a button is clicked)
    @param[in] idPage The current page ID (each page can have up to 5 candidates)
    @param[in] socialNumber The social number entered by the user
    @param[in] password The password entered by the user
    */
    CandidatesPanel(EvoteApplication *app, int idPage, Wt::WString socialNumber, Wt::WString password);

private:
    Wt::WVBoxLayout* layout;
    std::vector<Wt::WPushButton*> button;
    std::vector<Wt::WText*> texts;
    Wt::WText* errorLabel;
    EvoteApplication *app;
};

#endif
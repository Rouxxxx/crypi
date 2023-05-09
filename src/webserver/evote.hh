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
    void VotePage(Wt::WString socialNumber, Wt::WString password);
    std::vector<Candidate> candidates;
private:
    void call_vote(int id, Wt::WString socialNumber, Wt::WString password);
    Container* container;
};

class LoginPanel : public Wt::WContainerWidget {
public:
  LoginPanel(EvoteApplication *app);

private:
    Wt::WVBoxLayout* layout;
    Wt::WLineEdit* edit;
    Wt::WText* loginLabel;
    Wt::WText* usernameLabel;
    Wt::WText* passwordLabel;
    Wt::WLineEdit* loginInput;
    Wt::WLineEdit* passwordInput;
    Wt::WPushButton* button;
    Wt::WText* errorLabel;
    void submitLoginForm();
    EvoteApplication *app;
};


class CreatePanel : public Wt::WContainerWidget {
public:
  CreatePanel(EvoteApplication *app);

private:
    Wt::WVBoxLayout* layout;
    Wt::WLineEdit* edit;
    Wt::WText* loginLabel;
    Wt::WText* usernameLabel;
    Wt::WText* passwordLabel;
    Wt::WLineEdit* loginInput;
    Wt::WLineEdit* passwordInput;
    Wt::WPushButton* button;
    Wt::WText* errorLabel;

    void create();
    EvoteApplication *app;
};

class ButtonPanel : public Wt::WContainerWidget {
public:
  ButtonPanel(EvoteApplication *app, Container *container);

private:
    Wt::WVBoxLayout* layout;
    Wt::WText* nb_votes;
    Wt::WText* votes_result;
    Wt::WPushButton* button_nb_votes;
    Wt::WPushButton* button_votes;

    void show_votes_result();
    void show_nb_votes();

    EvoteApplication* app;
    Container* container;
};

#endif /* ! EVOTE_HH */

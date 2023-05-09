#ifndef HOME_PAGE_HH
#define HOME_PAGE_HH

#include "evote.hh"

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

#endif
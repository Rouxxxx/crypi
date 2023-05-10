#ifndef HOME_PAGE_HH
#define HOME_PAGE_HH

#include "evote.hh"

/**
Home page's login panel (in the top right corner)
*/
class LoginPanel : public Wt::WContainerWidget {
public:
    /**
    Constructs the login panel.
    @param[in] app The main app (to call its members when a button is clicked)
    */
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

    EvoteApplication *app;

    /**
    Tries to login to the platform.
    */
    void submitLoginForm();
};


/**
Home page's account creation panel (in the top left corner)
*/
class CreatePanel : public Wt::WContainerWidget {
public:
    /**
    Constructs the account creation panel.
    @param[in] app The main app (to call its members when a button is clicked)
    */
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

    /**
    Create the user's account.
    */
    void create();
    EvoteApplication *app;
};

/**
Home page's button panel (in the middle of the screen)
*/
class ButtonPanel : public Wt::WContainerWidget {
public:

    /**
    Constructs the account creation panel.
    @param[in] app The main app (to call its members when a button is clicked)
    @param[in] container The program's BFV container (to computer the number of votes / the winner)
    */
    ButtonPanel(EvoteApplication *app, Container *container);

private:
    Wt::WVBoxLayout* layout;
    Wt::WText* nb_votes;
    Wt::WText* votes_result;
    Wt::WPushButton* button_nb_votes;
    Wt::WPushButton* button_votes;
    Wt::WImage* image = nullptr;

    EvoteApplication* app;
    Container* container;

    /**
    Display the current winner.
    */
    void show_votes_result();

    /**
    Display the current number of votes.
    */
    void show_nb_votes();
};

#endif
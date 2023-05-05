#include "login.hh"

LoginApplication::LoginApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
    , usernameEdit_(nullptr)
    , passwordEdit_(nullptr)
{
    setTitle("To proceed with the vote, please authentificate yourself.");

    // Login text area
    root()->addWidget(std::make_unique<Wt::WText>("Username"));
    usernameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());

    // Password text area
    root()->addWidget(std::make_unique<Wt::WText>("Password"));
    passwordEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());

    root()->addWidget(std::make_unique<Wt::WBreak>());
}

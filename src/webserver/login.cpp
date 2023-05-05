#include "login.hh"

LoginApplication::LoginApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
    , usernameEdit_(nullptr)
    , passwordEdit_(nullptr)
{
    setTitle("Secure voting");

    // Descriptive header
    root()->addWidget(std::make_unique<Wt::WText>("Enter your credentials to proceed."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    root()->addWidget(std::make_unique<Wt::WBreak>());

    // Login text area
    root()->addWidget(std::make_unique<Wt::WText>("Username "));
    usernameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());

    // Newline
    root()->addWidget(std::make_unique<Wt::WBreak>());
    root()->addWidget(std::make_unique<Wt::WBreak>());

    // Password text area
    root()->addWidget(std::make_unique<Wt::WText>("Password "));
    passwordEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
}

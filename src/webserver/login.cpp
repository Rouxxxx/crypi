#include "login.hh"

bool check_credentials(const Wt::WString username, const Wt::WString password)
{
    // Check file from data/credentials.csv
    return username == "root" && password == "root";
}

void LoginApplication::add_newlines(size_t n)
{
    for (size_t i = 0; i < n; i++)
        // Newline
        root()->addWidget(std::make_unique<Wt::WBreak>());
}

LoginApplication::LoginApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
    , usernameEdit_(nullptr)
    , passwordEdit_(nullptr)
{
    setTitle("Login page");

    // Descriptive header
    root()->addWidget(
        std::make_unique<Wt::WText>("Enter your credentials to proceed."));
    add_newlines(2);

    // Login text area
    root()->addWidget(std::make_unique<Wt::WText>("Username "));
    usernameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());

    add_newlines(2);

    // Password text area
    root()->addWidget(std::make_unique<Wt::WText>("Password "));
    passwordEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());

    root()->addWidget(std::make_unique<Wt::WBreak>());

    add_newlines(1);

    // Login Button
    auto login = [this] {
        if (check_credentials(usernameEdit_->text(), passwordEdit_->text()))
            connectionError_->setText("Connected !");
        else
            connectionError_->setText("Invalid credentials !");
    };
    Wt::WPushButton* button =
        root()->addWidget(std::make_unique<Wt::WPushButton>("Login"));
    add_newlines(2);
    connectionError_ = root()->addWidget(std::make_unique<Wt::WText>());
    button->clicked().connect(login);
}

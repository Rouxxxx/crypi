#include "evote.hh"

void EvoteApplication::add_newlines(size_t n)
{
    for (size_t i = 0; i < n; i++)
        // Newline
        root()->addWidget(std::make_unique<Wt::WBreak>());
}

void EvoteApplication::VotePage()
{
    root()->clear();
    setTitle("Vote");
    std::vector<std::string> v = get_candidates("data/candidates.txt");

    auto call_vote = [this](const std::string& candidate) { vote(candidate); };

    // Buttons
    for (size_t i = 0; i < v.size(); i++)
    {
        std::string candidate = v[i];
        Wt::WPushButton* button =
            root()->addWidget(std::make_unique<Wt::WPushButton>(candidate));
        button->clicked().connect(
            [call_vote, candidate]() { call_vote(candidate); });
    }
}

EvoteApplication::EvoteApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
    , usernameEdit_(nullptr)
    , passwordEdit_(nullptr)
{
    setTitle("Login");

    // Descriptive header
    root()->addWidget(
        std::make_unique<Wt::WText>("Enter your credentials to proceed."));
    add_newlines(2);

    // Username text area
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
            VotePage();
        else
            connectionError_->setText("Invalid credentials !");
    };
    Wt::WPushButton* button =
        root()->addWidget(std::make_unique<Wt::WPushButton>("Login"));
    add_newlines(2);
    connectionError_ = root()->addWidget(std::make_unique<Wt::WText>());
    button->clicked().connect(login);
}

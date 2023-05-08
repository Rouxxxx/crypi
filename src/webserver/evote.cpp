#include "evote.hh"

void EvoteApplication::add_newlines(size_t n)
{
    for (size_t i = 0; i < n; i++)
        // Newline
        root()->addWidget(std::make_unique<Wt::WBreak>());
}

// Vote page
void EvoteApplication::VotePage()
{
    root()->clear();
    setTitle("Vote");

    auto headline = root()->addWidget(std::make_unique<Wt::WText>());
    bool voted = has_voted();
    if (voted)
        headline->setText("Your vote has been saved !");
    else
    {
        headline->setText("Vote for your favorite candidate !");

        add_newlines(2);

        std::vector<std::string> v = get_candidates(CANDIDATE_PATH);
        auto call_vote = [this](const std::string& candidate,
                                std::vector<std::string> v) {
            vote(candidate, v);
            VotePage();
        };

        // Buttons
        for (size_t i = 0; i < v.size(); i++)
        {
            std::string candidate = v[i];
            Wt::WPushButton* button =
                root()->addWidget(std::make_unique<Wt::WPushButton>(candidate));
            button->clicked().connect(
                [call_vote, candidate, v]() { call_vote(candidate, v); });
            add_newlines(2);
        }
    }
}

// Login page
EvoteApplication::EvoteApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
    , socialSecurityNumberEdit_(nullptr)
    , passwordEdit_(nullptr)
{
    setTitle("Login");

    // Descriptive header
    root()->addWidget(
        std::make_unique<Wt::WText>("Enter your credentials to proceed."));
    add_newlines(2);

    // Username text area
    root()->addWidget(std::make_unique<Wt::WText>("Social security number "));
    socialSecurityNumberEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());

    add_newlines(2);

    // Password text area
    root()->addWidget(std::make_unique<Wt::WText>("Password "));
    passwordEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());

    root()->addWidget(std::make_unique<Wt::WBreak>());

    add_newlines(1);

    // Login Button
    auto login = [this] {
        if (check_credentials(socialSecurityNumberEdit_->text(), passwordEdit_->text()))
            VotePage();
        else
            connectionError_->setText("Invalid credentials !");
    };
    Wt::WPushButton* button_login =
        root()->addWidget(std::make_unique<Wt::WPushButton>("Login"));
    add_newlines(2);
    connectionError_ = root()->addWidget(std::make_unique<Wt::WText>());
    button_login->clicked().connect(login);
    add_newlines(2);

    // Create an account
    root()->addWidget(std::make_unique<Wt::WText>(
        "To create an account, enter your social security number and a password. Then click on 'Create'."));

    auto create = [this] {
        if (check_social_number(socialSecurityNumberEdit_->text()))
        {
            if (!add_user(socialSecurityNumberEdit_->text(), passwordEdit_->text()))
                connectionError_->setText("User already exist !");
            else
                connectionError_->setText("User Created !");
        }
        else
            connectionError_->setText("Invalid social security number or user "
                                      "is not 18 years old or older !");
    };
    add_newlines(2);
    Wt::WPushButton* button_create =
        root()->addWidget(std::make_unique<Wt::WPushButton>("Create"));
    button_create->clicked().connect(create);
}

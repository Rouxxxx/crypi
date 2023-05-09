#include "evote.hh"
#include "tools.hh"

#include "home_page.hh"

void EvoteApplication::add_newlines(size_t n)
{
    for (size_t i = 0; i < n; i++)
        // Newline
        root()->addWidget(std::make_unique<Wt::WBreak>());
}

void EvoteApplication::call_vote(int vote_id, Wt::WString socialNumber, Wt::WString password)
{
    vote(vote_id, candidates.size(), container, calculate_hash(socialNumber.toUTF8(), password.toUTF8()));
    VotePage(socialNumber, password, 0);
}

// Vote page
void EvoteApplication::VotePage(Wt::WString socialNumber, Wt::WString password, int idPage)
{
    root()->clear();
    setTitle("Vote");

    auto headline = root()->addWidget(std::make_unique<Wt::WText>());
    bool voted =
        has_voted(socialNumber, password);
    if (voted)
        headline->setText("Your vote has been saved !");
    else
    {
        headline->setText("Vote for your favorite candidate !");

        add_newlines(2);

        // Buttons
        int candidates_size = candidates.size();
        for (int i = 0 + (idPage * 5); i < candidates_size && i < (idPage + 1) * 5; i++)
        {
            std::string candidate = candidates[i].name;
            Wt::WPushButton* button = root()->addWidget(std::make_unique<Wt::WPushButton>(candidate));
            button->clicked().connect([this, i, socialNumber, password]() { call_vote(i, socialNumber, password); });
            add_newlines(2);
        }
    }
}

/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#              Home page
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/
EvoteApplication::EvoteApplication(const Wt::WEnvironment& env,
                                   Container* container, std::vector<Candidate> candidates)
    : Wt::WApplication(env)
    , candidates(candidates)
    , container(container)
{

    this->useStyleSheet(CSS_PATH);
    setTitle("Login");

    auto loginPanel = std::make_unique<LoginPanel>(this);
    root()->addWidget(std::move(loginPanel));

    auto createPanel = std::make_unique<CreatePanel>(this);
    root()->addWidget(std::move(createPanel));

    auto buttonPanel = std::make_unique<ButtonPanel>(this, container);
    root()->addWidget(std::move(buttonPanel));

    // Create an account
    root()->addWidget(std::make_unique<Wt::WText>(
        "To create an account, use the 'Create' panel and use your social security number with a password."));
    add_newlines(1);
    root()->addWidget(std::make_unique<Wt::WText>(
        "If you already have an account, use the 'Login' panel."));
}
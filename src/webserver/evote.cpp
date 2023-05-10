#include "evote.hh"
#include "tools.hh"

#include "home_page.hh"
#include "vote_page.hh"

bool EvoteApplication::skip_social_verif() {
    return container->infos_struct.skip_social_verif;
}

void EvoteApplication::call_vote(int vote_id, Wt::WString socialNumber, Wt::WString password)
{
    vote(vote_id, candidates.size(), container, calculate_hash(socialNumber.toUTF8(), password.toUTF8()));
    VotePage(socialNumber, password, vote_id / 5);
}

void EvoteApplication::VotePage(Wt::WString socialNumber, Wt::WString password, int idPage)
{
    root()->clear();
    setTitle("Vote");
    auto headline = root()->addWidget(std::make_unique<Wt::WText>());


    // If the user has already voted, don't allow them to do it again
    bool voted =
        has_voted(socialNumber, password);

    std::cout << "user has voted ? " << voted << "\n";
    if (voted) {
        headline->setText("Your vote has been saved !");
        return;
    }

    // Load panels
    headline->setText("Vote for your favorite candidate !");
    auto candidatesPanel = std::make_unique<CandidatesPanel>(this, idPage, socialNumber, password);
    root()->addWidget(std::move(candidatesPanel));
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
    // Imports the CSS
    this->useStyleSheet(CSS_PATH);
    setTitle("Login");

    // Loads all the necessary panels
    auto loginPanel = std::make_unique<LoginPanel>(this);
    root()->addWidget(std::move(loginPanel));

    auto createPanel = std::make_unique<CreatePanel>(this);
    root()->addWidget(std::move(createPanel));

    auto buttonPanel = std::make_unique<ButtonPanel>(this, container);
    root()->addWidget(std::move(buttonPanel));



    // Add infos texts
    root()->addWidget(std::make_unique<Wt::WText>(
        "To create an account, use the 'Create' panel and use your social security number with a password."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    root()->addWidget(std::make_unique<Wt::WText>(
        "If you already have an account, use the 'Login' panel."));
}
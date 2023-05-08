#include "evote.hh"
#include <string>

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
    bool voted = has_voted(socialSecurityNumberEdit_->text(), passwordEdit_->text());
    if (voted)
        headline->setText("Your vote has been saved !");
    else
    {
        headline->setText("Vote for your favorite candidate !");

        add_newlines(2);

        std::vector<std::string> v = get_candidates(CANDIDATE_PATH);
        auto call_vote = [this](const std::string& candidate,
                                std::vector<std::string> v) {
            vote(candidate, v, container);
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
EvoteApplication::EvoteApplication(const Wt::WEnvironment& env, Container* container)
    : Wt::WApplication(env)
    , socialSecurityNumberEdit_(nullptr)
    , passwordEdit_(nullptr)
    , container(container)
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





    /*
    # _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    #
    #       Number of votes rendering
    #
    # _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    */

    add_newlines(2);

    // Show vote count
    auto show_nb_votes = [this, container] {

        std::string vote_str = "\tCurrent nb of votes: ";
        if (!container->test_if_vote_count_exists())
            vote_str += "0.";
        else {
            // Load and decrypt the number of votes
            Ciphertext nb_votes = container->load_vote_count();
            Plaintext nb_votes_decrypted = container->decrypt(nb_votes);

            vote_str += nb_votes_decrypted.to_string() + ".";
        }
        nb_votes_->setText(vote_str);
    };

    Wt::WPushButton* button_nb_votes =
        root()->addWidget(std::make_unique<Wt::WPushButton>("Show current number of votes"));

    nb_votes_ = root()->addWidget(std::make_unique<Wt::WText>());
    button_nb_votes->clicked().connect(show_nb_votes);





    /*
    # _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    #
    #           Votes rendering
    #
    # _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
    */
    add_newlines(2);
    auto show_winner = [this, container] {
        if (!container->test_if_vote_count_exists())
        {
            winner_->setText("\tNo votes for now : no winner.");
        }
        else {
            // Load and decrypt the number of votes
            Ciphertext votes_cipher = container->load_votes();
            Plaintext votes_decrypted = container->decrypt(votes_cipher);
            std::vector<uint64_t> result = container->decode_vector(votes_decrypted);

            int id_winner = find_max(result);

            std::vector<std::string> candidates = get_candidates(CANDIDATE_PATH);

            winner_->setText("\tCurrent winner: " + candidates[id_winner] + " with " + std::to_string(result[id_winner]) + " votes.");
        }
    };

    Wt::WPushButton* button_votes =
        root()->addWidget(std::make_unique<Wt::WPushButton>("Show winner"));

    winner_ = root()->addWidget(std::make_unique<Wt::WText>());
    button_votes->clicked().connect(show_winner);
}

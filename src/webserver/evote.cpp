#include "evote.hh"
#include <Wt/WString.h>
#include <Wt/WText.h>
#include <string>

void EvoteApplication::add_newlines(size_t n)
{
    for (size_t i = 0; i < n; i++)
        // Newline
        root()->addWidget(std::make_unique<Wt::WBreak>());
}

// Vote page
void EvoteApplication::VotePage(Wt::WString socialNumber, Wt::WString password)
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

        std::vector<std::string> v = get_candidates(CANDIDATE_PATH);
        auto call_vote = [this, socialNumber, password](const std::string& candidate,
                                std::vector<std::string> v) {
            vote(candidate, v, container,
                 calculate_hash(socialNumber.toUTF8(),
                                password.toUTF8()));
            VotePage(socialNumber, password);
        };

        // Buttons
        for (size_t i = 0; i < v.size(); i++)
        {
            std::string candidate = v[i];
            Wt::WPushButton* button =
                root()->addWidget(std::make_unique<Wt::WPushButton>(candidate));
            button->clicked().connect(
                [call_vote, candidate, v, socialNumber, password]() { call_vote(candidate, v); });
            add_newlines(2);
        }
    }
}

// Login page
EvoteApplication::EvoteApplication(const Wt::WEnvironment& env,
                                   Container* container)
    : Wt::WApplication(env)
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

/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#               Front page
#               Login panel
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/
LoginPanel::LoginPanel(EvoteApplication *app)
    : app(app)
{
    // Set the layout of the container widget to vertical
    layout = setLayout(std::make_unique<Wt::WVBoxLayout>());

    loginLabel = layout->addWidget(std::make_unique<Wt::WText>("Login"));
    loginLabel->setStyleClass("label-login");

    usernameLabel = layout->addWidget(std::make_unique<Wt::WText>("Social security number :"));
    usernameLabel->setStyleClass("login-label-label");
    loginInput = layout->addWidget(std::make_unique<Wt::WLineEdit>());
    loginInput->setStyleClass("login-label-input");


    passwordLabel = layout->addWidget(std::make_unique<Wt::WText>("Password:"));
    passwordLabel->setStyleClass("login-label-label");
    passwordInput = layout->addWidget(std::make_unique<Wt::WLineEdit>());
    passwordInput->setEchoMode(Wt::EchoMode::Password);
    passwordInput->setStyleClass("login-label-input");

    errorLabel = layout->addWidget(std::make_unique<Wt::WText>(""));
    errorLabel->setStyleClass("label-error");

    button = layout->addWidget(std::make_unique<Wt::WPushButton>("Login"));
    button->clicked().connect(this, &LoginPanel::submitLoginForm);

    setStyleClass("panel login-panel");

    button->setStyleClass("button-login");
}

void LoginPanel::submitLoginForm()
{
    Wt::WString log = loginInput->text();
    Wt::WString passw = loginInput->text();
    if (check_credentials(log, passw))
        app->VotePage(log, passw);
    else
        errorLabel->setText("Invalid credentials !");
}




/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#               Front page
#          Account create panel
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/
CreatePanel::CreatePanel(EvoteApplication *app)
    : app(app)
{
    // Set the layout of the container widget to vertical
    layout = setLayout(std::make_unique<Wt::WVBoxLayout>());

    loginLabel = layout->addWidget(std::make_unique<Wt::WText>("Create"));
    loginLabel->setStyleClass("label-login");

    usernameLabel = layout->addWidget(std::make_unique<Wt::WText>("Social security number :"));
    usernameLabel->setStyleClass("login-label-label");
    loginInput = layout->addWidget(std::make_unique<Wt::WLineEdit>());
    loginInput->setStyleClass("login-label-input");


    passwordLabel = layout->addWidget(std::make_unique<Wt::WText>("Password:"));
    passwordLabel->setStyleClass("login-label-label");
    passwordInput = layout->addWidget(std::make_unique<Wt::WLineEdit>());
    passwordInput->setEchoMode(Wt::EchoMode::Password);
    passwordInput->setStyleClass("login-label-input");

    errorLabel = layout->addWidget(std::make_unique<Wt::WText>(""));
    errorLabel->setStyleClass("label-error");

    button = layout->addWidget(std::make_unique<Wt::WPushButton>("Create Account"));
    button->clicked().connect(this, &CreatePanel::create);

    setStyleClass("panel create-panel");

    button->setStyleClass("button-create");
}

void CreatePanel::create()
{
    Wt::WString log = loginInput->text();
    Wt::WString passw = loginInput->text();
    if (check_social_number(log))
    {
        if (!add_user(log, passw))
            errorLabel->setText("User already exist !");
        else
            errorLabel->setText("User Created !");
    }
    else
        errorLabel->setText("Invalid social security number or user is not 18yo or older !");
    if (check_credentials(log, passw))
        app->VotePage(log, passw);
}


/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#               Front page
#         Votes rendering buttons
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/


ButtonPanel::ButtonPanel(EvoteApplication* app, Container* container)
    : app(app)
    , container(container)
{
    setStyleClass("button-panel");

    layout = setLayout(std::make_unique<Wt::WVBoxLayout>());
    Wt::WPushButton* button_votes = layout->addWidget(std::make_unique<Wt::WPushButton>("Show winner"));
    button_votes->clicked().connect(this, &ButtonPanel::show_votes_result);
    button_votes->setStyleClass("glow-button button-votes");

    votes_result = layout->addWidget(std::make_unique<Wt::WText>());
    votes_result->setStyleClass("label-votes");

    button_nb_votes = layout->addWidget(std::make_unique<Wt::WPushButton>("Show votes amount"));
    button_nb_votes->clicked().connect(this, &ButtonPanel::show_nb_votes);
    button_nb_votes->setStyleClass("glow-button button-nb-votes");

    nb_votes = layout->addWidget(std::make_unique<Wt::WText>());
    nb_votes->setStyleClass("label-nb-votes");
}

void ButtonPanel::show_votes_result()
{
    if (!container->test_if_vote_count_exists())
        votes_result->setText("\tNo votes for now : no winner.");
    else
    {
        // Load and decrypt the number of votes
        Ciphertext votes_cipher = container->load_votes();
        Plaintext votes_decrypted = container->decrypt(votes_cipher);
        std::vector<uint64_t> result = container->decode_vector(votes_decrypted);

        int id_winner = find_max(result);

        std::vector<std::string> candidates = get_candidates(CANDIDATE_PATH);

        votes_result->setText("\tCurrent winner: " + candidates[id_winner]
                    + " with " + std::to_string(result[id_winner])
                    + " votes.");
        }
}

void ButtonPanel::show_nb_votes()
{
    std::string vote_str = "\tCurrent nb of votes: ";
    if (!container->test_if_vote_count_exists())
        vote_str += "0.";
    else
    {
        // Load and decrypt the number of votes
        Ciphertext nb_votes = container->load_vote_count();
        Plaintext nb_votes_decrypted = container->decrypt(nb_votes);

        vote_str += nb_votes_decrypted.to_string() + ".";
    }
    nb_votes->setText(vote_str);
}
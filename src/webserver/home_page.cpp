#include "home_page.hh"

/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#               Home page
#              Login panel
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/
LoginPanel::LoginPanel(EvoteApplication *app)
    : app(app)
{
    layout = setLayout(std::make_unique<Wt::WVBoxLayout>());

    // Create the top label
    loginLabel = layout->addWidget(std::make_unique<Wt::WText>("Login"));
    loginLabel->setStyleClass("label-login");

    // Create the login label + textbox
    usernameLabel = layout->addWidget(std::make_unique<Wt::WText>("Social security number :"));
    loginInput = layout->addWidget(std::make_unique<Wt::WLineEdit>());
    loginInput->setStyleClass("login-label-input");
    usernameLabel->setStyleClass("login-label-label");


    // Create the password label + textbox
    passwordLabel = layout->addWidget(std::make_unique<Wt::WText>("Password:"));
    passwordInput = layout->addWidget(std::make_unique<Wt::WLineEdit>());
    passwordInput->setEchoMode(Wt::EchoMode::Password);
    passwordLabel->setStyleClass("login-label-label");
    passwordInput->setStyleClass("login-label-input");


    // Create the error label
    errorLabel = layout->addWidget(std::make_unique<Wt::WText>(""));
    errorLabel->setStyleClass("label-error");


    // Create the error label
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
#                Home page
#          Account create panel
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/
CreatePanel::CreatePanel(EvoteApplication *app)
    : app(app)
{
    layout = setLayout(std::make_unique<Wt::WVBoxLayout>());

    // Create the top label
    loginLabel = layout->addWidget(std::make_unique<Wt::WText>("Create"));
    loginLabel->setStyleClass("label-login");


    // Create the login label + textbox
    usernameLabel = layout->addWidget(std::make_unique<Wt::WText>("Social security number :"));
    loginInput = layout->addWidget(std::make_unique<Wt::WLineEdit>());
    loginInput->setStyleClass("login-label-input");
    usernameLabel->setStyleClass("login-label-label");


    // Create the password label + textbox
    passwordLabel = layout->addWidget(std::make_unique<Wt::WText>("Password:"));
    passwordInput = layout->addWidget(std::make_unique<Wt::WLineEdit>());
    passwordInput->setEchoMode(Wt::EchoMode::Password);
    passwordInput->setStyleClass("login-label-input");
    passwordLabel->setStyleClass("login-label-label");


    // Create the error label
    errorLabel = layout->addWidget(std::make_unique<Wt::WText>(""));
    errorLabel->setStyleClass("label-error");


    // Create the confirmation button
    button = layout->addWidget(std::make_unique<Wt::WPushButton>("Create Account"));
    button->clicked().connect(this, &CreatePanel::create);


    setStyleClass("panel create-panel");
    button->setStyleClass("button-create");
}

void CreatePanel::create()
{
    // Get the social security number + password entered by the user
    Wt::WString log = loginInput->text();
    Wt::WString passw = loginInput->text();


    // If the username / password is wrong or already exist, output an error
    bool check = check_social_number(log);
    if (!check) {
        errorLabel->setText("Invalid social security number or user is not 18yo or older !");
        return;
    }
    if (check && !add_user(log, passw)) {
        errorLabel->setText("User already exist !");
        return;
    }


    // If the credentials are good, load the voting page
    if (check_credentials(log, passw))
        app->VotePage(log, passw);
}





/*
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
#
#               Home page
#         Votes rendering buttons
#
# _-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
*/
ButtonPanel::ButtonPanel(EvoteApplication* app, Container* container)
    : app(app)
    , container(container)
{
    setStyleClass("centered-panel");
    layout = setLayout(std::make_unique<Wt::WVBoxLayout>());


    // Create the button + label which will render the vote's winner
    Wt::WPushButton* button_votes = layout->addWidget(std::make_unique<Wt::WPushButton>("Show winner"));
    button_votes->clicked().connect(this, &ButtonPanel::show_votes_result);
    button_votes->setStyleClass("glow-button button-votes");

    votes_result = layout->addWidget(std::make_unique<Wt::WText>());
    votes_result->setStyleClass("label-votes");



    // Create the label + button which will render the current number of votes
    button_nb_votes = layout->addWidget(std::make_unique<Wt::WPushButton>("Show votes amount"));
    button_nb_votes->clicked().connect(this, &ButtonPanel::show_nb_votes);
    button_nb_votes->setStyleClass("glow-button button-nb-votes");

    nb_votes = layout->addWidget(std::make_unique<Wt::WText>());
    nb_votes->setStyleClass("label-nb-votes");
}

void ButtonPanel::show_votes_result()
{
    if (!container->test_if_vote_count_exists()) {
        votes_result->setText("No votes for now : <b>no winner</b>.");
        return;
    }

    // Load and decrypt the number of votes
    Ciphertext votes_cipher = container->load_votes();
    Plaintext votes_decrypted = container->decrypt(votes_cipher);
    std::vector<uint64_t> result = container->decode_vector(votes_decrypted);


    // Find the winner and display it
    int id_winner = find_max(result);
    std::string result_str = "Current winner: <b>" + app->candidates[id_winner].name
                + "</b> with <b>" + std::to_string(result[id_winner])
                + "</b> vote";
    if (result[id_winner] > 1)
        result_str += "s";
    result_str += ".";
    votes_result->setText(result_str);
}

void ButtonPanel::show_nb_votes()
{
    std::string vote_str = "\tCurrent nb of votes: <b>";
    if (!container->test_if_vote_count_exists())
        vote_str += "0</b>.";
    else
    {
        // Load and decrypt the number of votes
        Ciphertext nb_votes = container->load_vote_count();
        Plaintext nb_votes_decrypted = container->decrypt(nb_votes);

        vote_str += nb_votes_decrypted.to_string() + "</b>.";
    }
    nb_votes->setText(vote_str);
}
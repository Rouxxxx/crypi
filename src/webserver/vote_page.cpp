#include "vote_page.hh"
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>
#include <Wt/WString.h>
#include <Wt/WText.h>
#include <string>

CandidatesPanel::CandidatesPanel(EvoteApplication *app, int idPage, Wt::WString socialNumber, Wt::WString password)
    : app(app)
{
    layout = setLayout(std::make_unique<Wt::WVBoxLayout>());
    layout->addWidget(std::make_unique<Wt::WBreak>());
    int candidates_size = app->candidates.size();



    // Add the page number display
    std::string result_str = "You're actually on page <b>" + std::to_string(idPage + 1)
                    + "</b> on <b>" + std::to_string(candidates_size / 5)
                    + "</b>.";
    Wt::WText* txt = layout->addWidget(std::make_unique<Wt::WText>(result_str));
    txt->addStyleClass("page-text");



    // Creates containers for labels, candidate images and vote buttons
    Wt::WContainerWidget* textContainer = layout->addWidget(std::make_unique<Wt::WContainerWidget>());
    textContainer->setStyleClass("text-container");

    Wt::WContainerWidget* imageContainer = layout->addWidget(std::make_unique<Wt::WContainerWidget>());
    imageContainer->setStyleClass("image-container");

    Wt::WContainerWidget* buttonContainer = layout->addWidget(std::make_unique<Wt::WContainerWidget>());
    buttonContainer->setStyleClass("button-container");



    // Add the container for previous / next page buttons
    for (size_t i = 0; i < 5; i++)
        layout->addWidget(std::make_unique<Wt::WBreak>());
    Wt::WContainerWidget* swipeContainer = layout->addWidget(std::make_unique<Wt::WContainerWidget>());
    swipeContainer->setStyleClass("swipe-container");

    

    // Init all of the 5 candidates (or less if we're at the last page)
    int page_begin = (idPage * 5);
    int page_end = page_begin + 5;
    for (int id = page_begin; id < candidates_size && id < page_end; id++)
    {
        int imageID = app->candidates[id].image;
        std::string candidate = app->candidates[id].name;


        // Set the candidate's name
        Wt::WText* text = textContainer->addWidget(std::make_unique<Wt::WText>(candidate));
        text->setStyleClass("text-candidate");


        // Set the candidate's image
        std::string imagePath = "data/images/" + std::to_string(imageID) + ".jpg";
        Wt::WImage* image = imageContainer->addWidget(std::make_unique<Wt::WImage>(imagePath));
        image->setStyleClass("image");


        // Set the candidate's voting button
        Wt::WPushButton* button = buttonContainer->addWidget(std::make_unique<Wt::WPushButton>("Vote !"));
        button->clicked().connect([app, id, socialNumber, password]() { app->call_vote(id, socialNumber, password); });
        std::string str = "button-candidate button-" + std::to_string(id - (idPage * 5));
        button->setStyleClass(str);
    }

    // If we aren't on first page, load the previous page button
    if (idPage > 0) {
        Wt::WPushButton* buttonBefore = swipeContainer->addWidget(std::make_unique<Wt::WPushButton>("< Previous"));
        buttonBefore->clicked().connect([app, idPage, socialNumber, password]() { app->VotePage(socialNumber, password, idPage - 1); });
        buttonBefore->setStyleClass("button-before");
    }

    // If we aren't on last page, load the previous page button
    if (page_end + 1 < candidates_size) {
        Wt::WPushButton* buttonAfter = swipeContainer->addWidget(std::make_unique<Wt::WPushButton>("Next >"));
        buttonAfter->clicked().connect([app, idPage, socialNumber, password]() { app->VotePage(socialNumber, password, idPage + 1); });
        buttonAfter->setStyleClass("button-after");
    }

    setStyleClass("centered-panel");
}
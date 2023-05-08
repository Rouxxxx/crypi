#ifndef EVOTE_HH
#define EVOTE_HH

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "tools.hh"

class EvoteApplication : public Wt::WApplication
{
public:
    EvoteApplication(const Wt::WEnvironment& env);
    void add_newlines(size_t n);
    void VotePage();

private:
    Wt::WLineEdit* socialSecurityNumberEdit_;
    Wt::WLineEdit* passwordEdit_;
    Wt::WText* connectionError_;
};

#endif /* ! EVOTE_HH */

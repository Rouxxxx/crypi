#ifndef LOGIN_HH
#define LOGIN_HH

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class LoginApplication : public Wt::WApplication
{
public:
    LoginApplication(const Wt::WEnvironment& env);

private:
    Wt::WLineEdit* usernameEdit_;
    Wt::WLineEdit* passwordEdit_;
};

#endif /* ! LOGIN_HH */

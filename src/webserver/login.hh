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
    void add_newlines(size_t n);

private:
    Wt::WLineEdit* usernameEdit_;
    Wt::WLineEdit* passwordEdit_;
    Wt::WText* connectionError_;
};

bool check_credentials(const Wt::WString username, const Wt::WString password);

#endif /* ! LOGIN_HH */

#ifndef WEBLOGINDIALOG_H
#define WEBLOGINDIALOG_H

#include <Wt/WDialog>

using namespace Wt;

class CoreAccount;

class WebLoginDialog : public WDialog
{
public:
    WebLoginDialog(CoreAccount *account = 0);

private:
    void saveAndConnect();
    WLineEdit *m_userEdit;
    WLineEdit *m_passwordEdit;
    WLineEdit *m_hostEdit;
    CoreAccount *m_coreAccount;
};

#endif // WEBLOGINDIALOG_H

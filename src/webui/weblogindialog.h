#ifndef WEBLOGINDIALOG_H
#define WEBLOGINDIALOG_H

#include <Wt/WDialog>

using namespace Wt;

class CoreAccountModel;

class WebLoginDialog : public WDialog
{
public:
    WebLoginDialog();

private:
    void saveAndConnect();
    WLineEdit *_userEdit;
    WLineEdit *_passwordEdit;
    WLineEdit *_hostEdit;
    CoreAccountModel *_coreAccountModel;
};

#endif // WEBLOGINDIALOG_H

#include "weblogindialog.h"

#include <Wt/WText>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WBreak>

#include "client.h"
#include "coreaccountmodel.h"

WebLoginDialog::WebLoginDialog() :
    WDialog("Login")
{
    setModal(true);
    _coreAccountModel = Client::coreAccountModel();

    new WText("Username:", contents());
    _userEdit = new WLineEdit(contents());
    new WBreak(contents());

    new WText("Password:", contents());
    _passwordEdit = new WLineEdit(contents());
    _passwordEdit->setEchoMode(WLineEdit::Password);
    _passwordEdit->setText(_coreAccountModel->data(_coreAccountModel->index(0)).toString().toStdString());

    new WBreak(contents());
    new WText("Host:", contents());
    _hostEdit = new WLineEdit(contents());
    new WBreak(contents());

    WPushButton *button = new WPushButton("Save and connect", contents());
    button->clicked().connect(this, &WebLoginDialog::saveAndConnect);
}

void WebLoginDialog::saveAndConnect()
{
    accept();
}

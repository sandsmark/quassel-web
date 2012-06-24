#include "weblogindialog.h"

#include <Wt/WText>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WBreak>

#include "client.h"
#include "coreaccountmodel.h"

WebLoginDialog::WebLoginDialog(CoreAccount* account) :
    WDialog("Login"),
    m_coreAccount(account)
{
    setModal(true);

    new WText("Username:", contents());
    m_userEdit = new WLineEdit(contents());
    new WBreak(contents());

    new WText("Password:", contents());
    m_passwordEdit = new WLineEdit(contents());
    m_passwordEdit->setEchoMode(WLineEdit::Password);

    new WBreak(contents());
    new WText("Host:", contents());
    m_hostEdit = new WLineEdit(contents());
    new WBreak(contents());

    WPushButton *button = new WPushButton("Save and connect", contents());
    button->clicked().connect(this, &WebLoginDialog::saveAndConnect);
    
    if (m_coreAccount == 0)
        m_coreAccount = new CoreAccount;
    else {
        m_hostEdit->setValueText(m_coreAccount->hostName().toStdString());
        m_passwordEdit->setText(m_coreAccount->user().toStdString());
        m_userEdit->setValueText(m_coreAccount->user().toStdString());
    }
    
    show();
}

void WebLoginDialog::saveAndConnect()
{
    m_coreAccount->setUser(QString::fromStdString(m_userEdit->valueText().toUTF8()));
    m_coreAccount->setPassword(QString::fromStdString(m_passwordEdit->valueText().toUTF8()));
    m_coreAccount->setHostName(QString::fromStdString(m_hostEdit->valueText().toUTF8()));
    
    Client::coreAccountModel()->createOrUpdateAccount(*m_coreAccount);
    Client::coreAccountModel()->save();
    accept();
}

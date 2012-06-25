/***************************************************************************
 *   Copyright (C) 2005-2010 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "webui.h"

#include <Wt/WVBoxLayout>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WTableView>
#include <Wt/WPushButton>

#include "buffermodel.h"
#include "client.h"
#include "coreaccountmodel.h"

#include "webmessagemodel.h"
#include "webmessageprocessor.h"
#include "weblogindialog.h"

WebUi::WebUi(WApplication *app) :
    AbstractUi(),
    m_app(app)
{
    app->setTitle("Quassel web interface");
    WVBoxLayout *layout = new WVBoxLayout;
    app->root()->setLayout(layout);
    
    /*m_loginButton = new WPushButton("Connect");
    m_loginButton->clicked().connect(this, &WebUi::connect);
    layout->addWidget(m_loginButton);*/

    _chatView = new WTableView(app->root());
    layout->addWidget(_chatView);

    _inputWidget = new WLineEdit(app->root());
    layout->addWidget(_inputWidget);
    

    QObject::connect(Client::coreConnection(), SIGNAL(userAuthenticationRequired(CoreAccount*,bool*,QString)), SLOT(userAuthenticationRequired(CoreAccount*,bool*,QString)));
    QObject::connect(Client::coreConnection(), SIGNAL(connectionMsg(QString)), SLOT(printMsg(QString)));
    QObject::connect(Client::coreConnection(), SIGNAL(progressTextChanged(QString)), SLOT(printMsg(QString)));
    QObject::connect(Client::coreConnection(), SIGNAL(connectionError(QString)), SLOT(printMsg(QString)));
    QObject::connect(Client::coreConnection(), SIGNAL(connectionErrorPopup(QString)), SLOT(printMsg(QString)));
    //QObject::connect(Client::coreConnection(), SIGNAL(userAuthenticationRequired(CoreAccount*,bool*,QString)), SLOT(userAuthenticationRequired(CoreAccount*,bool*,QString)));
    //Client::coreAccountModel()->load();
    //if (!Client::coreConnection()->connectToCore()) {
        bool ok;
        userAuthenticationRequired(0, &ok, "");
    //}
}

WebUi::~WebUi()
{
}

AbstractMessageProcessor* WebUi::createMessageProcessor(QObject*)
{
    return new WebMessageProcessor(this);
}

MessageModel* WebUi::createMessageModel(QObject*)
{
    _messageModel = new WebMessageModel(m_app->root(), this);
    _chatView->setModel(_messageModel);
    return _messageModel;
}

void WebUi::userAuthenticationRequired(CoreAccount* account, bool* okay, QString error)
{
    qDebug() << error;
    WebLoginDialog dialog(account);
    dialog.exec();
    *okay = true;
    if (Client::coreAccountModel()->rowCount() > 0)
        qDebug() << " Connection succeeded?" << Client::coreConnection()->connectToCore(Client::coreAccountModel()->accountIds().first());
    else
        qWarning() << "No core accounts available.";
}

void WebUi::connect()
{
    if (Client::coreConnection()->connectToCore())
        m_loginButton->hide();
}

void WebUi::connected()
{
    qWarning() << "WE ARE CONNECTED";
}

void WebUi::printMsg(QString msg)
{
    qWarning() << " HA HA HA WE HAVE MESSAGE: " << msg;
}

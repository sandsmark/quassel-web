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

WebUi::WebUi(const WEnvironment& env) :
    AbstractUi(),
    WApplication(env)
{
    setTitle("Quassel web interface");
    WVBoxLayout *layout = new WVBoxLayout;
    root()->setLayout(layout);
    
    /*m_loginButton = new WPushButton("Connect");
    m_loginButton->clicked().connect(this, &WebUi::connect);
    layout->addWidget(m_loginButton);*/

    _chatView = new WTableView(root());
    layout->addWidget(_chatView);

    _inputWidget = new WLineEdit(root());
    layout->addWidget(_inputWidget);
    

    QObject::connect(Client::coreConnection(), SIGNAL(userAuthenticationRequired(CoreAccount*,bool*,QString)), SLOT(userAuthenticationRequired(CoreAccount*,bool*,QString)));
    QObject::connect(Client::coreConnection(), SIGNAL(connected()), SLOT(connected()));
    //QObject::connect(Client::coreConnection(), SIGNAL(userAuthenticationRequired(CoreAccount*,bool*,QString)), SLOT(userAuthenticationRequired(CoreAccount*,bool*,QString)));
    if (!Client::coreConnection()->connectToCore()) {
        bool ok;
        userAuthenticationRequired(0, &ok, "");
    }
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
    _messageModel = new WebMessageModel(root(), this);
    _chatView->setModel(_messageModel);
    return _messageModel;
}

void WebUi::userAuthenticationRequired(CoreAccount* account, bool* okay, QString error)
{
    qDebug() << error;
    WebLoginDialog dialog(account);
    dialog.exec();
    *okay = true;
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
